import utils


def generate_for_each_dispatch_macro(macro_prefix, nested_loops_idx):
    """
    Generate the FOR_EACH_X macro, where X is the nested for loop level,
    1-indexed.
    """
    macro_lines = [
        '// FOR_EACH applies Fn(idx, fixed_arg, va_arg) for each va_arg in __VA_ARGS__.',
        '// idx is 0 for the first iteration and for each subsequent iteration increases',
        '// by 1.',
        '',
        '// Fn refers to two macros. F is the prefix of two macros, F_1 and F_0. F_1 is',
        '// used for non-final for loop iterations and F_0 is used by the final',
        '// iteration.'
    ]
    nested_loops_id = nested_loops_idx + 1

    for_each_define = '#define {}_FOR_EACH_{}(F, fixed_args, ...) \\'.format(
        macro_prefix.upper(), nested_loops_id)
    macro_lines.append(for_each_define)

    for_each_cat = (' ' * 4) + '{0}_CAT_2'.format(macro_prefix.upper())
    for_each_iter = '({0}_FOR_EACH_{1}_ITER, {0}_ARG_LENGTH(__VA_ARGS__))'.format(
        macro_prefix.upper(), nested_loops_id)
    for_each_iter_args = '(F, 0, fixed_arg, __VA_ARGS__)'
    macro_lines.append(for_each_cat + for_each_iter + for_each_iter_args)

    return macro_lines


def generate_for_each_iter1_macro(macro_prefix, nested_loops_idx):
    """
    Generate the FOR_EACH_X_ITER1 macro, which is the base case and final
    iteration of the for loop.
    """
    macro_lines = ['// ITER1. Invokes F_0.']
    nested_loops_id = nested_loops_idx + 1

    iter1_define = '#define {}_FOR_EACH_{}_ITER1(F, idx, fixed_arg, va_arg, ...) '.format(
        macro_prefix.upper(), nested_loops_id)
    iter1_body = 'F##0(idx, fixed_arg, va_arg)'
    macro_lines.append(iter1_define + iter1_body)

    return macro_lines


def generate_for_each_itern_macro(macro_prefix, nested_loops_idx, iter_idx):
    """
    Generate the FOR_EACH_X_ITERN macro, which is iterative case where N counts
    down toward the final iteration. Each these macros invokes the
    corresponding N-1 macro.
    """
    nested_loops_id = nested_loops_idx + 1
    iter_id = iter_idx
    macro_lines = ['// ITER{}. Invokes F_1'.format(iter_id)]

    # Generate ITERN macro, which calls an ITERN_IMPL macro to accomadate
    # expansion of arguments.
    itern_define = '#define {0}_FOR_EACH_{1}_ITER{2}(F, idx, fixed_arg, va_arg, ...) \\'.format(
        macro_prefix.upper(), nested_loops_id, iter_id)
    itern_define_body = (' ' * 4) + '{0}_FOR_EACH_{1}_ITER{2}_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)'.format(
        macro_prefix.upper(), nested_loops_id, iter_id)
    macro_lines.append(itern_define)
    macro_lines.append(itern_define_body)

    itern_impl_define = '#define {}_FOR_EACH_{}_ITER{}_IMPL(F, idx, fixed_arg, va_arg, ...) \\'.format(
        macro_prefix.upper(), nested_loops_id, iter_id)
    itern_impl_invoke_func = (' ' * 4) + 'F##1(idx, fixed_arg, va_arg) '
    itern_next_iter = '{0}_FOR_EACH_{1}_ITER{2}(F, {0}_CAT_1({0}_INC_, idx), fixed_arg, __VA_ARGS__)'.format(
        macro_prefix.upper(), nested_loops_id, iter_id - 1)
    macro_lines.append(itern_impl_define)
    macro_lines.append(itern_impl_invoke_func + itern_next_iter)

    return macro_lines


def generate_for_each(macro_prefix, header_guard_prefix, supported_size, nested_loops_count, output_dir):
    """
    Generate FOR_EACH macros, one per required nested level. Each for loop
    will support a VA_ARGS_length up to the specified `supported_size`.
    """
    lines = utils.generate_header_begin(
        macro_prefix, header_guard_prefix, 'for_each')
    lines.append('')

    # Generate #includes for CAT, DEFER, INC macros
    lines.append('#include "{}_arg.hpp"'.format(macro_prefix.lower()))
    lines.append('#include "{}_cat.hpp"'.format(macro_prefix.lower()))
    lines.append('#include "{}_inc.hpp"'.format(macro_prefix.lower()))
    lines.append('')

    # Generate multiple for each macros for nested loops
    for x in range(nested_loops_count):
        # Generate macro which invokes the correct iteration
        lines += generate_for_each_dispatch_macro(macro_prefix, x)
        lines.append('')
        # Generate the ITERN macros.
        for i in range(supported_size, 1, -1):
            lines += generate_for_each_itern_macro(macro_prefix, x, i)
        # Generate the ITER1 macro.
        lines += generate_for_each_iter1_macro(macro_prefix, x)

        lines.append('')

    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(
        macro_prefix, 'for_each', output_dir), lines)

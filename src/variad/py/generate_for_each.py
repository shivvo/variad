import utils

FOR_EACH_COMMENT_TEMPLATE = '''
// FOR_EACH applies Fn(idx, fixed_arg, va_arg) for eahc va_arg in __VA_ARGS__.
// `idx` is 0 for the first iteration and for each subsequent iteration step
// up by 1.
//
// Fn refers to two macros, F1 and F0. F1 is used for non-final loop
// iterations, and F0 is used for the final loop iteration. This is useful
// for forming expressions, where F1 generates a portion of an expression with
// some operand, and F0 generates the final term without any operand.
'''

FOR_EACH_TOP_LEVEL_TEMPLATE = \
    '''#define {0}FOR_EACH{1}(F, fixed_arg, ...) \\
    {0}CAT_2({0}FOR_EACH{1}_ITER, {0}ARG_LENGTH(__VA_ARGS__))(F, 0, fixed_arg, __VA_ARGS__)'''

FOR_EACH_ITER1_TEMPLATE = \
    '''// ITER1. Invokes F0.
#define {0}FOR_EACH{1}_ITER1(F, idx, fixed_arg, va_arg, ...) F##0(idx, fixed_arg, va_arg)'''

FOR_EACH_ITERN_TEMPLATE = \
    '''// ITER{2}. Invokes F1.
#define {0}FOR_EACH{1}_ITER{2}(F, idx, fixed_arg, va_arg, ...) \\
    {0}FOR_EACH{1}_ITER{2}_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define {0}FOR_EACH{1}_ITER{2}_IMPL(F, idx, fixed_arg, va_arg, ...) \\
    F##1(idx, fixed_arg, va_arg) {0}FOR_EACH{1}_ITER{3}(F, {0}CAT_1({0}INC_, idx), fixed_arg, __VA_ARGS__)'''


def generate_for_each_dispatch_macro(macro_prefix, nested_loops_idx):
    '''
    Generate the FOR_EACH_X macro, where X is the nested for loop level,
    1-indexed.
    '''
    macro_lines = [FOR_EACH_COMMENT_TEMPLATE]
    nested_loops_id = nested_loops_idx + 1

    macro_lines.append(FOR_EACH_TOP_LEVEL_TEMPLATE.format(
        macro_prefix.upper(), nested_loops_id, ))

    return macro_lines


def generate_for_each_iter1_macro(macro_prefix, nested_loops_idx):
    '''
    Generate the FOR_EACH_X_ITER1 macro, which is the base case and final
    iteration of the for loop.
    '''
    macro_lines = []
    nested_loops_id = nested_loops_idx + 1

    macro_lines.append(FOR_EACH_ITER1_TEMPLATE.format(
        macro_prefix.upper(), nested_loops_id))

    return macro_lines


def generate_for_each_itern_macro(macro_prefix, nested_loops_idx, iter_id):
    '''
    Generate the FOR_EACH_X_ITERN macro, which is iterative case where N counts
    down toward the final iteration. Each these macros invokes the
    corresponding N-1 macro.
    '''
    nested_loops_id = nested_loops_idx + 1
    macro_lines = [FOR_EACH_ITERN_TEMPLATE.format(
        macro_prefix.upper(), nested_loops_id, iter_id, iter_id - 1)]

    return macro_lines


def generate_for_each(macro_prefix, header_guard_prefix, supported_size, nested_loops_count, output_dir):
    '''
    Generate FOR_EACH macros, one per required nested level. Each for loop
    will support a VA_ARGS_length up to the specified `supported_size`.
    '''
    lines = utils.generate_header_begin(
        macro_prefix, header_guard_prefix, 'for_each')
    lines.append('')

    # Generate #includes for CAT, DEFER, INC macros
    lines.append('#include "{}arg.hpp"'.format(macro_prefix.lower()))
    lines.append('#include "{}cat.hpp"'.format(macro_prefix.lower()))
    lines.append('#include "{}inc.hpp"'.format(macro_prefix.lower()))
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

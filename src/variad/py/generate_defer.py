import utils

# Generate cascading expansions of EMPTY().
def generate_empty(macro_prefix, expansions):
    empty_macros = ['{}_EMPTY'.format(macro_prefix.upper())] * expansions
    invoke_parens = ['()'] * expansions
    return ' '.join(empty_macros) + ''.join(invoke_parens)

# Generate DEFER macros deferring expansion of another macro by some amount.
def generate_defer(macro_prefix, header_guard_prefix, supported_size, output_dir):
    lines = utils.generate_header_begin(macro_prefix, header_guard_prefix, 'defer')
    lines.append('')

    # Define the EMPTY() macro.
    empty_macro = "#define {}_EMPTY()".format(macro_prefix.upper())
    lines.append(empty_macro)

    # Generate DEFER_N macros, where N is the number of deferrals.
    defer_macros = ['#define {}_DEFER_{}(F) F {}'.format(macro_prefix.upper(), i, generate_empty(macro_prefix, i)) for i in range(1, supported_size + 1)]
    lines += defer_macros

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(macro_prefix, 'defer', output_dir), lines)


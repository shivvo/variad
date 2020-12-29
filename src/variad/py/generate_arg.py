import utils

ARG_NTH_TEMPLATE = '#define {0}ARG_{1}TH({2}, N, ...) N'
ARG_LENGTH_TEMPLATE = '#define {0}ARG_LENGTH(...) {0}ARG_{1}TH(__VA_ARGS__, {2})'
ARG_2ND_TEMPLATE = \
'''#define {0}ARG_2ND_IMPL(a, b, ...) b
#define {0}ARG_2ND(...) ARG_2ND_IMPL(__VA_ARGS__)'''
ARG_IS_SINGLE_TEMPLATE = \
'''#define {0}ARG_LENGTH_PROBE_1 _, 1
#define {0}ARG_IS_SINGLE(...) \\
    {0}ARG_2ND({0}ARG_CAT_2({0}ARG_LENGTH_PROBE_, {0}ARG_LENGTH(__VA_ARGS__)), 0)'''
ARG_IS_SINGULAR_TEMPLATE = \
'''#define {0}ARG_IDENTITY(...) __VA_ARGS__
#define {0}ARG_IS_SINGULAR(a) {0}ARG_IS_SINGLE({0}ARG_IDENTITY a)'''

def generate_arg(macro_prefix, header_guard_prefix, supported_size, output_dir):
    '''
    Generate the ARG_LENGTH macro.
    '''
    # Seed lines with header guard.
    lines = utils.generate_header_begin(
        macro_prefix, header_guard_prefix, 'arg')
    lines.append('')

    # Generate ARG_NTH, where N = `supported_size` + 1, giving back the Nth
    # argument in the variable arguments.
    args_list = ['_{}'.format(i) for i in range(1, supported_size + 1)]
    args_str = ', '.join(args_list)
    arg_nth = ARG_NTH_TEMPLATE.format(
        macro_prefix.upper(), supported_size + 1, args_str)
    lines.append(arg_nth)
    lines.append('')

    # Generate ARG_LENGTH for getting the length of the variable arguments.
    # Works for lists from 1 to `supported_size`.
    lengths_list = ['{}'.format(i) for i in range(supported_size, 0, -1)]
    lengths_str = ', '.join(lengths_list)
    arg_length = ARG_LENGTH_TEMPLATE.format(
        macro_prefix.upper(), supported_size + 1, lengths_str)
    lines.append(arg_length)
    lines.append('')

    # Generate macro for getting the second of the variable arguments.
    lines.append(ARG_2ND_TEMPLATE.format(macro_prefix))
    lines.append('')

    # Generate CAT for use in ARG macros.
    lines += utils.get_cat_lines(macro_prefix, 'ARG_', 2);
    lines.append('')

    # Generate ARG_IS_SINGLE for checking if the variable arguments is of size
    # 1.
    lines.append(ARG_IS_SINGLE_TEMPLATE.format(macro_prefix.upper()))
    lines.append('')

    # Generate ARG_SINGULAR for checking if de-paranthesized argument is
    # a list of size 1.
    lines.append(ARG_IS_SINGULAR_TEMPLATE.format(macro_prefix.upper()))

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(
        macro_prefix, 'arg', output_dir), lines)

import utils

ARG_NTH_TEMPLATE = '#define {0}ARG_{1}TH({2}, N, ...) N'
ARG_LENGTH_TEMPLATE = '#define {0}ARG_LENGTH(...) {0}ARG_{1}TH(__VA_ARGS__, {2})'


def generate_arg(macro_prefix, header_guard_prefix, supported_size, output_dir):
    '''
    Generate the ARG_LENGTH macro.
    '''
    # Seed lines with header guard.
    lines = utils.generate_header_begin(
        macro_prefix, header_guard_prefix, 'arg')
    lines.append('')

    # Generate macro for ARG_N, where N = `supported_size` + 1,
    args_list = ['_{}'.format(i) for i in range(1, supported_size + 1)]
    args_str = ', '.join(args_list)
    arg_nth = ARG_NTH_TEMPLATE.format(
        macro_prefix.upper(), supported_size + 1, args_str)
    lines.append(arg_nth)

    # Generate macro for getting the length of the variable arguments, up to `supported_size`.
    lengths_list = ['{}'.format(i) for i in range(supported_size, 0, -1)]
    lengths_str = ', '.join(lengths_list)
    arg_length = ARG_LENGTH_TEMPLATE.format(
        macro_prefix.upper(), supported_size + 1, lengths_str)
    lines.append(arg_length)

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(
        macro_prefix, 'arg', output_dir), lines)

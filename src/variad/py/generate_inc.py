import utils

INC_TEMPLATE = '#define {0}INC_{1} {2}'


def generate_inc(macro_prefix, header_guard_prefix, supported_size, output_dir):
    '''
    Generate INC macros which gives a number one higher than the invoked INC.
    '''
    lines = utils.generate_header_begin(
        macro_prefix, header_guard_prefix, 'inc')
    lines.append('')
    lines.append('// INC_N gives back N+1')

    # Generate INC_N macros, which gives back N + 1.
    inc_macros = [INC_TEMPLATE.format(
        macro_prefix.upper(), i, i + 1) for i in range(supported_size)]
    lines += inc_macros

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(
        macro_prefix, 'inc', output_dir), lines)

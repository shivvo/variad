import utils

# Generate INC macros which gives a number one higher than the invoked INC.
def generate_inc(macro_prefix, header_guard_prefix, supported_size, output_dir):
    lines = utils.generate_header_begin(macro_prefix, header_guard_prefix, 'inc')
    lines.append('')

    # Generate INC_N macros, which gives back N + 1.
    inc_macros = ['#define {}_INC_{} {}'.format(macro_prefix.upper(), i, i + 1) for i in range(supported_size)]
    lines += inc_macros

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(macro_prefix, 'inc', output_dir), lines)


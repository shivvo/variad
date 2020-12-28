import os

def write_lines(output_file_name, lines):
    with open(output_file_name, 'w') as output_file:
        for line_str in lines:
            # print(line_str)
            output_file.write(line_str)
            output_file.write('\n')
        output_file.write('\n')

# Generate list of lines containing the beginning of the header guard
def generate_header_begin(macro_prefix, header_guard_prefix, macro):
    guard_define = '{}_{}_{}'.format(header_guard_prefix.upper(), macro_prefix.upper(), macro.upper())
    return [
            '#ifndef {}'.format(guard_define),
            '#define {}'.format(guard_define)
            ]

# Generate the end of the header guard. 
def generate_header_end():
    return '#endif'

# Generate the file name for the macros.
def get_output_file_name(macro_prefix, macro, output_dir):
    return os.path.join(output_dir, '{}_{}.hpp'.format(macro_prefix.lower(), macro.lower()))



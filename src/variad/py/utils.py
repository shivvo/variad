import os


def write_lines(output_file_name, lines):
    """
    Write lines to the output file.
    """
    with open(output_file_name, 'w') as output_file:
        for line_str in lines:
            # print(line_str)
            output_file.write(line_str)
            output_file.write('\n')
        output_file.write('\n')


def generate_header_begin(macro_prefix, header_guard_prefix, macro):
    """
    Generate a list of lines that contain the start of a header guard.
    """
    guard_define = '{}_{}_{}'.format(
        header_guard_prefix.upper(), macro_prefix.upper(), macro.upper())
    return [
        '#ifndef {}'.format(guard_define),
        '#define {}'.format(guard_define)
    ]


def generate_header_end():
    """
    Generate the end of the header guard.
    """
    return '#endif'


def get_output_file_name(macro_prefix, macro, output_dir):
    """
    Generate the file name for the macros.
    """
    return os.path.join(output_dir, '{}_{}.hpp'.format(macro_prefix.lower(), macro.lower()))

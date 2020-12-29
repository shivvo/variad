import os

CAT_1_TEMPLATE = '#define {0}{1}CAT_1(a, b) a##b'
CAT_N_TEMPLATE = '#define {0}{1}CAT_{2}(a, b) {0}{1}CAT_{3}(a, b)'

def write_lines(output_file_name, lines):
    '''
    Write lines to the output file.
    '''
    with open(output_file_name, 'w') as output_file:
        for line_str in lines:
            # print(line_str)
            output_file.write(line_str)
            output_file.write('\n')


def get_cat_lines(macro_prefix, cat_prefix, cat_count):
    cat_lines = []
    cat_lines.append(CAT_1_TEMPLATE.format(
        macro_prefix.upper(), cat_prefix.upper()))

    for i in range(2, cat_count+1):
        cat_lines.append(CAT_N_TEMPLATE.format(
            macro_prefix.upper(), cat_prefix.upper(), i, i - 1))

    return cat_lines


def generate_header_begin(macro_prefix, header_guard_prefix, macro):
    '''
    Generate a list of lines that contain the start of a header guard.
    '''
    guard_define = '{}{}{}'.format(
        header_guard_prefix.upper(), macro_prefix.upper(), macro.upper())
    return [
        '#ifndef {}'.format(guard_define),
        '#define {}'.format(guard_define)
    ]


def generate_header_end():
    '''
    Generate the end of the header guard.
    '''
    return '#endif'


def get_output_file_name(macro_prefix, macro, output_dir):
    '''
    Generate the file name for the macros.
    '''
    return os.path.join(output_dir, '{}{}.hpp'.format(macro_prefix.lower(), macro.lower()))

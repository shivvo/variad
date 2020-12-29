import utils


def generate_cat(macro_prefix, header_prefix, supported_size, output_dir):
    '''
    Generate CAT macro which concatenate its two arguments.
    '''
    lines = utils.generate_header_begin(macro_prefix, header_prefix, 'cat')
    lines.append('')

    lines += utils.get_cat_lines(macro_prefix, '', supported_size)

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(
        macro_prefix, 'cat', output_dir), lines)

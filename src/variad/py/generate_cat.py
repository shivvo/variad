import utils

def generate_cat(macro_prefix, header_prefix, supported_size, output_dir):
    lines = utils.generate_header_begin(macro_prefix, header_prefix, 'cat')
    lines.append('')

    cat_define = "#define {}_CAT(a, b) a##b".format(macro_prefix.upper())
    lines.append(cat_define)

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(macro_prefix, 'cat', output_dir), lines)

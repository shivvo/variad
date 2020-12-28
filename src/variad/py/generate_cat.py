import utils


def generate_cat(macro_prefix, header_prefix, supported_size, output_dir):
    """
    Generate CAT macro which concatenate its two arguments.
    """
    lines = utils.generate_header_begin(macro_prefix, header_prefix, 'cat')
    lines.append('')

    cat1_define = "#define {}_CAT_1(a, b) a##b".format(macro_prefix.upper())
    lines.append(cat1_define)

    for i in range(1, supported_size):
        catn_define = "#define {0}_CAT_{1}(a, b) {0}_CAT_{2}(a, b)".format(
            macro_prefix.upper(), i + 1, i)
        lines.append(catn_define)

    lines.append('')
    lines.append(utils.generate_header_end())
    utils.write_lines(utils.get_output_file_name(
        macro_prefix, 'cat', output_dir), lines)

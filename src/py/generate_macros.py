import json
import sys

import generate_arg
import generate_cat
import generate_for_each
import generate_inc


def generate_macros(config, output_dir):
    """
    Generate macros using the given macro config and output directory.
    """
    macro_prefix = config['macro_prefix']
    header_guard_prefix = config['header_guard_prefix']
    supported_size = int(config['supported_size'])
    generate_arg.generate_arg(
        macro_prefix, header_guard_prefix, supported_size, output_dir)
    generate_cat.generate_cat(
        macro_prefix, header_guard_prefix, supported_size, output_dir)
    generate_inc.generate_inc(
        macro_prefix, header_guard_prefix, supported_size, output_dir)
    generate_for_each.generate_for_each(
        macro_prefix, header_guard_prefix, supported_size, 2, output_dir)


if __name__ == '__main__':
    if len(sys.argv) == 3:
        with open(sys.argv[1], 'r') as config_file:
            config = json.load(config_file)
            generate_macros(config, sys.argv[2])

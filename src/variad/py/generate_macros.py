import json
import sys
import generate_arg

def load_config(config, output_dir):
    macro_prefix = config['macro_prefix']
    header_guard_prefix = config['header_guard_prefix']
    supported_size = int(config['supported_size'])
    generate_arg.generate_arg(macro_prefix, header_guard_prefix, supported_size, output_dir)

if __name__ == '__main__':
    if (len(sys.argv) == 3):
        with open(sys.argv[1], 'r') as config_file:
            config = json.load(config_file)
            load_config(config, sys.argv[2])

# Variad

This project includes experimentation using macros to define abstractions in
C++. The intent of this repository is for me to track my iterations on my
ideas.

# Requirements

This requires Boost, CMake, and C++11.

# Build

```shell
python3 src/py/generate_macros.py internal_macro_config.json
python3 src/py/generate_macros.py hvv_macro_config.json
mkdir build
cd build
cmake ..
make
```

# Generating macros

Due to the large number of macros, to save time I wrote some scripts to generate the header files containing macros. The configuration parameters are in macro config JSONs, controlling the macro prefixes, the header guard prefixes, the supported number of expansions (for loops, defers), and some other parameters. This allows me to prototype the macro generation with small supported sizes, before expanding it for flexibility.

The following command will generate the headers according to the included JSONs.

```shell
python3 src/variad/py/generate_macros.py internal_macro_config.json
python3 src/variad/py/generate_macros.py hvv_macro_config.json
```

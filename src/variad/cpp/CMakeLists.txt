# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()

variad_cxx_library(
  NAME "utils"
  HDRS 
    "utils.hpp"
  SRCS
    "utils.cpp"
)

variad_cxx_library(
  NAME "heavy_variant"
  HDRS 
    "heavy_variant.hpp"
  SRCS
    "heavy_variant.cpp"
  DEPS
    variad::cpp::utils
)

variad_cxx_test(
  NAME "heavy_variant_test"
  SRCS
    "heavy_variant_test.cpp"
)

variad_cxx_test(
  NAME "hvv_for_each_test"
  SRCS
    "hvv_for_each_test.cpp"
)

variad_cxx_test(
  NAME "hvv_arg_test"
  SRCS
    "hvv_arg_test.cpp"
)

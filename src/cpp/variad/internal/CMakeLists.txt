# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()

variad_cxx_test(
  NAME "for_each_test"
  SRCS
    "for_each_test.cpp"
)

variad_cxx_test(
  NAME "arg_test"
  SRCS
    "arg_test.cpp"
)

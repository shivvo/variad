# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()

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

add_subdirectory("internal")

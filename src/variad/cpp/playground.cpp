// Macro expansion playground.
// gcc -E src/variad/cpp/playground.cpp

#include <memory>
#include "for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

#define TEST_MULTIPLY_IDX_0(idx, fixed_arg, va_arg) (idx + 1)
#define TEST_MULTIPLY_IDX_1(idx, fixed_arg, va_arg) (idx + 1) *

#define VG_CAT_1(a, b) a##b
#define VG_CAT_2(a, b) VG_CAT_1(a, b)
#define VG_CAT_3(a, b) VG_CAT_2(a, b)
#define VG_CAT_4(a, b) VG_CAT_3(a, b)

#define VG_DEFINE_0(a, ...) template <__VA_ARGS__>
#define VG_DEFINE_1(a)

#define VG_DEFINE(template_args) VG_CAT_3(VG_DEFINE_, ARG_IS_SINGULAR(template_args)) template_args 

#define VARIANT(name, template_args, ...) \
namespace name { \
  class t_internal {}; \
  typedef std::shared_ptr<t_internal> t; \
}

VARIANT(
    Optional,
    (None, (_)),
    (Some, (_, T), T))

int factorial = FOR_EACH1(TEST_MULTIPLY_ARG_, abc, 1, 2, 3, 4, 5);
int factorial2 = FOR_EACH2(TEST_MULTIPLY_IDX_, 123, a, b, c, d, e);
int is_single = ARG_IS_SINGULAR((Some, (int, value)));
int is_single2 = ARG_IS_SINGULAR((None));

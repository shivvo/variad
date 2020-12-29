// Macro expansion playground.
// gcc -E src/variad/cpp/hvv_playground.cpp

#include "hvv_for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

#define TEST_MULTIPLY_IDX_0(idx, fixed_arg, va_arg) (idx + 1)
#define TEST_MULTIPLY_IDX_1(idx, fixed_arg, va_arg) (idx + 1) *

#define ARG_SECOND_1(a, b, ...) b
#define ARG_SECOND_2(...) ARG_SECOND_1(__VA_ARGS__)
#define ARG_SECOND_3(...) ARG_SECOND_2(__VA_ARGS__)
#define ARG_SECOND_4(...) ARG_SECOND_3(__VA_ARGS__)
#define ARG_SECOND_5(...) ARG_SECOND_4(__VA_ARGS__)
#define ARG_SECOND_6(...) ARG_SECOND_5(__VA_ARGS__)

#define ARG_SOME_PROBE_1 ~, 1
#define ARG_IS_SINGLE(...) ARG_SECOND_2(HVV_CAT_2(ARG_SOME_PROBE_, HVV_ARG_LENGTH(__VA_ARGS__)), 0)

#define A() 5
#define B() A

int factorial = HVV_FOR_EACH_1(TEST_MULTIPLY_ARG_, abc, 1, 2, 3, 4, 5);
int factorial2 = HVV_FOR_EACH_2(TEST_MULTIPLY_IDX_, 123, a, b, c, d, e);
int is_single = ARG_IS_SINGLE(Some, (int, value));
int is_single2 = ARG_IS_SINGLE(None);
int subs = B()();

// Macro expansion playground.
// gcc -E src/variad/cpp/hvv_playground.cpp

#include "hvv_for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

#define TEST_MULTIPLY_IDX_0(idx, fixed_arg, va_arg) (idx + 1)
#define TEST_MULTIPLY_IDX_1(idx, fixed_arg, va_arg) (idx + 1) *


int factorial = HVV_FOR_EACH_1(TEST_MULTIPLY_ARG_, abc, 1, 2, 3, 4, 5);
int factorial2 = HVV_FOR_EACH_2(TEST_MULTIPLY_IDX_, 123, a, b, c, d, e);

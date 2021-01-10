#define BOOST_TEST_MODULE variad_hvv_for_each_test

#include <boost/test/included/unit_test.hpp>
#include "hvv_for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

#define TEST_MULTIPLY_IDX_0(idx, fixed_arg, va_arg) (idx + 1)
#define TEST_MULTIPLY_IDX_1(idx, fixed_arg, va_arg) (idx + 1) *


BOOST_AUTO_TEST_SUITE(VariadHvvForEachTest)

BOOST_AUTO_TEST_CASE(SimpleForEach)
{
  int factorial = HVV_FOR_EACH1(TEST_MULTIPLY_ARG_, abc, 1, 2, 3, 4, 5);
  BOOST_TEST(factorial == 120);
  
  int factorial2 = HVV_FOR_EACH2(TEST_MULTIPLY_IDX_, 123, a, b, c, d, e);
  BOOST_TEST(factorial2 == 120);
}

BOOST_AUTO_TEST_SUITE_END()

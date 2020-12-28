#define BOOST_TEST_MODULE variad_hvv_for_each_test

#include <boost/test/included/unit_test.hpp>
#include "hvv_for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

BOOST_AUTO_TEST_SUITE(VariadHvvForEachTest)

BOOST_AUTO_TEST_CASE(SimpleForEach)
{
  BOOST_TEST(HVV_FOR_EACH_1(TEST_MULTIPLY_ARG_, abc, 1, 2, 3, 4, 5) == 120);
}

BOOST_AUTO_TEST_SUITE_END()

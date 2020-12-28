#define BOOST_TEST_MODULE variad_hvv_arg_test

#include <boost/test/included/unit_test.hpp>
#include "hvv_for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

BOOST_AUTO_TEST_SUITE(VariadHvvArgTest)

BOOST_AUTO_TEST_CASE(SimpleArg)
{
  BOOST_TEST(HVV_ARG_LENGTH(1, 2, 3, 4, 5) == 5);
}

BOOST_AUTO_TEST_SUITE_END()

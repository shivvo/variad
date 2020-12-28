#define BOOST_TEST_MODULE variad_hvv_arg_test

#include <boost/test/included/unit_test.hpp>
#include "hvv_arg.hpp"

BOOST_AUTO_TEST_SUITE(VariadHvvArgTest)

BOOST_AUTO_TEST_CASE(SimpleArg)
{
  BOOST_TEST(HVV_ARG_LENGTH(a, b, c, d, e) == 5);
}

BOOST_AUTO_TEST_SUITE_END()

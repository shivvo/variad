#define BOOST_TEST_MODULE variad_internal_arg_test

#include <boost/test/included/unit_test.hpp>
#include "arg.hpp"

BOOST_AUTO_TEST_SUITE(VariadInternalArgTest)

BOOST_AUTO_TEST_CASE(SimpleArg)
{
  BOOST_TEST(ARG_LENGTH(a, b, c, d, e) == 5);
}

BOOST_AUTO_TEST_SUITE_END()

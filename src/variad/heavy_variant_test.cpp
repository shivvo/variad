#define BOOST_TEST_MODULE variad_heavy_variant_test.cpp

#include <boost/test/included/unit_test.hpp>

#include <memory>

class OutcomeInternal {};
typedef std::shared_ptr<OutcomeInternal> Outcome;

#define DEFINE_STRUCT_NAME_IMPL(struct_name) struct_name##Internal
#define DEFINE_STRUCT_NAME_EXPAND(struct_name) DEFINE_STRUCT_NAME_IMPL(struct_name)
#define DEFINE_STRUCT_NAME(struct_name) DEFINE_STRUCT_NAME_EXPAND(struct_name)

#define DEFINE_STRUCT_MEMBER_MAKE_NAME(name1, name2) name1##_##name2
#define DEFINE_STRUCT_MEMBER(type, name) type DEFINE_STRUCT_MEMBER_MAKE_NAME name;

#define DEFINE_STRUCT(struct_name, ...) \
  struct DEFINE_STRUCT_NAME(struct_name) { \
    DEFINE_STRUCT_MEMBER __VA_ARGS__ \
  } \

DEFINE_STRUCT(Temp, (int, (a, butt)));

BOOST_AUTO_TEST_SUITE(VariadHeavyVariantTest)

BOOST_AUTO_TEST_CASE(UseHeavyVariant)
{
  TempInternal foo;
  foo.a_butt = 5;
}

BOOST_AUTO_TEST_SUITE_END()

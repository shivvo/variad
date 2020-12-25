#define BOOST_TEST_MODULE variad_heavy_variant_test.cpp

#include <boost/test/included/unit_test.hpp>

#include <memory>

#define HVV_DEFINE_IDENTITY(...) __VA_ARGS__
//#define HVV_DEFINE_IDENTITY_EXPANDED(...) HVV_DEFINE_IDENTITY_IMPL __VA_ARGS__
//#define HVV_DEFINE_IDENTITY(...) HVV_DEFINE_IDENTITY_EXPANDED(__VA_ARGS__)

#define HVV_DEFINE_ADD_PARENS(...) (__VA_ARGS__)
//#define HVV_DEFINE_ADD_PARENS_EXPAND(...) HVV_DEFINE_ADD_PARENS_IMPL(__VA_ARGS__)
//#define HVV_DEFINE_ADD_PARENS(...) HVV_DEFINE_ADD_PARENS_EXPAND(__VA_ARGS__)

#define HVV_DEFINE_NAME_IMPL(name) name
#define HVV_DEFINE_NAME_EXPAND(name) HVV_DEFINE_NAME_IMPL(name)

#define HVV_DEFINE_INTERNAL_NAME_IMPL(name) name##Internal
#define HVV_DEFINE_INTERNAL_NAME_EXPAND(name) HVV_DEFINE_INTERNAL_NAME_IMPL(name)
#define HVV_DEFINE_INTERNAL_NAME(name) HVV_DEFINE_INTERNAL_NAME_EXPAND(name)

#define HVV_DEFINE_VALUE_TYPE_MEMBER(type, name) \
  public: \
    type name; \

#define HVV_ARG_65(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, N, ...) N 
#define HVV_HAS_ELEMENTS(...) \
  HVV_ARG_65(__VA_ARGS__, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1)

#define HVV_DEFINE_VALUE_TYPE_IMPL(has_elements) HVV_DEFINE_VALUE_TYPE_##has_elements
#define HVV_DEFINE_VALUE_TYPE_EXPAND(has_elements) HVV_DEFINE_VALUE_TYPE_IMPL(has_elements)
#define HVV_DEFINE_VALUE_TYPE(has_elements)  HVV_DEFINE_VALUE_TYPE_EXPAND(has_elements)

#define HVV_DEFINE_VALUE_TYPE_1(name, ...) 4

#define HVV_CAT_R1(a, b) a##b
#define HVV_CAT_R2(a, b) HVV_CAT_R1(a, b)

#define HVV_DEFINE_VALUE_TYPE_2_IMPL(name, value_type_name, ...) 5//\
  //private: \
  //  class HVV_DEFINE_INTERNAL_NAME(value_type_name) : public HVV_DEFINE_INTERNAL_NAME(name) {}; \
  //public: \
  //  typedef std::shared_ptr< HVV_DEFINE_INTERNAL_NAME(value_type_name) > HVV_DEFINE_NAME_EXPAND(value_type_name); \

#define HVV_DEFINE_VALUE_TYPE_2_EXPANDED(name, value_type_name, ...) HVV_DEFINE_VALUE_TYPE_2_IMPL(name, value_type_name, __VA_ARGS__)
#define HVV_DEFINE_VALUE_TYPE_2_INTERNAL(name, value_type_name, ...) HVV_DEFINE_VALUE_TYPE_2_EXPANDED(name, value_type_name, __VA_ARGS__)
#define HVV_DEFINE_VALUE_TYPE_2(name, value_type, ...) \
  HVV_DEFINE_VALUE_TYPE_2_INTERNAL(name, HVV_DEFINE_IDENTITY value_type)// HVV_DEFINE_FOR_EACH_VALUE_TYPES(name, __VA_ARGS__)

#define HVV_DEFINE_FOR_EACH_VALUE_TYPES(name, ...) \
  HVV_CAT_R2(HVV_DEFINE_VALUE_TYPE_, HVV_HAS_ELEMENTS(__VA_ARGS__))(name, __VA_ARGS__)

#define HVV_DEFINE(name, ...) \
  class HVV_DEFINE_INTERNAL_NAME(name); \
  typedef std::shared_ptr< HVV_DEFINE_INTERNAL_NAME(name) > HVV_DEFINE_NAME_EXPAND(name); \
  class HVV_DEFINE_INTERNAL_NAME(name) { \
  }; \
  //HVV_DEFINE_FOR_EACH_VALUE_TYPES(name, __VA_ARGS__) \


HVV_DEFINE(Outcome, None);

BOOST_AUTO_TEST_SUITE(VariadHeavyVariantTest)

BOOST_AUTO_TEST_CASE(UseHeavyVariant)
{
  //OutcomeInternal::None foo;
  //BOOST_TEST(HVV_HAS_ELEMENTS(1, 2, 3) == 1);
  //BOOST_TEST(HAS_ARGS() == 0);
  //BOOST_TEST(HAS_ARGS((None)) == 1);
  //BOOST_TEST(HAS_ARGS((None), (Some, int)) == 1);
  BOOST_TEST(HVV_DEFINE_FOR_EACH_VALUE_TYPES(Outcome, (None), (Some, int)) == 5);
  BOOST_TEST(HVV_DEFINE_FOR_EACH_VALUE_TYPES(Outcome, (None)) == 4);
}

BOOST_AUTO_TEST_SUITE_END()

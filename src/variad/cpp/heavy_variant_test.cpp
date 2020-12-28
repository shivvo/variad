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

#define HVV_DEFINE_VALUE_TYPE_IMPL(has_elements) HVV_DEFINE_VALUE_TYPE_##has_elements
#define HVV_DEFINE_VALUE_TYPE_EXPAND(has_elements) HVV_DEFINE_VALUE_TYPE_IMPL(has_elements)
#define HVV_DEFINE_VALUE_TYPE(has_elements)  HVV_DEFINE_VALUE_TYPE_EXPAND(has_elements)

#define HVV_DEFINE_VALUE_TYPE_1(name, ...) 4


#define HVV_DEFINE_VALUE_TYPE_2_IMPL(name, value_type_name, ...) 5//\
  //private: \
  //  class HVV_DEFINE_INTERNAL_NAME(value_type_name) : public HVV_DEFINE_INTERNAL_NAME(name) {}; \
  //public: \
  //  typedef std::shared_ptr< HVV_DEFINE_INTERNAL_NAME(value_type_name) > HVV_DEFINE_NAME_EXPAND(value_type_name); \

#define HVV_DEFINE_VALUE_TYPE_2_EXPANDED(name, value_type_name, ...) HVV_DEFINE_VALUE_TYPE_2_IMPL(name, value_type_name, __VA_ARGS__)
#define HVV_DEFINE_VALUE_TYPE_2_INTERNAL(name, value_type_name, ...) HVV_DEFINE_VALUE_TYPE_2_EXPANDED(name, value_type_name, __VA_ARGS__)
#define HVV_DEFINE_VALUE_TYPE_2(name, value_type, ...) \
  HVV_DEFINE_VALUE_TYPE_2_INTERNAL(name, HVV_DEFINE_IDENTITY value_type)// HVV_DEFINE_FOR_EACH_VALUE_TYPES(name, __VA_ARGS__)

#define HVV_VARIANT(name, ...) \
  class HVV_VARIANT_INTERNAL_NAME(name); \
  typedef std::shared_ptr< HVV_DEFINE_INTERNAL_NAME(name) > HVV_DEFINE_NAME_EXPAND(name); \
  class HVV_DEFINE_INTERNAL_NAME(name) { \
  }; \
  //HVV_DEFINE_FOR_EACH_VALUE_TYPES(name, __VA_ARGS__) \


BOOST_AUTO_TEST_SUITE(VariadHeavyVariantTest)

BOOST_AUTO_TEST_CASE(UseHeavyVariant)
{
}

BOOST_AUTO_TEST_SUITE_END()

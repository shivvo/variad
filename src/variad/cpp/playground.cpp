// Macro expansion playground.
// gcc -E src/variad/cpp/playground.cpp

#include <memory>
#include "for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

#define TEST_MULTIPLY_IDX_0(idx, fixed_arg, va_arg) (idx + 1)
#define TEST_MULTIPLY_IDX_1(idx, fixed_arg, va_arg) (idx + 1) *

#define VG_CAT_1(a, b) a##b
#define VG_CAT_2(a, b) VG_CAT_1(a, b)
#define VG_CAT_3(a, b) VG_CAT_2(a, b)
#define VG_CAT_4(a, b) VG_CAT_3(a, b)

#define VG_TYPE_NAME_0(_1, _2, t) typename t
#define VG_TYPE_NAME_1(_1, _2, t) typename t,
#define VG_DEFINE_0(a, ...) template <FOR_EACH2(VG_TYPE_NAME_, _, __VA_ARGS__)>
#define VG_DEFINE_1(a)
#define VG_DEFINE(template_args) VG_CAT_3(VG_DEFINE_, ARG_IS_SINGULAR(template_args)) template_args 

#define VG_ENCLOSED_LIST_0(a, ...) <__VA_ARGS__>
#define VG_ENCLOSED_LIST_1(a)
#define VG_ENCLOSED_LIST(template_args) VG_CAT_3(VG_ENCLOSED_LIST_, ARG_IS_SINGULAR(template_args)) template_args 


#define VT_CAT_1(a, b) a##b
#define VT_CAT_2(a, b) VG_CAT_1(a, b)
#define VT_CAT_3(a, b) VG_CAT_2(a, b)
#define VT_CAT_4(a, b) VG_CAT_3(a, b)

// Define tag template and extra data fields.
#define VT_DEFINE_INTERNAL_0_IMPL(idx, variant_name, tag_name, template_types, ...) \
  namespace tag_name { \
    VG_DEFINE(template_types) \
    class t_internal : public variant_name::t {}; \
    VG_DEFINE(template_types)\
    using t = std::shared_ptr<t_internal VG_ENCLOSED_LIST(template_types) >; \
  }
#define VT_DEFINE_INTERNAL_0(...) VT_DEFINE_INTERNAL_0_IMPL(__VA_ARGS__)

// Define tag with no extra data fields.
#define VT_DEFINE_INTERNAL_1(idx, variant_name, tag_name, ...) \
  namespace tag_name { \
    class t_internal {}; \
    using t = std::shared_ptr<t_internal>; \
  }
// Redirect to the right tag define macro based on `tag_info` contents.
#define VT_DEFINE_IMPL(idx, variant_name, tag_info) \
  VT_CAT_3(VT_DEFINE_INTERNAL_, ARG_IS_SINGULAR(tag_info))(idx, variant_name, ARG_IDENTITY tag_info)
  // Redirect to VT_DEFINE_IMPL.
#define VT_DEFINE_0(...) VT_DEFINE_IMPL(__VA_ARGS__)
#define VT_DEFINE_1(...) VT_DEFINE_IMPL(__VA_ARGS__)

#define VARIANT(variant_name, ...) \
namespace variant_name { \
  class t_internal {}; \
  using t = std::shared_ptr<t_internal>; \
  FOR_EACH1(VT_DEFINE_, variant_name, __VA_ARGS__)  \
}

VARIANT(
    Optional,
    (None),
    (Some, (_, T), (T, value))
    )

int factorial = FOR_EACH1(TEST_MULTIPLY_ARG_, abc, 1, 2, 3, 4, 5);
int factorial2 = FOR_EACH2(TEST_MULTIPLY_IDX_, 123, a, b, c, d, e);
int is_single = ARG_IS_SINGULAR((Some, (int, value)));
int is_single2 = ARG_IS_SINGULAR((None));

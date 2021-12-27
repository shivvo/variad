// Macro expansion playground.
// g++ -std=c++11 -E -DPLAYGROUND_ONLY src/variad/cpp/playground3.cpp

#ifndef PLAYGROUND_ONLY
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#endif

#include "for_each.hpp"

// VG_TEMPLATE_BRKLST_FE
// Variant Generics Template Bracket List For Each
// 1 and 0 macros for the typename declarations FOR_EACH. 1 has trailing comma,
// 0 does not.
// * ignore1
// * ignore2
// * type - the template type
#define VG_TEMPLATE_BRKTLST_FE0(ignore1, ignore2, type) type
#define VG_TEMPLATE_BRKTLST_FE1(ignore1, ignore2, type) type,

// VG_TEMPLATE_BRKTLST_OPT0
// Variant Generics Template Bracket List Option 0
// Substitutes template bracket list for template type lists of format `(_,
// etc)`.
#define VG_TEMPLATE_BRKTLST_OPT0(ignore, ...)                                  \
<FOR_EACH2(VG_TEMPLATE_BRKTLST_FE, _, __VA_ARGS__)>

// VG_TEMPLATE_BRKTLST_OPT1
// Variant Generics Template Bracket List Option 1
// Substitutes for the case where there are no template types which happens in
// the case of `(_)`.
// * ignore
#define VG_TEMPLATE_BRKTLST_OPT1(ignore)

// VG_TEMPLATE_BRKTLST
// Variant Generics Template Bracket List
// Substitutes in <A, B, etc> based on a template list.
// * template_types - template types formatted as `(_, A, B, etc)`
#define VG_TEMPLATE_BRKTLST(template_types)                                    \
  CAT_3(VG_TEMPLATE_BRKTLST_OPT, ARG_IS_SINGULAR(template_types)) template_types

// VG_TYPENAME_DECLARE
// Variant Generics Typename Declare
// Substitutes typename declaration for a single type.
// * type - the typename
#define VG_TYPENAME_DECLARE(type) typename type

// VG_TEMPLATE_DECLARE_FE
// Variant Generics Template Declare For Each
// 1 and 0 macros for the typename declarations FOR_EACH. 1 has trailing comma,
// 0 does not.
// * ignore1
// * ignore2
// * type - the template type to declare
#define VG_TEMPLATE_DECLARE_FE0(ignore1, ignore2, type)                        \
  VG_TYPENAME_DECLARE(type)
#define VG_TEMPLATE_DECLARE_FE1(ignore1, ignore2, type)                        \
  VG_TYPENAME_DECLARE(type),

// VG_TEMPLATE_DECLARE_OPT0
// Variant Generics Template Declare Option 0
// Substitutes template declare for template type lists of format `(_, etc)`.
#define VG_TEMPLATE_DECLARE_OPT0(ignore, ...)                                  \
  template <FOR_EACH2(VG_TEMPLATE_DECLARE_FE, _, __VA_ARGS__)>

// VG_TEMPLATE_DECLARE_OPT1
// Variant Generics Template Declare Option 1
// Substitutes for the case where there are no template types which happens in
// the case of `(_)`.
// * ignore
#define VG_TEMPLATE_DECLARE_OPT1(ignore)

// VG_TEMPLATE_DECLARE
// Variant Generics Template Declare
// Substitutes in `template <typename A, etc>` based on a template list.
// * template_types - template types formatted as `(_, A, etc)`
#define VG_TEMPLATE_DECLARE(template_types)                                    \
  CAT_3(VG_TEMPLATE_DECLARE_OPT, ARG_IS_SINGULAR(template_types)) template_types

// VT_DEFINE_TAGDATA
// Variant Tag Define Tag with Data
// VT_DEFINE_LVL2_OPT0
// Variant Tag Define Level 2 Option 0
// Define a variant tag with extra data.
// * tag_idx - the tag index
// * variant_name - the variant name
// * template_types - the template types, format `(_, etc)`
// * variant_tag_name - the variant tag name
// * ... / __VA_ARGS__ - the variant tag data members, formatted as
//   `(int, data)`
#define VT_DEFINE_TAGDATA(tag_idx, variant_name, template_types,               \
                          variant_tag_name, ...)

#define VT_DEFINE_LVL2_OPT0(tag_idx, variant_name, template_types,             \
                            variant_tag_name, ...)                             \
  VT_DEFINE_TAGDATA(tag_idx, variant_name, template_types, variant_tag_name,   \
                    __VA_ARGS__)

// VT_DEFINE_TAGONLY
// Variant Tag Define Tag Only
// VT_DEFINE_LVL2_OPT1
// Variant Tag Define Level 2 Option 1
// Define a variant tag with no extra data.
// * tag_idx - the tag index
// * variant_name - the variant name
// * template_types - the template types, format `(_, etc)`
// * variant_tag_name - the variant tag name
#define VT_DEFINE_TAGONLY(tag_idx, variant_name, template_types,               \
                          variant_tag_name)

#define VT_DEFINE_LVL2_OPT1(tag_idx, variant_name, template_types,             \
                            variant_tag_name)                                  \
  VT_DEFINE_TAGONLY(tag_idx, variant_name, template_types, variant_tag_name)

// VT_DEFINE_LVL2
// Variant Tag Define Level 2
// Accepts index, variant_name, template args and variant tag definition.
// * idx - the index of the iteration. Starts at 0
// * variant_name - name of the variant
// * template_types - template tytpes is the `(_, etc)` format
// * variant_tag_define - variant tag definition
//   formatted as `(Tag, (int, data), etc.)`
#define VT_DEFINE_LVL2(idx, variant_name, template_types, variant_tag_define)  \
  CAT_3(VT_DEFINE_LVL2_OPT, ARG_IS_SINGULAR(variant_tag_define))               \
  (idx, variant_name, template_types, ARG_IDENTITY variant_tag_define)

// VT_DEFINE_LVL1
// Variant Tage Define Level 1
// Accepts index, fixed arg and variant tag definition
// * idx - the index of the iteration. Starts at 0
// * fixed_arg - expected format: (variant_name, template_types)
//   * template_types is the `(_, etc)` format
// * variant_tag_define - variant tag definition
//   formatted as (Tag, (int, data), etc.)
#define VT_DEFINE_LVL1(idx, fixed_arg, variant_tag_define)                     \
  VT_DEFINE_LVL2(idx, ARG_IDENTITY fixed_arg, variant_tag_define)

// VT_DEFINE_ - Variant Tag Define
// 1 and 0 macros for FOR_EACH macros. Defined as the same via VT_DEFINE_L1.
// * ... / __VA_ARGS__ - expected format:
//   idx, (variant_name, template_types), variant_tag_define
//   * template_types is the (_, etc) format
//   * variant_tag_define is the (Tag, (int, data), etc) format
#define VT_DEFINE_0(...)
#define VT_DEFINE_1(...)

// VARIANT
// Defines variant type.
// * variant_name - name of the variant
// * template_types - list of template arguments,
//   formed as `(_)` for none or `(_, A, B)` etc. for typenames A, B
// * ... / __VA_ARGS__ - list of variant tags
//   formed as `(TagOnly)` or `(TagAndData, (int, data), (double, more_data))`
#define VARIANT(variant_name, template_types, ...)                             \
  namespace variant_name {                                                     \
  namespace internal {                                                         \
  VG_TEMPLATE_DECLARE(template_types)                                          \
  class t {                                                                    \
  public:                                                                      \
    t(int tag) : m_tag(tag) {}                                                 \
                                                                               \
    int tag() { return m_tag; }                                                \
                                                                               \
  private:                                                                     \
    int m_tag;                                                                 \
  };                                                                           \
  }                                                                            \
                                                                               \
  VG_TEMPLATE_DECLARE(template_types)                                          \
  using t = std::shared_ptr<variant_name::internal::t VG_TEMPLATE_BRKTLST(     \
      template_types)>;                                                        \
  FOR_EACH1(VT_DEFINE_, (variant_name, template_types), __VA_ARGS__)           \
  }

VARIANT(Boolean, (_), (True)(False))

VARIANT(Tree, (_, K, V),
        (Leaf)(Node2, (K, key), (V, value), (Tree::t<K, V>, left_child),
               (Tree::t<K, V>, right_child)))

int main(int argc, char **argv) { return 0; }

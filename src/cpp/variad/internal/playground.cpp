// Macro expansion playground.
// g++ -std=c++11 -E src/variad/cpp/playground.cpp

#ifndef PLAYGROUND_ONLY
#include <memory>
#include <string>
#endif

#include "for_each.hpp"

#define TEST_MULTIPLY_ARG_0(idx, fixed_arg, va_arg) va_arg
#define TEST_MULTIPLY_ARG_1(idx, fixed_arg, va_arg) va_arg *

#define TEST_MULTIPLY_IDX_0(idx, fixed_arg, va_arg) (idx + 1)
#define TEST_MULTIPLY_IDX_1(idx, fixed_arg, va_arg) (idx + 1) *

#define VG_CAT_1(a, b) a##b
#define VG_CAT_2(a, b) VG_CAT_1(a, b)
#define VG_CAT_3(a, b) VG_CAT_2(a, b)
#define VG_CAT_4(a, b) VG_CAT_3(a, b)

// Define list of typenames when declaring a template.
#define VG_TYPE_NAME_0(_1, _2, t) typename t
#define VG_TYPE_NAME_1(_1, _2, t) typename t,
#define VG_DEFINE_0(a, ...) template <FOR_EACH2(VG_TYPE_NAME_, _, __VA_ARGS__)>
#define VG_DEFINE_1(a)
#define VG_DEFINE(template_args)                                               \
  VG_CAT_3(VG_DEFINE_, ARG_IS_SINGULAR(template_args)) template_args

// Define a list of typenames for template instantiation.
#define VG_ENCLOSED_LIST_0(a, ...) <__VA_ARGS__>
#define VG_ENCLOSED_LIST_1(a)
#define VG_ENCLOSED_LIST(template_args)                                        \
  VG_CAT_3(VG_ENCLOSED_LIST_, ARG_IS_SINGULAR(template_args)) template_args

#define VT_CAT_1(a, b) a##b
#define VT_CAT_2(a, b) VG_CAT_1(a, b)
#define VT_CAT_3(a, b) VG_CAT_2(a, b)
#define VT_CAT_4(a, b) VG_CAT_3(a, b)

#define VTF_DEFINE_IMPL(idx, variant_name, tag_idx, tag_name, field_type,      \
                        field_name)                                            \
public:                                                                        \
  field_type field_name;
#define VTF_DEFINE_EXPANDED(idx, fixed_arg, field_info)                        \
  VTF_DEFINE_IMPL(idx, fixed_arg, field_info)
#define VTF_DEFINE_0(idx, fixed_arg, field_info)                               \
  VTF_DEFINE_EXPANDED(idx, ARG_IDENTITY fixed_arg, ARG_IDENTITY field_info)
#define VTF_DEFINE_1(idx, fixed_arg, field_info)                               \
  VTF_DEFINE_EXPANDED(idx, ARG_IDENTITY fixed_arg, ARG_IDENTITY field_info)

#define VT_FUNCTION_OF(idx, variant_name, tag_name, template_types, ...)

// Define tag template and extra data fields.
#define VT_DEFINE_INTERNAL_0_IMPL(idx, variant_name, tag_name, template_types, \
                                  ...)                                         \
  namespace tag_name {                                                         \
  VG_DEFINE(template_types)                                                    \
  class t_internal : public variant_name::t {                                  \
    FOR_EACH2(VTF_DEFINE_, (variant_name, idx, tag_name), __VA_ARGS__)         \
  private:                                                                     \
    t_internal() {}                                                            \
  };                                                                           \
  VG_DEFINE(template_types)                                                    \
  using t = std::shared_ptr<t_internal VG_ENCLOSED_LIST(template_types)>;      \
  }
#define VT_DEFINE_INTERNAL_0(...) VT_DEFINE_INTERNAL_0_IMPL(__VA_ARGS__)

// Define tag with no extra data fields.
#define VT_DEFINE_INTERNAL_1(idx, variant_name, tag_name, ...)                 \
  namespace tag_name {                                                         \
  class t_internal {};                                                         \
  using t = std::shared_ptr<t_internal>;                                       \
  }
// Redirect to the right tag define macro based on `tag_info` contents.
#define VT_DEFINE_IMPL(idx, variant_name, tag_info)                            \
  VT_CAT_3(VT_DEFINE_INTERNAL_, ARG_IS_SINGULAR(tag_info))                     \
  (idx, variant_name, ARG_IDENTITY tag_info)
// Redirect to VT_DEFINE_IMPL.
#define VT_DEFINE_0(...) VT_DEFINE_IMPL(__VA_ARGS__)
#define VT_DEFINE_1(...) VT_DEFINE_IMPL(__VA_ARGS__)

#define VARIANT(variant_name, ...)                                             \
  namespace variant_name {                                                     \
  class t_internal {};                                                         \
  using t = std::shared_ptr<t_internal>;                                       \
  FOR_EACH1(VT_DEFINE_, variant_name, __VA_ARGS__)                             \
  }
/*
VARIANT(
    Optional,
    (None),
    (Some,
     (_, T),
     (T, value)),
    (StatusOr,
     (_, T),
     (T, value)),
    (Outcome,
     (_, E, R, T),
     (E, unrecoverable_error),
     (R, recoverable_error),
     (T, value)),
    (SomeInt,
     (_),
     (int, value))
    )
*/
template <typename T, typename V> class TestClass;

template <typename T, typename V> class TestClass {};

namespace variad {
template <typename T> class IntOr {
public:
  enum Type { TYPE_INTEGER, TYPE_T };
  IntOr(const int &int_value)
      : type_(Type::TYPE_INTEGER), int_value_(int_value), t_value_(nullptr) {}
  IntOr(const int &&int_value)
      : type_(Type::TYPE_INTEGER), int_value_(int_value), t_value_(nullptr) {}
  IntOr(std::shared_ptr<T> t_value)
      : type_(Type::TYPE_INTEGER), int_value_(0), t_value_(t_value) {}

private:
  Type type_;
  int int_value_;
  std::shared_ptr<T> t_value_;
};
} // namespace variad

namespace Tree {
namespace internal {
template <typename K, typename V> class t {
public:
  t(int tag) : m_tag(tag) {}

private:
  int m_tag;
};
} // namespace internal
template <typename K, typename V> using t = variad::IntOr<internal::t<K, V>>;

namespace Leaf {
namespace internal {
const int tag = 0;
}

template <typename K, typename V> Tree::t<K, V> of() {
  return Leaf::internal::tag;
}
} // namespace Leaf

namespace Node2 {
namespace internal {
const int tag = 1;

template <typename K, typename V> class t : public Tree::internal::t<K, V> {
public:
  t(int tag, K key, V value, Tree::t<K, V> left_child,
    Tree::t<K, V> right_child)
      : Tree::internal::t<K, V>(tag), m_key(key), m_value(value),
        m_left_child(left_child), m_right_child(right_child){};

private:
  K m_key;
  V m_value;
  Tree::t<K, V> m_left_child;
  Tree::t<K, V> m_right_child;
};
} // namespace internal

template <typename K, typename V>
Tree::t<K, V> of(K key, V value, Tree::t<K, V> left_child,
                 Tree::t<K, V> right_child) {
  auto ret = std::make_shared<Node2::internal::t<K, V>>(
      Node2::internal::tag, key, value, left_child, right_child);
  return Tree::t<K, V>(ret);
}
} // namespace Node2
} // namespace Tree

int main(int argc, char **argv) {
  int factorial = FOR_EACH1(TEST_MULTIPLY_ARG_, abc, 1, 2, 3, 4, 5);
  int factorial2 = FOR_EACH2(TEST_MULTIPLY_IDX_, 123, a, b, c, d, e);
  int is_single = ARG_IS_SINGULAR((Some, (int, value)));
  int is_single2 = ARG_IS_SINGULAR((None));

  variad::IntOr<bool> int_or_bool(std::make_shared<bool>(true));
  variad::IntOr<bool> int_or_bool2 = int_or_bool;
  Tree::t<std::string, std::string> tree =
      Tree::Leaf::of<std::string, std::string>();
  tree = Tree::Node2::of(std::string("a"), std::string("b"),
                         Tree::Leaf::of<std::string, std::string>(),
                         Tree::Leaf::of<std::string, std::string>());
}

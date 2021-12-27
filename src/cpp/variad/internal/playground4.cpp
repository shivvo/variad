// Macro expansion playground.
// g++ -std=c++11 -E -DPLAYGROUND_ONLY src/variad/cpp/playground4.cpp

#ifndef PLAYGROUND_ONLY
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#endif

#include "for_each.hpp"

namespace Tree {
namespace internal {

template <typename T> class int_or {
public:
  enum kind { KIND_INTEGER, KIND_T };
  int_or() = delete;
  int_or(const int &int_value)
      : m_kind(kind::KIND_INTEGER), m_int_value(int_value), m_t_value(nullptr) {
  }
  int_or(const int &&int_value)
      : m_kind(kind::KIND_INTEGER), m_int_value(int_value), m_t_value(nullptr) {
  }
  int_or(const std::shared_ptr<T> &t_value)
      : m_kind(kind::KIND_T), m_int_value(0), m_t_value(t_value) {}
  int_or(const std::shared_ptr<T> &&t_value)
      : m_kind(kind::KIND_T), m_int_value(0), m_t_value(t_value) {}

  bool is_int() const { return m_kind == kind::KIND_INTEGER; }
  bool is_t() const { return m_kind == kind::KIND_T; }
  int int_value() const { return m_int_value; }
  const T &t_value() const { return *m_t_value; }

private:
  kind m_kind = kind::KIND_UNDEFINED;
  int m_int_value = -1;
  std::shared_ptr<T> m_t_value = nullptr;
};

// Internal type for Tree<K, V>.
// Has tag information.
template <typename K, typename V> class t {
public:
  t(int tag) : m_tag(tag) {}

  int tag() const { return m_tag; }

private:
  int m_tag;
};
} // namespace internal

template <typename K, typename V>
using t = Tree::internal::int_or<Tree::internal::t<K, V>>;

namespace internal {

template <typename K, typename V> int get_tag(const Tree::t<K, V> &arg) {
  return arg.is_t() ? arg.t_value().tag() : arg.int_value();
}

} // namespace internal

namespace Leaf {

namespace intermediate {
class t;
}

Tree::Leaf::intermediate::t of();

namespace internal {

namespace fixed {
const int tag = 0;
}

template <typename K, typename V> class t : public Tree::internal::t<K, V> {
public:
  t() : Tree::internal::t<K, V>(Tree::Leaf::internal::fixed::tag) {}
};
} // namespace internal

namespace intermediate {

class t {
public:
  template <typename K, typename V> operator Tree::t<K, V>() {
    return Tree::t<K, V>(Tree::Leaf::internal::fixed::tag);
  }

private:
  t() {}

  friend t Tree::Leaf::of();
};

} // namespace intermediate

Tree::Leaf::intermediate::t of() { return Tree::Leaf::intermediate::t(); }

} // namespace Leaf

namespace Node2 {

namespace intermediate {
template <typename T1, typename T2, typename T3, typename T4> class t;
}

template <typename T1, typename T2, typename T3, typename T4>
Tree::Node2::intermediate::t<T1, T2, T3, T4> of(T1 arg1, T2 arg2, T3 arg3,
                                                T4 arg4);

namespace internal {
namespace fixed {
const int tag = 1;
}

template <typename K, typename V> class t : public Tree::internal::t<K, V> {
public:
  t(K arg1, V arg2, Tree::t<K, V> arg3, Tree::t<K, V> arg4)
      : Tree::internal::t<K, V>(Tree::Node2::internal::fixed::tag), m_key(arg1),
        m_value(arg2), m_left_child(arg3), m_right_child(arg4) {}

private:
  K m_key;
  V m_value;
  Tree::t<K, V> m_left_child;
  Tree::t<K, V> m_right_child;
};

} // namespace internal

namespace intermediate {

template <typename T1, typename T2, typename T3, typename T4> class t {
public:
  template <
      typename K, typename V,
      typename std::enable_if<std::is_convertible<T1, K>::value>::type * =
          nullptr,
      typename std::enable_if<std::is_convertible<T2, V>::value>::type * =
          nullptr,
      typename std::enable_if<
          std::is_convertible<T3, Tree::t<K, V>>::value>::type * = nullptr,
      typename std::enable_if<
          std::is_convertible<T4, Tree::t<K, V>>::value>::type * = nullptr>
  operator Tree::t<K, V>() {
    return Tree::t<K, V>(std::make_shared<Tree::Node2::internal::t<K, V>>(
        m_arg1, m_arg2, m_arg3, m_arg4));
  }

private:
  t(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
      : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4) {}

  T1 m_arg1;
  T2 m_arg2;
  T3 m_arg3;
  T4 m_arg4;

  friend t<T1, T2, T3, T4> Tree::Node2::of<T1, T2, T3, T4>(T1 arg1, T2 arg2,
                                                           T3 arg3, T4 arg4);
};

} // namespace intermediate

template <typename T1, typename T2, typename T3, typename T4>
Tree::Node2::intermediate::t<T1, T2, T3, T4> of(T1 arg1, T2 arg2, T3 arg3,
                                                T4 arg4) {
  return Tree::Node2::intermediate::t<T1, T2, T3, T4>(arg1, arg2, arg3, arg4);
}

} // namespace Node2

} // namespace Tree

int main(int argc, char **argv) {
  std::cout << "hello, world!" << std::endl;
  std::cout << "is double convertible to int "
            << std::is_convertible<double, int>::value << std::endl;
  std::cout << "is const char * convertible to int "
            << std::is_convertible<const char *, int>::value << std::endl;
  std::cout << "is Tree::Leaf::intermediate::t convertible to "
               "Tree::t<std::string, int> "
            << std::is_convertible<Tree::Leaf::intermediate::t,
                                   Tree::t<std::string, int>>::value
            << std::endl;
  std::cout << "is Tree::Leaf::intermediate::t convertible to "
               "Tree::t<std::string, int> "
            << std::is_convertible<Tree::Leaf::intermediate::t,
                                   Tree::t<std::string, int>>::value
            << std::endl;
  std::cout << "is Tree::Node2::intermediate::t<const char *, const char *, "
               "Tree::Leaf::intermediate::t, Tree::Leaf::intermediate::t> "
               "convertible to Tree::t<std::string, int> "
            << std ::is_convertible<
                   Tree::Node2::intermediate::t<const char *, const char *,
                                                Tree::Leaf::intermediate::t,
                                                Tree::Leaf::intermediate::t>,
                   Tree::t<std::string, int>>::value
            << std::endl;

  Tree::t<std::string, int> tree = Tree::Leaf::of();
  Tree::t<std::string, int> tree2 =
      Tree::Node2::of("a", 2.0, Tree::Leaf::of(), Tree::Leaf::of());
  Tree::t<std::string, int> tree3 = Tree::Node2::of(
      "a", 2.0, Tree::Node2::of("b", 3, Tree::Leaf::of(), Tree::Leaf::of()),
      tree2);
  return 0;
}

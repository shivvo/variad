// Macro expansion playground.
// g++ -std=c++11 -E -DPLAYGROUND_ONLY src/variad/cpp/playground2.cpp

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
template <typename K, typename V> class t;
}
template <typename K, typename V>
using t = std::shared_ptr<Tree::internal::t<K, V>>;

namespace internal {

template <typename K, typename V> class Node {
public:
  Node(K arg1, V arg2, Tree::t<K, V> arg3, Tree::t<K, V> arg4)
      : m_key(arg1),
        m_value(arg2), m_left_child(arg3), m_right_child(arg4) {}

private:
  K m_key;
  V m_value;
  Tree::t<K, V> m_left_child;
  Tree::t<K, V> m_right_child;
};

// Internal type for Tree<K, V>.
// Has tag information.
template <typename K, typename V> class t {
public:
  t(int tag) : m_tag(tag) {}

  int tag() { return m_tag; }

private:
  int m_tag;
};
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
  template <typename K, typename V> operator Tree::Leaf::internal::t<K, V>() {
    return Tree::Leaf::internal::t<K, V>();
  }

  template <typename K, typename V>
  operator std::shared_ptr<Tree::internal::t<K, V>>() {
    return std::make_shared<Tree::Leaf::internal::t<K, V>>();
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
  operator Tree::Node2::internal::t<K, V>() {
    return Tree::Node2::internal::t<K, V>(m_arg1, m_arg2, m_arg3, m_arg4);
  }

  template <typename K, typename V> operator Tree::t<K, V>() {
    return std::make_shared<Tree::Node2::internal::t<K, V>>(m_arg1, m_arg2,
                                                            m_arg3, m_arg4);
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
  return 0;
}

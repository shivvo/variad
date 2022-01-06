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

namespace variad {} // namespace variad

namespace Tree {

template <typename K, typename V> class t;

namespace internal {
namespace intermediate {
class Leaf;
}
} // namespace internal
Tree::internal::intermediate::Leaf Leaf();

namespace internal {
namespace intermediate {
template <typename T1, typename T2, typename T3, typename T4> class Node2;
}
} // namespace internal
template <typename T1, typename T2, typename T3, typename T4>
Tree::internal::intermediate::Node2<T1, T2, T3, T4> Node2(T1 arg1, T2 arg2,
                                                          T3 arg3, T4 arg4);

namespace internal {

template <typename T> struct auto_use_ptr_type { using type = T; };
template <typename T> struct base_type {
  using type = typename auto_use_ptr_type<typename std::remove_const<
      typename std::remove_reference<T>::type>::type>::type;
};
template <typename T> struct const_type {
  using type = const typename base_type<T>::type;
};
template <typename K, typename V> struct auto_use_ptr_type<t<K, V>> {
  using type = std::shared_ptr<t<K, V>>;
};

template <typename K, typename V> class Node2 {
  Node2(K arg1, V arg2, Tree::t<K, V> arg3, Tree::t<K, V> arg4)
      : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4) {}

  typename base_type<K>::type m_arg1;
  typename base_type<V>::type m_arg2;
  typename base_type<Tree::t<K, V>>::type m_arg3;
  typename base_type<Tree::t<K, V>>::type m_arg4;

  friend class Tree::t<K, V>;
  template <typename T1, typename T2, typename T3, typename T4>
  friend class Tree::internal::intermediate::Node2;
};
} // namespace internal

namespace internal {
namespace intermediate {
class Leaf {
public:
  template <typename K, typename V> operator Tree::t<K, V>() {
    return Tree::t<K, V>(0);
  }

  template <typename K, typename V> operator std::shared_ptr<Tree::t<K, V>>() {
    return Tree::t<K, V>::make_shared(0);
  }

private:
  Leaf() {}
  friend Leaf Tree::Leaf();
};

template <typename T1, typename T2, typename T3, typename T4> class Node2 {
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
    return Tree::t<K, V>(
        1, Tree::internal::Node2<K, V>(m_arg1, m_arg2, m_arg3, m_arg4));
  }

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
  operator std::shared_ptr<Tree::t<K, V>>() {
    return Tree::t<K, V>::make_shared(
        1, internal::Node2<K, V>(m_arg1, m_arg2, m_arg3, m_arg4));
  }

private:
  Node2(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
      : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4) {}

  T1 m_arg1;
  T2 m_arg2;
  T3 m_arg3;
  T4 m_arg4;

  friend internal::intermediate::Node2<T1, T2, T3, T4>
  Tree::Node2<T1, T2, T3, T4>(T1 arg1, T2 arg2, T3 arg3, T4 arg4);
};

} // namespace intermediate
} // namespace internal

template <typename K, typename V> class t {
public:
  t(const t &other) {
    m_tag = other.m_tag;
    if (other.m_tag == 1) {
      m_tagdata1 = other.m_tagdata1;
    }
  }
  t(t &&other) {
    m_tag = other.m_tag;
    if (other.m_tag == 1) {
      m_tagdata1 = other.m_tagdata1;
    }
  }
  ~t() {
    if (m_tag == 1) {
      m_tagdata1.~Node2();
    }
  }
  operator std::shared_ptr<t<K, V>>() { return make_shared(); }

private:
  t(int tag) : m_tag(tag) {}
  static std::shared_ptr<t<K, V>> make_shared(int tag) {
    class make_shared_t : public t<K, V> {
    public:
      make_shared_t(int tag) : t<K, V>(tag) {}
    };
    return std::make_shared<make_shared_t>(tag);
  }
  t(int tag, const internal::Node2<K, V> &tagdata1)
      : m_tag(tag), m_tagdata1(tagdata1) {}
  static std::shared_ptr<t<K, V>>
  make_shared(int tag, const internal::Node2<K, V> tagdata1) {
    class make_shared_t : public t<K, V> {
    public:
      make_shared_t(int tag, const internal::Node2<K, V> tagdata1)
          : t<K, V>(tag, tagdata1) {}
    };
    return std::make_shared<make_shared_t>(tag, tagdata1);
  }

  std::shared_ptr<t<K, V>> make_shared() {
    class make_shared_t : public t<K, V> {
    public:
      make_shared_t(const t<K, V> &other) : t<K, V>(other) {}
    };
    return std::make_shared<make_shared_t>(*this);
  }
  int tag() { return m_tag; }
  const internal::Node2<K, V> &tagdata1() { return m_tagdata1; }

  int m_tag;
  union {
    Tree::internal::Node2<K, V> m_tagdata1;
  };

  friend class Tree::internal::intermediate::Leaf;
  template <typename T1, typename T2, typename T3, typename T4>
  friend class Tree::internal::intermediate::Node2;
};

Tree::internal::intermediate::Leaf Leaf() {
  return Tree::internal::intermediate::Leaf();
}

template <typename T1, typename T2, typename T3, typename T4>
Tree::internal::intermediate::Node2<T1, T2, T3, T4> Node2(T1 arg1, T2 arg2,
                                                          T3 arg3, T4 arg4) {
  return Tree::internal::intermediate::Node2<T1, T2, T3, T4>(arg1, arg2, arg3,
                                                             arg4);
}

} // namespace Tree

#define ESCAPE_LVL3(arg3)
#define ESCAPE_LVL2(arg) #arg
#define ESCAPE(arg) ESCAPE_LVL2(arg)
#define PRINT_AND_EVAL(expr)                                                   \
  std::cout << ESCAPE(expr) << " " << ARG_IDENTITY expr << std::endl

int main(int argc, char **argv) {

  PRINT_AND_EVAL((std::is_convertible<Tree::internal::intermediate::Leaf,
                                      Tree::t<std::string, int>>::value));

  Tree::t<std::string, int> tree1 = Tree::Leaf();
  Tree::t<std::string, int> tree2 =
      Tree::Node2("a", 2, Tree::Leaf(), Tree::Leaf());
  Tree::t<std::string, int> tree3 = Tree::Node2(
      "c", 4, Tree::Node2("b", 3, Tree::Leaf(), Tree::Leaf()), Tree::Leaf());
  Tree::t<std::string, int> tree4 =
      Tree::Node2("d", 5, tree1, Tree::Node2("e", 6, tree2, tree3));
  return 0;
}

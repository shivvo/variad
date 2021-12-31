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

namespace variad {
template <typename A> struct ref {
public:
  template <typename B, typename std::enable_if<
                            std::is_convertible<B, A>::value>::type * = nullptr>
  ref(const B &raw_data) : m_data(std::make_shared<A>(raw_data)) {}
  template <typename B, typename std::enable_if<
                            std::is_convertible<B, A>::value>::type * = nullptr>
  ref(B &&raw_data) : m_data(std::make_shared<A>(raw_data)) {}

  operator const A &() { return *m_data; }
  operator const std::shared_ptr<A> &() { return m_data; }

private:
  std::shared_ptr<A> m_data;
};

template <typename T> struct remove_cvref {
  using type = typename std::remove_cv<typename std::remove_reference<T>>::type;
};

} // namespace variad

struct A {
  A() {}
  A(const A &a) {}
  A(A &&a) {}
};

struct B {
  B() {}
  operator A() { return A(); }
};

template <typename K, typename V> class BinaryTree {
private:
  template <typename T> struct auto_ptrize {
    using type = typename std::conditional<
        std::is_same<typename ::variad::remove_cvref<T>::type,
                     BinaryTree<K, V>>::value,
        ::variad::ref<BinaryTree<K, V>>,
        typename ::variad::remove_cvref<T>::type>;
  };

  template <typename T> struct tagdata_type {
    using type =
        typename auto_ptrize<typename ::variad::remove_cvref<T>::type>::type;
  };

  class internal_Node;

public:
  class transient_Leaf;
  template <typename T0, typename T1, typename T2, typename T3>
  class transient_Node;

private:
  class internal_Node {
    internal_Node(const K &arg0, const V &arg1, const BinaryTree<K, V> &arg2,
                  const BinaryTree<K, V> &arg3)
        : m_arg0(arg0), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) {}

    const typename tagdata_type<K>::type &arg0() { return arg0; };
    const typename tagdata_type<V>::type &arg1() { return arg1; }
    const typename tagdata_type<BinaryTree<K, V>>::type &arg2() {
      return arg2;
    };
    const typename tagdata_type<BinaryTree<K, V>>::type &arg3() {
      return arg3;
    };

    typename tagdata_type<K>::type m_arg0;
    typename tagdata_type<V>::type m_arg1;
    typename tagdata_type<BinaryTree<K, V>>::type m_arg2;
    typename tagdata_type<BinaryTree<K, V>>::type m_arg3;

    template <typename T0, typename T1, typename T2, typename T3>
    friend class transient_Node;
  };

  BinaryTree(const int &tag) : m_tag(tag) {}
  BinaryTree(const internal_Node &dtag1) : m_tag(1), m_dtag1(dtag1) {}
  BinaryTree() = delete;

public:
  BinaryTree(const BinaryTree &other) {
    m_tag = other.m_tag;
    if (other.m_tag == 1) {
      m_dtag1 = other.m_dtag1;
    }
  }
  BinaryTree(BinaryTree &&other) {
    m_tag = other.m_tag;
    if (other.m_tag == 1) {
      m_dtag1 = other.m_dtag1;
    }
  }
  ~BinaryTree() {
    if (m_tag == 1) {
      m_dtag1.~internal_Node();
    }
  }

  class transient_Leaf {
  public:
    operator BinaryTree<K, V>() { return BinaryTree<K, V>(0); }

  private:
    transient_Leaf() {}

    friend class BinaryTree<K, V>;
  };
  template <typename T0, typename T1, typename T2, typename T3>
  class transient_Node {

  private:
    transient_Node(T0 arg0, T1 arg1, T2 arg2, T3 arg3)
        : m_arg0(arg0), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) {}

    T0 m_arg0;
    T1 m_arg1;
    T2 m_arg2;
    T3 m_arg3;
  };

private:
  int m_tag;
  union {
    internal_Node m_dtag1;
  };
};

int main(int argc, char **argv) {
  auto a1 = std::make_shared<A>(B());
  auto a2 = std::make_shared<A>(A());
  return 0;
}

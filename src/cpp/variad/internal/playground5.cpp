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
template <typename A> class ref {
public:
  template <typename B, typename std::enable_if<
                            std::is_convertible<B, A>::value>::type * = nullptr>
  ref(const B &raw_data) : m_data(std::make_shared<A>(raw_data)) {}
  template <typename B, typename std::enable_if<
                            std::is_convertible<B, A>::value>::type * = nullptr>
  ref(B &&raw_data) : m_data(std::make_shared<A>(std::move(raw_data))) {}

  operator const A &() { return *m_data; }
  operator const std::shared_ptr<A> &() { return m_data; }

private:
  std::shared_ptr<A> m_data;
};

template <typename T> struct remove_cvref {
  using type = typename std::remove_cv<typename std::remove_reference<T>>::type;
};

namespace _internal {
template <bool...> struct bool_pack {};

template <bool... B>
using conjunction = std::is_same<bool_pack<true, B...>, bool_pack<B..., true>>;

template <std::size_t... S> struct seq {};

template <std::size_t N, std::size_t... S>
struct gens : gens<N - 1, N - 1, S...> {};

template <std::size_t... S> struct gens<0, S...> { typedef seq<S...> type; };

template <template <typename X, typename Y> class Func>
struct tuple_zip_compare {

  template <template <typename...> class Tup1,
            template <typename...> class Tup2, typename... A, typename... B,
            std::size_t... S>
  std::array<bool, sizeof...(A)> invoke_with_seq(Tup1<A...> t1, Tup2<B...> t2,
                                                 seq<S...> s) {
    return {Func<typename std::tuple_element<S, A...>::type,
                 typename std::tuple_element<S, B...>>::type >
            (std::get<S>(t1), std::get<S>(t2))...};
  }
  template <template <typename...> class Tup1,
            template <typename...> class Tup2, typename... A, typename... B>
  std::array<bool, sizeof...(A)> invoke(Tup1<A...> t1, Tup2<B...> t2) {
    static_assert(sizeof...(A) == sizeof...(B),
                  "The tuple sizes must be the same");
    return invoke_with_seq(t1, t2, typename gens<sizeof...(A)>::type());
  }
};

} // namespace _internal

template <int i, template <typename T> class AutoType, typename... T>
class tagged_tuple {
public:
  using type = std::tuple<T...>;

  template <typename... U,
            typename = typename std::enable_if<std::is_convertible<
                std::tuple<U...>,
                std::tuple<typename AutoType<T>::type...>>::value>::type>
  tagged_tuple(std::tuple<U...> tuple) : m_tuple(tuple) {}

  int m_tag = i;
  std::tuple<typename AutoType<T>::type...> m_tuple;
};

template <int i, typename Variant, typename... Rest> class transient_tag;

template <int i, typename Variant> class transient_tag<i, Variant> {
public:
  transient_tag() {}

  template <typename = typename std::enable_if<
                std::is_convertible<int, Variant>::value>::type>
  operator Variant() {
    return Variant(i);
  }
};

template <int i, typename Variant, typename Tag, typename... Args>
class transient_tag<i, Variant, Tag, Args...> {
public:
  transient_tag(const Args &... args) : m_tuple(args...) {}

  template <typename = typename std::enable_if<
                std::is_convertible<std::tuple<Args...>, Tag>::value>::type>
  operator Variant() {
    return Variant(i, Tag(m_tuple));
  }

  std::tuple<Args...> m_tuple;
};

template <int i, template <typename...> class Variant>
class transient_template_simple_tag {
public:
  template <typename... VariantTypes,
            typename = typename std::enable_if<std::is_convertible<
                int, Variant<VariantTypes...>>::value>::type>
  operator Variant<VariantTypes...>() const {
    return Variant<VariantTypes...>(i);
  }
};

template <int i, template <typename...> class Variant,
          template <typename...> class Tag, typename... Args>
class transient_template_complex_tag {
public:
  transient_template_complex_tag(const Args &... args) : m_tuple(args...) {}

  template <typename... VariantTypes,
            typename = typename std::enable_if<std::is_convertible<
                int, Variant<VariantTypes...>>::value>::type>
  operator Variant<VariantTypes...>() const {
    return Variant<VariantTypes...>(i, Tag<VariantTypes...>(m_tuple));
  }

  std::tuple<Args...> m_tuple;
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

struct C {
  C(int i) {}
};

namespace Tree {

template <typename K, typename V> class t;

namespace _internal_Tree {
template <typename K, typename V> class impl_Node2;

class transient_Leaf;
template <typename T1, typename T2, typename T3, typename T4>
class transient_Node2;
} // namespace _internal_Tree

_internal_Tree::transient_Leaf Leaf();
template <typename T1, typename T2, typename T3, typename T4>
_internal_Tree::transient_Node2<T1, T2, T3, T4> Node2();

namespace _internal_Tree {}

} // namespace Tree

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
  auto c1 = variad::transient_tag<0, C>();
  return 0;
}

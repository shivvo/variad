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
  template <typename B, typename = typename std::enable_if<
                            std::is_convertible<B, A>::value>::type>
  ref(const B &raw_data) : m_data(std::make_shared<A>(raw_data)) {}
  template <typename B, typename = typename std::enable_if<
                            std::is_convertible<B, A>::value>::type>
  ref(B &&raw_data) : m_data(std::make_shared<A>(std::move(raw_data))) {}

  operator const A &() { return *m_data; }
  operator const std::shared_ptr<A> &() { return m_data; }

private:
  std::shared_ptr<A> m_data;
};

template <typename T> struct remove_cvref {
  using type =
      typename std::remove_cv<typename std::remove_reference<T>::type>::type;
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
                 typename std::tuple_element<S, B...>::type>()(
        std::get<S>(t1), std::get<S>(t2))...};
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
template <typename K, typename V> class repr_Node2;

class transient_Leaf;
template <typename T1, typename T2, typename T3, typename T4>
class transient_Node2;
} // namespace _internal_Tree

template <typename T1, typename T2, typename T3, typename T4>
_internal_Tree::transient_Node2<T1, T2, T3, T4> Node2(T1, T2, T3, T4);

namespace _internal_Tree {

template <typename K, typename V, typename T> struct auto_ptrize {
  using type = typename std::conditional<
      std::is_same<typename ::variad::remove_cvref<T>::type, t<K, V>>::value,
      ::variad::ref<t<K, V>>, typename ::variad::remove_cvref<T>::type>::type;
};

template <typename K, typename V, typename T> struct tagdata_type {
  using type =
      typename auto_ptrize<K, V,
                           typename ::variad::remove_cvref<T>::type>::type;
};

template <typename K, typename V> class repr_Node2 {
private:
  repr_Node2(const typename tagdata_type<K, V, K>::type &arg0,
             const typename tagdata_type<K, V, V>::type &arg1,
             const typename tagdata_type<K, V, t<K, V>>::type &arg2,
             const typename tagdata_type<K, V, t<K, V>>::type &arg3)
      : m_arg0(arg0), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) {}

  const typename tagdata_type<K, V, K>::type &arg0() { return arg0; };
  const typename tagdata_type<K, V, V>::type &arg1() { return arg1; }
  const typename tagdata_type<K, V, t<K, V>>::type &arg2() { return arg2; };
  const typename tagdata_type<K, V, t<K, V>>::type &arg3() { return arg3; };

  typename tagdata_type<K, V, K>::type m_arg0;
  typename tagdata_type<K, V, V>::type m_arg1;
  typename tagdata_type<K, V, t<K, V>>::type m_arg2;
  typename tagdata_type<K, V, t<K, V>>::type m_arg3;

  template <typename T0, typename T1, typename T2, typename T3>
  friend class transient_Node2;
};
} // namespace _internal_Tree

template <typename K, typename V> class t {
public:
  t(const t &other) {
    m_tag = other.m_tag;
    if (other.m_tag == 1) {
      m_dtag1 = other.m_dtag1;
    }
  }
  t(t &&other) {
    m_tag = other.m_tag;
    if (other.m_tag == 1) {
      m_dtag1 = std::move(other.m_dtag1);
    }
  }
  ~t() {
    if (m_tag == 1) {
      m_dtag1.~repr_Node2();
    }
  }

private:
  t(int i) : m_tag(i) {}
  t(int i, const _internal_Tree::repr_Node2<K, V> &dtag1)
      : m_tag(i), m_dtag1(dtag1) {}

  int m_tag;
  union {
    _internal_Tree::repr_Node2<K, V> m_dtag1;
  };

  friend class _internal_Tree::transient_Leaf;
  template <typename T0, typename T1, typename T2, typename T3>
  friend class _internal_Tree::transient_Node2;
};

namespace _internal_Tree {

class transient_Leaf {
public:
  template <typename K, typename V> operator t<K, V>() const { return t<K, V>(0); }
};

template <typename T0, typename T1, typename T2, typename T3>
class transient_Node2 {
public:
  template <typename K, typename V> operator t<K, V>() const {
    return t<K, V>(1, repr_Node2<K, V>(m_arg0, m_arg1, m_arg2, m_arg3));
  }

private:
  transient_Node2(T0 arg0, T1 arg1, T2 arg2, T3 arg3)
      : m_arg0(arg0), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) {}

  T0 m_arg0;
  T1 m_arg1;
  T2 m_arg2;
  T3 m_arg3;

  friend transient_Node2<T0, T1, T2, T3> Node2<T0, T1, T2, T3>(T0, T1, T2,
                                                                     T3);
};

} // namespace _internal_Tree

const _internal_Tree::transient_Leaf Leaf = _internal_Tree::transient_Leaf();

template <typename T1, typename T2, typename T3, typename T4>
_internal_Tree::transient_Node2<T1, T2, T3, T4> Node2(T1 arg0, T2 arg1, T3 arg2,
                                                      T4 arg3) {
  return std::move(
      _internal_Tree::transient_Node2<T1, T2, T3, T4>(arg0, arg1, arg2, arg3));
}

} // namespace Tree

int main(int argc, char **argv) {
  auto a1 = std::make_shared<A>(B());
  auto a2 = std::make_shared<A>(A());
  auto c1 = variad::transient_tag<0, C>();
  std::cout
      << "is transient Leaf convertible to variad::ref<Tree::t> "
      << std::is_convertible<Tree::_internal_Tree::transient_Leaf,
                             ::variad::ref<Tree::t<std::string, int>>>::value
      << std::endl;

  Tree::t<std::string, std::size_t> tree1 = Tree::Leaf;
  Tree::t<std::string, std::size_t> tree2 =
      Tree::Node2("a", 2, Tree::Leaf, Tree::Leaf);

  Tree::t<std::string, std::size_t> tree3 =
      Tree::Node2("b", 3, Tree::Node2("c", 4, Tree::Leaf, tree1), tree2);

  return 0;
}

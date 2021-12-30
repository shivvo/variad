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

template <typename K, typename V> class BinaryTree {
private:
  class launder;

public:
  class transient {
    class Leaf {
      friend class launder;
    };
    template <typename T1, typename T2, typename T3, typename T4> class Node {
      friend class launder;
    };
  };

private:
  template <typename T> struct raw_type {
    using type =
        typename std::remove_cv<typename std::remove_reference<T>>::type;
  };
  template <typename T> struct auto_ptr_type {
    using type = typename std::conditional<
        std::is_same<typename raw_type<T>::type, BinaryTree<K, V>>::value, T,
        std::shared_ptr<T>>::type;
  };

  template <typename T> struct tagdata_type {
    using type = typename auto_ptr_type<typename raw_type<T>::type>::type;
  };
};

int main(int argc, char **argv) { return 0; }

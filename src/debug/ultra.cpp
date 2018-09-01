// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Ultra DEBUG
// @snippet ultra_debug
// @alias vector_myvector myvector
#if 1
/// --- Ultra DEBUG {{{ ///
#ifdef DEBUG

template < class T >
struct myvector : public vector< T > {
  T &operator[](int i) {
    struct CannotAccessNullPointer {} ex;
    if(i < 0 || (int) vector< T >::size() <= i) {
      DEBUG_OUT << "accessed " << i << " but size is " << vector< T >::size() << endl;
      throw ex;
    }
    return vector< T >::operator[](i);
  }
  const T &operator[](int i) const {
    struct CannotAccessNullPointer {} ex;
    if(i < 0 || (int) vector< T >::size() <= i) {
      DEBUG_OUT << "accessed " << i << " but size is " << vector< T >::size() << endl;
      throw ex;
    }
    return vector< T >::operator[](i);
  }
  myvector(size_t n = 0, T t = T()) : vector< T >(n, t) {}
  template < class InputIter, class = typename iterator_traits< InputIter >::value_type >
  myvector(InputIter first, InputIter last) : vector< T >(first, last) {}
};

#define vector myvector

#endif
/// }}}--- ///
#endif

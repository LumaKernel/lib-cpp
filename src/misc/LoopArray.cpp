// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Loop Array
// @snippet looparray
// @alias array_loop myarray

// LoopArray {{{
#include <array>
template < class T, size_t N >
class LoopArray : public array< T, N > {
  using Index = ll;

public:
  T &at(Index i) { return *this[i]; }
  const T &at(Index i) const { return *this[i]; }
  T &operator[](Index i) {
    i %= Index(N);
    if(i < 0) i += Index(N);
    return array< T, N >::operator[](i);
  }
  const T &operator[](Index i) const {
    i %= Index(N);
    if(i < 0) i += Index(N);
    return array< T, N >::operator[](i);
  }
};
// }}}

template < class T, size_t N >
using myarray = LoopArray< T, N >;

// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ ternary search
// @snippet ternary_search
// @alias sanbu_tansaku search_ternary

// ternary_search {{{
// needed iteration : log((hi - lo) / eps) / log(3. / 2)
template < class T, class Func >
T ternary_search(T lo, T hi, Func f, int c, bool maximize = 0) {
  for(int i = 0; i < c; i++) {
    T m1 = lo + (hi - lo) / 3;
    T m2 = lo + (hi - lo) * 2 / 3;
    if(maximize ? f(m1) > f(m2) : f(m1) < f(m2))
      hi = m2;
    else
      lo = m1;
  }
  return (lo + hi) / 2;
}

// needed iteration : log((hi - lo) / eps) / log(phi)
#include <cmath>
template < class T, class Func >
T golden_search(T lo, T hi, Func f, int c, bool maximize = 0) {
  const double phi_inv = 2 / (1 + sqrt(5));
  T v1, v2;
  bool f1 = 1, f2 = 1;
  for(int i = 0; i < c; i++) {
    T m1 = lo + (hi - lo) * (phi_inv * phi_inv);
    T m2 = lo + (hi - lo) * phi_inv;
    v1 = f1 ? f(m1) : v1;
    v2 = f2 ? f(m2) : v2;
    f1 = f2 = 0;
    if(maximize ? v1 > v2 : v1 < v2)
      hi = m2, v2 = v1, f1 = 1;
    else
      lo = m1, v1 = v2, f2 = 1;
  }
  return (lo + hi) / 2;
}
// }}}

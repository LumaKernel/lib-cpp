// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     fftlongdouble
// @alias       fftld
// @options     head
// @name FFT with long double Library
/// --- FFT with long double Library {{{ ///

using C = complex< ld >;
using VC = vector< C >;

// using FFT
VC dft(VC a, bool inverse = false) {
  int n = a.size();
  if(n == 1) return a;
  VC odd(n / 2), even(n / 2);
  for(int i = 0; i < n / 2; i++) odd[i] = a[i * 2 + 1];
  for(int i = 0; i < n / 2; i++) even[i] = a[i * 2];
  odd = dft(odd);
  even = dft(even);
  C zeta = C(cos(2 * PI / n), sin(2 * PI / n));
  if(inverse) zeta = C(1, 0) / zeta;
  C powZeta = C(1, 0);
  REP(_i, n) {
    int i = _i;
    if(inverse) i = (n - i) % n;
    // powZeta = pow(zeta, i)
    a[_i] = even[i % (n / 2)] + powZeta * odd[i % (n / 2)]; ////
    if(inverse) a[_i] /= n;
    powZeta *= zeta;
  }
  return a;
}

// convolution
VC conv(VC a, VC b) {
  int m = a.size();
  int n = 1;
  while(n < m) n <<= 1;
  a.resize(n, C(0, 0));
  b.resize(n, C(0, 0));
  a = dft(a);
  b = dft(b);
  VC c(n);
  REP(i, n) c[i] = a[i] * b[i];
  return dft(c, true);
}

/// }}}--- ///

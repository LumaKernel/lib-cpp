// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     fftlongdouble
// @alias       fftld
// @options     head
// @name FFT standard

#include <cmath>
#include <complex>
#include <vector>

using Real = long double;
using Complex = complex< Real >;

/// --- FFT standard {{{ ///

// FFT
vector< Complex > dft(vector< Complex > a, bool inverse) {
  constexpr Real PI = 3.14159265358979323846;
  size_t n = a.size(), mask = n - 1;
  static vector< Complex > tmp;
  tmp.resize(n);
  for(size_t i = n >> 1; i >= 1; i >>= 1) {
    Real theta = 2 * PI * i * (inverse ? -1 : 1) / n;
    Complex zeta(cos(theta), sin(theta));
    Complex powZeta = 1;
    for(size_t j = 0, jh = 0; j < n; j += i, ++jh) {
      for(size_t k = 0; k < i; ++k) {
        tmp[j + k] =
            a[((j << 1) & mask) + k] + powZeta * a[(((j << 1) + i) & mask) + k];
      }
      powZeta *= zeta;
    }
    swap(a, tmp);
  }
  if(inverse)
    for(size_t i = 0; i < n; ++i) a[i] /= n;
  return a;
}

// convolution
vector< ll > conv(const vector< ll > &ar, const vector< ll > &br) {
  int deg = ar.size() + br.size() - 1, n = 1;
  while(n < deg) n <<= 1;
  vector< Complex > a(n), b(n);
  for(size_t i = 0; i < ar.size(); ++i) a[i].real(ar[i]);
  for(size_t i = 0; i < br.size(); ++i) b[i].real(br[i]);
  a = dft(a, false), b = dft(b, false);
  for(int i = 0; i < n; ++i) a[i] *= b[i];
  a = dft(a, true);
  vector< ll > cr(n);
  for(int i = 0; i < n; ++i) cr[i] = round(a[i].real());
  return cr;
}

/// }}}--- ///

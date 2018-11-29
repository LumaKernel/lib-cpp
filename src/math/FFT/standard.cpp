// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     fft
// @alias     conv convfast
// @options     head
// @name FFT standard

/// --- FFT standard {{{ ///
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>
#include <vector>

template < int MAX_N, class Real, class Complex = complex< Real > >
class fft_base {
public:
  // semi-private
  static void fft(Complex *a, size_t n, size_t nh, bool inverse) {
    // assert(n == (1u << nh));
    constexpr Real PI = 3.14159265358979323846;
    size_t mask = n - 1;
    static Complex *tmp = new Complex[MAX_N];
    for(size_t i = n >> 1; i >= 1; i >>= 1) {
      Real theta = 2 * PI * i * (inverse ? -1 : 1) / n;
      Complex zeta(cos(theta), sin(theta));
      Complex powZeta(1);
      for(size_t j = 0; j < n; j += i) {
        for(size_t k = 0; k < i; ++k) {
          tmp[j + k] =
              a[((j << 1) & mask) | k] + powZeta * a[(((j << 1) | i) & mask) | k];
        }
        powZeta *= zeta;
      }
      swap(a, tmp);
    }
    if(nh & 1) {
      swap(a, tmp);
      for(size_t i = 0; i < n; ++i) a[i] = tmp[i];
    }
    if(inverse)
      for(size_t i = 0; i < n; ++i) a[i] /= n;
  }

  // c[k] = sum(k = i + j, a[i] * b[j])
  static vector< ll > conv(const vector< ll > &ar, const vector< ll > &br) {
    int nt = ar.size() + br.size() - 1, n = 1, nh = 0;
    while(n < nt) n <<= 1, ++nh;
    static Complex *a = new Complex[MAX_N], *b = new Complex[MAX_N];
    for(size_t i = 0; i < ar.size(); ++i) a[i].real(ar[i]);
    for(size_t i = 0; i < br.size(); ++i) b[i].real(br[i]);
    fft(a, n, nh, 0), fft(b, n, nh, 0);
    for(int i = 0; i < n; ++i) a[i] *= b[i];
    fft(a, n, nh, 1);
    vector< ll > cr(n);
    for(int i = 0; i < n; ++i) cr[i] = round(a[i].real());
    return cr;
  }

  // c[k] = sum(k = i + j, a[i] * b[j])
  static vector< ll > convFast(const vector< ll > &ar, const vector< ll > &br) {
    int deg = ar.size() + br.size() - 1, n = 1, nh = 0;
    while(n < deg) n <<= 1, ++nh;
    static Complex *a = new Complex[MAX_N], *c = new Complex[MAX_N];
    for(size_t i = 0; i < n; ++i) a[i] = 0;
    for(size_t i = 0; i < ar.size(); ++i) a[i].real(ar[i]);
    for(size_t i = 0; i < br.size(); ++i) a[i].imag(br[i]);
    fft(a, n, nh, 0);
    for(int i = 0; i < n; ++i) {
      int j = i == 0 ? 0 : n - i;
      c[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j])) * Complex(0, -.25);
    }
    fft(c, n, nh, 1);
    vector< ll > cr(n);
    for(int i = 0; i < n; ++i) cr[i] = round(c[i].real());
    return cr;
  }
};

/// }}}--- ///

// N * 4 is enough for 1st param
using fft = fft_base< 1 << 20, double >;

// @new
// @ FFT 2D
// @snippet fft2
// @alias conv2

// require FFT standard
/// --- FFT 2D {{{ ///

template < int MAX_N, int MAX_NM, class Real, class Complex = complex< Real > >
class fft2_base : public fft_base< MAX_N, Real, Complex > {
  // semi-private
  template < class T >
  static void transpose(T *a, size_t n, size_t m, size_t mh) {
    // assert(m == (1u << mh));
    if(n == m) {
      for(size_t i = 0; i < n - 1; ++i)
        for(size_t j = i + 1; j < m; ++j) swap(a[(i << mh) | j], a[(j << mh) | i]);
    } else {
      static T *tmp = new T[MAX_NM];
      for(size_t i = 0; i < n * m; ++i) tmp[i] = a[i];
      for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < m; ++j) a[(i << mh) | j] = tmp[(j << mh) | i];
    }
  }

  // semi-private
  static void fft2(Complex *a, size_t n, size_t m, size_t nh, size_t mh, bool inverse) {
    // assert(n == (1u << nh));
    // assert(m == (1u << mh));
    for(int t = 0; t < 2; ++t) {
      for(size_t i = 0; i < n * m; i += m) fft(a + i, m, mh, inverse);
      transpose(a, n, m, mh);
      swap(n, m);
      swap(nh, mh);
    }
  }

  static vector< vector< ll > > conv2Fast(const vector< vector< ll > > &ar,
                                          const vector< vector< ll > > &br) {
    int nt = ar.size() + br.size() - 1, mt = ar[0].size() + br[0].size() - 1;
    int n = 1, m = 1, nh = 0, mh = 0;
    while(n < nt) n <<= 1, ++nh;
    while(m < mt) m <<= 1, ++mh;
    static Complex *a = new Complex[MAX_NM], *c = new Complex[MAX_NM];
    for(size_t i = 0; i < ar.size(); ++i)
      for(size_t j = 0; j < ar[0].size(); ++j) a[(i << mh) | j].real(ar[i][j]);
    for(size_t i = 0; i < br.size(); ++i)
      for(size_t j = 0; j < br[0].size(); ++j) a[(i << mh) | j].imag(br[i][j]);
    fft2(a, n, m, nh, mh, 0);
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < m; ++j) {
        int k = i == 0 ? 0 : n - i;
        int l = j == 0 ? 0 : m - j;
        c[(i << mh) | j] = (a[(i << mh) | j] + conj(a[(k << mh) | l])) *
                           (a[(i << mh) | j] - conj(a[(k << mh) | l])) * Complex(0, -.25);
      }
    fft2(c, n, m, nh, mh, 1);
    vector< vector< ll > > cr(n, vector< ll >(m));
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < m; ++j) cr[i][j] = round(c[(i << mh) | j].real());
    return cr;
  }
};

/// }}}--- ///

using fft2 = fft2_base< 1 << 22, 1 << 22, double >;

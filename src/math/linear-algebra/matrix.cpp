// @ Matrix mult pow Library
// @snippet matrix

// mult(a, b), makeE(n), pow(a, k)
/// --- Matrix mult pow Library {{{ ///
#include <vector>
template < class T >
std::vector< std::vector< T > > mult(std::vector< std::vector< T > > a,
                                     std::vector< std::vector< T > > b) {
  assert(a[0].size() == b.size());
  std::vector< std::vector< T > > res(a.size(), std::vector< T >(b[0].size(), 0));
  for(std::size_t i = 0; i < a.size(); i++) {
    for(std::size_t j = 0; j < b[0].size(); j++) {
      for(std::size_t k = 0; k < b.size(); k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return res;
}

template < class T >
std::vector< std::vector< T > > makeE(std::size_t n) {
  std::vector< std::vector< T > > r(n, std::vector< T >(n, 0));
  for(std::size_t i = 0; i < n; i++) r[i][i] = 1;
  return r;
}

template < class T >
std::vector< std::vector< T > > pow(std::vector< std::vector< T > > a,
                                    unsigned long long k) {
  assert(a.size() == a[0].size());
  std::vector< std::vector< T > > r = makeE< T >(a.size());
  while(k) {
    if(k & 1) r = mult(r, a);
    a = mult(a, a);
    k >>= 1;
  }
  return r;
}
/// }}}--- ///

// using Vec = std::vector< modint >;
// using Mat = std::vector< Vec >;

// @ Kitamasa Library
// @snippet kitamasa

// kitamasa(c, u, v) {{{
#include <vector>
template < class T >
std::vector< T > kitamasa(const std::vector< T > &c, const std::vector< T > &u,
                          const std::vector< T > &v) {
  using size_type = std::size_t;
  size_type k = c.size();
  std::vector< T > r(2 * k - 1);
  for(size_type i = 0; i < k; i++)
    for(size_type j = 0; j < k; j++) r[i + j] += u[i] * v[j];
  for(size_type i = 2 * k - 2; i >= k; i--)
    for(size_type j = 0; j < k; j++) r[i - k + j] += r[i] * c[j];
  r.resize(k);
  return r;
}
// }}}

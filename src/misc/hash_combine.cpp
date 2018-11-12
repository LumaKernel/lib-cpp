// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ hash_combine
// @snippet hashcombine

/// hash_combine {{{
template < class T >
void hash_combine(size_t& seed, T const& v) {
  seed ^= hash< T >{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
/// }}}

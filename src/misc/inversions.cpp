// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ inversions
// @snippet inversions
// @alias hantensuu

// require BIT
// inversions {{{
#include <iterator>
#include <vector>
template < class InputIter, class T = typename iterator_traits< InputIter >::value_type >
vector< int > inversions(InputIter first, InputIter last, const bool right = 0) {
  int n = distance(first, last);
  vector< int > ret(n);
  BIT<> bit(n);
  int i = 0;
  InputIter ite = first;
  vector< pair< T, int > > v(n);
  for(; i < n; ++ite, ++i) v[i] = make_pair(*ite, i);
  if(right)
    sort(v.begin(), v.end());
  else
    sort(v.rbegin(), v.rend());
  for(int i = 0; i < n; i++) {
    ret[v[i].second] = right ? i - bit.sum(v[i].second) : bit.sum(v[i].second);
    bit.add(v[i].second, 1);
  }
  return ret;
}

template < class T >
vector< int > inversions(vector< T > v, bool right = 0) {
  return inversions(v.begin(), v.end(), right);
}
// }}}

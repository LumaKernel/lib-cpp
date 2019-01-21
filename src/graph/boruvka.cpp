// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ boruvka
// @snippet boruvka
// @alias mst_boruvka

// require UnionFind
// F(component-size, belongs) -> vector<(cost, to)>
// boruvka {{{
#include <vector>
template < class T, class F >
T boruvka(int n, const F &f) {
  UF uf(n);
  T res(0);
  bool update = 1;
  vector< int > belongs(n), rev(n);
  while(update) {
    update = 0;
    int ptr = 0;
    for(int i = 0; i < n; i++)
      if(i == uf.find(i)) rev[ptr] = i, belongs[i] = ptr++;
    for(int i = 0; i < n; i++) belongs[i] = belongs[uf.find(i)];
    auto v = f(ptr, belongs);
    for(int i = 0; i < ptr; i++)
      if(v[i].second >= 0 && uf.unite(rev[i], rev[v[i].second]))
        res += v[i].first, update = 1;
    if(!update) break;
  }
  return res;
}
// }}}

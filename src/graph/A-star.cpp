// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ A-star
// @snippet a_star

const ll inf = 1e18;
// A* {{{
{
  using P = tuple< ll, ll, int >;
  priority_queue< P, vector< P >, greater< P > > pq;
  vector< ll > dist(n, inf);
  pq.emplace(0, 0, s);
  ll res = inf;
  dist[i] = 0;
  while(pq.size()) {
    ll di, rdi;
    int i;
    tie(di, rdi, i) = pq.top();
    pq.pop();
    if(i == t) {
      res = rdi;
      break;
    }
    if(dist[i] < di) continue;
    for(auto to : g[i]) {
      int j, co;
      tie(j, co) = to;
      if(hstar(j) == inf) continue;
      ll nrdi = rdi + co;
      if(dist[i] > nrdi) pq.emplace(nrdi + hstar(j), nrdi, j);
    }
  }
}
// }}}

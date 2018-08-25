// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name Hu-Tucker Algorithm Library
// @snippet     hutucker
// @alias       bst
// @title Hu-Tuckerのアルゴリズム

// calculate value of optimal alphabetic binary search tree
// if you want to construct? you can do it!
/// --- Hu-Tucker Algorithm Library {{{ ///
template < class Heap, class T = long long >
T HuTucker(const vector< T > &w) {
  using P = pair< T, int >; // value, index
  int n = w.size();
  function< T(Heap * &a) > calc = [](Heap *&a) { ////
    return a->val.first + second(a)->val.first;
  };
  vector< int > rig(n), lef(n);
  vector< int > removed(n), used(n);
  vector< Heap * > dat(n);
  function< bool(int) > isAvailable = [&](int idx) {
    if(idx < 0) return true;
    if(idx >= n) idx -= n; /////
    return !used[idx];
  };
  function< void(Heap *&, int, int) > check = [&](Heap *&top, int gid,
                                                  int idx) {
    if(idx < 0) return;
    if(idx < n) {
      used[idx] = 1;
      if(lef[gid] >= 0) {
        top = meld(top, dat[lef[gid]]);
        removed[lef[gid]] = 1;
        lef[gid] = lef[lef[gid]];
        if(lef[gid] >= 0) rig[lef[gid]] = gid; ///
      }
    } else {
      used[idx - n] = 1;
      if(rig[gid] < n - 1) {
        top = meld(top, dat[rig[gid]]);
        removed[rig[gid]] = 1;
        rig[gid] = rig[rig[gid]];
        if(rig[gid] < n - 1) lef[rig[gid]] = gid; ///
      }
    }
  };
  priority_queue< P, vector< P >, greater< P > > pq; ///
  for(int i = 0; i < n - 1; i++) {
    auto *a = new Heap(P(w[i], i)), *b = new Heap(P(w[i + 1], i + 1 + n));
    dat[i] = meld(a, b);
    pq.emplace(calc(dat[i]), i); ///
    lef[i] = i - 1;
    rig[i] = i + 1;
  }
  ll ans = 0;
  while(pq.size()) {
    int i = pq.top().second;
    auto top = dat[i];
    pq.pop();
    if(removed[i]) continue;
    P p0 = top->val;
    P p1 = second(top)->val;
    pop(top);
    pop(top);
    bool c0 = isAvailable(p0.second);
    bool c1 = isAvailable(p1.second);
    if(!c0 || !c1) {
      if(c0) push(top, p0);
      if(c1) push(top, p1);
      dat[i] = top;
      if(top != nullptr && top->l != nullptr) {
        pq.emplace(calc(top), i); ///
      }
      continue;
    }
    T nval = p0.first + p1.first;
    ans += nval;
    check(top, i, p0.second);
    check(top, i, p1.second);
    if(top != nullptr) {
      push(top, P(nval, -1));
      dat[i] = top;
      pq.emplace(calc(top), i); ///
    }
  }
  return ans;
}
/// }}}--- ///

// usage :
// HuTucker< SkewHeap< pair<long long, int> > >(w)

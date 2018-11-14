// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name Drivable Dynamic SegmentTree Library
// @snippet     drivablednamicseg
// @alias       dynamicdrivableseg segdynamicdrivable
// WARN : これはデータがstaticかつactのみの利用で使える(微妙)
// constructor(int sizex, int sizey, T identity, func merge)
// WARN : query in range by yourself!
/// --- Drivable Dynamic SegmentTree Library {{{ ///

template < class T >
struct DrivableDynamicSegTree {
  struct Node {
    T value;
    Node *l = nullptr, *r = nullptr;
    Node(T value) : value(value) {}
  };
  Node *top;
  int n;
  T identity;
  DrivableDynamicSegTree(int t, T identity) : identity(identity) {
    n = 1;
    while(t > n) n <<= 1;
    top = new Node(identity);
  }

public:
  void update(int i, function< void(T &) > const &f) {
    update(i, f, 0, n, top);
  }
  void init(function< void(T &) > const &f) { init(f, top); }

private:
  // from top
  void init(function< void(T &) > const &f, Node *node) {
    if(node == nullptr) return;
    f(node->value);
    init(f, node->l);
    init(f, node->r);
  }
  void update(int i, function< void(T &) > const &f, int l, int r,
              Node *&node) {
    if(i + 1 <= l || r <= i) return;
    if(node == nullptr) node = new Node(identity);
    dump(l, r);
    f(node->value);
    if(i <= l && r <= i + 1) return;
    update(i, f, l, (l + r) / 2, node->l);
    update(i, f, (l + r) / 2, r, node->r);
  }

public:
  template < class U, class H, class M >
  U query(int a, int b, H h, M merge) {
    return query< U >(a, b, h, merge, 0, n, top);
  }

private:
  // template<class U>
  template < class U, class H, class M >
  U query(int a, int b, H h, M merge, int l, int r, Node *node) {
    if(node == nullptr) return P(inf, -inf);  // todo
    if(b <= l || r <= a) return P(inf, -inf); // todo
    if(a <= l && r <= b) {
      dump(l, r);
      return h(node->value);
    }
    return merge(query< U >(a, b, h, merge, l, (l + r) / 2, node->l),
                 query< U >(a, b, h, merge, (l + r) / 2, r, node->r));
  }
};

/// }}}--- ///
// using Q = tuple<vector<int>, map<int, int>, RMQ>;
// updateで収集
// initで座圧
// updateで更新
// queryで使用

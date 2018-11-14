// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @snippet     dynamicseg2d
// @alias        seg2ddynamin 2dsegdynamic
// @ Dynamic 2D SegmentTree

// Deprecated
// これはデータがstaticかつactのみの利用で使える(微妙)
// 静的かつオフラインならFC-segをつかおう
// constructor(int sizex, int sizey, T identity, func merge)
// WARN : query in range by yourself!
/// --- Dynamic 2D SegmentTree {{{ ///

template < class T >
struct DynamicSegTree2D {
  struct Node {
    T value;
    Node *l = nullptr, *r = nullptr, *c = nullptr;
    Node(T value) : value(value) {}
  };
  Node *top;
  int sizex, sizey;
  T identity;
  function< T(T, T) > merge;
  DynamicSegTree2D(int tx, int ty, T identity, function< T(T, T) > merge)
      : identity(identity), merge(merge) {
    sizex = sizey = 1;
    while(tx > sizex) sizex <<= 1;
    while(ty > sizey) sizey <<= 1;
    top = new Node(identity);
  }

public:
  void set(int x, int y, T const &val) { setx(x, y, val, 0, sizex, top, 1); }
  void act(int x, int y, T const &val) { setx(x, y, val, 0, sizex, top, 0); }

private:
  void setx(int x, int y, T const &val, int sxl, int sxr, Node *&node,
            int set) {
    if(x + 1 <= sxl || sxr <= x) return;
    if(node == nullptr) node = new Node(identity);
    if(x <= sxl && sxr <= x + 1) {
      sety(y, val, 0, sizey, node->c, set);
      return;
    }
    sety(y, val, 0, sizey, node->c, 0);
    setx(x, y, val, sxl, (sxl + sxr) / 2, node->l, set);
    setx(x, y, val, (sxl + sxr) / 2, sxr, node->r, set);
  }
  void sety(int y, T const &val, int syl, int syr, Node *&node, int set) {
    if(y + 1 <= syl || syr <= y) return;
    if(node == nullptr) node = new Node(identity);
    if(y <= syl && syr <= y + 1) {
      node->value = set ? val : merge(node->value, val);
      return;
    }
    sety(y, val, syl, (syl + syr) / 2, node->l, set);
    sety(y, val, (syl + syr) / 2, syr, node->r, set);
    node->value = merge(get(node->l), get(node->r));
  }
  T get(Node *node) { return node == nullptr ? identity : node->value; }

public:
  T query(int xl, int xr, int yl, int yr) {
    return queryx(xl, xr, yl, yr, 0, sizex, top);
  }

private:
  T queryx(int xl, int xr, int yl, int yr, int sxl, int sxr, Node *node) {
    if(node == nullptr) return identity;
    if(xr <= sxl || sxr <= xl) return identity;
    if(xl <= sxl && sxr <= xr) return queryy(yl, yr, 0, sizey, node->c);
    return merge(queryx(xl, xr, yl, yr, sxl, (sxl + sxr) / 2, node->l),
                 queryx(xl, xr, yl, yr, (sxl + sxr) / 2, sxr, node->r));
  }
  T queryy(int yl, int yr, int syl, int syr, Node *node) {
    if(node == nullptr) return identity;
    if(yr <= syl || syr <= yl) return identity;
    if(yl <= syl && syr <= yr) return node->value;
    return merge(queryy(yl, yr, syl, (syl + syr) / 2, node->l),
                 queryy(yl, yr, (syl + syr) / 2, syr, node->r));
  }
};

/// }}}--- ///

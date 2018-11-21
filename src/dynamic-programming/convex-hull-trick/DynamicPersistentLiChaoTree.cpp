// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Dynamic Persistent Li-Chao Tree
// @snippet dyanmiclichaotree
// @alias dynamiccht_lichao lichao_dynamic

// DynamicPersistentLiChaoTree<T, Comp> (L, R [, EPS])
// - x is [L, R]
// - (R - L) / EPS is in T's significand
// - maximize : let Comp = greater<T>
// .add(a, b [, time]) : f(x) = ax + b
// .add(a, b, l, r [, time]) : f(x) = ax + b (x in [l, r])
// .query(x [, time])
// SPEED UP : new without deleting
/// --- Dynamic Persistent Li-Chao Tree {{{ ///

#include <functional>
#include <utility>
#include <vector>

template < class T = long long, class Comp = less< T > >
struct DynamicPersistentLiChaoTree {
  static Comp comp;

  using Line = pair< T, T >;
  static inline T f(const Line& line, T x) { return line.first * x + line.second; }
  struct Node {
    Line line;
    bool used;
    Node *l = nullptr, *r = nullptr;
    Node() : used(false) {}
    Node(Line line) : line(line), used(true) {}
  };

  Node* NIL = new Node;
  Node* lastRoot = nullptr;
  vector< Node* > roots;

  T L, R;
  T EPS;
  DynamicPersistentLiChaoTree(const T& L, const T& R, const T& EPS = T(1))
      : L(L), R(R), EPS(EPS) {
    this->R += this->EPS;
    NIL->l = NIL;
    NIL->r = NIL;
    roots.push_back(NIL);
  }
  int add(const T& a, const T& b, int time = -1) { return add(a, b, L, R, time); }
  // [lx, rx]
  int add(const T& a, const T& b, const T& lx, const T& rx, int time = -1) {
    if(time == -1) time = roots.size() - 1;
    Node* newRoot;
    add(max(lx, L), min(rx + EPS, R), newRoot, roots[time], L, R, Line(a, b));
    roots.push_back(newRoot);
    return roots.size() - 1;
  }

private:
  void add(const T& a, const T& b, Node*& node, Node* prevNode, const T& l, const T& r,
           Line line) {
    node = new Node;
    *node = *prevNode;
    if(b - EPS < l || r < a + EPS) return;
    if(a - EPS < l && r < b + EPS) {
      if(!node->used) {
        node->line = line;
        node->used = 1;
        return;
      }
      T ly = f(line, l), ry = f(line, r - EPS);
      T nly = f(node->line, l), nry = f(node->line, r - EPS);
      if(comp(nly, ly) && comp(nry, ry)) return;
      if(comp(ly, nly) && comp(ry, nry)) {
        node->line = line;
        return;
      }
      if(r - l <= EPS) return;
      T m = (l + r) / 2;
      if(comp(nly, ly)) swap(node->line, line);
      if(comp(f(line, m), f(node->line, m))) {
        swap(node->line, line);
        add(a, b, node->r, prevNode->r, m, r, line);
      } else {
        add(a, b, node->l, prevNode->l, l, m, line);
      }
      return;
    }
    add(a, b, node->l, prevNode->l, l, (l + r) / 2, line);
    add(a, b, node->r, prevNode->r, (l + r) / 2, r, line);
  }

public:
  T query(const T& x, int time = -1) { return f(get(x, time), x); }
  Line get(const T& x, int time = -1) {
    if(time == -1) time = roots.size() - 1;
    return get(x, roots[time], L, R)->line;
  }

private:
  Node* get(const T& x, Node* node, const T& l, const T& r) {
    if(node == NIL) return NIL;
    Node* p;
    if(x < (l + r) / 2) {
      p = get(x, node->l, l, (l + r) / 2);
    } else {
      p = get(x, node->r, (l + r) / 2, r);
    }
    return node == NIL || (p != NIL && comp(f(p->line, x), f(node->line, x))) ? p : node;
  }
};

template < class T, class Comp >
Comp DynamicPersistentLiChaoTree< T, Comp >::comp;

/// }}}--- ///

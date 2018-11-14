// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Dynamic Li-Chao Tree
// @snippet dyanmiclichaotree
// @alias dynamiccht_lichao lichao_dynamic

// DynamicLiChaoTree<T, Comp> (L, R [, EPS])
// - x is [L, R]
// - (R - L) / EPS is in T's significand
// - maximize : let Comp = greater<T>
// .add(a, b) : f(x) = ax + b
// .add(a, b, l, r) : f(x) = ax + b (x in [l, r])
// .query(x)
// SPEED UP : new without deleting
/// --- Dynamic Li-Chao Tree {{{ ///

#include <functional>

template < class T = long long, class Comp = less< T > >
struct DynamicLiChaoTree {
  static Comp comp;

  using Line = pair< T, T >;
  static inline T f(const Line& line, T x) {
    return line.first * x + line.second;
  }
  struct Node {
    Line line;
    bool used;
    Node *l = nullptr, *r = nullptr;
    Node() : used(false) {}
    Node(Line line) : line(line), used(true) {}
    ~Node() {
      delete l;
      delete r;
    }
  };

  Node* top = nullptr;
  T L, R;
  T EPS;
  DynamicLiChaoTree(const T& L, const T& R, const T& EPS = T())
      : L(L), R(R), EPS(EPS) {
    if(this->EPS == T()) this->EPS = T(1);
    this->R += this->EPS;
  }
  ~DynamicLiChaoTree() { delete top; }
  void add(const T& a, const T& b) { add(a, b, L, R); }
  // [lx, rx]
  void add(const T& a, const T& b, const T& lx, const T& rx) {
    add(max(lx, L), min(rx + EPS, R), top, L, R, Line(a, b));
  }

private:
  void add(const T& a, const T& b, Node*& node, const T& l, const T& r,
           Line line) {
    if(b - EPS < l || r < a + EPS) return;
    if(a - EPS < l && r < b + EPS) {
      if(!node || !node->used) {
        if(!node)
          node = new Node(line);
        else
          node->line = line, node->used = 1;
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
        add(a, b, node->r, m, r, line);
      } else {
        add(a, b, node->l, l, m, line);
      }
      return;
    }
    if(!node) node = new Node;
    add(a, b, node->l, l, (l + r) / 2, line);
    add(a, b, node->r, (l + r) / 2, r, line);
  }

public:
  T query(const T& x) { return f(get(x), x); }

  Line get(const T& x) { return get(x, top, L, R)->line; }

private:
  Node* get(const T& x, Node* node, const T& l, const T& r) {
    if(node == nullptr) return nullptr;
    Node* p;
    if(x < (l + r) / 2) {
      p = get(x, node->l, l, (l + r) / 2);
    } else {
      p = get(x, node->r, (l + r) / 2, r);
    }
    return node == nullptr ||
                   (p != nullptr && comp(f(p->line, x), f(node->line, x)))
               ? p
               : node;
  }
};

template < class T, class Comp >
Comp DynamicLiChaoTree< T, Comp >::comp;

/// }}}--- ///

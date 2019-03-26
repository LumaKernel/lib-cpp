// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name LinkCutTree
// @snippet linkcuttree
// @alias hl_decomp_with_lct

// do make(index, Monoid::T value)
// .link(p, c) : [c] is root
// .cut(c) : [c] is not root
// .same(a, b)
// .query(a) : from root to [a]
// node->id
// lc[index] to access nodes
/// --- LinkCutTree {{{ ///
#include <cstdlib>
#include <vector>
template < class M_act >
struct LinkCutTree {
  using Monoid = typename M_act::Monoid;
  using X = typename Monoid::T;
  using M = typename M_act::M;

  // Splay sequence {{{
  struct Splay {
    int id;
    Splay *ch[2] = {nullptr, nullptr}, *p = nullptr;
    X val, accum;
    M lazy = M_act::identity(); ///////
    // size of BST // not of real subtree
    int sz = 1;
    bool isRoot() { return !p || (p->ch[0] != this && p->ch[1] != this); }
    bool rev = false;
    // call before use
    void eval() {
      if(lazy != M_act::identity()) {
        val = M_act::actInto(lazy, 1, val);
        accum = M_act::actInto(lazy, sz, accum);
        if(ch[0]) ch[0]->lazy = M_act::op(lazy, ch[0]->lazy);
        if(ch[1]) ch[1]->lazy = M_act::op(lazy, ch[1]->lazy);
        lazy = M_act::identity();
      }
      if(rev) {
        swap(ch[0], ch[1]);
        if(ch[0]) ch[0]->rev ^= 1;
        if(ch[1]) ch[1]->rev ^= 1;
        // accum = reverse(accum, sz)
        rev = false;
      }
    }
    void evalDown() {
      vector< Splay * > b2t;
      Splay *t = this;
      for(; !t->isRoot(); t = t->p) b2t.emplace_back(t);
      t->eval();
      while(b2t.size()) b2t.back()->eval(), b2t.pop_back();
    }
    X accumulated(Splay *a) { return !a ? Monoid::identity() : a->accum; }
    int size(Splay *a) { return !a ? 0 : a->sz; }
    // call after touch
    void prop() {
      if(ch[0]) ch[0]->eval();
      if(ch[1]) ch[1]->eval();
      sz = size(ch[0]) + 1 + size(ch[1]);
      accum = Monoid::op(Monoid::op(accumulated(ch[0]), val), accumulated(ch[1]));
    }
    Splay(const X &val, int id) : id(id), val(val), accum(val) {}
    Splay *rotate(bool R) {
      Splay *t = ch[!R];
      if((ch[!R] = t->ch[R])) ch[!R]->p = this;
      t->ch[R] = this;
      if((t->p = p)) {
        if(t->p->ch[0] == this) t->p->ch[0] = t;
        if(t->p->ch[1] == this) t->p->ch[1] = t;
      }
      p = t;
      prop(), t->prop();
      return t;
    }
    // bottom-up
    void splay() {
      evalDown();
      while(!isRoot()) {
        Splay *q = p;
        if(q->isRoot()) {
          q->rotate(q->ch[0] == this);
        } else {
          Splay *r = q->p;
          bool V = r->ch[0] == q;
          if(q->ch[!V] == this)
            r->rotate(V);
          else
            q->rotate(!V);
          p->rotate(V);
        }
      }
    }
  };
  // }}}

  Splay *pool;
  LinkCutTree(int n) { pool = (Splay *) malloc(sizeof(Splay) * n); }
  ~LinkCutTree() { free(pool); }
  Splay *operator[](int i) const { return pool + i; }
  Splay *make(int i, const X &x = Monoid::identity()) {
    return new(pool + i) Splay(x, i);
  }
  const X &get(Splay *x) {
    x->splay();
    return x->val;
  }
  void set(Splay *x, const X &val) {
    x->splay();
    x->val = val;
    x->prop();
  }
  Splay *expose(Splay *x) {
    Splay *prv = nullptr, *now = x;
    for(; now; prv = now, now = now->p) {
      now->splay();
      now->ch[1] = prv;
      now->prop();
    }
    x->splay();
    return prv;
  }
  void cut(Splay *c) {
    expose(c);
#ifdef DEBUG
    static const struct CannotCutRoot {} ex;
    if(!c->ch[0]) throw ex;
#endif
    Splay *s = c->ch[0];
    c->ch[0] = nullptr;
    c->prop();
    s->p = nullptr;
  }
  void link(Splay *parent, Splay *child) {
#ifdef DEBUG
    static const struct CannotLinkSameNode {} ex;
    if(same(parent, child)) throw ex;
#endif
    expose(parent), expose(child);
    child->p = parent;
    parent->ch[1] = child;
    parent->prop();
  }
  void evert(Splay *x) {
    expose(x);
    x->rev = true;
  }
  bool same(Splay *a, Splay *b) {
    if(a == b) return true;
    expose(a), expose(b);
    return a->p != nullptr;
  }
  Splay *lca(Splay *a, Splay *b) {
#ifdef DEBUG
    static const struct CannotLCADifferentNode {} ex;
    if(!same(a, b)) throw ex;
#endif
    expose(a), a = expose(b);
    return !a ? b : a;
  }
  void act(Splay *a, const M &m) { expose(a), a->lazy = m; }
  X fold(Splay *a) {
    expose(a);
    return a->accum;
  }
  // root of subtree
  Splay *getRoot(Splay *a) {
    expose(a);
    Splay *t = a;
    while(t->ch[0]) t = t->ch[0];
    t->splay();
    return t;
  }
};

/// }}}--- ///

/// --- Monoid examples {{{ ///
constexpr long long inf_monoid = 1e18 + 100;
#include <algorithm>
struct Nothing {
  using T = char;
  using Monoid = Nothing;
  using M = T;
  static constexpr T op(const T &, const T &) { return T(); }
  static constexpr T identity() { return T(); }
  template < class X >
  static constexpr X actInto(const M &, long long, const X &x) {
    return x;
  }
};

template < class U = long long >
struct RangeMin {
  using T = U;
  static T op(const T &a, const T &b) { return std::min< T >(a, b); }
  static constexpr T identity() { return T(inf_monoid); }
};

template < class U = long long >
struct RangeMax {
  using T = U;
  static T op(const T &a, const T &b) { return std::max< T >(a, b); }
  static constexpr T identity() { return -T(inf_monoid); }
};

template < class U = long long >
struct RangeSum {
  using T = U;
  static T op(const T &a, const T &b) { return a + b; }
  static constexpr T identity() { return T(0); }
};

template < class U >
struct RangeProd {
  using T = U;
  static T op(const T &a, const T &b) { return a * b; }
  static constexpr T identity() { return T(1); }
};

template < class U = long long >
struct RangeOr {
  using T = U;
  static T op(const T &a, const T &b) { return a | b; }
  static constexpr T identity() { return T(0); }
};

#include <bitset>

template < class U = long long >
struct RangeAnd {
  using T = U;
  static T op(const T &a, const T &b) { return a & b; }
  static constexpr T identity() { return T(-1); }
};

template < size_t N >
struct RangeAnd< std::bitset< N > > {
  using T = std::bitset< N >;
  static T op(const T &a, const T &b) { return a & b; }
  static constexpr T identity() { return std::bitset< N >().set(); }
};

/// }}}--- ///

/// --- M_act examples {{{ ///
template < class U = long long, class V = U >
struct RangeMinAdd {
  using X = U;
  using M = V;
  using Monoid = RangeMin< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, const X &x) { return m + x; }
};

template < class U = long long, class V = U >
struct RangeMaxAdd {
  using X = U;
  using M = V;
  using Monoid = RangeMax< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll, const X &x) { return m + x; }
};

template < class U = long long, class V = U >
struct RangeMinSet {
  using M = U;
  using Monoid = RangeMin< U >;
  using X = typename Monoid::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -M(inf_monoid); }
  static X actInto(const M &m, ll, const X &) { return m; }
};

template < class U = long long, class V = U >
struct RangeMaxSet {
  using M = U;
  using Monoid = RangeMax< U >;
  using X = typename Monoid::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -M(inf_monoid); }
  static X actInto(const M &m, ll, const X &) { return m; }
};

template < class U = long long, class V = U >
struct RangeSumAdd {
  using X = U;
  using M = V;
  using Monoid = RangeSum< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, ll n, const X &x) { return m * n + x; }
};

template < class U = long long, class V = U >
struct RangeSumSet {
  using X = U;
  using M = V;
  using Monoid = RangeSum< U >;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return -M(inf_monoid); }
  static X actInto(const M &m, ll n, const X &) { return m * n; }
};

template < class U, class V = U >
struct RangeProdMul {
  using X = U;
  using M = V;
  using Monoid = RangeProd< U >;
  static M mpow(M a, ll b) {
    X r(1);
    while(b) {
      if(b & 1) r = r * a;
      a = a * a;
      b >>= 1;
    }
    return r;
  }
  static M op(const M &a, const M &b) { return a * b; }
  static constexpr M identity() { return M(1); }
  static X actInto(const M &m, ll n, const X &x) { return x * mpow(m, n); }
};

template < class U, class V = U >
struct RangeProdSet {
  using X = U;
  using M = V;
  using Monoid = RangeProd< U >;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return V::unused; }
  static X actInto(const M &m, ll n, const X &) {
    return RangeProdMul< U, V >::mpow(m, n);
  }
};

template < class U = long long, class V = U >
struct RangeOr2 {
  using X = U;
  using M = V;
  using Monoid = RangeOr< U >;
  static M op(const M &a, const M &b) { return a | b; }
  static constexpr M identity() { return M(0); }
  static X actInto(const M &m, ll, const X &x) { return m | x; }
};

template < class U = long long, class V = U >
struct RangeAnd2 {
  using X = U;
  using M = V;
  using Monoid = RangeAnd< U >;
  static M op(const M &a, const M &b) { return a & b; }
  static constexpr M identity() { return M(-1); }
  static X actInto(const M &m, ll, const X &x) { return m & x; }
};

template < class U, size_t N >
struct RangeAnd2< U, std::bitset< N > > {
  using X = U;
  using M = std::bitset< N >;
  using Monoid = RangeAnd< U >;
  static M op(const M &a, const M &b) { return a & b; }
  static constexpr M identity() { return std::bitset< N >().set(); }
  static X actInto(const M &m, ll, const X &x) { return m & x; }
};
/// }}}--- ///

using LCT = LinkCutTree< RangeSumAdd<> >;

LCT lc(N);

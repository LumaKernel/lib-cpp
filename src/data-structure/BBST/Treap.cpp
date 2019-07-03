// @ Treap Sequence
// @snippet treap_seq
// @alias seq_treap lazy_treap bst_treap_seq

/// --- Treap Sequence {{{ ///
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <ostream>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

// Implicit Treap
// node {{{
template < class M_act >
struct TreapSequenceNode {
private:
  using u32 = uint_fast32_t;
  using Monoid = typename M_act::Monoid;
  using X = typename Monoid::T;
  using M = typename M_act::M;

public:
  using size_type = std::size_t;
  using node_type = TreapSequenceNode;
  using pointer = node_type *;

  pointer l = nullptr, r = nullptr;
  X val;
  X accum = Monoid::identity();
  M lazy = M_act::identity();
  bool rev = false;
  size_type sz = 1;
  u32 pri;

  TreapSequenceNode(X val, u32 pri) : val(val), accum(val), pri(pri) {}
  TreapSequenceNode(X val = Monoid::identity())
      : TreapSequenceNode(val, nextPriority()) {}

private:
  /// --- XorShift128 Embeddable {{{ ///

  struct XorShift128Embeddable {
    using result_type = uint_fast32_t;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 0xFFFFFFFF; }
    result_type x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    XorShift128Embeddable(result_type seed = 0) { z ^= seed; }
    result_type operator()() {
      result_type t = x ^ (x << 11);
      x = y, y = z, z = w;
      return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
  };

  /// }}}--- ///
  u32 nextPriority() {
    static XorShift128Embeddable xs(__LINE__ * 1333 + 57);
    return xs();
  }
};
// }}}

// core {{{
template < class M_act, class Allocator = std::allocator< TreapSequenceNode< M_act > > >
struct TreapSequence {
private:
  using u32 = uint_fast32_t;
  using Monoid = typename M_act::Monoid;
  using X = typename Monoid::T;
  using M = typename M_act::M;

  using tree_type = TreapSequence;

public:
  using size_type = std::size_t;
  using index_type = long long;
  using node_type = TreapSequenceNode< M_act >;
  using pointer = node_type *;
  using const_pointer = const node_type *;

public:
  static Allocator alc;

private:
  pointer root = 0;
  bool valid = 1;

public:
  TreapSequence() {}
  TreapSequence(std::initializer_list< X > li) {
    for(auto x : li) push_back(x);
  }

private:
  TreapSequence(pointer root) : root(root) {}

private:
  // node info {{{
  inline static size_type get_size(const_pointer a) { return a ? a->sz : 0; }
  inline static X get_accumulation(pointer a) {
    return a == nullptr ? Monoid::identity() : (eval(a), a->accum);
  }
  // }}}

  // prop, eval {{{
  // call after touch its child
  // a is not nullptr and is evaled, its child is proped
  static pointer prop(pointer a) {
    a->sz = get_size(a->l) + 1 + get_size(a->r);
    a->accum =
        Monoid::op(Monoid::op(get_accumulation(a->l), a->val), get_accumulation(a->r));
    return a;
  }
  // call before use val, accum
  static pointer eval(pointer a) {
    a->val = M_act::actInto(a->lazy, 1, a->val);
    a->accum = M_act::actInto(a->lazy, a->sz, a->accum);
    if(a->l != nullptr) a->l->lazy = M_act::op(a->lazy, a->l->lazy);
    if(a->r != nullptr) a->r->lazy = M_act::op(a->lazy, a->r->lazy);
    a->lazy = M_act::identity();

    if(a->rev) {
      std::swap(a->l, a->r);
      if(a->l != nullptr) a->l->rev ^= 1;
      if(a->r != nullptr) a->r->rev ^= 1;
      a->rev = false;
    }

    return a;
  }
  // }}}

  // BBST members {{{
public:
  static tree_type merge(tree_type a, tree_type b) {
    assert(a.valid && b.valid);
    a.valid = b.valid = 0;
    return tree_type(merge(a->root, b->root));
  }

private:
  static pointer merge(pointer a, pointer b) {
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    eval(a), eval(b);
    if(a->pri > b->pri) {
      a->r = merge(a->r, b);
      return prop(a);
    } else {
      b->l = merge(a, b->l);
      return prop(b);
    }
  }

public:
  size_type size() const {
    assert(valid);
    return get_size(root);
  }

  // [0, k), [k, n)
  std::pair< tree_type, tree_type > split(index_type k) {
    assert(valid);
    auto ps = split(root, k);
    valid = 0;
    return std::make_pair(tree_type(ps.first), tree_type(ps.second));
  }
  // [0, l), [l, r), [r, n)
  std::tuple< tree_type, tree_type, tree_type > split(index_type l, index_type r) {
    assert(valid);
    assert(l < r);
    auto ps = split(root, l, r);
    valid = 0;
    return std::make_tuple(tree_type(std::get< 0 >(ps)), tree_type(std::get< 1 >(ps)),
                           tree_type(std::get< 2 >(ps)));
  }

private:
  static std::pair< pointer, pointer > split(pointer a, index_type k) {
    if(k < 0) return std::make_pair(nullptr, a);
    if(k >= static_cast< index_type >(get_size(a))) return std::make_pair(a, nullptr);
    return _split(a, k);
  }

  static std::pair< pointer, pointer > _split(pointer a, size_type k) {
    if(a == nullptr) return std::make_pair(nullptr, nullptr);
    eval(a);
    pointer sl, sr;
    if(k <= get_size(a->l)) {
      std::tie(sl, sr) = _split(a->l, k);
      a->l = sr;
      return std::make_pair(sl, prop(a));
    } else {
      std::tie(sl, sr) = _split(a->r, k - get_size(a->l) - 1);
      a->r = sl;
      return std::make_pair(prop(a), sr);
    }
  }

  static std::tuple< pointer, pointer, pointer > split(pointer a, index_type l,
                                                       index_type r) {
    assert(l <= r);
    pointer sl, sr, tl, tr;
    std::tie(sl, sr) = split(a, r);
    std::tie(tl, tr) = split(sl, l);
    return std::make_tuple(tl, tr, sr);
  }

  static std::tuple< pointer, pointer, pointer > _split(pointer a, size_type l,
                                                        size_type r) {
    pointer sl, sr, tl, tr;
    std::tie(sl, sr) = _split(a, r);
    std::tie(tl, tr) = _split(sl, l);
    return std::make_tuple(tl, tr, sr);
  }

public:
  // k : implicit key
  void insert(size_type k, const X &x) {
    assert(valid);
    assert(k <= size());
    root = insert(root, k, x);
  }

  void push_front(const X &x) {
    assert(valid);
    root = insert(root, 0, x);
  }

  void push_back(const X &x) {
    assert(valid);
    root = insert(root, size(), x);
  }

  void pop_front() { erase(0); }

  void pop_back() {
    assert(size());
    erase(size() - 1);
  }

private:
  pointer insert(pointer a, size_type k, const X &x) {
    pointer sl, sr;
    std::tie(sl, sr) = split(a, k);
    pointer p = alc.allocate(1);
    std::allocator_traits< Allocator >::construct(alc, p, x);
    return merge(sl, merge(p, sr));
  }

public:
  X erase(size_type k) {
    assert(valid);
    assert(k < size());
    auto p = erase(root, k);
    root = p.first;
    return p.second;
  }

private:
  std::pair< pointer, X > erase(pointer a, size_type k) {
    assert(valid);
    pointer s1, s2, s3;
    std::tie(s1, s2, s3) = split(a, k, k + 1);
    return std::make_pair(merge(s1, s3), eval(s2)->val);
  }

public:
  void erase(index_type l, index_type r) {
    assert(valid);
    pointer s1, s2, s3;
    std::tie(s1, s2, s3) = split(root, l, r);
    root = merge(s1, s3);
  }

public:
  void set(size_type k, X const &x) {
    assert(valid);
    assert(k < size());
    pointer a, b, c;
    std::tie(a, b, c) = split(root, k, k + 1);
    eval(b);
    b->val = b->accum = x;
    root = merge(a, merge(b, c));
  }

  X get(size_type k) const {
    assert(valid);
    assert(k < size());
    pointer a = root;
    while(1) {
      eval(a);
      if(get_size(a->l) == k)
        return a->val;
      else if(get_size(a->l) < k)
        k -= get_size(a->l) + 1, a = a->r;
      else
        a = a->l;
    }
  }

  std::vector< X > get(size_type l, size_type r) {
    assert(valid);
    assert(l <= r && r < size());
    pointer a, b, c;
    std::tie(a, b, c) = _split(root, l, r);
    auto v = get_all(b);
    root = merge(a, merge(b, c));
    return v;
  }

  std::vector< X > get() const {
    assert(valid);
    return get_all(root);
  }

private:
  static std::vector< X > get_all(pointer a) {
    std::stack< std::pair< pointer, bool > > stk;
    std::vector< X > v;
    if(!a) return v;
    v.reserve(get_size(a));
    stk.emplace(a, 0);
    while(stk.size()) {
      pointer p;
      bool f;
      std::tie(p, f) = stk.top();
      stk.pop();
      if(!f) {
        eval(p);
        if(p->r) stk.emplace(p->r, 0);
        stk.emplace(p, 1);
        if(p->l) stk.emplace(p->l, 0);
      } else {
        v.push_back(p->val);
      }
    }
    return v;
  }

public:
  inline void act(const M &m) { act(0, size(), m); }

  void act(index_type l, index_type r, const M &m) {
    assert(valid);
    if(l >= r) return;
    pointer a, b, c;
    std::tie(a, b, c) = split(root, l, r);
    if(b) eval(b)->lazy = M_act::op(m, b->lazy);
    root = merge(a, merge(b, c));
  }

  inline X fold() { return fold(0, size()); }

  X fold(index_type l, index_type r) {
    assert(valid);
    pointer a, b, c;
    std::tie(a, b, c) = split(root, l, r);
    X tmp = b ? eval(b)->accum : Monoid::identity();
    root = merge(a, merge(b, c));
    return tmp;
  }

  void reverse() const {
    assert(valid);
    root->rev ^= 1;
  }

  void reverse(size_type l, size_type r) {
    assert(valid);
    assert(l <= r && r <= size());
    if(l == r) return;
    pointer a, b, c;
    std::tie(a, b, c) = _split(root, l, r);
    b->rev ^= 1;

    root = merge(a, merge(b, c));
  }

  void rotate(size_type l, size_type m, size_type r) {
    assert(valid);
    assert(l <= m && m <= r && r <= size());
    if(l == m) return;
    pointer a, b, c;
    std::tie(a, b, c) = _split(root, l, r);
    pointer d, e;
    std::tie(d, e) = _split(b, m - l);
    d->rev ^= 1;
    e->rev ^= 1;

    b = merge(d, e);

    b->rev ^= 1;

    root = merge(a, merge(b, c));
  }

  void clear() {
    assert(valid);
    root = nullptr;
  }

public:
  static const index_type not_found = -1;
  template < class T >
  index_type binary_search(const bool maximize, const T &exists) {
    return binary_search(0, size(), maximize, exists, root, 0);
  }
  template < class T >
  index_type binary_search(index_type l, index_type r, const bool maximize,
                           const T &exists) const {
    if(l < 0) l = 0;
    if(r > static_cast< index_type >(size())) r = size();
    if(l >= r) return not_found;
    return binary_search(l, r, maximize, exists, root, 0);
  }

private:
  template < class T >
  index_type binary_search(size_type a, size_type b, const bool maximize, T exists,
                           pointer k, size_type l) const {
    if(!k) return not_found;
    eval(k);
    if(!exists(get_accumulation(k), l, l + get_size(k))) return not_found;
    index_type i;
    if(maximize) {
      i = binary_search(a, b, maximize, exists, k->r, l + get_size(k->l) + 1);
      if(i == not_found) {
        if(exists(k->val, l + get_size(k->l), l + get_size(k->l) + 1))
          i = l + get_size(k->l);
        else
          i = binary_search(a, b, maximize, exists, k->l, l);
      }
    } else {
      i = binary_search(a, b, maximize, exists, k->l, l);
      if(i == not_found) {
        if(exists(k->val, l + get_size(k->l), l + get_size(k->l) + 1))
          i = l + get_size(k->l);
        else
          i = binary_search(a, b, maximize, exists, k->r, l + get_size(k->l) + 1);
      }
    }
    return i;
  }
  // }}}

public:
  friend std::ostream &operator<<(std::ostream &os, const tree_type &a) {
    auto v = a.get();
    os << "{";
    if(v.size()) os << v[0];
    for(size_type i = 1; i < v.size(); i++) os << ", " << v[i];
    os << "}";
    return os;
  }
};

template < class M_act, class Allocator >
Allocator TreapSequence< M_act, Allocator >::alc;
// }}}
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
  static constexpr T identity() { return T(-inf_monoid); }
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
  static X actInto(const M &m, long long, const X &x) { return m + x; }
};

template < class U = long long, class V = U >
struct RangeMaxAdd {
  using X = U;
  using M = V;
  using Monoid = RangeMax< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, long long, const X &x) { return m + x; }
};

template < class U = long long, class V = U >
struct RangeMinSet {
  using M = U;
  using Monoid = RangeMin< U >;
  using X = typename Monoid::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return M(-inf_monoid); }
  static X actInto(const M &m, long long, const X &x) { return m == identity() ? x : m; }
};

template < class U = long long, class V = U >
struct RangeMaxSet {
  using M = U;
  using Monoid = RangeMax< U >;
  using X = typename Monoid::T;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return M(-inf_monoid); }
  static X actInto(const M &m, long long, const X &x) { return m == identity() ? x : m; }
};

template < class U = long long, class V = U >
struct RangeSumAdd {
  using X = U;
  using M = V;
  using Monoid = RangeSum< U >;
  static M op(const M &a, const M &b) { return a + b; }
  static constexpr M identity() { return 0; }
  static X actInto(const M &m, long long n, const X &x) { return m * n + x; }
};

template < class U = long long, class V = U >
struct RangeSumSet {
  using X = U;
  using M = V;
  using Monoid = RangeSum< U >;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return M(-inf_monoid); }
  static X actInto(const M &m, long long n, const X &x) {
    return m == identity() ? x : m * n;
  }
};

template < class U, class V = U >
struct RangeProdMul {
  using X = U;
  using M = V;
  using Monoid = RangeProd< U >;
  static M mpow(M a, long long b) {
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
  static X actInto(const M &m, long long n, const X &x) { return x * mpow(m, n); }
};

template < class U, class V = U >
struct RangeProdSet {
  using X = U;
  using M = V;
  using Monoid = RangeProd< U >;
  static M op(const M &a, const M &) { return a; }
  static constexpr M identity() { return V::unused; }
  static X actInto(const M &m, long long n, const X &) {
    if(m == identity()) return;
    return RangeProdMul< U, V >::mpow(m, n);
  }
};

template < class U = long long, class V = U >
struct RangeOrSet {
  using X = U;
  using M = V;
  using Monoid = RangeOr< U >;
  static M op(const M &a, const M &b) { return a == identity() ? b : a; }
  static constexpr M identity() { return M(-inf_monoid); }
  static X actInto(const M &m, long long, const X &x) { return m == identity() ? x : m; }
};

template < class U = long long, class V = U >
struct RangeAndSet {
  using X = U;
  using M = V;
  using Monoid = RangeAnd< U >;
  static M op(const M &a, const M &b) { return a == identity() ? b : a; }
  static constexpr M identity() { return M(-inf_monoid); }
  static X actInto(const M &m, long long, const X &x) { return m == identity() ? x : m; }
};

template < class U = long long, class V = U >
struct RangeOr2 {
  using X = U;
  using M = V;
  using Monoid = RangeOr< U >;
  static M op(const M &a, const M &b) { return a | b; }
  static constexpr M identity() { return M(0); }
  static X actInto(const M &m, long long, const X &x) { return m | x; }
};

template < class U = long long, class V = U >
struct RangeAnd2 {
  using X = U;
  using M = V;
  using Monoid = RangeAnd< U >;
  static M op(const M &a, const M &b) { return a & b; }
  static constexpr M identity() { return M(-1); }
  static X actInto(const M &m, long long, const X &x) { return m & x; }
};

template < class U, size_t N >
struct RangeAnd2< U, std::bitset< N > > {
  using X = U;
  using M = std::bitset< N >;
  using Monoid = RangeAnd< U >;
  static M op(const M &a, const M &b) { return a & b; }
  static constexpr M identity() { return std::bitset< N >().set(); }
  static X actInto(const M &m, long long, const X &x) { return m & x; }
};
/// }}}--- ///

using Seq = TreapSequence< RangeSumAdd<> >;

// @new
// @name Treap Multiset
// @snippet     treap_multiset
// @alias       multiset_treap set_treap bst_treap_multiset

/// --- Treap Multiset {{{ ///

#include <cstdint>
#include <utility>

template < class Key >
struct TreapMultiset {
public:
  const Key key;

private:
  using u32 = uint_fast32_t;
  using PNN = std::pair< TreapMultiset *, TreapMultiset * >;
  u32 pri;
  TreapMultiset *l = nullptr, *r = nullptr;
  int sz = 1;
  // call after touch its child
  friend TreapMultiset *prop(TreapMultiset *a) {
    a->sz = size(a->l) + 1 + size(a->r);
    return a;
  }
  /// --- XorShift128 Embeddable {{{ ///

  struct XorShift128Embeddable {
    using result_type = uint_fast32_t;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 0xFFFFFFFF; }
    result_type x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    XorShift128Embeddable(result_type seed = 0) { z ^= seed; }
    result_type operator()() {
      result_type t = x ^ (x << 11);
      x = y, y = z, z = w;
      return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
  };

  /// }}}--- ///
  u32 nextPriority() {
    static XorShift128Embeddable xs(__LINE__ * 3 + 5);
    return xs();
  }

public:
  TreapMultiset(Key key, u32 pri) : key(key), pri(pri) {}
  TreapMultiset(Key key) : TreapMultiset(key, nextPriority()) {}
  friend TreapMultiset *merge(TreapMultiset *a, TreapMultiset *b) {
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(a->pri > b->pri) {
      a->r = merge(a->r, b);
      return prop(a);
    } else {
      b->l = merge(a, b->l);
      return prop(b);
    }
  }
  // lower (-inf, key), [key, inf)
  // upper (-inf, key], (key, inf)
  friend PNN split(TreapMultiset *a, Key key, bool upper) {
    if(a == nullptr) return PNN(nullptr, nullptr);
    TreapMultiset *sl, *sr;
    if(upper ? key < a->key : !(a->key < key)) {
      tie(sl, sr) = split(a->l, key, upper);
      a->l = sr;
      return PNN(sl, prop(a));
    } else {
      tie(sl, sr) = split(a->r, key, upper);
      a->r = sl;
      return PNN(prop(a), sr);
    }
  }
  friend PNN lower_split(TreapMultiset *a, const Key &key) {
    return split(a, key, false);
  }
  friend PNN upper_split(TreapMultiset *a, const Key &key) { return split(a, key, true); }
  friend int size(TreapMultiset *a) { return a == nullptr ? 0 : a->sz; }
  friend void insert(TreapMultiset *&a, Key key) {
    TreapMultiset *sl, *sr;
    tie(sl, sr) = lower_split(a, key);
    a = merge(sl, merge(new TreapMultiset(key), sr));
  }
  friend void erase(TreapMultiset *&a, Key key) {
    TreapMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = upper_split(a, key);
    tie(tl, tr) = lower_split(sl, key);
    a = merge(tl, sr);
  }
  friend void erase(TreapMultiset *&a, Key keyL, Key keyR, bool inclusive = false) {
    TreapMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, keyR, inclusive);
    tie(tl, tr) = lower_split(sl, keyL);
    a = merge(tl, sr);
  }
  friend void erase1(TreapMultiset *&a, Key key) {
    if(a == nullptr) return;
    if(key < a->key) {
      erase1(a->l, key);
    } else {
      if(!(a->key < key)) {
        a = merge(a->l, a->r);
        return;
      }
      erase1(a->r, key);
    }
    prop(a);
  }
  friend Key getKth(TreapMultiset *&a, int k) {
    static const struct CannotGetKthOfNullptr {} ex;
    if(a == nullptr) throw ex;
    if(k <= size(a->l)) {
      if(k == size(a->l)) return a->key;
      return getKth(a->l, k);
    } else {
      return getKth(a->r, k - size(a->l) - 1);
    }
  }
  friend int count(TreapMultiset *a, Key key) {
    TreapMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = upper_split(a, key);
    tie(tl, tr) = lower_split(sl, key);
    int cnt = size(tr);
    merge(merge(tl, tr), sr);
    return cnt;
  }
  friend int count(TreapMultiset *a, Key keyL, Key keyR, bool inclusive = false) {
    TreapMultiset *sl, *sr, *tl, *tr;
    tie(sl, sr) = split(a, keyR, inclusive);
    tie(tl, tr) = lower_split(sl, keyL);
    int cnt = size(tr);
    merge(merge(tl, tr), sr);
    return cnt;
  }
};

/// }}}--- ///

using MS = TreapMultiset< long long > *;
MS ms = nullptr;

// @new Treap TEST
// {{{

// #undef DEBUG
// #define DEBUG
// DEBUG {{{
#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <valarray>
#include <vector>
template < int n, class... T >
typename std::enable_if< (n >= sizeof...(T)) >::type __output_tuple(
    std::ostream &, std::tuple< T... > const &) {}
template < int n, class... T >
typename std::enable_if< (n < sizeof...(T)) >::type __output_tuple(
    std::ostream &os, std::tuple< T... > const &t) {
  os << (n == 0 ? "" : ", ") << std::get< n >(t);
  __output_tuple< n + 1 >(os, t);
}
template < class... T >
std::ostream &operator<<(std::ostream &os, std::tuple< T... > const &t) {
  os << "(";
  __output_tuple< 0 >(os, t);
  os << ")";
  return os;
}
template < class T, class U >
std::ostream &operator<<(std::ostream &os, std::pair< T, U > const &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}
template < class T >
std::ostream &operator<<(std::ostream &os, const std::stack< T > &a) {
  os << "{";
  for(auto tmp = a; tmp.size(); tmp.pop())
    os << (a.size() == tmp.size() ? "" : ", ") << tmp.top();
  os << "}";
  return os;
}
template < class T, class Container, class Compare >
std::ostream &operator<<(std::ostream &os,
                         std::priority_queue< T, Container, Compare > a) {
  os << "{ (top) ";
  while(a.size()) os << a.top() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
template < class T, class Container >
std::ostream &operator<<(std::ostream &os, std::queue< T, Container > a) {
  os << "{ ";
  while(a.size()) os << a.front() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
#ifdef DEBUG
#if !defined(DEBUG_OUT)
#define DEBUG_OUT std::cerr
#endif
#define dump(...)                                                                \
  [&]() {                                                                        \
    auto __debug_tap = std::make_tuple(__VA_ARGS__);                             \
    DEBUG_OUT << "[" << __LINE__ << "] " << #__VA_ARGS__ << " = " << __debug_tap \
              << std::endl;                                                      \
  }()
template < class T >
inline void dump2D(T &d, size_t sizey, size_t sizex) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << "\t";
    for(size_t j = 0; j < sizex; j++)
      DEBUG_OUT << d[i][j] << (j + 1 == sizex ? "" : "\t");
    DEBUG_OUT << std::endl;
  }
}
template < class T >
inline void dump1D(T &d, size_t sizey) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << d[i] << (i + 1 == sizey ? "" : " ");
  }
  DEBUG_OUT << std::endl;
}
template <
    class T, class = typename std::iterator_traits< decltype(begin(T())) >::value_type,
    class = typename std::enable_if< !std::is_same< T, std::string >::value >::type >
std::ostream &operator<<(std::ostream &os, const T &a) {
  os << "{";
  for(auto ite = begin(a); ite != end(a); ++ite)
    os << (ite == begin(a) ? "" : ", ") << *ite;
  os << "}";
  return os;
}
#else
#define dump(...) (42)
#define dump2D(...) (42)
#define dump1D(...) (42)
template <
    class T, class = typename std::iterator_traits< decltype(begin(T())) >::value_type,
    class = typename std::enable_if< !std::is_same< T, std::string >::value >::type >
std::ostream &operator<<(std::ostream &os, const T &a) {
  for(auto ite = begin(a); ite != end(a); ++ite)
    os << (ite == begin(a) ? "" : " ") << *ite;
  return os;
}
#endif
// }}}

int main() {
  Seq seq;
  dump(seq);
  seq.insert(0, 1);
  seq.push_back(2);
  seq.push_front(-1);
  dump(seq);
  seq.erase(1);
  dump(seq);
  assert(seq.size() == 2);
  seq.reverse();
  dump(seq);
  seq.push_back(3);
  seq.push_back(4);
  seq.push_back(5);
  dump(seq);
  seq.rotate(1, 3, 4);
  dump(seq);
  seq.get(2);

  seq.clear();

  for(int i = 0; i < 20; i++) seq.push_back(i);
  dump(seq);
  seq.rotate(3, 7, 10);
  dump(seq);

  dump(seq.get(4, 15));

  seq = Seq({1, 3, 4, 2, 4, 5});

  dump(seq);

  dump("done");
}
// }}}

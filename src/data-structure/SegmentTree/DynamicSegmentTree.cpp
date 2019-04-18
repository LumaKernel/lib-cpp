// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Dynamic SegmentTree
// @snippet     dynamicsegmenttree
// @alias       segdynamic

// - scalable
//    DynamicSegmentTree( [, <initial> ])
// - fixed-range
//    DynamicSegmentTree(L, R [, <initial> ])
//    DynamicSegmentTree(size [, <initial> ])
// === initial values ===
// <initial> := one value or function
// when you feed initial-one-value : O(log^2 N) time / query
// when you feed initial-function
//    : O(timeof(f(l, r)) log N) time / query
// === --- ===
// NOTE : one value is recommended rather than O(log SIZE) function
// NOTE : better to use fixed-range
/// --- Dynamic SegmentTree {{{ ///
#include <cassert>
#include <functional>
#include <memory>
template < class Monoid >
struct DynamicSegmentTreeNode {
public:
  using T = typename Monoid::T;
  using node_type = DynamicSegmentTreeNode;
  using pointer = node_type *;
  T value;
  pointer l = 0, r = 0;
  DynamicSegmentTreeNode(T value = Monoid::identity()) : value(value) {}
  DynamicSegmentTreeNode(pointer l, pointer r) : l(l), r(r) {}
};

template < class Monoid,
           class Allocator = std::allocator< DynamicSegmentTreeNode< Monoid > > >
struct DynamicSegmentTree {
public:
  using T = typename Monoid::T;
  using size_type = long long;
  using node_type = DynamicSegmentTreeNode< Monoid >;
  using pointer = node_type *;
  using func_type = std::function< T(size_type l, size_type r) >;

private:
  static Allocator alc;
  pointer top = 0;
  // it should be only given positive length ranges
  func_type get_initial = [](...) { return Monoid::identity(); };
  const bool range_fixed;
  size_type L, R;

  void expand(size_type t) {
    assert(!range_fixed);
    while(t < L || R <= t) {
      if(R == static_cast< size_type >(0))
        R = 1;
      else {
        R <<= 1;
        if(top) {
          pointer new_l = 0, new_r = 0;
          if(top->l)
            std::allocator_traits< Allocator >::construct(
                alc, new_l = alc.allocate(1), nullptr, top->l);
          if(top->r)
            std::allocator_traits< Allocator >::construct(
                alc, new_r = alc.allocate(1), top->r, nullptr);
          top->l = new_l, top->r = new_r;
          if(new_l) update(new_l, -R, 0);
          if(new_r) update(new_r, 0, R);
          update(top, -R, R);
        }
      }
      L = -R;
    }
  }

  void update(pointer node, size_type l, size_type r) {
    assert(node && r - l >= 2);
    node->value = Monoid::op(node->l ? node->l->value : get_initial(l, (l + r) / 2),
                             node->r ? node->r->value : get_initial((l + r) / 2, r));
  }

public:
  // scalable
  DynamicSegmentTree() : range_fixed(0), L(0), R(0) {}
  DynamicSegmentTree(const T &initial) : DynamicSegmentTree() { set_initial(initial); }
  DynamicSegmentTree(const func_type &get_initial) : DynamicSegmentTree() {
    this->get_initial = get_initial;
  }
  // [L, R)
  DynamicSegmentTree(size_type L, size_type R) : range_fixed(1), L(L), R(R) {
    assert(L < R);
  }
  DynamicSegmentTree(size_type L, size_type R, const T &initial)
      : DynamicSegmentTree(L, R) {
    set_initial(initial);
  }
  DynamicSegmentTree(size_type L, size_type R, const func_type &get_initial)
      : DynamicSegmentTree(L, R) {
    this->get_initial = get_initial;
  }
  // [0, R)
  DynamicSegmentTree(size_type R) : DynamicSegmentTree(0, R) {}
  DynamicSegmentTree(size_type R, const T &initial) : DynamicSegmentTree(R) {
    set_initial(initial);
  }
  DynamicSegmentTree(size_type R, const func_type &get_initial) : DynamicSegmentTree(R) {
    this->get_initial = get_initial;
  }

  void set_initial(const T &initial) {
    get_initial = [initial](size_type l, size_type r) {
      size_type n = r - l;
      n--;
      T u = initial, v = initial;
      while(n) {
        if(n & 1) u = Monoid::op(u, v);
        n >>= 1;
        if(n) v = Monoid::op(v, v);
      }
      return u;
    };
  }

  void set(size_type i, const T &val) {
    if(!range_fixed)
      expand(i);
    else
      assert(L <= i && i < R);
    if(!top)
      std::allocator_traits< Allocator >::construct(
          alc, top = alc.allocate(1), get_initial(L, R));
    set(i, val, L, R, top);
  }

private:
  void set(size_type i, const T &val, size_type l, size_type r, pointer node) {
    assert(node);
    if(r - l == 1) {
      node->value = val;
      return;
    }
    size_type m = (l + r) / 2;
    if(i < m) {
      if(!node->l)
        std::allocator_traits< Allocator >::construct(
            alc, node->l = alc.allocate(1), get_initial(l, m));
      set(i, val, l, m, node->l);
    } else {
      if(!node->r)
        std::allocator_traits< Allocator >::construct(
            alc, node->r = alc.allocate(1), get_initial(m, r));
      set(i, val, m, r, node->r);
    }
    update(node, l, r);
  }

public:
  T fold(size_type l, size_type r) {
    if(range_fixed) {
      if(l < L) l = L;
      if(R < r) r = R;
    }
    if(l >= r) return Monoid::identity();
    if(!range_fixed) {
      if(r < L || R < l) return get_initial(l, r);
      if(l < L) return Monoid::op(get_initial(l, L), fold(L, r));
      if(R < r) return Monoid::op(fold(l, R), get_initial(R, r));
    }
    return fold(l, r, L, R, top);
  }
  T get(size_type i) {
    if(range_fixed) assert(L <= i && i < R);
    return fold(i, i + 1);
  }

private:
  T fold(size_type a, size_type b, size_type l, size_type r, pointer node) {
    if(b <= l || r <= a) return Monoid::identity();
    if(!node)
      return get_initial(std::max< size_type >(a, l), std::min< size_type >(b, r));
    if(a <= l && r <= b) return node->value;
    return Monoid::op(
        fold(a, b, l, (l + r) / 2, node->l), fold(a, b, (l + r) / 2, r, node->r));
  }
};
template < class Monoid, class Allocator >
Allocator DynamicSegmentTree< Monoid, Allocator >::alc;
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

using Seg = DynamicSegmentTree< RangeMin<> >;

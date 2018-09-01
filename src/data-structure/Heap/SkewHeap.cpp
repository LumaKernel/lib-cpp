// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name SkewHeap Library
// @snippet     skewheap
// @title SkewHeap
/// --- SkewHeap Library {{{ ///
template < class T >
struct SkewHeap {
  SkewHeap *l = nullptr, *r = nullptr;
  T val;
  SkewHeap(T val = T()) : val(val) {}
};

template < class T, class Compare = less< T > >
SkewHeap< T > *meld(SkewHeap< T > *a, SkewHeap< T > *b,
                    const Compare &comp = Compare()) {
  if(a == nullptr) return b;
  if(b == nullptr) return a;
  if(!comp(a->val, b->val)) swap(a, b);
  a->r = meld(a->r, b, comp);
  swap(a->l, a->r);
  return a;
}

template < class T, class Compare = less< T > >
inline SkewHeap< T > *push(SkewHeap< T > *&a, T const &e,
                           const Compare &comp = Compare()) {
  SkewHeap< T > *b = new SkewHeap< T >(e);
  a = a == nullptr ? b : meld(a, b, comp);
  return b;
}

template < class T, class Compare = less< T > >
inline void pop(SkewHeap< T > *&a, const Compare &comp = Compare()) {
  a = meld(a->l, a->r, comp);
}
template < class T, class Compare = less< T > >
SkewHeap< T > *second(SkewHeap< T > *a, Compare comp = Compare()) {
  return a->r == nullptr ? a->l : comp(a->l->val, a->r->val) ? a->l : a->r;
}
/// }}}--- ///

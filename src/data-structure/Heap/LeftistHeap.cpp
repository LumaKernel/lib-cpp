// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name LeftistHeap Library
// @snippet     leftistheap
// @alias       meldable_heap_leftistheap
/// --- LeftistHeap Library {{{ ///
template < class T >
struct LeftistHeap {
  LeftistHeap *l = nullptr, *r = nullptr;
  T val;
  int rnk;
  LeftistHeap(T val = T()) : val(val) {}
};

template < class T, class Compare = less< T > >
LeftistHeap< T > *meld(LeftistHeap< T > *a, LeftistHeap< T > *b,
                       const Compare &comp = Compare()) {
  if(a == nullptr) return b;
  if(b == nullptr) return a;
  if(!comp(a->val, b->val)) swap(a, b);
  a->r = meld(a->r, b, comp);
  if(a->l == nullptr || a->l->rnk < a->r->rnk) swap(a->l, a->r);
  a->rnk = ((a->r == nullptr) ? 0 : a->r->rnk) + 1;
  return a;
}

template < class T, class Compare = less< T > >
inline LeftistHeap< T > *push(LeftistHeap< T > *&a, T const &e,
                              const Compare &comp = Compare()) {
  LeftistHeap< T > *b = new LeftistHeap< T >(e);
  a = a == nullptr ? b : meld(a, b, comp);
  return b;
}

template < class T, class Compare = less< T > >
inline void pop(LeftistHeap< T > *&a, const Compare &comp = Compare()) {
  a = meld(a->l, a->r, comp);
}
template < class T, class Compare = less< T > >
LeftistHeap< T > *second(LeftistHeap< T > *a, const Compare &comp = Compare()) {
  return a->r == nullptr ? a->l : comp(a->l->val, a->r->val) ? a->l : a->r;
}
/// }}}--- ///

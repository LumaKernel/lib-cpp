// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ DEBUG
// @snippet dump
// @alias debug

// #undef DEBUG
// #define DEBUG
// DEBUG {{{
#include <array>
#include <deque>
#include <list>
#include <ostream>
#include <queue>
#include <stack>
#include <tuple>
#include <valarray>
#include <vector>
template < int n, class... T >
typename enable_if< (n >= sizeof...(T)) >::type __output_tuple(ostream &,
                                                               tuple< T... > const &) {}
template < int n, class... T >
typename enable_if< (n < sizeof...(T)) >::type __output_tuple(ostream &os,
                                                              tuple< T... > const &t) {
  os << (n == 0 ? "" : ", ") << get< n >(t);
  __output_tuple< n + 1 >(os, t);
}
template < class... T >
ostream &operator<<(ostream &os, tuple< T... > const &t) {
  os << "(";
  __output_tuple< 0 >(os, t);
  os << ")";
  return os;
}
template < class T, class U >
ostream &operator<<(ostream &os, pair< T, U > const &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}
template < class T >
ostream &operator<<(ostream &os, const stack< T > &a) {
  os << "{";
  for(auto tmp = a; tmp.size(); tmp.pop())
    os << (a.size() == tmp.size() ? "" : ", ") << tmp.top();
  os << "}";
  return os;
}
template < class T, class Container, class Compare >
ostream &operator<<(ostream &os, priority_queue< T, Container, Compare > a) {
  os << "{ (top) ";
  while(a.size()) os << a.top() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
template < class T, class Container >
ostream &operator<<(ostream &os, queue< T, Container > a) {
  os << "{ ";
  while(a.size()) os << a.front() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
#ifdef DEBUG
#if !defined(DEBUG_OUT)
#define DEBUG_OUT cerr
#endif
#define dump(...)                                                                \
  [&]() {                                                                        \
    auto __debug_tap = make_tuple(__VA_ARGS__);                                  \
    DEBUG_OUT << "[" << __LINE__ << "] " << #__VA_ARGS__ << " = " << __debug_tap \
              << endl;                                                           \
  }()
template < class T >
inline void dump2D(T &d, size_t sizey, size_t sizex) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << "\t";
    for(size_t j = 0; j < sizex; j++)
      DEBUG_OUT << d[i][j] << (j + 1 == sizex ? "" : "\t");
    DEBUG_OUT << endl;
  }
}
template < class T >
inline void dump1D(T &d, size_t sizey) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << d[i] << (i + 1 == sizey ? "" : " ");
  }
  DEBUG_OUT << endl;
}
template < class T, class = typename iterator_traits< decltype(begin(T())) >::value_type,
           class = typename enable_if< !is_same< T, string >::value >::type >
ostream &operator<<(ostream &os, const T &a) {
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
template < class T, class = typename iterator_traits< decltype(begin(T())) >::value_type,
           class = typename enable_if< !is_same< T, string >::value >::type >
ostream &operator<<(ostream &os, const T &a) {
  for(auto ite = begin(a); ite != end(a); ++ite)
    os << (ite == begin(a) ? "" : " ") << *ite;
  return os;
}
#endif
// }}}

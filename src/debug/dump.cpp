// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ DEBUG
// @snippet dump
// @alias debug
// #undef DEBUG
// #define DEBUG
// DEBUG {{{
// clang-format off
#ifdef DEBUG
#if !defined(DEBUG_OUT)
#define DEBUG_OUT cerr
#endif
template <typename T> ostream &operator<<(ostream &o, const vector<T> &v) { o << "{"; for(size_t i = 0; i < v.size(); i++) o << v[i] << (i + 1 != v.size() ? ", " : ""); o << "}"; return o; }
#define dump(...) [&](){auto __debug_tap=make_tuple(__VA_ARGS__);DEBUG_OUT<<"["<<__LINE__<< "] "<<#__VA_ARGS__<<" = "<<__debug_tap<<"\n";}()
template<class T> inline void dump2D(T &d, size_t sizey, size_t sizex) {
  for(size_t i = 0; i < sizey; i++) { for(size_t j = 0; j < sizex; j++) DEBUG_OUT << d[i][j] << " "; DEBUG_OUT << endl; }
}
#else
template <typename T> ostream &operator<<(ostream &o, const vector<T> &v) { for(size_t i = 0; i < v.size(); i++) o << v[i] << (i + 1 != v.size() ? " " : ""); return o; }
#define dump(...) (42)
#define dump2D(...) (42)
#endif
template<int n, class...T> typename enable_if<(n>=sizeof...(T))>::type _ot(ostream &, tuple<T...> const &){}
template<int n, class...T> typename enable_if<(n< sizeof...(T))>::type _ot(ostream & os, tuple<T...> const & t){ os << (n==0?"":", ") << get<n>(t); _ot<n+1>(os, t); }
template<class...T> ostream & operator<<(ostream &o, tuple<T...> const &t){ o << "("; _ot<0>(o, t); o << ")"; return o; }
template<class T, class U> ostream & operator<<(ostream &o, pair<T, U> const &p) { o << "(" << p.first << ", " << p.second << ")"; return o; }
// clang-format on
// }}}

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
#include <iostream>
#include <stack>
#include <tuple>
#include <valarray>
#include <vector>
// clang-format off
template<int n, class...T> typename enable_if<(n>=sizeof...(T))>::type _ot(ostream &, tuple<T...> const &){}
template<int n, class...T> typename enable_if<(n< sizeof...(T))>::type _ot(ostream & os, tuple<T...> const & t){ os << (n==0?"":", ") << get<n>(t); _ot<n+1>(os, t); }
template<class...T> ostream & operator<<(ostream &o, tuple<T...> const &t){ o << "("; _ot<0>(o, t); o << ")"; return o; }
template<class T, class U> ostream & operator<<(ostream &o, pair<T, U> const &p) { o << "(" << p.first << ", " << p.second << ")"; return o; }
template < class T > ostream &operator<<(ostream &o, const stack<T> &a) { o << "{"; for(auto tmp = a; tmp.size(); tmp.pop()) o << (a.size() == tmp.size() ? "" : ", ") << tmp.top(); o << "}"; return o; }
#ifdef DEBUG
#if !defined(DEBUG_OUT)
#define DEBUG_OUT cerr
#endif
#if !defined(DEBUG_LEFT)
  #define DEBUG_LEFT "\e[1;36m"
#endif
#if !defined(DEBUG_RIGHT)
  #define DEBUG_RIGHT ":\e[m"
#endif
#define dump(...) [&](){auto __debug_tap=make_tuple(__VA_ARGS__);DEBUG_OUT<<DEBUG_LEFT<<__LINE__ << DEBUG_RIGHT << " " <<#__VA_ARGS__<<" = "<<__debug_tap<<endl;}()
template < class T > inline void dump2D(T &d, size_t sizey, size_t sizex) { for(size_t i = 0; i < sizey; i++) { DEBUG_OUT << "\t"; for(size_t j = 0; j < sizex; j++) DEBUG_OUT << d[i][j] << (j + 1 == sizex ? "" : "\t"); DEBUG_OUT << endl; } }
template < class T, class = typename iterator_traits< typename T::iterator >::value_type, class = typename enable_if<!is_same<T, string>::value>::type > ostream &operator<<(ostream &o, const T &a) { o << "{"; for(auto ite = a.begin(); ite != a.end(); ++ite) o << (ite == a.begin() ? "" : ", ") << *ite; o << "}"; return o; }
#else
#define dump(...) (42)
#define dump2D(...) (42)
template < class T, class = typename iterator_traits< typename T::iterator >::value_type, class = typename enable_if<!is_same<T, string>::value>::type > ostream &operator<<(ostream &o, const T &a) { for(auto ite = a.begin(); ite != a.end(); ++ite) o << (ite == a.begin() ? "" : " ") << *ite; return o; }
#endif
// clang-format on
// }}}

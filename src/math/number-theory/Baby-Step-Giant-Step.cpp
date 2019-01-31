// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ modlog with Baby-Step Giant-Step algorithm
// @snippet modlog

// require math library
// modlog(a, b, p) = log_a b
// gcd(a, p) is arbitrary
// modlog(a, b, p) {{{

// Baby-Step Giant-Step algorithm
ll modlog(ll a, ll b, ll p) {
  a %= p;
  b %= p;
  if(a < 0) a += p;
  if(b < 0) b += p;

  if(a == 1 && b != 1) return -1;
  if(b == 1) return 0;

  ll g;
  ll bias = 0;
  while((g = gcd(a, p)) != 1) {
    if(b % g != 0) return -1;
    b /= g;
    p /= g;
    b = b * modinv(a / g, p) % p;
    bias++;
    if(b == 1) return bias;
  }

  // p <= r^2

  ll ok = p, ng = 0;
  while(ok - ng > 1) {
    ll mid = (ok + ng) >> 1;
    if(mid * mid >= p)
      ok = mid;
    else
      ng = mid;
  }

  int r = ok;

  ll A = modpow(a, r, p);
  ll ainv = modinv(a, p);

  map< ll, int > table;

  // baby step
  ll baby = b;
  for(int i = 0; i < r; i++, baby = baby * ainv % p) {
    table[baby] = max(table[baby], r - i);
  }

  // giant step
  ll giant = 1;
  for(int i = 0; i <= r; i++, giant = giant * A % p) {
    if(table.count(giant)) {
      return (ll) i * r + r - table[giant] + bias;
    }
  }

  return -1;
}

// }}}

// @new TEST-modlog

#if 0
// {{{
// #undef DEBUG
// #define DEBUG
// DEBUG {{{
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

set<int> V;
#define RESET(x) (V.clear())
#define C(x) (V.insert(__LINE__), x)

/// --- math {{{ ///
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ll extgcd(ll a, ll b, ll &x, ll &y) {
  ll d;
  return b == 0 ? (x = a < 0 ? -1 : 1, y = 0, a < 0 ? -a : a)
                : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
}
ll modinv(ll a, ll mod) {
  ll x, y;
  extgcd(a, mod, x, y);
  if(x < 0) x += mod;
  return x;
}
ll modpow(ll a, ll b, ll mod) {
  ll r = 1;
  a %= mod;
  while(b) {
    if(b & 1) r = r * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return r;
}
/// }}}--- ///

// require math library
// modlog(a, b, p) = log_a b
// gcd(a, p) = 1
// modlog {{{

// Baby-Step Giant-Step algorithm
ll modlog(ll a, ll b, ll p) {
  a %= p;
  b %= p;
  if(a < 0) a += p;
  if(b < 0) b += p;

  if(a == 1 && b != 1) return -1;
  if(b == 1) return 0;

  ll g;
  ll bias = 0;
  while((g = gcd(a, p)) != 1) {
    if(b % g != 0) return -1;
    b /= g;
    p /= g;
    b = b * modinv(a / g, p) % p;
    bias++;
    if(b == 1) return C(bias);
  }
  if(bias) C(0);

  // p <= r^2

  ll ok = p, ng = 0;
  while(ok - ng > 1) {
    ll mid = (ok + ng) >> 1;
    if(mid * mid >= p) ok = mid;
    else ng = mid;
  }

  int r = ok;
  
  ll A = modpow(a, r, p);
  ll ainv = modinv(a, p);

  map<ll, int> table;
  
  // baby step
  ll baby = b;
  for(int i = 0; i < r; i++, baby = baby * ainv % p) {
    table[baby] = max(table[baby], r - i);
  }

  // giant step
  ll giant = 1;
  for(int i = 0; i <= r; i++, giant = giant * A % p) {
    if(table.count(giant)) {
      return C((ll) i * r + r - table[giant] + bias);
    }
  }

  return -1;
}

// }}}

ll test1(ll a, ll b, ll p) {
  if(p <= 0) return -1;
  a %= p;
  b %= p;
  ll t = modlog(a, b, p);
  assert(t == -1 || modpow(a, t, p) == b);
  return t;
}

ll test2(ll a, ll k, ll p) {
  if(p <= 0) return -1;
  ll b = modpow(a, k, p);
  ll t = test1(a, b, p);
  assert(t != -1);

  if(t != -1 && t < 1000) {
    C(0);
    for(int i = 0; i < t; i++) {
      assert(modpow(a, i, p) != b);
    }
  }

  return t;
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);

  random_device rnd;
  mt19937 mt(rnd());

  int T = 20;

  for(int i = 0; i < T; i++) {
    ll a = mt();
    ll b = mt();
    ll p = mt() % int(2e9);
    test1(a, b, p);
  }

  for(int i = 0; i < T; i++) {
    ll a = mt();
    ll k = mt();
    ll p = mt() % int(2e9);
    test2(a, k, p);
  }

  test2(2 * 3 * 3, 777,
      (ll)
      2 * 2 * 2 * 2 * 2 *
      3 * 3 * 3 * 3 * 3 *
      7
      );

  test2(2 * 3 * 3, 3323,
      (ll)
      2 * 2 * 2 * 2 * 2 *
      3 * 3 * 3 * 3 * 3 *
      7
      );

  test2(2 * 3 * 3 * 43, 1132,
      (ll)
      2 * 2 * 2 * 2 * 2 *
      3 * 3 * 3 * 3 * 3 *
      7 * 11
      );

  assert(V.size() == 4);
  dump("done");
  return 0;
}


// }}}
#endif

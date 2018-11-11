// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ modsqrt with Tonelli-Shanks algorithm
// @snippet modsqrt
// @alias sqrt_mod legendre is_quadratic_residue heihoujouyo rujandoru

// require math library
// modsqrt {{{

inline int legendre(ll a, ll p) {
  a %= p;
  if(a < 0) a += p;
  // a ^ ((p - 1) / 2) mod p
  return a == 0 ? 0 : modpow(a, p >> 1, p) == 1 ? 1 : -1;
}

#include <random>

// simplified Tonelli-Shanks algorithm
// a : quadratic residue (if not, return -1)
// p : odd prime
ll modsqrt(ll a, ll p) {
  a = a % p;
  if(a < 0) a += p;

  if(a == 0) return 0;

  if(legendre(a, p) == -1) return -1;

  int s = 1;
  ll q = p >> 1;
  while((q & 1) == 0) q >>= 1, ++s;

  static mt19937 mt;
  ll z;
  do {
    z = 2 + mt() % (p - 2);
  } while(modpow(z, p >> 1, p) == 1);

  int m = s;
  ll c = modpow(z, q, p);
  ll t = modpow(a, q, p);
  ll r = modpow(a, (q + 1) >> 1, p);

  for(; m > 1; --m) {
    ll b = modpow(t, ll(1) << (m - 2), p);
    if(b != 1) r = r * c % p, t = c * c % p * t % p;
    c = c * c % p;
  }
  return r;
}

ll modsqrt(ll a, ll p, ll y) {
  ll x = modsqrt(a, p);
  ll py = 1;
  for(ll i = 0; i < y; i++) py *= p;
  return modpow(x, py / p, py) * modpow(a, (py + 1) / 2 - py / p, py) % py;
}

// }}}

// @new TEST tonnelli-shanks algorithm

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

/// --- isPrime {{{ ///

bool isPrime(ll n) {
  if(n < 2) return false;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i == 0) return false;
  }
  return true;
}

/// }}}--- ///

// {{{
int main() {
  ll mods[] = {
      3, 5, 7, 11, 10007, ll(1e9 + 7), ll(1e9 + 9), 199181, 95009, 92179};
  ll nums[] = {1234,    1234567, 14567, 7654, 2345,   2381, 4823, 58184,
               3838431, 38482,   23832, 4283, 384194, 49,   2312, 1124};

  for(ll p : mods) {
    assert(isPrime(p));
    dump(p, p % 8);
    for(ll num : nums) {
      if(legendre(num, p) == 1) {
        dump(num, p);
        ll py = 1;
        for(int i = 1; i <= 1; i++) {
          py *= p;
          ll x = modsqrt(num, p, i);
          assert(x * x % py == num % py);
        }
      }
    }
  }

  dump("done");

  return 0;
}
// }}}

// @ Kitamasa Fast
// あとでやる
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ll extgcd(ll a, ll b, ll &x, ll &y) {
  ll d;
  return b == 0 ? (x = 1, y = 0, a)
                : (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
}
ll modinv(ll a, ll mod = 1e9 + 7) {
  ll x = 0, y = 0;
  extgcd(a, mod, x, y);
  return (x + mod) % mod;
}
ll modpow(ll a, ll b, ll mod = 1e9 + 7) {
  ll r = 1;
  a %= mod;
  while(b) {
    if(b & 1) r = r * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return r;
}

// require math library
struct NTT {
  const ll mod, primitive;
  NTT() : mod(1), primitive(0) {}
  NTT(ll mod, ll primitive) : mod(mod), primitive(primitive) {}
  void fft(vector< int > &a, bool inv = 0) const {
    int n = a.size();
    int h = 31 - __builtin_clz(n);
    // bitの反転
    for(int i = 0; i < n; i++) {
      int j = 0;
      for(int k = 0; k < h; k++) j |= (i >> k & 1) << (h - 1 - k);
      if(i < j) swap(a[i], a[j]);
    }
    // i : 今考えている多項式の次数 / 2
    for(int i = 1; i < n; i *= 2) {
      ll zeta = modpow(primitive, (mod - 1) / (i * 2), mod);
      if(inv) zeta = modinv(zeta, mod);
      ll tmp = 1;
      // j : 指数
      for(int j = 0; j < i; j++) {
        // k : 何個目の多項式か
        for(int k = 0; k < n; k += i * 2) {
          ll s = a[k + j + 0];
          ll t = (ll) a[k + j + i] * tmp % mod;
          a[k + j + 0] = (s + t) % mod;
          a[k + j + i] = (s - t + mod) % mod;
        }
        tmp = tmp * zeta % mod;
      }
    }
    int invn = modinv(n, mod);
    if(inv)
      for(int i = 0; i < n; i++) a[i] = a[i] * invn % mod;
    // for(int i = 0; i < n; i++) a[i] = (a[i] + mod) % mod;
  }
  template < class T, class U >
  vector< int > conv(vector< T > aa, vector< U > bb, int _n = -1) const {
    int deg = aa.size() + bb.size() - 1;
    int n = 1;
    if(_n < 0)
      while(n < deg) n <<= 1;
    else
      n = _n;
    vector< int > a(n), b(n);
    for(size_t i = 0; i < aa.size(); i++) a[i] = aa[i] % mod;
    for(size_t i = 0; i < bb.size(); i++) b[i] = bb[i] % mod;
    fft(a), fft(b);
    vector< int > c(n);
    for(int i = 0; i < n; i++) c[i] = a[i] * b[i] % mod;
    fft(c, 1);
    c.resize(deg);
    return c;
  }
};

vector< NTT > ntts{
    NTT((1 << 24) * 73 + 1, 3),
    NTT((1 << 21) * 3 * 7 * 23 + 1, 5),
    NTT((1 << 25) * 5 + 1, 3),
    NTT((1 << 26) * 7 + 1, 3),
    NTT((1 << 21) * 3 * 3 * 7 * 7 + 1, 5),
};

// require garner library when use more than 2 ntt
ll garner(vector< int > n, vector< int > mods, ll mod);
template < class T, class U >
vector< ll > conv(const vector< T > &a, const vector< U > &b, int use = 1,
                  ll mod = (ll) 1e9 + 7) {
  int deg = a.size() + b.size() - 1;
  int n = 1;
  while(n < deg) n <<= 1;
  vector< vector< int > > cs;
  auto nlist = ntts;
  nlist.resize(use);
  for(auto ntt : nlist) {
    cs.emplace_back(ntt.conv(a, b, n));
  }
  if(use == 1) return vector< ll >(begin(cs[0]), end(cs[0]));
  vector< int > res(deg);
  vector< int > mods(use);
  for(int j = 0; j < use; j++) {
    mods[j] = nlist[j].mod;
  }
  vector< int > vals(use);
  for(int i = 0; i < deg; i++) {
    for(int j = 0; j < use; j++) {
      vals[j] = cs[j][i];
    }
    res[i] = garner(vals, mods, mod);
  }
  return res;
}

ll garner(vector< int > n, vector< int > mods, ll mod) {
  n.emplace_back(0);
  mods.emplace_back(mod);
  vector< ll > coeffs(n.size(), 1); // v_i の係数
  // v_i の項より後ろの項の和,答え mod mods[i]
  vector< ll > constants(n.size(), 0);
  for(size_t i = 0; i < n.size(); i++) {
    // coeffs[i] * v_i + constants[i] == n[i] (mod mods[i]) を解く
    ll v = ll(n[i] - constants[i]) * modinv(coeffs[i], mods[i]) % mods[i];
    if(v < 0) v += mods[i];
    for(size_t j = i + 1; j < n.size(); j++) {
      // coeffs[j] is (mod j)
      (constants[j] += coeffs[j] * v) %= mods[j];
      (coeffs[j] *= mods[i]) %= mods[j];
    }
  }
  return constants.back();
}

vector< int > mult(const vector< int > &c, const vector< int > &a,
                   const vector< int > &b, const NTT &ntt) {
  const int k = c.size();
  const int deg = k * 2 - 1;
  int n = 1;
  while(n < deg) n <<= 1;
  vector< int > ic(1, 1);
  int t = 1;
  while(t <= k) {
    t = min(2 * t, k + 1);
    auto c2 = c;
    c2.resize(t);
    auto cur = ntt.conv(c2, ic);
    cur[0] += 2;
    cur.resize(t);
    ic = ntt.conv(ic, cur);
    ic.resize(t);
  }
  auto beta = ntt.conv(a, b);
  auto q = ntt.conv(beta, ic);
  q.resize(k - 1);
  auto r = ntt.conv(c, q);
  vector< int > res(k);
  for(int i = k - 1; i < 2 * k - 1; i++) {
    res[i - k + 1] = i >= deg ? r[i - deg] : beta[i];
  }
  return res;
}

ll kitamasa(ll n, const vector< int > &c, const vector< int > &a, int use = 1,
            ll mod = (ll) 1e9 + 7) {
  const int k = c.size();
  if(n < k) return a[n];
  vector< int > r(k), t(k);
  r[0] = t[1] = 1;
  vector< int > vals(use), mods(use);
  for(int i = 0; i < use; i++) {
    while(n) {
      if(n & 1) r = mult(c, r, t, ntts[i]);
      t = mult(c, t, t, ntts[i]);
      n >>= 1;
    }
    int res = 0;
    for(int i = 0; i < k; i++)
      res = (res + (ll) a[i] * r[i] % ntts[i].mod) % ntts[i].mod;
    vals[i] = res;
  }
  return garner(vals, mods, mod);
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);
  int n, k;
  cin >> k >> n;
  n--;
  vector< int > c(k, 1);
  vector< int > a(k, 1);
  cout << kitamasa(n, c, a) << endl;
  return 0;
}

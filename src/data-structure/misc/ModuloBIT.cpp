// @import header
// @@
// @name MODBIT Library
// @snippet     modbit
/// --- MODBIT Library {{{ ///

struct MODBIT{
  int n;
  vector<int> data;
  int mod;
  MODBIT(int n, int mod = 1e9 + 7): n(n), data(n), mod(mod) {}
  void add(int i, long long x) {
    x %= mod;
    i++;
    while(i<=n){
      data[i - 1] = ((data[i - 1] + x) % mod + mod) % mod;
      i += i & -i;
    }
  }
  int sum(int i) {
    if(i<0) return 0;
    i++;
    long long s = 0;
    while(i>0){
      s += data[i - 1];
      i -= i & -i;
    }
    return (s % mod + mod) % mod;
  }
  int range(int a, int b) {
    return (sum(b) - sum(a-1)) % mod;
  }
};

/// }}}--- ///
// MODBIT bit(N, mod);


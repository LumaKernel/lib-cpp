// @import header
// @@
// @name Garner
// @title Garnerのアルゴリズム
/// --- Garner {{{ ///
ll garner(vector<ll> n, vector<ll> mods, ll mod);
template<typename T>
vector<ll> conv(vector<T> a, vector<T> b, int use = 1, ll mod = 1e9 + 7) {
  vector< vector<ll> > cs;
  auto nlist = ntts;
  nlist.resize(use);
  for(auto ntt : nlist) {
    cs.emplace_back(ntt.conv(a, b));
  }
  if(use == 1) return cs[0];
  int n = cs[0].size();
  vector<ll> c(n);
  for(int i = 0; i < n; i++) {
    vector<ll> vals(use), mods(use);
    for(int j = 0; j < use; j++) {
      vals[j] = cs[j][i];
      mods[j] = nlist[j].mod;
    }
    c[i] = garner(vals, mods, mod);
  }
  return c;
}
/// }}}--- ///

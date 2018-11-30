// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Garner Library
// @snippet garner

// require math library
/// --- Garner Library {{{ ///
#include <vector>
ll garner(const vector< ll > &x, vector< ll > mods, ll mod) {
  mods.emplace_back(mod);
  vector< ll > coeffs(x.size() + 1, 1); // coeffs[i]v_i
  vector< ll > constants(x.size() + 1, 0);
  for(size_t i = 0; i < x.size(); i++) {
    // x[i] - constants[i] == coeffs[i] * v_i (mod mods[i])
    ll v = (x[i] - constants[i]) * modinv(coeffs[i], mods[i]) % mods[i];
    if(v < 0) v += mods[i];
    for(size_t j = i + 1; j < x.size() + 1; j++) {
      // coeffs[j] is (mod mods[j])
      constants[j] = (constants[j] + coeffs[j] * v) % mods[j];
      coeffs[j] = (coeffs[j] * mods[i]) % mods[j];
    }
  }
  return constants.back();
}
/// }}}--- ///

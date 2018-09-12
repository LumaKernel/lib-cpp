// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Garner Library
// @snippet garner

/// --- Garner Library {{{ ///
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
/// }}}--- ///

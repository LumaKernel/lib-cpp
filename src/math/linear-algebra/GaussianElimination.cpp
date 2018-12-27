// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Gaussian Elimination
// @snippet     gaussjordan
// @alias       gauss

// return 0-length vector when unsolvable
/// --- Gauss {{{ ///
#include<vector>
#include<cassert>
template<class T>
vector<T> Gauss(vector<vector<T>> mat, vector<T> v, T eps = T(1e-9)) {
  int n = mat.size();
  assert(n == (int) mat[0].size() && n == (int) v.size());
  for(int i = 0; i < (int) v.size(); i++) {
    mat[i].emplace_back(v[i]);
  }
  for(int i = 0; i < n; i++) {
    int pivot = i;
    for(int j = i + 1; j < n; j++) {
      if(abs(mat[pivot][i] < abs(mat[j][i]))) pivot = j;
    }
    if(mat[pivot][i] <= eps) return vector<T>();
    swap(mat[i], mat[pivot]);
    for(int j = i + 1; j <= n; j++) {
      mat[i][j] /= mat[i][i];
    }
    for(int j = 0; j < n; j++)
      if(j != i) {
        for(int k = i + 1; k <= n; k++) {
          mat[j][k] -= mat[j][i] * mat[i][k];
        }
      }
  }
  for(int i = 0; i < n; i++) v[i] = mat[i][n];
  return v;
}
/// }}}--- ///

// @ Matrix Determinant
// @snippet det

// require Gaussian Elimination
// det {{{
template<class T>
T det(vector<vector<T>> mat) {
  vector<T> v(mat.size(), T(1));
  v = Gauss(mat, v);
  T res(1);
  for(size_t i = 0; i < v.size(); i++) {
    assert(v[i] != T(0));
    res /= v[i];
  }
  return res;
}
// }}}

// @ Matrix Rank
// @snippet det

// require Gaussian Elimination
// det {{{
template<class T>
T det(vector<vector<T>> mat) {
  vector<T> v(mat.size(), T(1));
  v = Gauss(mat, v);
  T res(1);
  for(size_t i = 0; i < v.size(); i++) {
    assert(v[i] != T(0));
    res /= v[i];
  }
  return res;
}
// }}}

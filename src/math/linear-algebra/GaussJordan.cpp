// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name GaussJordan
// @snippet     gaussjordan
// @alias       gauss
using Vec = vector< double >;
using Mat = vector< Vec >;
/// --- GaussJordan {{{ ///
Vec gaussJordan(Mat mat, Vec v, double eps = 1e-9) {
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
    if(mat[pivot][i] < eps) return Vec();
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

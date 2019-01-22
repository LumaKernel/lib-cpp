// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Gaussian Elimination
// @snippet     gaussjordan
// @alias       gauss

// return (m + 1)-length vector when unsolvable
// NOTE : when size < m , indefite
/// --- Gaussian Elimination {{{ ///
#include <cassert>
#include <vector>
template < class T >
vector< T > Gauss_float(vector< vector< T > > mat, vector< T > v, T eps = T(1e-9)) {
  size_t n = mat.size(), m = mat[0].size();
  assert(n == v.size());
  for(size_t i = 0; i < n; i++) {
    mat[i].emplace_back(v[i]);
  }
  size_t now = 0;
  for(size_t i = 0; i < m; i++) {
    int pivot = i;
    // pivotting
    for(size_t j = i + 1; j < m; j++) {
      if(abs(mat[pivot][i] < abs(mat[j][i]))) pivot = j;
    }
    if(mat[pivot][i] <= eps) continue;
    swap(mat[now], mat[pivot]);
    for(size_t j = i + 1; j <= n; j++) {
      mat[now][j] /= mat[now][i];
    }
    for(size_t j = 0; j < n; j++)
      if(j != i) {
        for(size_t k = i + 1; k <= n; k++) {
          mat[j][k] -= mat[j][i] * mat[now][k];
        }
      }
    now++;
    if(now == n) break;
  }
  v.resize(now);
  for(size_t i = 0; i < now; i++) v[i] = mat[i][m];
  for(size_t i = now; i < n; i++) {
    T r(0);
    if(now == m) {
      for(size_t j = 0; j < m; j++) {
        r += mat[i][j] * v[j];
      }
    }
    r -= mat[i][m];
    if(abs(r) > eps) return vector<T>(m + 1);
  }
  return v;
}
template < class T >
vector< T > Gauss(vector< vector< T > > mat, vector< T > v) {
  size_t n = mat.size(), m = mat[0].size();
  assert(n == v.size());
  for(size_t i = 0; i < n; i++) {
    mat[i].emplace_back(v[i]);
  }
  size_t now = 0;
  for(size_t i = 0; i < m; i++) {
    for(size_t j = i + 1; j <= n; j++) {
      mat[now][j] /= mat[now][i];
    }
    for(size_t j = 0; j < n; j++)
      if(j != i) {
        for(size_t k = i + 1; k <= n; k++) {
          mat[j][k] -= mat[j][i] * mat[now][k];
        }
      }
    now++;
    if(now == n) break;
  }
  v.resize(now);
  for(size_t i = 0; i < now; i++) v[i] = mat[i][m];
  for(size_t i = now; i < n; i++) {
    T r(0);
    if(now == m) {
      for(size_t j = 0; j < m; j++) {
        r += mat[i][j] * v[j];
      }
    }
    r -= mat[i][m];
    if(r != T(0)) return vector<T>(m + 1);
  }
  return v;
}
/// }}}--- ///

// @ Matrix Determinant
// @snippet det

// det {{{
template < class T >
T det_float(vector< vector< T > > mat, T eps = T(1e-9)) {
  size_t n = mat.size();
  assert(n == mat[0].size());
  T res(1);
  for(size_t i = 0; i < n; i++) {
    int pivot = i;
    // pivotting
    for(size_t j = i + 1; j < n; j++) {
      if(abs(mat[pivot][i]) < abs(mat[j][i])) pivot = j;
    }
    if(mat[pivot][i] <= eps) return T(0);
    swap(mat[i], mat[pivot]);
    res *= mat[i][i];
    for(size_t j = i + 1; j < n; j++) {
      mat[i][j] /= mat[i][i];
    }
    for(size_t j = i + 1; j < n; j++)
      for(size_t k = i + 1; k < n; k++) {
        mat[j][k] -= mat[j][i] * mat[i][k];
      }
  }
  return res;
}
template < class T >
T det(vector< vector< T > > mat, T eps = T(1e-9)) {
  size_t n = mat.size();
  assert(n == mat[0].size());
  T res(1);
  for(size_t i = 0; i < n; i++) {
    res *= mat[i][i];
    for(size_t j = i + 1; j < n; j++) {
      mat[i][j] /= mat[i][i];
    }
    for(size_t j = i + 1; j < n; j++)
      for(size_t k = i + 1; k < n; k++) {
        mat[j][k] -= mat[j][i] * mat[i][k];
      }
  }
  return res;
}
// }}}

// @ Matrix Rank
// @snippet rank

// rank {{{
template < class T >
int matrank(vector< vector< T > > mat) {
  size_t n = mat.size(), m = mat[0].size();
  int res = 0;
  size_t now = 0;
  for(size_t i = 0; i < m; i++) {
    if(mat[now][i] == 0) continue;
    for(size_t j = i + 1; j < m; j++) {
      mat[now][j] /= mat[now][i];
    }
    for(size_t j = now + 1; j < n; j++)
      for(size_t k = i + 1; k < m; k++) {
        mat[j][k] -= mat[j][i] * mat[now][k];
      }
    now++;
    res++;
    if(now == n) break;
  }
  return res;
}
// }}}


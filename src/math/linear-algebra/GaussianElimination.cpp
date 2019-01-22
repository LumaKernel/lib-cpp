// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ Gaussian Elimination
// @snippet     gaussjordan
// @alias       gauss

// return ( values, isSolvable, rank )
// return 0-length vector when unsolvable
/// --- Gaussian Elimination {{{ ///
// using Gauss-Jordan Elimination
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>
template < class T >
tuple< vector< T >, bool, int > Gauss_float(vector< vector< T > > &mat, vector< T > v,
                                      T eps = T(1e-9)) {
  size_t n = mat.size(), m = mat[0].size();
  assert(n == v.size());
  for(size_t i = 0; i < n; i++) {
    mat[i].push_back(v[i]);
  }
  size_t now = 0;
  for(size_t i = 0; i < m; i++) {
    int pivot = now;
    // pivotting
    for(size_t j = now + 1; j < n; j++) {
      if(abs(mat[pivot][i]) < abs(mat[j][i])) pivot = j;
    }
    if(abs(mat[pivot][i]) <= eps) continue;
    swap(mat[now], mat[pivot]);
    for(size_t j = i + 1; j <= m; j++) {
      mat[now][j] /= mat[now][i];
    }
    for(size_t j = 0; j < n; j++)
      if(j != i) {
        for(size_t k = i + 1; k <= m; k++) {
          mat[j][k] -= mat[j][i] * mat[now][k];
        }
      }
    now++;
    if(now == n) break;
  }
  for(size_t i = 0; i < n; i++) v[i] = mat[i][m];
  for(size_t i = now; i < n; i++) {
    if(abs(mat[i][m]) > eps) return make_tuple(v, false, now);
  }
  return make_tuple(v, true, now);
}
template < class T >
tuple< vector< T >, bool, int > Gauss(vector< vector< T > > &mat, vector< T > v) {
  size_t n = mat.size(), m = mat[0].size();
  assert(n == v.size());
  for(size_t i = 0; i < n; i++) {
    mat[i].push_back(v[i]);
  }
  size_t now = 0;
  for(size_t i = 0; i < m; i++) {
    int pivot = now;
    // pivotting
    for(size_t j = now + 1; j < n; j++) {
      if(mat[pivot][i] != T(0)) break;
      pivot = j;
    }
    if(mat[pivot][i] == T(0)) continue;
    swap(mat[now], mat[pivot]);
    for(size_t j = i + 1; j <= m; j++) {
      mat[now][j] /= mat[now][i];
    }
    for(size_t j = 0; j < n; j++)
      if(j != i) {
        for(size_t k = i + 1; k <= m; k++) {
          mat[j][k] -= mat[j][i] * mat[now][k];
        }
      }
    now++;
    if(now == n) break;
  }
  for(size_t i = 0; i < n; i++) v[i] = mat[i][m];
  for(size_t i = now; i < n; i++) {
    if(mat[i][m] != T(0)) return make_tuple(v, false, now);
  }
  return make_tuple(v, true, now);
}
/// }}}--- ///

// @new
// @ Matrix Determinant
// @snippet det

// det {{{
#include <cassert>
#include <cmath>
#include <vector>
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
    if(abs(mat[pivot][i]) <= eps) return T(0);
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
T det(vector< vector< T > > mat) {
  size_t n = mat.size();
  assert(n == mat[0].size());
  T res(1);
  for(size_t i = 0; i < n; i++) {
    int pivot = i;
    // pivotting
    for(size_t j = i + 1; j < n; j++) {
      if(mat[pivot][i] != T(0)) break;
      pivot = j;
    }
    if(mat[pivot][i] == T(0)) return T(0);
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
// }}}

// @new
// @ Matrix Rank
// @snippet rank
// @alias matrank

// matrank, degree_of_freedom {{{
#include <vector>
template < class T >
int matrank(vector< vector< T > > mat) {
  size_t n = mat.size(), m = mat[0].size();
  size_t now = 0;
  for(size_t i = 0; i < m; i++) {
    int pivot = now;
    // pivotting
    for(size_t j = now + 1; j < n; j++) {
      if(mat[pivot][i] != T(0)) break;
      pivot = j;
    }
    if(mat[pivot][i] == T(0)) continue;
    swap(mat[now], mat[pivot]);
    for(size_t j = i + 1; j < m; j++) {
      mat[now][j] /= mat[now][i];
    }
    for(size_t j = now + 1; j < n; j++)
      for(size_t k = i + 1; k < m; k++) {
        mat[j][k] -= mat[j][i] * mat[now][k];
      }
    now++;
    if(now == n) break;
  }
  return now;
}
template < class T >
int degree_of_freedom(const vector< vector< T > > &mat) {
  return mat[0].size() - matrank(mat);
}
// }}}

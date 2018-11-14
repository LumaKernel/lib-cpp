// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name givens
// @title 連立一次方程式 (Givens)
// @snippet     givens
using Vec = vector< double >;
using Mat = vector< Vec >;
#define mkrot(x, y, c, s)           \
  {                                 \
    double r = sqrt(x * x + y * y); \
    c = x / r;                      \
    s = y / r;                      \
  }
#define rot(x, y, c, s)        \
  {                            \
    double u = c * x + s * y;  \
    double v = -s * x + c * y; \
    x = u;                     \
    y = v;                     \
  }
Vec givens(Mat A, Vec b) {
  const int n = b.size();
  for(int i = 0; i < n; ++i)
    for(int j = i + 1; j < n; ++j) {
      double c, s;
      mkrot(A[i][i], A[j][i], c, s);
      rot(b[i], b[j], c, s);
      for(int k = i; k < n; k++) rot(A[i][k], A[j][k], c, s);
    }
  for(int i = n - 1; i >= 0; --i) {
    for(int j = i + 1; j < n; ++j) b[i] -= A[i][j] * b[j];
    b[i] /= A[i][i];
  }
  return b;
}

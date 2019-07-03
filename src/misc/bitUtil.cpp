// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name msb
// @snippet     msb
// @alias       topbit
int msb(int x) {
  x = x & 0xFFFF0000 ? x & 0xFFFF0000 : x;
  x = x & 0xFF00FF00 ? x & 0xFF00FF00 : x;
  x = x & 0xF0F0F0F0 ? x & 0xF0F0F0F0 : x;
  x = x & 0xCCCCCCCC ? x & 0xCCCCCCCC : x;
  x = x & 0xAAAAAAAA ? x & 0xAAAAAAAA : x;
  return x;
}

// @new msbll
// @snippet     msbll
// @alias     topbitll
int msbll(ll x) {
  x = x & 0xFFFFFFFF00000000 ? x & 0xFFFFFFFF00000000 : x;
  x = x & 0xFFFF0000FFFF0000 ? x & 0xFFFF0000FFFF0000 : x;
  x = x & 0xFF00FF00FF00FF00 ? x & 0xFF00FF00FF00FF00 : x;
  x = x & 0xF0F0F0F0F0F0F0F0 ? x & 0xF0F0F0F0F0F0F0F0 : x;
  x = x & 0xCCCCCCCCCCCCCCCC ? x & 0xCCCCCCCCCCCCCCCC : x;
  x = x & 0xAAAAAAAAAAAAAAAA ? x & 0xAAAAAAAAAAAAAAAA : x;
  return x;
}

// @new logmsb
// @snippet     logmsb
// @alias       log2_int
int logmsb(int x) {
  int h = 0;
  x = x & 0xFFFF0000 ? (h += 16, x) & 0xFFFF0000 : x;
  x = x & 0xFF00FF00 ? (h += 8, x) & 0xFF00FF00 : x;
  x = x & 0xF0F0F0F0 ? (h += 4, x) & 0xF0F0F0F0 : x;
  x = x & 0xCCCCCCCC ? (h += 2, x) & 0xCCCCCCCC : x;
  x = x & 0xAAAAAAAA ? (h += 1, x) & 0xAAAAAAAA : x;
  return h;
}

// @new logmsbll
// @snippet     logmsbll
// @alias       log2_ll
int logmsbll(ll x) {
  int h = 0;
  x = x & 0xFFFFFFFF00000000 ? (h += 32, x) & 0xFFFFFFFF00000000 : x;
  x = x & 0xFFFF0000FFFF0000 ? (h += 16, x) & 0xFFFF0000FFFF0000 : x;
  x = x & 0xFF00FF00FF00FF00 ? (h += 8, x) & 0xFF00FF00FF00FF00 : x;
  x = x & 0xF0F0F0F0F0F0F0F0 ? (h += 4, x) & 0xF0F0F0F0F0F0F0F0 : x;
  x = x & 0xCCCCCCCCCCCCCCCC ? (h += 2, x) & 0xCCCCCCCCCCCCCCCC : x;
  x = x & 0xAAAAAAAAAAAAAAAA ? (h += 1, x) & 0xAAAAAAAAAAAAAAAA : x;
  return h;
}

// @new popcount
// @snippet     popcount
int popcount(int x) {
  x = (x & 0x55555555) + ((x & 0xAAAAAAAA) >> 1);
  x = (x & 0x33333333) + ((x & 0xCCCCCCCC) >> 2);
  x = (x & 0x0F0F0F0F) + ((x & 0xF0F0F0F0) >> 4);
  x = (x & 0x00FF00FF) + ((x & 0xFF00FF00) >> 8);
  x = (x & 0x0000FFFF) + ((x & 0xFFFF0000) >> 16);
  return x;
}

// @new popcountll
// @snippet     popcountll
int popcountll(ll x) {
  x = (x & 0x5555555555555555) + ((x & 0xAAAAAAAAAAAAAAAA) >> 1);
  x = (x & 0x3333333333333333) + ((x & 0xCCCCCCCCCCCCCCCC) >> 2);
  x = (x & 0x0F0F0F0F0F0F0F0F) + ((x & 0xF0F0F0F0F0F0F0F0) >> 4);
  x = (x & 0x00FF00FF00FF00FF) + ((x & 0xFF00FF00FF00FF00) >> 8);
  x = (x & 0x0000FFFF0000FFFF) + ((x & 0xFFFF0000FFFF0000) >> 16);
  x = (x & 0x00000000FFFFFFFF) + ((x & 0xFFFFFFFF00000000) >> 32);
  return x;
}

// @new bitreverse
// @snippet     bitreverse
int bitreverse(int x) {
  x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
  x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
  x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
  x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
  x = (x << 16) | (x >> 16);
  return x;
}

// @new bitreversell
// @snippet     bitreversell
int bitreversell(ll x) {
  x = ((x & 0x5555555555555555) << 1) | ((x & 0xAAAAAAAAAAAAAAAA) >> 1);
  x = ((x & 0x3333333333333333) << 2) | ((x & 0xCCCCCCCCCCCCCCCC) >> 2);
  x = ((x & 0x0F0F0F0F0F0F0F0F) << 4) | ((x & 0xF0F0F0F0F0F0F0F0) >> 4);
  x = ((x & 0x00FF00FF00FF00FF) << 8) | ((x & 0xFF00FF00FF00FF00) >> 8);
  x = ((x & 0x0000FFFF0000FFFF) << 16) | ((x & 0xFFFF0000FFFF0000) >> 16);
  x = (x << 32) | (x >> 32);
  return x;
}

// @new bitrotation
// @snippet bitrot
// @alias rot_bit
// @alias rotation_bit
// @alias kaiten_bit
// x を右に r だけ回転 (b bits)
ll bitrot(ll x, int r, int b = 32) {
  r %= b;
  if(r < 0) r += b;
  if(r == 0) return x;
  return (x >> r) | ((x & ((1ll << r) - 1)) << (b - r));
}

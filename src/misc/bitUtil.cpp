// @import header
// @@
# reference : https://www.slideshare.net/KMC_JP/slide-www
// @name topbit
// @snippet     topbit
int topbit(int x) {
  x = x & 0xFFFF0000 ? x & 0xFFFF0000 : x;
  x = x & 0xFF00FF00 ? x & 0xFF00FF00 : x;
  x = x & 0xF0F0F0F0 ? x & 0xF0F0F0F0 : x;
  x = x & 0xCCCCCCCC ? x & 0xCCCCCCCC : x;
  x = x & 0xAAAAAAAA ? x & 0xAAAAAAAA : x;
  return x;
}

// @new topbitll
// @snippet     topbitll
int topbitll(long long x) {
  x = x & 0xFFFFFFFF00000000 ? x & 0xFFFFFFFF00000000 : x;
  x = x & 0xFFFF0000FFFF0000 ? x & 0xFFFF0000FFFF0000 : x;
  x = x & 0xFF00FF00FF00FF00 ? x & 0xFF00FF00FF00FF00 : x;
  x = x & 0xF0F0F0F0F0F0F0F0 ? x & 0xF0F0F0F0F0F0F0F0 : x;
  x = x & 0xCCCCCCCCCCCCCCCC ? x & 0xCCCCCCCCCCCCCCCC : x;
  x = x & 0xAAAAAAAAAAAAAAAA ? x & 0xAAAAAAAAAAAAAAAA : x;
  return x;
}

// @new logbin
// @snippet     logbin
int logbin(int x) {
  int h = 0;
  x = x & 0xFFFF0000 ? (h += 16, x) & 0xFFFF0000 : x;
  x = x & 0xFF00FF00 ? (h += 8, x) & 0xFF00FF00 : x;
  x = x & 0xF0F0F0F0 ? (h += 4, x) & 0xF0F0F0F0 : x;
  x = x & 0xCCCCCCCC ? (h += 2, x) & 0xCCCCCCCC : x;
  x = x & 0xAAAAAAAA ? (h += 1, x) & 0xAAAAAAAA : x;
  return h;
}

// @new logbinll
// @snippet     logbinll
int logbinll(long long x) {
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
  x = (x & 0x55555555)
    + ((x & 0xAAAAAAAA) >> 1);
  x = (x & 0x33333333)
    + ((x & 0xCCCCCCCC) >> 2);
  x = (x & 0x0F0F0F0F)
    + ((x & 0xF0F0F0F0) >> 4);
  x = (x & 0x00FF00FF)
    + ((x & 0xFF00FF00) >> 8);
  x = (x & 0x0000FFFF)
    + ((x & 0xFFFF0000) >> 16);
  return x;
}

// @new popcountll
// @snippet     popcountll
int popcountll(long long x) {
  x = (x & 0x5555555555555555)
    + ((x & 0xAAAAAAAAAAAAAAAA) >> 1);
  x = (x & 0x3333333333333333)
    + ((x & 0xCCCCCCCCCCCCCCCC) >> 2);
  x = (x & 0x0F0F0F0F0F0F0F0F)
    + ((x & 0xF0F0F0F0F0F0F0F0) >> 4);
  x = (x & 0x00FF00FF00FF00FF)
    + ((x & 0xFF00FF00FF00FF00) >> 8);
  x = (x & 0x0000FFFF0000FFFF)
    + ((x & 0xFFFF0000FFFF0000) >> 16);
  x = (x & 0x00000000FFFFFFFF)
    + ((x & 0xFFFFFFFF00000000) >> 32);
  return x;
}

// @new bitreverse
// @snippet     bitreverse
int bitreverse(int x) {
  x = ((x & 0x55555555) << 1)
    | ((x & 0xAAAAAAAA) >> 1);
  x = ((x & 0x33333333) << 2)
    | ((x & 0xCCCCCCCC) >> 2);
  x = ((x & 0x0F0F0F0F) << 4)
    | ((x & 0xF0F0F0F0) >> 4);
  x = ((x & 0x00FF00FF) << 8)
    | ((x & 0xFF00FF00) >> 8);
  x = (x << 16) | (x >> 16);
  return x;
}

// @new bitreversell
// @snippet     bitreversell
int bitreversell(long long x) {
  x = ((x & 0x5555555555555555) << 1)
    | ((x & 0xAAAAAAAAAAAAAAAA) >> 1);
  x = ((x & 0x3333333333333333) << 2)
    | ((x & 0xCCCCCCCCCCCCCCCC) >> 2);
  x = ((x & 0x0F0F0F0F0F0F0F0F) << 4)
    | ((x & 0xF0F0F0F0F0F0F0F0) >> 4);
  x = ((x & 0x00FF00FF00FF00FF) << 8)
    | ((x & 0xFF00FF00FF00FF00) >> 8);
  x = ((x & 0x0000FFFF0000FFFF) << 16)
    | ((x & 0xFFFF0000FFFF0000) >> 16);
  x = (x << 32) | (x >> 32);
  return x;
}

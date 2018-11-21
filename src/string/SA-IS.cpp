// @import header
// #include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @ SA-IS
// @snippet sa_is
/// --- SA-IS {{{ ///

#include <string>
#include <vector>

static string push_sentinel(const string &v) { return v + char(); }
template < class T >
static vector< T > push_sentinel(vector< T > v) {
  v.emplace_back(0);
  return v;
}

template < class _T = string, class U = char, int K = 128 >
struct SA {
  using T = _T;
  const int n;
  const T &s;
  vector< int > rnk;
  vector< int > sa;
  int operator[](int i) const { return sa[i]; }
  template < class V >
  SA(const string &s) : n(s.size()), s(s), rnk(n) {
    sa_is< T, U >(sa, push_sentinel(s), K);
    sa.erase(begin(sa));
    for(int i = 0; i < n; i++) rnk[sa[i]] = i;
  }
  template < class V = string, class W = char >
  void sa_is(vector< int > &sa, const V &s, int k) {
    int n = s.size();
    vector< int > S(n); // or L
    //
    S.back() = 1;
    for(int i = n - 2; i >= 0; i--) {
      if(s[i] < s[i + 1])
        S[i] = 1;
      else if(s[i] > s[i + 1])
        S[i] = 0;
      else
        S[i] = S[i + 1];
    }
    //
    vector< int > lms;
    for(int i = 0; i < n; i++)
      if(isLMS(S, i)) lms.emplace_back(i);
    auto seed = lms;

    vector< int > _sa;
    inducedSort< V, W >(_sa, s, k, S, seed);

    sa.resize(0);
    for(auto el : _sa)
      if(isLMS(S, el)) sa.emplace_back(el);

    vector< int > nums(n, -1);
    int num = 0;
    nums[sa[0]] = 0;

    for(int x = 0; x < (int) sa.size() - 1; x++) {
      int i = sa[x], j = sa[x + 1];
      int diff = 0;
      for(int d = 0; d < n; d++) {
        if(s[i + d] != s[j + d] || isLMS(S, i + d) != isLMS(S, j + d)) {
          diff = 1;
          break;
        } else if(d && (isLMS(S, i + d) || isLMS(S, j + d)))
          break;
      }
      if(diff) num++;
      nums[j] = num;
    }
    auto _nums = nums;
    nums.resize(0);
    for(int el : _nums)
      if(el != -1) nums.emplace_back(el);

    if(num + 1 < (int) nums.size()) {
      sa_is< vector< int >, int >(seed, nums, num + 1);
    } else {
      seed.resize(num + 1);
      for(int i = 0; i < num + 1; i++) seed[nums[i]] = i;
    }

    for(int &el : seed) el = lms[el];

    inducedSort< V, W >(sa, s, k, S, seed);
  }
  template < class V = string, class W = char >
  void inducedSort(vector< int > &sa, const V &s, int k, const vector< int > &S,
                   const vector< int > &lms) {
    int n = s.size();
    sa.resize(n), sa.assign(n, -1);
    vector< int > bin(k + 1, 0);
    for(W ch : s) bin[ch + 1]++;
    int sum = 0;
    for(int &el : bin) el = sum += el;
    // step 1
    vector< int > count(k);
    for(auto it = rbegin(lms); it != rend(lms); ++it) {
      int i = *it;
      W ch = s[i];
      sa[bin[ch + 1] - 1 - count[ch]] = i;
      count[ch]++;
    }
    // step 2
    count.assign(k, 0);
    for(int i : sa) {
      if(i == -1 || i == 0) continue;
      if(S[i - 1]) continue;
      W ch = s[i - 1];
      sa[bin[ch] + count[ch]] = i - 1;
      count[ch]++;
    }
    // step 3
    count.assign(k, 0);
    for(auto it = rbegin(sa); it != rend(sa); ++it) {
      int i = *it;
      if(i == -1 || i == 0) continue;
      if(!S[i - 1]) continue;
      W ch = s[i - 1];
      sa[bin[ch + 1] - 1 - count[ch]] = i - 1;
      count[ch]++;
    }
  }
  inline bool isLMS(const vector< int > &S, int i) { return i > 0 && !S[i - 1] && S[i]; }
};

/// }}}--- ///

// @name manacher
// @title Manacher
// @snippet     manacher
// [i] = max radius as a palindrome when [i] is center
// NOTE : 偶数長ほしいなら'$'とか挿入してね
vector<int> Manacher(string s) {
  int n = s.size();
  int i = 0, j = 0;
  vector<int> R(n);
  while(i < n) {
    while(i - j >= 0 && i + j < n &&
        s[i - j] == s[i + j]) ++j;
    R[i] = j;
    int k = 1;
    while(i - k >= 0 && R[i - k] < j - k) R[i + k] = R[i - k], ++k;
    i += k, j -= k;
  }
  return R;
}

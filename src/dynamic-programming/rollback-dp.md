---
title: 戻すDP
---

# メモ

`dp[i]` が `dp[i+1]` から復元でき，任意をswapできると嬉しいことがある

i番目とN番目をswapしたときの`dp`を`swapped_dp`とすると，`dp[N]` と `swapped_dp[N]`が恒等的に等しくなり，`swapped_dp[N-1] (1-indexed)`が求められる 

つまり，特定のi番目をなかったことにしたりできる

これは多項式での積を考えると自明になる

つまり，多項式環において可換なため入れ替えることができ，逆元を書けるという操作 (割り算) ができるということ
境界値に頭を悩ませたりすることも少なくなるだろう

# 練習問題

* [D - 注文の多い高橋商店 - AtCoder](https://arc028.contest.atcoder.jp/tasks/arc028_4){:target="_blank"}<!--_-->

# 参考

* [戻すDP - sigma425のブログ](http://sigma425.hatenablog.com/entry/2015/07/31/121439){:target="_blank"}<!--_-->
* [多項式を使うテクニックたち - yukicoder wiki](https://yukicoder.me/wiki/polynomial_techniques){:target="_blank"}<!--_-->


---
title: 戻すDP
---

# メモ

`dp[i]` が `dp[i+1]` から復元でき，任意をswapできると嬉しいことがある

i番目とN番目をswapしたときの`dp`を`swapped_dp`とすると，`swapped_dp[N-1] (1-indexed)`が求められる

つまり，特定のi番目をなかったことにしたりできる

# 練習問題

* [D - 注文の多い高橋商店 - AtCoder](https://arc028.contest.atcoder.jp/tasks/arc028_4){:target="_blank"}<!--_-->

# 参考

* [戻すDP - sigma425のブログ](http://sigma425.hatenablog.com/entry/2015/07/31/121439){:target="_blank"}<!--_-->


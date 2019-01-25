---
title: 動的 Li-Chao Tree
---

[Li-Chao Tree]({{ "dynamic-programming/convex-hull-trick/LiChaoTree" | absolute_url }}) を動的にしただけです

`prebuild` が必要なくなりましたが，渡すxの範囲が分かる必要があります

# 実装

`DynamicLiChaoTree(L, R)` でxが\[L, R\)の範囲であることを意味します

// @ Dynamic Li-Chao Tree

## 計算量

$H = \log(\frac{R-L}{EPS})$ とおくと (整数なら $EPS=1$ )

* `add`
  * 直線追加なら $O(H)$
  * 線分追加なら $O(H^2)$
* `query`, `get` : $O(H)$

## 小数を使う場合

EPSを渡す必要があります

`(R-L)/EPS` の桁数が小数の仮数部に入りきる必要があります

この場合に限っては (線分クエリがなければ) [CHT-Ex]({{ "dynamic-programming/convex-hull-trick/CHT-Ex" | absolute_url }}) を使うほうが無難かと思います

# 検証

* [C - スペースエクスプローラー高橋君 - AtCoder](https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/3599211){:target="_blank"}<!--_-->
* [C - Kalila and Dimna in the Logging Industry - codeforces](https://codeforces.com/contest/319/submission/48887914){:target="_blank"}<!--_-->
  * overflowとTLが厳しいため，overflowする前に丸めるようにしている


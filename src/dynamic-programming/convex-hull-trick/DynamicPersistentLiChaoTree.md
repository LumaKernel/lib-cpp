---
title: 永続動的 Li-Chao Tree
---

[動的 Li-Chao Tree]({{ "dynamic-programming/convex-hull-trick/DynamicLiChaoTree" | absolute_url }}) を永続にしただけです

完全永続

# 実装

`DynamicPersistentLiChaoTree(L, R)` でxが\[L, R\)の範囲であることを意味します

初期の時間は0, その後1クエリ1ずつ増えます

`NIL` を使って実装を簡単にしています．メモリ解放はしていません

// @ Dynamic Persistent Li-Chao Tree

# 検証

* [C - スペースエクスプローラー高橋君 - AtCoder](https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/3599893){:target="_blank"}<!--_-->
* [C - スペースエクスプローラー高橋君 - AtCoder](https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/3599901){:target="_blank"}<!--_-->
  * ランダムな邪魔を入れて永続の確認 (MLE)

# 練習問題

いつ使うんでしょうね


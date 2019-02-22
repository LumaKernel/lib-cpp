---
title: 直線追加任意順序のCHT
---

[CHT]({{ "dynamic-programming/convex-hull-trick/CHT" | absolute_url }}) を直線を任意順序で追加できるようにしたもの

[Li-Chao Tree]({{ "dynamic-programming/convex-hull-trick/LiChaoTree" | absolute_url }}) で代用できる

直線の数を$N$，クエリの数を$Q$ とする

# 実装

オンラインクエリ可能

[ここ](http://d.hatena.ne.jp/sune2/20140310/1394440369){:target="_blank"}<!--_--> で紹介されているものに手を加えたもの

// @ Convex Hull Trick Extended

インターフェースは [CHT]({{ "dynamic-programming/convex-hull-trick/CHT" | absolute_url }}) と同じ

* `add` : ならし $O(\log N)$
* `get` : $O(\log N)$

# EPSについて

`(aの正の最小値)(bの正の最小値)` より小さな正の値を採用するといい

たとえばデフォルトでは `1e-19` になっているが，これは両方が小数9桁ずつを想定している

---

その他のTIPSに関しては [CHT]({{ "dynamic-programming/convex-hull-trick/CHT" | absolute_url }}) の方に載せています

# 検証

* [D - Computer Game - codeforces](https://codeforces.com/contest/1067/submission/45442782){:target="_blank"}<!--_-->
* [C - Kalila and Dimna in the Logging Industry - codeforces](https://codeforces.com/contest/319/submission/48890326){:target="_blank"}<!--_-->
  * overflow対策で `D = double` としています

# 練習問題

* [NIKKEI 2019本選 G - Greatest Journey (1200) - AtCoder](https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_g){:target="_blank"}<!--_-->

# 参考

* [Convex Hull Trick - 競技プログラミング+αなブログ](http://d.hatena.ne.jp/sune2/20140310/1394440369){:target="_blank"}<!--_-->


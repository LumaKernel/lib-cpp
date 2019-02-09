---
title: Monotone Minima
---

執筆中です

TODO : 図となにか

# 移動回数は準線形

$y, x$ が1ずつしか移動できないとします ([Mo]({{ "algorithm/Mo" | absolute_url }}) のようなイメージ)

$y$ は $O(H \log H)$ 回，$x$ は $O(W \log H)$ 回となります

解析は再帰の深さが $O(\log H)$ で各深さでそれぞれ $O(H)$, $O(W)$ だけ動けばよいからです (この証明はnoshiさんに教えてもらいました)

2冪に丸めて完全二分木上のDFSの経路の長さを解析することでも同様の結果を得られます

この性質が使える問題を [Divide and Conquer Optimization]({{ "dynamic-programming/Divide-and-Conquer-Optimization" | absolute_url }}) で紹介しています

# 実装

// @ Monotone Minima

# 参考

* [Totally Monotone Matrix Searching (SMAWK algorithm) - 週刊 spaghetti_source](https://topcoder.g.hatena.ne.jp/spaghetti_source/20120923/1348327542){:target="_blank"}<!--_-->
* [DP高速化 - ferinの競プロ帳](https://ferin-tech.hatenablog.com/entry/2018/02/23/071343){:target="_blank"}<!--_-->


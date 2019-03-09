---
title: 最小全域有向木問題 (Chu-Liu/Edmonds' algorithm)
---

Minimum Spanning Arborscense

詳細は [#参考](#参考) を参照してください

関連 - [最小全域木]({{ "graph/MST" | absolute_url }})

# 実装

$O(NM)$ , 構築もする場合は $O(NM \log N)$ ぐらいだとおもうんですがもっと速いかもしれません

[SCC]({{ "graph/StronglyConnectedComponent" | absolute_url }}) が必要

// @ Minimum Spanning Arborescence

# 検証

* [Spanning Tree - Minimum-Cost Arborescence - AOJ](http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3419423#1){:target="_blank"}<!--_-->

# 参考

* [最小全域有向木 - Chu-Liu/Edmondsのアルゴリズム](https://www.creativ.xyz/chu-liu-edmonds-522){:target="_blank"}<!--_-->
* [最小有向全域木を求める - Chu-Liu/Edmonds' algorithm - Ark's Blog](https://ark4rk.hatenablog.com/entry/2017/09/15/011937){:target="_blank"}<!--_-->
* [最小全域有向木（m log n） - ｼﾞｮｲｼﾞｮｲｼﾞｮｲ](http://joisino.hatenablog.com/entry/2017/01/11/230141){:target="_blank"}<!--_-->


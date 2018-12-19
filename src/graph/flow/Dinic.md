---
title: 最大フロー (Dinic)
---

[FordFulkerson]({{ "graph/flow/FordFulkerson" | absolute_url }})と基本的なところは同じ

流すことのできる辺のみをつかったBFSをして，sourceからの距離を求めて，距離が増える方へのみフローを流す，というのを繰り返す

$O(EV^2)$

* コスト1のみのとき， $$O(\min\{V^{2/3}, E^{1/2}\}E)$$
* 二部マッチングで使うときは $O(\sqrt V E)$

動的なもの（あとで辺の重みや辺自体が減ったり増えたり）ができなかった  
[FordFulkerson]({{ "graph/flow/FordFulkerson" | absolute_url }})ならできる  
なんでかとかはわかってない  
ちゃんと考えるとできるのかもしれない  

実用上はとても速いが最悪ケースが知られているため，任意のグラフが与えられるような問題は向いていない．**グラフに帰着できる問題**などは**意図的にグラフを操作しにくい**のであれば，Dinic法が有効，ということがある (参考 : [ここ](http://topcoder.g.hatena.ne.jp/Mi_Sawa/20140311){:target="_blank"}<!--_-->の「結論」)

# 実装

// @ Max Flow with Dinic

# 検証

* [AGC029F - Construction of a tree - AtCoder](https://atcoder.jp/contests/agc029/submissions/3823160){:target="_blank"}<!--_-->

# 練習問題

* [ARC074F - Lotus Leaves (800) - AtCoder](https://atcoder.jp/contests/arc074/tasks/arc074_d){:target="_blank"}<!--_-->
* [AGC029F - Construction of a tree (2200) - AtCoder](https://atcoder.jp/contests/agc029/tasks/agc029_f){:target="_blank"}<!--_-->

# 参考

* [Dinic's algorithm - wikipedia(en)](https://en.wikipedia.org/wiki/Dinic%27s_algorithm){:target="_blank"}
* [Dinic法 - Algoogle](http://algoogle.hadrori.jp/algorithm/dinic.html){:target="_blank"}
* [最大流問題について. - れんしゅうちょう。 - TopCoder部](http://topcoder.g.hatena.ne.jp/Mi_Sawa/20140311){:target="_blank"}<!--_-->
  * Dinic法とその計算量，最悪ケースや最悪ケースについて書かれています
* [最大流問題について その3 - れんしゅうちょう。 - TopCoder部](http://topcoder.g.hatena.ne.jp/Mi_Sawa/20140320){:target="_blank"}<!--_-->
  * LCTでの高速化について書かれています


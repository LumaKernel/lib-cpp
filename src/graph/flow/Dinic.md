---
title: 最大フロー (Dinic)
---

[FordFulkerson]({{ "graph/flow/FordFulkerson" | absolute_url }})と基本的なところは同じ．

流すことのできる辺のみをつかったBFSをして，sourceからの距離を求めて，  
距離が増える方へのみフローを流す，というのを繰り返す．

$ O(EV^2) $

* コスト1のみのとき， $O(\min\{V^{2/3}, E^{1/2}\}E)$
* 二部マッチングで使うときは $O(\sqrt{V}E)$

TODO : LCTで高速化できるらしく，やってみたく思っている．

動的なもの（あとで辺の重みや辺自体が減ったり増えたり）ができなかった．  
[FordFulkerson]({{ "graph/flow/FordFulkerson" | absolute_url }})ならできる．  
なんでかとかはわかってない．  
ちゃんと考えるとできるのかもしれない．

なんとなく動的を考慮した実装になっている．

// @ Dinic Libary

# 検証

* [F - Lotus Leaves \| AC](https://beta.atcoder.jp/contests/arc074/submissions/2141547){:target="_blank"}<!--_-->


# 参考

* [Dinic's algorithm - wikipedia(en)](https://en.wikipedia.org/wiki/Dinic%27s_algorithm){:target="_blank"}
* [Dinic法 - Algoogle](http://algoogle.hadrori.jp/algorithm/dinic.html){:target="_blank"}


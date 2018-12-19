---
title: 二部マッチング
---

**二部グラフ**に対する最大マッチングを最大流問題を用いて解く

$O(VE)$ だが実際はそれなりに速い (1000頂点250000辺とかでふつうに200msとか)．速くなる詳しい条件がちょっとわかっていない

[Dinic]({{ "graph/flow/Dinic" | absolute_url }}) を用いると $O(\sqrt V E)$ になる

# 実装

// @ BipartiteMatching

# 検証

* [C - 2D Plane 2N Points (400) - AtCoder](https://beta.atcoder.jp/contests/arc092/submissions/2225494){:target="_blank"}<!--_-->

### 二部グラフの最大安定集合の復元

* [F - Electric Scheme - codeforces](https://codeforces.com/contest/1054/submission/44568085){:target="_blank"}<!--_-->

### 二部グラフの最小辺カバーの復元

未verify

# 練習問題

* [C - 2D Plane 2N Points (400) - AtCoder](https://beta.atcoder.jp/contests/arc092/tasks/arc092_a){:target="_blank"}<!--_-->
* [F - Electric Scheme - codeforces](https://codeforces.com/contest/1054/problem/F){:target="_blank"}<!--_-->

# 参考

* [二部グラフの最小点被覆と最大安定集合と最小辺被覆の求め方 - SlideShare](https://www.slideshare.net/drken1215/ss-86894312){:target="_blank"}<!--_-->
* [二部グラフの最小点被覆、最大安定集合 (最大独立集合)、最小辺被覆を総整理！ - Qiita](https://qiita.com/drken/items/7f98315b56c95a6181a4){:target="_blank"}<!--_-->



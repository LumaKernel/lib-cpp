---
title: 木のダブリング
---

ダブリング自体は木でなくともできます．(数列とか?)

$ O(logN) $ で1クエリを処理でき，[HL分解]({{ "graph/HL-Decomposition" | absolute_url }})より時間計算量で有利ですが，  
空間計算量は $ O(N log N) $ とちょっと増えます．
[HL分解]({{ "graph/HL-Decomposition" | absolute_url }})とちがって，  
遅延させたりもできず，通常のセグ木でできることができます．

// @ Doubilng Tree Library

# 検証

* [D - 旅行会社高橋君 - AC](https://beta.atcoder.jp/contests/arc039/submissions/2136670){:target="_blank"}<!--_-->
* HackerRankの問題でやろうとしたらMLEった（Aborted, REとは限らない）


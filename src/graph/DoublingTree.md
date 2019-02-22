---
title: 木のダブリング
---

ダブリング自体は木でなくともできます．(数列とか)

$O(\log N)$ で1クエリを処理でき，[HL分解]({{ "graph/HL-Decomposition" | absolute_url }})より時間計算量で有利ですが，  
空間計算量は $O(N \log N)$ とちょっと増えます
[HL分解]({{ "graph/HL-Decomposition" | absolute_url }})とちがって，  
遅延させたりもできず，通常のセグ木でできることができます

// @ Doubilng Tree

# 検証

* [D - 旅行会社高橋君 - AtCoder](https://atcoder.jp/contests/arc039/submissions/2136670){:target="_blank"}<!--_-->
* HackerRankの問題でやろうとしたらMLEった

# 練習問題

* [E - Wandering TKHS (1200) - AtCoder](https://atcoder.jp/contests/agc029/tasks/agc029_e){:target="_blank"}<!--_-->



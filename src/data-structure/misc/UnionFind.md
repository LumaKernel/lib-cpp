---
title: Union Find (DSU)
---

Union Find; UF  
Disjoint Set Union; DSU

kruskal法や矛盾検知，他いろいろつかえる便利ですごい．

アッカーマン関数の逆関数はこの宇宙に書き下せるどのような数字(おそらく十進数を想定)をぶち込んでも4以下を返す関数なので，クエリの係数は4程度．(参考は英語wiki)

UFのunite(merge)中に森を構築したりできる（練習問題にあります）  
unite時に新しい頂点xを用意して，unite(a, x), unite(x, b)とかましてやると，  
二分木になる．  
2つの頂点のLCAが初めて2つが連結になった瞬間．

// @ Union Find Library

# 検証

* [B - Union Find - AC](https://beta.atcoder.jp/contests/atc001/submissions/2147616){:target="_blank"}<!--_-->

# 練習

* [H - Union Sets (600) - AC](https://beta.atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h)
* [D - Propagating Edges (800) - AC](https://beta.atcoder.jp/contests/soundhound2018-summer-final-open/tasks/soundhound2018_summer_final_d)
* [E - Black Cats Deployment (800) - AC](https://beta.atcoder.jp/contests/cf17-tournament-round3-open/tasks/asaporo2_e)


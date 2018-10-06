---
title: Union Find (DSU)
---

Union Find; UF  
Disjoint Set Union; DSU

kruskal法や矛盾検知(これを利用して二部グラフ判定)，他いろいろつかえる便利ですごい．

アッカーマン関数の逆関数はこの宇宙に書き下せるどのような数字(おそらく十進数を想定)をぶち込んでも4以下を返す関数なので，クエリの係数は4程度．(参考は英語wiki)

UFのunite(merge)中に森を構築したりできる（練習問題にあります）  
unite時に新しい頂点xを用意して，unite(a, x), unite(x, b)とかましてやると，  
二分木になる  
2つの頂点のLCAが初めて2つが連結になった瞬間

# 計算量について

UnionFindをマージテクを用いてクエリあたりならし$O(\log N)$を実現する方法があります (参考: [iwiさんのマージテク解説](https://topcoder.g.hatena.ne.jp/iwiwi/20131226/1388062106){:target="_blank"}<!--_-->)

それと区別して，通常のUnionFindがQuick Unionとよばれることがある

findやuniteの1クエリあたりの計算量は，  
経路圧縮とQuick Unionにより以下のようになる

||経路圧縮する|しない|
|--|--|--|
|Quick Unionする|**ならし**$O(\alpha (N))$|$O(\log N)$|
|しない|$O(\log N)$ぐらい^*1^|$O(N)$|

*1: このパターンについては計算量が複雑でよくわかりません

unionとfindにはそれぞれ実現方法がいろいろあります

英語wikiに詳しく書いてありました([Disjoint-set data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure){:target="_blank"}<!--_-->)

# 永続化について

部分永続については[紙ぺーぱーさんのこれ](https://camypaper.bitbucket.io/2016/12/18/adc2016/){:target="_blank"}<!--_-->とか[noshiさんのこれ](http://noshi91.hatenablog.com/entry/2018/02/18/161529){:target="_blank"}<!--_-->とかですね．

完全永続については[noshiさんのこれ](http://noshi91.hatenablog.com/entry/2018/05/30/191943){:target="_blank"}<!--_-->で触れられていますね（何もわからない

# 実装

Union by sizeとPath compressionを用いています

// @ Union Find Library

# 検証

* [B - Union Find - AC](https://beta.atcoder.jp/contests/atc001/submissions/2147616){:target="_blank"}<!--_-->

# 練習

* [H - Union Sets (600) - AC](https://beta.atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h){:target="_blank"}<!--_-->
* [D - Propagating Edges (800) - AC](https://beta.atcoder.jp/contests/soundhound2018-summer-final-open/tasks/soundhound2018_summer_final_d){:target="_blank"}<!--_-->
* [E - Black Cats Deployment (800) - AC](https://beta.atcoder.jp/contests/cf17-tournament-round3-open/tasks/asaporo2_e){:target="_blank"}<!--_-->



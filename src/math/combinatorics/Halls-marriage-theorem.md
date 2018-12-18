---
title: Hallの結婚定理
---

二部グラフ $G = (U + V, E)$ について，以下の２つが同値

* $U$ の頂点全てを使うマッチングが存在する
* 全ての $A \subseteq U$ について $\|A\| \leq \|\Gamma(A)\|$ が成立する

ただし $\Gamma(A)$ とは $A$ 内の頂点と隣接する $V$ 内の頂点の集合である

これを結婚定理という

一般のグラフへと一般化するとTutteの定理 ([るまブログでの紹介記事](https://tomorinao.blogspot.com/2018/07/tutte.html){:target="_blank"}<!--_-->) となる

# 重み付き結婚定理

この名前は適当につけた

二部グラフ $G = (U + V, E)$ において 各 $u \in U$ について重み $w(u)$ がきまっていて，**その分だけ右に対して辺が張れる** とする． $V$ は特に変わらず一つまで

この時

* $U$ をその重み全て使い切るマッチング (っぽいもの) が存在する ($$\sum_{u \in U} w(u) = \text{マッチングのサイズ}$$)
* 全ての $A \subseteq U$ について $\sum_{u \in A} w(u) \leq \|\Gamma(A)\|$ が成立する

が同値である

これは $u \in U$ について $w(u)$ 個の頂点に置き換えた $$U'$$ を考えると普通の結婚定理になるが，この時下の条件を満たすかを考える時，より多くの (同じ頂点から作られた) 頂点を $$U'$$ から選んだほうがキツい条件となるためである

# 練習問題

結婚定理

* [AGC029F - Construction of a tree (2200) - AtCoder](https://atcoder.jp/contests/agc029/tasks/agc029_f){:target="_blank"}<!--_-->

重み付き結婚定理

* [G. Allowed Letters - codeforces](https://codeforces.com/contest/1009/problem/G){:target="_blank"}<!--_-->

# 参考

* [Hall's marriage theorem - Wikipedia (en)](https://en.wikipedia.org/wiki/Hall%27s_marriage_theorem){:target="_blank"}<!--_-->
* [Hallの結婚定理とその証明 - 高校数学の美しい物語](https://mathtrain.jp/hall){:target="_blank"}<!--_-->


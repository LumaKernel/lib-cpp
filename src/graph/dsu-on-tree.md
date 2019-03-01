---
title: DSU on Tree
---

根付き木に対し部分木クエリを行います

# キーワード

**部分木クエリ**をします

* 条件をみたすものを数えよ

# 説明

[\[Tutorial\] Sack (dsu on tree)](https://codeforces.com/blog/entry/44351){:target="_blank"}<!--_--> がわかりやすいです

"v, cが与えられ，vの部分木内の色cの頂点の数を答えろ" みたいなのに対応できます

より正確には，これは実装を見てから理解したほうがいいと思うが，

* ある頂点を有効化/無効化する
* 各頂点vについて部分木が有効になったタイミングでクエリに答える

といったことができればいい

これは $O(N \log N)$ でできる．色々な書き方が紹介されているが，どれかひとつ把握すればいいと思う．HLD Styleを紹介する

# 計算量について

[HL分解]({{ "graph/HL-Decomposition" | absolute_url }}) による木の変換を考える．HLD StyleはLight Edgeを登ったタイミングで全ての部分木内の頂点を走査している

ここで各頂点についていつ走査されるか考える．これは根へと向かう途中にある Light Edgeの本数だが，これは $O(\log N)$ 本となる．よって全体で $O(N \log N)$ となる

# 実装

// @ DSU on Tree - HLD Style

# 検証

* [ECR47 F - Dominant Indices - codeforces](https://codeforces.com/contest/1009/submission/50643706){:target="_blank"}<!--_-->

# 練習問題

* [ECR47 F - Dominant Indices - codeforces](https://codeforces.com/contest/1009/problem/F){:target="_blank"}<!--_-->

# 参考

* [\[Tutorial\] Sack (dsu on tree)](https://codeforces.com/blog/entry/44351){:target="_blank"}<!--_-->


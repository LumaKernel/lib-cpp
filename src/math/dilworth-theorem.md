---
title: DAGの最小パス被覆と最大反鎖 (dilworthの定理)
---

$\text{dilworthの定理} : \|\text{DAGの最小パス被覆}\| = \|\text{DAGの最大反鎖}\|$

前提知識 : フロー, DAG, 二部グラフ

# DAGの最小パス被覆

いくつのパスで全ての頂点をカバーできるか (最小点カバーに似ている)

蟻本pp.242-244 にも載っている典型

DAGの頂点数を$N$，頂点を複製して左右に振り分けた二部グラフを考えて，DAG上に辺$(a, b)$があるなら，二部グラフに辺$(a, b)$があるようにして，最大マッチングのサイズを $M$ とすると，$N - M$が最小パス被覆のサイズ

**マッチングに選ばれた辺にDAGで対応していた辺をパスとして採用する**と考えると復元や証明ができる

# 反鎖

順序集合 (DAGを成す) から取り出した要素で，どの二点も比較不能 (DAG上で結ばれていない) ならその要素集合を反鎖 (antichain) と呼ぶ

# dilworthの定理

DAGの反鎖でサイズが最大のもののサイズを $X$ とおくと，$X = N - M$ が成り立つ

# 練習問題

* [OUPC2012 - Divisor - AOJ](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2352){:target="_blank"}<!--_-->
  * 最大反鎖サイズ $X$ を求めたくて，最小パス被覆 $N - M$ が求められる
* [JOI春15Day1 - A - マトリョーシカ人形 - AtCoder](https://beta.atcoder.jp/contests/joisc2016/tasks/joisc2016_a){:target="_blank"}<!--_-->
  * 最小パス被覆 $N - M$ を求めたくて，最大反鎖サイズ $X$ が求められる

# 参考

* 蟻本pp.242-244
* [Divisor - SlideShare](https://www.slideshare.net/oupc/divisor){:target="_blank"}<!--_-->
  * OUPC2012 - Dicisorの解説
* [pdf: マトリョーシカ人形](https://www.slideshare.net/oupc/divisor){:target="_blank"}<!--_-->
  * JOI春の解説
* [Dilworth's theorem - Wikipedia (en)](https://en.wikipedia.org/wiki/Dilworth%27s_theorem){:target="_blank"}<!--_-->


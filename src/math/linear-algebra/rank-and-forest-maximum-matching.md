---
title: 隣接行列のランクと森の最大マッチングの関係
---

単純無向グラフ $G = (V, E)$ は**森**であるとし，その隣接行列を $A$ とする

また，グラフ $G$ の最大マッチングを $M$ と表すと，以下が成り立つ

$2M = \mathrm{rank} A$

## 前提知識

最大マッチング (Maximum Matching) とは作り得る最大のマッチング，完全マッチング (Perfect Matching) とはすべての頂点がマッチングとして使われているマッチングのこと

誘導部分グラフ (Induced Subgraph) とは，部分グラフで，もとのグラフで繋がっていた頂点同士が結ばれているもののこと

$\sigma$ は置換を表し，証明にはあまり関係ないが，$\mathrm{sgn(\sigma)}$ は奇置換であれば$-1$, 偶置換であれば$+1$を返す

また，ページ下部にある参照も確認するといいかもしれない

## 証明

$n = \|V\|$ とおく

$\mathrm{rank} A = n$ であることと $\mathrm{det} A \not= 0$ であることは同値である (これは対偶などを考えることをで示せる)

$\mathrm{rank} A = n$ となる条件を考える．定義より，

$\displaystyle\mathrm{det} A = \sum\_{\sigma}\mathrm{sgn}(\sigma)\prod\_{i=1}^n A\_{i, \sigma(i)}$

となるが，置換 $\sigma$ はいくつかのサイクルを作っていると考えることができる ($n$個の有向辺 $(i, \sigma(i))$ からなるグラフを考える)

このサイクルに長さが1や3以上のものが含まれていると， $\displaystyle\prod\_{i=1}^n A\_{i, \sigma(i)}$ は $0$ となる．なぜなら，もとのグラフは森なので長さが1や3以上のサイクルは存在せず，そのようなサイクルを置換による有向グラフが形成していると $A_{i, \sigma(i)} = 0$ であるもの (つまり$G$に辺 $(i, \sigma(i))$ がない) が存在するから

よって，すべてのサイクルの長さが2であり，$(i, \sigma(i))$ に辺があるような置換のみが残る．サイクルの長さが2で辺が存在すれば $A_{i, \sigma(i)}$ は0にならないから．よって，$\mathrm{rank} A = n$ であれば森に完全マッチングが存在することになる．逆に，森に完全マッチングが存在すれば，それは (葉から順次決めていくなどの) 貪欲な構築で一意に定まるため，$\displaystyle\prod\_{i=1}^n A\_{i, \sigma(i)}$ を満たす置換は一つしか無い．よって， $\mathrm{rank} A = n$ であることと森に完全マッチングが存在することが同値であることがわかった

今，ある森にある最大マッチングの大きさが $M$ であるとする．それが完全マッチングであるなら，$2M = n = \mathrm{rank} A$ となる

$2M \lt n$ である場合を考える．マッチングの端点を用いた誘導部分グラフ $G'$ とその隣接行列 $A'$ を考える

まず $\mathrm{rank} A \geq 2M$ を示す．$A$ を適切に行列基本変形することで $A'$ が左上にあるようにできる．左上 $2M \times 2M$ が線形独立なため， $\mathrm{rank} A$ は少なくとも $2M$ となる

次に $\mathrm{rank} A \leq 2M$ を示す．これは自明で，仮に大きいランクになり得たとしたら，適切に行列基本変形して左上に詰めたとき，左上 $m \times m$ が線形独立 ($m \gt 2M$) といえる状況を作れるが，そこを部分グラフで切り取ったとき完全マッチングになるということになる．これは$m$が奇数なら単純に矛盾しており，そうでなくとも $M$ が最大マッチングであることに矛盾している

よって $\mathrm{rank} A = 2M$ が示された

---

どうでもいいんですが，maximal, maximumはそれぞれ極大, 最大という意味で区別して使われるようです

# 参考

* [行列の基本変形 - Wikipedia](https://www.google.co.jp/search?client=opera&q=行列基本変形&sourceid=opera&ie=UTF-8&oe=UTF-8){:target="_blank"}<!--_-->
* 上記の証明は [Random Forest Rankの解説 (Codeforces)](https://codeforces.com/blog/entry/62688){:target="_blank"}<!--_--> を参考にしました
* [行列のランクの意味（８通りの同値な定義） - 高校数学の美しい物語](https://mathtrain.jp/matrixrank){:target="_blank"}<!--_-->
* [行列式の３つの定義と意味 - 高校数学の美しい物語](https://mathtrain.jp/determinant){:target="_blank"}<!--_-->

# 練習問題

* [E - Random Forest Rank - Codeforces](https://codeforces.com/contest/1067/problem/E){:target="_blank"}<!--_-->


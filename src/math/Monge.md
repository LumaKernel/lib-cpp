---
title: Mongeなどについて
---

わかった範囲でまとめていきます．随時情報を募集しています

$N \times M$ の行列 $w$ を考えます (以下では二変数関数のように書きます)

# Monge

"もんじゅ" とよむ (?)

任意の $i \lt j,~k \lt l$ について $w(i, k) + w(j, l) \leq w(i, l) + w(j, k)$ が成り立つ

Concave Quadratic Inequalityともいう (他にも色々あるようです)

単に QI と呼ばれることも

Monge性を満たす行列のことを Monge Arraies, Monge Matricesという

### 同値な言い換え

任意の**連結な** $2 \times 2$ の部分行列がMongeならその行列もMonge

# Totally Monotone (TM)

任意の部分行列 (連結している必要はありません) について Monotone

同値な言い換えとして，任意の$2 \times 2$ 部分行列について Monotone

# Monotone

**各行の最も左 (最も右) の最小値**が右下がりにある行列のこと

最も右については解釈の仕方に自身がありません

最も右で考えても最も左で考えても，という意味だと思います

(Abstractに最も左，に対してのみ定義しているような文献もありましたが全文を読んでいないのでわかりません)

ある $2 \times 2$ の行列 $\left(\begin{array}{}a & b \\ c & d \end{array}\right)$ が Monotone であるとは，

* $c \lt d$ ならば $a \lt b$
* $c = d$ ならば $a \leq b$

が成り立つことです

定義より，TMならばMonotoneです

MongeならばTMでもあります

### 証明

TMでないとする．$i \lt j,~k \lt l$ で，「$w(i, k) \geq w(i, l)$ かつ $w(j, k) \lt w(j, l)$」 か 「$w(i, k) \gt w(i, l)$ かつ $w(j, k) = w(j, l)$」 であるようなものが存在する．どちらにせよ $w(i, k) + w(j, l) \gt w(i, l) + w(j, k)$ が導かれるが，これはMongeを満たさない

よって背理法よりMongeならばTM ■

(この証明はnoshiさんに教えてもらいました)

# Convex QI

これはConcave QIの条件の不等号の向きを変えたものです (Inverse QIとも呼ばれている[^1])

任意の $i \lt j,~k \lt l$ について $w(i, k) + w(j, l) \geq w(i, l) + w(j, k)$ が成り立つ

当サイトのいくつかの記事ではConvex QI (上三角) などといっていますが，それらは $j \lt k$ や $j \leq k$ という条件を加えたものを想定しています

# 上三角Monge

Mongeの条件に加えて $j \lt k$ であるものです

Mongeであれば上三角Mongeです

# Closest Zero Property

文献 \[1\] で出てきたワードです

$l \lt k$ に対し $$f(r) = w(l, r) - w(k, r) - a$$ が0となるような$r$を$O(1)$で求められる場合，Closest Zero Propertyと言います

これが嬉しい性質になることは割と自然なことなので特別覚えておくようなことでもないかと思います



# 参考

* [Totally Monotone Matrix Searching (SMAWK algorithm) - 週刊 spaghetti_source](https://topcoder.g.hatena.ne.jp/spaghetti_source/20120923/1348327542){:target="_blank"}<!--_-->
* [Knuth-Yao speedup - 週刊 spaghetti_source](https://topcoder.g.hatena.ne.jp/spaghetti_source/20120915){:target="_blank"}<!--_-->
* [SMAWK algorithm - wikipedia(en)](https://en.wikipedia.org/wiki/SMAWK_algorithm){:target="_blank"}<!--_-->
* [Monge Array - wikipedia(en)](https://en.wikipedia.org/wiki/Monge_array){:target="_blank"}<!--_-->
* [Supermodular function - wikipedia(en)](https://en.wikipedia.org/wiki/Supermodular_function){:target="_blank"}<!--_-->
  * Monge Arrayの別名
* [DP高速化 - ferinの競プロ帳](https://ferin-tech.hatenablog.com/entry/2018/02/23/071343){:target="_blank"}<!--_-->
* [DPF: The SMAWK Algorithm](http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf){:target="_blank"}<!--_-->
* [PDF: Dynamic Programming Speedups](http://www.cse.ust.hk/~golin/COMP572/Notes/DP_speedup.pdf){:target="_blank"}<!--_-->
* [直前合宿 講義スライド](https://www.slideshare.net/ikumihide/ss-50881829){:target="_blank"}<!--_-->
* [Geometric applications of a matrix-searching algorithm](https://link.springer.com/article/10.1007%2FBF01840359){:target="_blank"}<!--_--> のAbstract

[^1]: [Speeding up dynamic programming with applications to molecular biology](https://www.sciencedirect.com/science/article/pii/0304397589901011){:target="_blank"}<!--_-->


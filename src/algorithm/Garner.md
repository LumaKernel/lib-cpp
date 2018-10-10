---
title: Garnerのアルゴリズム
---

$x$が以下のように与えられているとする

$$
\begin{aligned}
&x \equiv x_1 \mod m_1 \\
&x \equiv x_2 \mod m_2 \\
&\cdots \\
&x \equiv x_k \mod m_k \\
\end{aligned}
$$

ただし，$m_i$はどの2つについても互いに素

$x \leq m_1m_2\cdots m_k-1$
となるものを任意のmodで求めることができる

$x \mod M$ を求めたいとする

[中国剰余定理(CRT)]({{ "math/CRT" | absolute_url }})を使う場合は，$m_1m_2\cdots m_k-1$以下の整数を管理できるような多倍長変数などが必要になる ($k=2$の場合とかはCRT使えばいいと思う)

Garnerのアルゴリズムでは，各$m_i$に関するmodでの値だけ持つことができればよい

# Garnerのアルゴリズム

変数 $v_i \lt m_i$を用いて，

$x = v_1 + m_1v_2 + m_1m_2v_3 +\cdots + m_1m_2\cdots m_{k-1} v_k$

と表す

---

簡単のため，ここからは$k=3$で説明する

$x = v_1 + m_1v_2 + m_1m_2v_3$

この形で，$v_i \lt m_i$の制約のもとで，すべての$x$に対応する$v=(v_i)_{i=1}^{k-1}$ が存在する

そのようなもののうち一つを，$m_1,m_2,m_3$ のmodで求める．ところで，$v$ は $m_1\cdots m_k$ 通りなので，$v$ は唯一つに定まる

modを$m_1,m_2,m_3$と変えながら求めていく

---

まずは $v_1$ を求めるために $\mod m_1$ を考えると

$$
(\text{左辺}) \equiv x \equiv x_1 \\
(\text{右辺}) \equiv v_1
$$

ところで，$v_1 \lt m_1$なので$\mod m_1$を$m_1$で割ったあまり，とすると$v_1 = x_1$である ($\equiv$ではなく$=$であることが重要，つまり厳密値がわかる)

---

次に$\mod m_2$で考える

$v_2$を求めるので，$v_1$を移項する

$x_2 - v_1 \equiv m_1v_2$

が得られます

$v_1$は厳密値がわかっているので$\mod m_2$での値を予め持っておきます

$m_1$も厳密値なので予め$\mod m_2$しておきます

$m_1$と$m_2$は互いに素なので，逆元掛けて（もしくはextgcdで) $v_2 \mod m_2$がもとまります

$v_2 \lt m_2$ より厳密値がわかります

---

続いて$\mod m_3$を考えます

移項すると

$x_3 - (v_1 + m_1v_2) \equiv m_1m_2v_3$

$v1,m_1,v_2$の厳密値がそれぞれ分かっているので，  
$(v_1 + m_1v_2)$はあらかじめ$\mod m_3$で求めておきます

同様に，$v_3$の係数である$m_1m_2$も予め求めておくと，  
$m_1m_2$と$m_3$は互いに素なので，逆元かけて$v_3 \mod m_3$，そして$v_3$の厳密値がわかります

---

最後に$\mod M$を考えますが，右辺の各変数は厳密値がわかっているので，$\mod M$を取りながら求めていくことで，$x \mod M$が求まります

以上がGarnerのアルゴリズムです

---

まとめると，

$v_i$を求める時の，$\mod m_i$での一般的な移項した後の式は，

$x_i - (v_1 + m_1v_2 + \cdots + m_1\cdots m_{i-2}v_{i-1}) \equiv m_1m_2\cdots m_{i-1}v_i$

$x_i,v_i$以外の変数はすべて厳密値が分かっているので，$\mod m_i$での値を求めることができ，$m_1m_2\cdots m_{i-1}$と$m_i$は互いに素なので，逆元かけて，$v_i$の$\mod m_i$，もとより厳密値が求まります

# 実装

$O(k^2 + k\log m)$ぐらいだと思います

// @ Garner Library

# 検証

* [No.187 中華風 (Hard) - yukicoder](https://yukicoder.me/submissions/289727){:target="_blank"}<!--_-->

# 練習問題

* [No.187 中華風 (Hard) - yukicoder](https://yukicoder.me/problems/no/187){:target="_blank"}<!--_-->

# 参考

* [Garner のアルゴリズムと多倍長整数演算 - kirika_compのブログ](http://kirika-comp.hatenablog.com/entry/2017/12/18/143923){:target="_blank"}<!--_-->
* [任意modでの畳み込み演算をO(n log(n))で - math314のブログ](http://kirika-comp.hatenablog.com/entry/2017/12/18/143923){:target="_blank"}<!--_-->



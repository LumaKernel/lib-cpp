---
title: オイラーのトーシェント関数（ファイ関数）の性質
---

正整数$n$に対し，
$\phi(n)$は$n$以下で$n$と互いに素な数がいくつあるか，を表します

オイラーのトーシェント関数，ファイ関数，オイラー関数とか色々よばれています

なんでtotientというのかという話は [Where does the word “totient” come from? - StackExchange](https://english.stackexchange.com/questions/23694/where-does-the-word-totient-come-from){:target="_blank"} とかを参照してください

[オイラーのφ関数 - Wikipedia](https://ja.wikipedia.org/wiki/オイラーのφ関数){:target="_blank"}

---

$p$を素数，$k$を正整数とすると，

* $\phi(p) = p - 1$
* $\phi(p^k) = p^k - p^{k-1} = p^k \cdot \frac{p-1}{p}$

となります．このことはすぐわかります

---

$n,m$を互いに素な正整数とすると，

$\phi(nm)=\phi(n)\phi(m)$ が成り立ちます(乗法性)

参考: [オイラーのφ関数の性質 > オイラー関数の乗法性 - 思考力を鍛える数学](http://www.mathlion.jp/article/ar042.html#3){:target="_blank"}

証明も上記リンク先にあります

---

以上より，

$n = p_1^{e_1}p_2^{e_2}\cdots p_m^{e_m}$と素因数分解できるとすると，

$$\phi(n) = n \prod_{i = 1}^m \frac{p_i - 1}{p_i}$$

となります．これも上記の性質を使えばわかります

---

$n \geq 2$ について

* $n$が奇数なら$\phi(n)$は偶数
* $n$が偶数なら$\phi(n) \le n/2$

が成り立ちます

証明は [F: ModularPowerEquation!!の謎を紐解く - るまブログ](https://tomorinao.blogspot.com/2018/09/f-modularpowerequation.html){:target="_blank"}に書きました

以上より，$n \geq 3$ に対して $\phi(\phi(n)) \lt n/2$が成り立ちます

---

というか，一旦偶数になると $3$ 以上の奇数はノントーシェントなので何回$\phi$関数を適用してもずっと偶数のままです

(ノントーシェントとは，トーシェント関数の値域にない数のことです)

以上より，$n \geq 3$ に対して， $O(\log n)$ 回 $\phi$を適用すると$1$になります

---

互いに素な $n, m$ について，  
$n^{\phi(m)} = 1 \mod m$ が成り立ちます

証明については「初等整数論からp進数へ」に書いてありましたが，略して書くと，

$$\{ x_1, x_2, \cdots, x_{\phi(m)} \}$$ をすべての $m$ と互いに素な$m$以下の正整数とすると，$\mod m$を省略すると  
$n^{\phi(m)}x_1\cdots x_{\phi(m)} \equiv (nx_1)\cdots (nx_{\phi(m)}) \equiv x_1 \cdots x_{\phi(m)}$ となり，  
$(x_1 \cdots x_{\phi(m)})$ と $m$ は互いに素なので逆元を両辺にかけて， 証明できます

---

十分大きな$x$について，

$A^x \equiv A^{x+\phi(N)} \mod N$ が成り立ちます

$x \geq \log_2 N$ であれば大丈夫です

つまり，$A^x \mod N$ の値は $x \mod \phi(N)$ によってわかるということです

証明・さらなる議論についてはこちらも同様に  
[F: ModularPowerEquation!!の謎を紐解く - るまブログ](https://tomorinao.blogspot.com/2018/09/f-modularpowerequation.html){:target="_blank"}に書きました

練習問題

* [F - ModularPowerEquation!! (1400) - AC](https://beta.atcoder.jp/contests/tenka1-2017/tasks/tenka1_2017_f){:target="_blank"}

---

$$
\sum_{d\mid n} \phi(d) = n
$$

これとメビウスの反転公式より

$$
\sum_{d|n} \mu(\frac{n}{d})d = \phi(n)
$$

が導ける

参考: [メビウスの反転公式の証明と応用 - 高校数学の美しい物語](https://mathtrain.jp/mobiusinversion){:target="_blank"}

やばくない？やばいね

ポリアの数え上げ定理（蟻本にあるやつ）を証明するのにも使えます  
（証明についてはそのうち記事にするかもしれない）

# 原始根の数

奇素数 $p$ について $\mathrm{mod}\ p$ における原始根の数は $\phi(\phi(p)) = \phi(p-1)$ 個 参考: [原始根の数のかぞえかた](http://tsujimotter.hatenablog.com/entry/primitive-root){:target="_blank"}<!--_-->

# 実装

$O(\sqrt N)$ です

// @ phi

$O(\sqrt N / \log N)$ でできる（もしくはこれが達成している?）という言及を見つけましたがリンク切れとかで真偽は闇の中です( [ここ](https://github.com/eandbsoftware/libraryCPP/blob/master/ライブラリまとめ.txt#L279){:target="_blank"} )  
だれか知っている方がいらっしゃったら，コメントで教えてくださると助かります

## 列挙

N以下についてすべての $\phi(n)$ を求めるものです  
`euler[i] == i` は素数を判定しています  
計算量はエラトステネスのふるいに従います

// @ phi2

エラトステネスのふるいの計算量については，  
[エラトステネスのふるいとその計算量 - 高校数学の美しい物語](https://mathtrain.jp/eratosthenes){:target="_blank"}  
を参照してください


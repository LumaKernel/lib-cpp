---
title: メビウス関数, メビウスの反転公式
---

自然数 $n$ に対し

$\displaystyle \mu(n) = \begin{cases} (-1)^k & (nがk個の相異なる素数の積) \\\\ 0 & (nが素数の平方を約数に持つ) \\\\ \end{cases}$

て定義される．特に，$\mu(1) = 1$ となる

# 乗法性

互いに素な $n, m$ について $\mu(nm) = \mu(n)\mu(m)$ が成り立つ

# 基本公式

$\displaystyle \sum\_{d \mid n} \mu(d) = \begin{cases} 1 & (n = 1) \\\\ 0 & (n \not= 1) \end{cases}$

参考: [メビウスの反転公式の証明と応用 - 高校数学の美しい物語](https://mathtrain.jp/mobiusinversion){:target="_blank"}<!--_-->

# メビウスの反転公式

関数 $f(n), g(n)$ に対して，以下の2つが同値である

$\displaystyle g(n) = \sum\_{d \mid n} f(d)$

$\displaystyle f(n) = \sum\_{d \mid n} \mu(\frac{n}{d}) g(d)$

これをメビウスの反転公式という

## 使い方

上の式が成り立つ $f(n), g(n)$ が定義できたとき，求めたい $f(n)$ を直接求めるのは難しいが $g(n)$ を求めることはできるという場合，下の式を経由すれば $f(n)$ を求められるかもしれない

---

[一般化された包除原理]({{ "math/PIE#一般化された包除原理" | absolute_url }}) と形が似ているが，この2つは [隣接代数](https%3A%2F%2Fja.wikipedia.org%2Fwiki%2F%E9%9A%A3%E6%8E%A5%E4%BB%A3%E6%95%B0_%28%E9%A0%86%E5%BA%8F%E7%90%86%E8%AB%96%29){:target="_blank"}<!--_--> というもので関連付けられているようだ

# ポリアの数え上げ定理

そのうち書きます

# 列挙

与えられた整数の約数に対して，メビウス関数の値をすべて求める

計算量 : $O(\sqrt{N})$

// @ mobius-function

素因数の数を$x$とすると $2^x$ の時間がかかるが，素因数の数は十分小さい

$n$ 以下の数で持つことができる素因数の数の最大値 $x$

|$n$|素因数の数の最大値 $x$|
|--|--|
|$10^5$|6|
|$10^6$|7|
|$10^{10}$|10|
|$10^{11}$|10|
|$10^{12}$|11|
|$10^{13}$|12|
|$10^{14}$|12|
|$10^{18}$|15|


# 練習問題

なし

# 参考

* 蟻本
* [メビウス関数 - Wikipedia](https://ja.wikipedia.org/wiki/メビウス関数){:target="_blank"}<!--_-->
* [メビウスの反転公式 - Wikipedia](https://ja.wikipedia.org/wiki/メビウスの反転公式){:target="_blank"}<!--_-->
* [メビウスの反転公式の証明と応用 - 高校数学の美しい物語](https://mathtrain.jp/mobiusinversion){:target="_blank"}<!--_-->
* [隣接代数 (順序理論) - Wikipedia](https%3A%2F%2Fja.wikipedia.org%2Fwiki%2F%E9%9A%A3%E6%8E%A5%E4%BB%A3%E6%95%B0_%28%E9%A0%86%E5%BA%8F%E7%90%86%E8%AB%96%29){:target="_blank"}<!--_-->


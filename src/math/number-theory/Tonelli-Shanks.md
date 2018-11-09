---
title: √a mod p (Tonelli-Shanks algorithm)
---

奇素数 $p$ と $a$ に対し，$x^2 \equiv a \mod p$ なる $x$ を求めます

そのような $x$ が存在する $a \not \equiv 0$ を平方剰余，存在しないものを平方非剰余とよび，それぞれ $\frac{p-1}{2}$ 個ずつ存在します

また，当然ですが $x$ が条件を満たすなら $-x \mod p$ も条件を満たします

# ルジャンドル記号

奇素数 $p$ とそれに互いに素な $a$ に対しルジャンドル記号は

$\displaystyle \left(\frac{a}{p}\right)= \begin{cases} 1 &(a\text{が平方剰余})\\\\ -1 &(a\text{が平方非剰余})\\\\ \end{cases}$

と定義されます

# 平方剰余の判定

オイラーの規準:

$p$ を奇素数，$a$を$p$と互いに素な整数とすると，

$\displaystyle a^{\frac{p-1}{2}} \equiv \left(\frac{a}{p} \right) \mod p$

# Tonelli-Shanks algorithm

$Q$を奇数，$s \geq 1$ とし， $p = Q2^s + 1$ とします

$r^2=at$ が常に成り立つよう保ちながら，$t$ を $1$ に近づける感じです

## 初期値

$z$ を適当な平方非剰余とします (全体の半分だけあるので乱択で探します)

* $m = s$
* $c = z^Q$
* $t = a^Q$
* $\displaystyle r = a^{\frac{Q+1}{2}}$

## 不変量

遷移前に以下の３つの条件が成り立つようにします

* $r^2 \equiv at$
* $c^{2^{m-1}} \equiv -1$
* $t^{2^{m-1}} \equiv 1$

$t \qeuiv 1$ にするのが目標です

## 遷移

$m = 1$ なら上記の条件より $t = 1$ なので終了

$i$ を $1 \leq i \lt m$ で，$t^{2^i} \equiv 1$ 満たす最小の $i$ とします

とすると不変量より $t^{2^{m-1}} \equiv 1$ なので，最小の $i$ は $m-1$ 以下となります  
(このことから条件を満たす$i$が必ず存在します)

$i$ は $t$ を2乗を繰り返すことで求められます

* $m\' = i$
* $c\' = c^{2^{m-i}}$
* $t\' = tc^{2^{m-i}}$
* $r\' = rc^{2^{m-i-1}}$

この代入は不変量を保ち，$m$ が必ず減るのでいつか終了します

不変量が保たれることの証明はそれぞれ代入することでわかります

# いくつかの公式

$p \mod 8$ が $3, 5, 7$ のときに公式があります

* $p = 4k + 3$ なら $\displaystyle a^{\frac{p-1}{4}}$
* $p = 8k + 5$ なら
  * $\displaystyle \left(\frac{\sqrt a}{p}\right) = 1$ なら $\displaystyle a^{\frac{p + 3}{8}}$
  * $-1$ なら $\displaystyle 2^{\frac{p-1}{4}}a^{\frac{p + 3}{8}}$
    * $2$ は平方剰余の相互法則第2補充法則 $\displaystyle \left(\frac{2}{p}\right) = (-1)^\frac{p^2-1}{8}$ より平方非剰余であることから用いられています

証明はそれぞれ代入するとわかります

# √a mod p^k

$k$ を正整数とすると $X^2 \equiv a \mod p^k$ も求められるようです．wikipediaにあるものをそのまま書いてみました

ふつうに $x = \sqrt{a} \mod p$ を求めた後，

$\displaystyle X \equiv x^{p^{y-1}} \times c^{(p^y+1)/2-p^{y-1}} \mod p^k$

# 実装

上述の遷移を $m$ が1ずつ減るように変えたものになっています ($i$ の求め方を変えている)

また $p \mod 8 \equiv 3, 5, 7$ のときはせっかくなので公式を使いました

計算量は $O(\log^2 N)$ です

// @ modsqrt with Tonelli-Shanks algorithm

3引数の modsqrt(a, p, k) は $\sqrt{a} \mod p^k$ を求めます

`mod`が大きい場合，`ll`を多倍長整数に置き換えるとそのまま動きますが，乱択部分は `uint32` の範囲なので，`mt19937_64` に差し替えるか，変わらんやろと妥協するなどの選択があります

# 検証

* [C - Timofey and remoduling - Codeforces](https://codeforces.com/contest/763/submission/45482806){:target="_blank"}<!--_-->

# 練習問題

* [C - Timofey and remoduling - Codeforces](https://codeforces.com/contest/763/problem/C){:target="_blank"}<!--_-->

---

奇素数modでの合同二次方程式を解いたりもできます．普通の二次方程式の解の公式で解けます．判別式$D$が平方非剰余なら解なしです

# 参考

* [Tonelli–Shanks algorithm - Wikipedia (en)](https://en.wikipedia.org/wiki/Tonelli–Shanks_algorithm){:target="_blank"}<!--_-->
* [kirikaさんの整数論集](https://github.com/kirika-comp/articles){:target="_blank"}<!--_-->
* [平方剰余の根 - Tech Tips](http://techtipshoge.blogspot.com/2015/04/blog-post_5.html){:target="_blank"}<!--_-->
* [Tonelli–Shanks algorithm - メモ](http://sugarknri.hatenablog.com/entry/2018/02/16/115740){:target="_blank"}<!--_-->
* [ルジャンドル記号とオイラーの規準 - 高校数学の美しい物語](https://mathtrain.jp/criterion){:target="_blank"}<!--_-->


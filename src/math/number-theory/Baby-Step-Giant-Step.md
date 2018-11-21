---
title: log_a b mod p (Baby-Step Gian-Step algortihm)
---

離散対数

与えられた $a, b, p$ に対し，

$a^x \equiv b \mod p$ を満たす非負整数 $x$ の最小値を求めます

# Baby-Step Gian-Step algortihm

$\gcd(a, p) = 1$ とします

$x^{\phi(m)} \equiv 1 \mod m$ , $\phi(m) \leq m - 1$ より周期性があり，解が存在する場合，$0 \leq x \lt m-1$ が成立する $x$ が存在することがわかります

([オイラーのファイ関数の特徴]({{ "math/number-theory/EulerTotient" | absolute_url }}))

$\displaystyle r = \lceil \sqrt{m} \rceil$ とすると

$\displaystyle x = pr + q \\ \\ (0 \leq p \leq r, 0 \leq q \lt r)$ と置くことができます

代入して式変形すると

$b(a^{-1})^q \equiv (a^r)^p$ がわかります

左辺を各$q$ について求めて，`map[値] = その値を達成する最小のq` を保持します (Baby-Step)

右辺に$p$ を代入して **左辺がその値になり得るか** を`map`で判定できます (Giant-Step)

なり得る場合は $x$ を復元できます

計算量は $r = O(\sqrt m)$ なので， $O(\sqrt m \log m)$ ，hashmapを使うと $O(\sqrt m)$ でできます

## 補足

$q$ から求めることで早期リターンできます

Baby-Step Giant-Step アルゴリズムは中間一致攻撃のひとつです

巡回群 $G$ と生成元 $\alpha$ から $\alpha^x = \beta$ になる $x$ を求めていると言うことができます

なので $\gcd(a, p) \not= 1$ のときはこのアルゴリズムの範疇ではないんですが，もし求めるなら，

$x = 0$ の場合は自明なので $x \geq 1$ とします．$g=\gcd(a, p)$ とすると

まず $g \nmid b$ ($g$ は $b$ の約数でない) なら解はありません


$g \mid b$ なら

$\displaystyle a^x \equiv b \mod p$

$\displaystyle a a^{x-1} \equiv b \mod p$

$\displaystyle \left(\frac{a}{g}\right) a^{x-1} \equiv \frac{b}{g} \mod \frac{p}{g}$

$\displaystyle \gcd\left(\frac{a}{g}, \frac{p}{g}\right) = 1$ なので逆元が存在して，

$\displaystyle a^{x-1} \equiv \frac{b}{g}\left(\frac{a}{g}\right)^{-1} \mod \frac{p}{g}$

となりサイズの小さい問題に帰着できました (**このときの割り算と逆元は意味が違うので注意してください**)

$p \\ \\ (\geq 1)$ は単調減少なのでいつか終了します．また，$g \geq 2$ であるため，$O(\log p)$ 回で $\gcd(a, p)=1$ になります．毎回gcd, modinvに$O(\log p)$かかりますが$O(\log^2 p) \subset O(\sqrt{p})$ より悪化なしです

# 実装

aとpが互いに素でなくてもよい．解が存在する場合は非負の最小値，存在しない場合は `-1` を返す

計算量は $O(\sqrt p \log p)$ です

[数学基本ライブラリ]({{ "math/general" | absolute_url }}) のmathを必要とします

// @ modlog with Baby-Step Giant-Step algorithm

# 検証

* 互いに素のみ [D - あまり - AtCoder](https://beta.atcoder.jp/contests/arc042/submissions/3573120){:target="_blank"}<!--_-->

互いに素でない場合はなるべく慎重にテストしました

# 練習問題

* [D - あまり - AtCoder](https://beta.atcoder.jp/contests/arc042/tasks/arc042_d){:target="_blank"}<!--_-->

# 参考

* [「1000000007 で割ったあまり」の求め方を総特集！ 〜 逆元から離散対数まで 〜 #離散対数 - Qiita](https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#6-離散対数-log_a-b){:target="_blank"}<!--_-->
* [Baby-step giant-step - Wikipedia (en)](https://en.wikipedia.org/wiki/Baby-step_giant-step){:target="_blank"}<!--_-->


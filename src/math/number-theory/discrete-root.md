---
title: x^a=b mod pなるxを求める
---

$x^a \equiv b \mod p$

$p$は素数とします．$a$はとりあえず $0 \leq a \lt p - 1$ にすることができます

$a \equiv 2 \mod (p - 1)$ であれば [Tonelli-Shanksのアルゴリズム]({{ "math/number-theory/Tonelli-Shanks" | absolute_url }}) などで求めることができます．ここでは一般の $a$ に対して考えます

以下，$\mathrm{mod}~p$で考えます．原始根が存在するので，その内の一つを$g$とおくと，

$x \equiv g^y$ なる $y$ が必ず存在します

$(g^y)^a \equiv b$

$(g^a)^y \equiv b$

となりますが，$g,a,b$ は分かっているので，これは離散対数問題となります．よって [Baby-Step Giant-Step]({{ "math/number-theory/Baby-Step-Giant-Step" | absolute_url }}) により $O(\sqrt{p} \log p)$ などで求めることができます

これが$g$のとり方によらないことは，$x$が存在すれば必ず$y$が存在することから言えます

# 実装

解が存在しない場合は `-1` を返します

// @ Discrete Root

# 練習問題

* [#536 F - Lunar New Year and a Recursive Sequence - codeforces](https://codeforces.com/contest/1106/problem/F){:target="_blank"}<!--_-->

# 参考

* [Discrete Root - CP-Algorithms](https://cp-algorithms.com/algebra/discrete-root.html){:target="_blank"}<!--_-->


---
title: 中国剰余定理 (CRT)
---

Chenese Remainder Theorem; CRT

$m_1, m_2$ を互いに素であるとし，

$$
\begin{aligned}
&x \equiv x_1 \mod m_1 \\
&x \equiv x_2 \mod m_2 \\
\end{aligned}
$$

が分かっているとします．$x \mod m1m2$ を求めます (また，このような値は一意に定まります)

$m_1, m_2$ は互いに素より，ある $y_1, y_2$ で，$m_1y_1+m_2y_2=1$ であるものがわかります．よって，$0 \leq (x \mod m_1m_2) = (x_2m_1y_1+x_1m_2y_2 \mod m_1m_2) \leq m_1m_2-1$ が一意に定まり，これは仮定条件を満たします

$m = m_1m_2$ は二倍しても64bitに収まるとします (収まらない場合は適切に多倍長整数を使う)

式が3つ以上ある場合はCRTを複数回適用すれば求まりますが，途中の計算をするために大きな数を扱える必要があります．そのような場合は [Garnerのアルゴリズム]({{ "algorithm/Garner" | absolute_url }}) を使うと良いかもしれません

// @ CRT

math, modmulについては [数学に関する基本的なライブラリ]({{ "math/general" | absolute_url }}) にあります


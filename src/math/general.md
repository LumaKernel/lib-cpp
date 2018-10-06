---
title: 基本
---

// @ isPrime

// @ divisor

// @ primeFactors

# オイラーのトーシェント関数

[オイラーのトーシェント関数の性質]({{ "math/EulerTotient" | absolute_url }}) に色々書きました

// @ phi

// @ phi2

---

// @ primes

---

gcd, lcm, extgcd, modinv, movpow

剰余を使わない高速なgcdもありますが，  
gcd(a,b)の計算量は $O(\log \max(a, b))$ です

証明は蟻本にありますが，第一引数が2段階の再帰で $1/2$ 以下になることから言えます

extgcd(a, b, x, y)は $ab \not= 0$ のとき $$|x| \leq b, |y| \leq a$$ が言えます  
帰納法で証明することができます

modinv(a, m)は $a^{-1} \mod m$ を返します  
$gcd(a, m) = 1$ であれば $m$ が素数でなくとも逆元を返せるようにextgcdを使っています  
速度もこちらのほうが速い気がします

// @ math

# 参考

* 蟻本


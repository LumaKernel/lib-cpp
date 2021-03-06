---
title: 基本
---

// @ isPrime

// @ divisor

// @ primeFactors

# オイラーのトーシェント関数

[オイラーのトーシェント関数の性質]({{ "math/number-theory/EulerTotient" | absolute_url }}) に色々書きました

// @ phi

// @ phi2

---

// @ primes

# 原始根判定

奇素数 $p$ に対し $p-1$ の約数を乗じたときに $1 \pmod p$ でなければ原始根であると言えます

このことはフェルマーの小定理などから簡単に導けます

// @ isPrimitive

---

gcd, lcm, extgcd, modinv, modpow

gcd(a,b)の計算量は $O(\log \max(a, b))$ です

証明は蟻本にありますが，第一引数が2段階の再帰で $1/2$ 以下になることから言えます

extgcd(a, b, x, y)は $ab \not= 0$ のとき $$|x| \leq b, |y| \leq a$$ が言えます  
帰納法で証明することができます

modinv(a, m)は $a^{-1} \bmod m$ を返します  
$\gcd(a, m) = 1$ であれば $m$ が素数でなくとも逆元を返せるようにextgcdを使っています  
速度もこちらのほうが速い気がします

// @ math

# 剰余を使わないgcd

`%2` などは `&1` と読み替えてください

```cpp
Integer gcd(Integer a, Integer b) {
  if(a < 0) a = -a;
  if(b < 0) b = -b;
  Integer res = 1;
  while(a != b) {
    if(a < b) swap(a, b);
    if(b == 0) break;
    if(!(a % 2) && !(b % 2)) res *= 2, a /= 2, b /= 2;
    else if(!(a % 2)) a /= 2;
    else if(!(b % 2)) b /= 2;
    else a = (a - b) / 2;
  }
  return res * a;
}
```

# 大きなmodでの掛け算

二倍しても大丈夫なmodでの掛け算をしたいときに，二分累乗や繰り返し二乗法を使うことでoverflowを防ぐことができますが，ちょっと時間がかかります．[多倍長整数]({{ "misc/BigInteger" | absolute_url }})を使うのもありです

### long doubleを使った方法

参考 : [巨大modでの掛け算の高速化 (Codeforces Round #259 D Little Pony and Elements of Harmony) - kazuma8128’s blog](http://kazuma8128.hatenablog.com/entry/2018/06/04/144254){:target="_blank"}<!--_-->

// @ modmul

overflowを打ち消しています

### 繰り返し二乗法

対数時間かかります

```cpp
ll modmul_slow(ll a, ll b, ll mod) {
  if(b < 0) a *= -1, b *= -1;
  ll res = 0;
  while(b) {
    if(b & 1) res = (res + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return res;
}
```

# 参考

* 蟻本
* アルゴリズムイントロダクション
* [巨大modでの掛け算の高速化 (Codeforces Round #259 D Little Pony and Elements of Harmony) - kazuma8128’s blog](http://kazuma8128.hatenablog.com/entry/2018/06/04/144254){:target="_blank"}<!--_-->

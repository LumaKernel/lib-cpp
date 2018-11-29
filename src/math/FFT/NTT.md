---
title: 数論変換 (Number Theoretic Transform; NTT)
---

多項式2つを高速にかけ合わせます

[FFT導入]({{ "math/FFT/introduction" | absolute_url }}) で紹介しているように，FFTをする際の $\zeta_N$ に複素数ではなく $\mathrm{mod}\ m$ 上の原始N乗根を使うというのがNTTです

掛け算と足し算が定義されている可換環 $R$ において，$N$ で割ること，位数 $N$ の元が存在することができれば，畳み込みができますね (正確には $N = x_1x_2\cdots x_t (x_i \in R)$ と表したときに，各 $x_i$ で任意の元を割り算できるような $x$ があれば十分となります) (可換環については整数みたいに足し算掛け算ができて掛け算が $a\*b=b\*a$ を満たす，程度に考えてください)

なので，$m$ と $N$ が互いに素で，位数 $N$ の元があればいいので，$m$ を素数とし，$N \mid (m - 1)$ となるように $m$ を選べば良くなります (素数modでは逆元が存在するため割り算が可能)

ところで $N$ についてですが，FFTのアルゴリズムの選び方に依存します．NTTはどのような構造の上でFFTをするか，という話で，FFTのアルゴリズムは別に決定することができます

以下では [基本的なFFT]({{ "math/FFT/standard" | absolute_url }}) で紹介している非再帰の2基底FFTを使用します．$N$ は2ベキとします

# 使い方

$k, n$ を正整数とし，$m = 2^nk + 1$ と表せるもので， $ 2^n \geq N$ であるような **素数** $m$ を選び， $\mathrm{mod}\ m$ でFFTができる  

出力の最大値について考える．荒い評価として，$a, b$ を入力，各サイズを $N, M$ とすると，$\max(a)\max(b)\min(N, M)$ ぐらいとなる

## 求めたい値がmod上での値のとき

まず，予めmodをとることができるので各要素の値をmodしておく

上記の条件を満たすようなmodの場合はそのままNTTを使えばいい (以下の実装では `NTT::Core<mod, primitive, MAX_H> ntt` を宣言し `ntt::conv(vector<ll> a, vecror<ll> b)`)

mod 1e9+7 といったような任意modについては [中国剰余定理 (CRT)]({{ "math/number-theory/CRT" | absolute_url }}) などで復元する必要がある

以下の実装では `NTT::conv< USE > (vector<ll> a, vector<ll> b, ll m)` を使うと `USE` 個のmod上で値を出して [Garnerのアルゴリズム]({{ "math/number-theory/Garner" | absolute_url }}) を用いて mod m に復元を行う

NTTを行うmodを $m_1, m_2, \cdots, m_{USE}$ とすると，厳密値 (予めmodを取った場合はそれを厳密値とする) の最大値 (mod $m$に復元したいとした時，$m^2\min(N, M)$ ぐらい) を $m_1m_2\cdots m_{USE}$ が超えるように取らなければならない

## 求めたい値が厳密な値のとき (64bitに収まるとき)

基本的にmod上で求めるときと同じように，最大値より大きな値をmodとすればよい

掛け算でoverflowする可能性がある．これを防ぐには，**int128などで掛け算を行うか**，
[数学>基本]({{ "math/general" | absolute_url }}) にあるmodmulなどがある (このような状況はたまにあるだろうが，特別な実装はしていない (ジャッジによるところもあるかもしれない))


## 求めたい値が厳密な値の時 (64bitに収まらないとき)

復元時にint128, int256など多倍長整数使うしか無い

# 実装

// @ NTT

コード中の `NTT_PRIMES` が素数であること，原始根が正しいことを確認した

原始根判定については [数学関係のライブラリ全般]({{ "math/general" | absolute_url }}) の中においてある

# 検証

* [C - 高速フーリエ変換 - AtCoder](https://beta.atcoder.jp/contests/atc001/submissions/3370462){:target="_blank"}<!--_-->
* Garnerのアルゴリズムによる復元 [C - 高速フーリエ変換 - AtCoder](https://beta.atcoder.jp/contests/atc001/submissions/3370425){:target="_blank"}<!--_-->

# 練習問題

[基本的なFFT]({{ "math/FFT/standard" | absolute_url }}) にまとめてあります

# 参考

* [任意modでの畳み込み演算をO(n log(n))で - math314のブログ](http://kirika-comp.hatenablog.com/entry/2017/12/18/143923){:target="_blank"}<!--_-->
* [第２回　可換環の定義 - Pythonで学ぶ「プログラミング可換環論」](http://groebner-basis.hatenadiary.jp/entry/2017/12/02/000043){:target="_blank"}<!--_-->


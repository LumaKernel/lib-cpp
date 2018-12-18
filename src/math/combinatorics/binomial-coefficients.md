---
title: 二項係数の式変形
---

# 基本

$$
{}_nC_k = \binom n k = n! / k! / (n - k)! \\[1em]
{}_nH_k = \binom {n + k - 1} k \\
$$

$n$ 人の中から重複なく $k$ 人選ぶ方法は $\binom n k$

$n$ 人の中から重複を許して $k$ 人選ぶ方法は ${}_nH_k$ (重複組み合わせ)

$(0, 0)$ から $(y, x)$ へ行く方法の数は $\binom {y + x} y = \binom {y + x} x$

$\binom n 0 = 1$ や $\binom n k = 0\ \ (n \lt k)$ のように定義すると都合がいいことが多い

実際にこれらを求めるには [階乗事前計算]({{ "misc/Factorial" | absolute_url }}) をすることで $O(1)$ で求められる

重複組み合わせについてはいくつかの証明方法があるが，
<a target="_blank" href="https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)">Stars and bars</a> が初等的でわかりやすい．[重複組み合わせ#重複組み合わせの総数](https://ja.wikipedia.org/wiki/重複組合せ#重複組合せの総数){:target="_blank"}<!--_--> の証明4 にて日本語で説明されている

先に大事なことを行っておくと，**何かしらの式のオーダーを落とすことが目的**です

また，<span style="color:red">これは単純に [wolfram alpha](https://ja.wolframalpha.com/){:target="_blank"}<!--_--> に突っ込むと解決することが多い</span>かと思います

## Pascal's identity

パスカルの恒等式

$$\binom n k = \binom {n-1} {k-1} + \binom {n-1} k$$

これを用いるとdpをすることでコンビネーションの値が求まる

ところで，そのdpによって出来上がる表は [パスカルの三角形](https://ja.wikipedia.org/wiki/パスカルの三角形){:target="_blank"}<!--_--> と呼ばれる

このdpの累積和をとることで $$\sum_{i=l}^r \binom n i$$ を $O(1)$ で求めることができる (問題を見失いました，知っている方がいたら教えてくださると助かります)
<!--_-->

### 証明

<a target="_blank" href="https://en.wikipedia.org/wiki/Double_counting_(proof_technique)">double counting</a> で証明する

両辺とも $n$ 人から $k$ 人選ぶ方法の数になっている

右辺は **適当に選んだ一人** についてその人を選ぶか選ばないかで場合分けしている

<br/>

# 式変形のための公式

式変形は主に，「グリッド上でのパスの数え上げに帰着する」といった，別の数え方をする．証明したい式の両辺を，**同じものを数えていると捉え，別の数え方をしていると捉える証明手法** を <a target="_blank" href="https://en.wikipedia.org/wiki/Double_counting_(proof_technique)">double counting</a> と呼ぶ

## Vandermonde's identity

ヴァンデルモンドの恒等式

$$\sum_{k=0}^r \binom m k \binom n {r - k} = \binom {m + n} r$$

### 証明

<a target="_blank" href="https://en.wikipedia.org/wiki/Double_counting_(proof_technique)">double counting</a> による証明を紹介する

両辺ともに 男 $m$ 人，女 $n$ 人から $k$ 人 選ぶ方法になっている

左辺は 男を $k$ 人選ぶと固定したものを数えている

## Hockey-stick identity

ホッケースティック恒等式．クリスマスストッキング恒等式とも

$$\sum_{i = r}^n \binom i r = \binom {n + 1} {r + 1}$$

なぜホッケースティックなのかというと，両辺に出てくる二項係数をパスカルの三角形上でみると，ウネッとした形になっているから ([ここ](https://math.stackexchange.com/questions/1490794/proof-of-the-hockey-stick-identity-sum-limits-t-0n-binom-tk-binomn1){:target="_blank"}<!--_--> にある画像を見てみてください)

### 証明

<a target="_blank" href="https://en.wikipedia.org/wiki/Double_counting_(proof_technique)">double counting</a> で証明する

$n$個の星を$k$個の瓶に詰め込む場合の数を考える (<a href="https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)">Stars and bars</a>)

$n$個の星と$k-1$個の仕切りを並び替えてできる列の数に等しいので，

$$\binom {n + k - 1} {k - 1}$$

となる．また，１つめの瓶に詰め込む星の数 $i$ で場合分けすると，

$$\binom {n + k - 1} {k - 1} = \sum_{i=0}^n \binom {n + k - 2 - i} {k - 2}$$
ここで，$$r = k - 2$$, $$n' = n + k - 2 = n + r$$ とおくと

$$\binom {n' + 1} {r + 1} = \sum_{i=0}^{n' - r} \binom {n' - i} {r} = \sum_{i=r}^{n'} \binom i r$$

# その他

$$
(1)\ \ 
\sum_{i=0}^n \binom n i = 2^n
$$

$$
(2)\ \ 
\sum_{i=0}^{\lfloor {n/2} \rfloor} \binom n {2i} = 2^{n-1}
$$

$$
(3)\ \ 
\sum_{i=0}^k \sum_{j=0}^l \binom {i+j} j = \binom {k + l + 2} {k + 1} - 1
$$

$$
(4)\ \ 
\sum_{i=0}^k \binom {n + i} i \binom {m - i} {k - i} = \binom {n + m + 1} k
$$

$$
(5)\ \ 
\sum_{i=0}^k \binom {n + i} i = \binom {n + 1} k
$$

### それぞれの証明

#### (1) 証明

両辺ともに$n$人から任意人を選ぶ方法．左辺は選ぶ人数 $i$ で場合分け

#### (2) 証明

偶数人選ぶ方法と奇数人選ぶ方法は同じ数だけあります．全ての選び方を，**1番の人の選ぶ/選ばないを反転した選び方と対応付ける** と偶奇人数どうしの一対一対応ができます．これにより半分ずつであることがわかります
<!--_-->

#### (3) 証明

<a target="_blank" href="https://en.wikipedia.org/wiki/Double_counting_(proof_technique)">double counting</a> で証明する

両辺から1を引いた数は，それぞれ $(0, 0)$ から $(k + 1, l + 1)$ までに**二回以上**折れ曲がって辿りつくパスの数，になっています (つまり $(k + 1, 0),\ (0, l + 1)$ は通ってはいけない)

左辺は **最後から二番目に折れ曲がった点** を $(i, j)$ として場合分けしています (それは $(0, 0)$ にはなりえないので，その分を左辺から引きます)

![二項係数2]({{ "img/comb2.png" | absolute_url }})

これはHockey-stick identityを使った簡潔な証明もあります

詳しくは [math stackexchangeでのこの質問](https://math.stackexchange.com/questions/3036489/proof-for-this-binomial-coefficients-equation){:target="_blank"}<!--_--> を参照してください

#### (4) 証明

![二項係数1]({{ "img/comb1.png" | absolute_url }})

上の左下 $(0, 0)$ から右上 $(k, n + m - k + 1)$ へのパスの数を考えます

途中の幅1のところを**どの高さで右に進むか**，で別々に足し合わせると求めたい式になります

#### (5) 証明

(4) に $m=k$ を代入します

# 練習問題

なし

# 参考

* [DEGwerさんの数え上げテクニック集](http://d.hatena.ne.jp/DEGwer/20171220){:target="_blank"}<!--_-->
* [重複組み合わせ - Wikipedia](https://ja.wikipedia.org/wiki/重複組合せ){:target="_blank"}<!--_-->
* [math stackexchangeでの質問](https://math.stackexchange.com/questions/3036489/proof-for-this-binomial-coefficients-equation){:target="_blank"}<!--_-->
* <a target="_blank" href="https://en.wikipedia.org/wiki/Double_counting_(proof_technique)">double counting - Wikipedia (en)</a>
* <a target="_blank" href="https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)">Stars and bars - Wikipedia (en)</a>
* [パスカルの三角形](https://ja.wikipedia.org/wiki/パスカルの三角形){:target="_blank"}<!--_-->
* [Vandermonde's identity - Wikipedia (en)](https://en.wikipedia.org/wiki/Vandermonde%27s_identity){:target="_blank"}<!--_-->
* [Hockey-stick identity](https://en.wikipedia.org/wiki/Hockey-stick_identity){:target="_blank"}<!--_-->


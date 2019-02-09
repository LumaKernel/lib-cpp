---
title: Divide and Conquer Optimiziation
---

$$f(i, j) = \min_{0 \leq k \lt j}\{f(i-1,k)+w_i[k+1,j]\}$$

という形のDPを解く．$i,j$の範囲をそれぞれ$N, M$としておく．愚直にやると $O(NM^2)$ かかる

$$
\newcommand{\argmin}{\mathop{\rm arg~min}\limits}
\newcommand{\argmax}{\mathop{\rm arg~max}\limits}
g(i, j, k) = f(i-1,k) + w_i[k + 1, j] \\
A[i][j] = \min \argmin_{0 \leq k \lt j} g(i, j, k)
$$

と置く．$A$は最小値を決定づける値 (の内の最小値) である．なぜか$A$が使われるので慣習的に$A$を使うことにする

また，$i=0$については適当に求めるとする．以下，$i\not = 0$ について考える

任意の $i, j$ について $A[i][j] \leq A[i][j+1]~~(\spadesuit)$ が成り立つ場合はDivide and Conquer Optimization (以降DAC Opt. と書く) を適用できる

DAC Opt.のメインアイデアは上記の制約$(\spadesuit)$をもとに，[Monotone Minima]({{ "dynamic-programming/speedup/Monotone-Minima" | absolute_url }}) を行うことである．Monotone Minima自体の説明はそちらに譲る

y軸方向に$j$, x軸方向に$k$ をとり，$g(i, j, k)$ をプロットすることを考える (これは行列とみなすことができる) ．各行についてその行の最小値 (で最も左) となる場所に注目すると，制約$(\spadesuit)$によりこれは右下がりにプロットされることになる

![Monotone]({{ "img/dac-opt1.png" | absolute_url }})

上記の図は$i = 1$だとする．実際は $k \lt j$ という条件があるため，対角線より下のみについてのみ考える点に注意すること．空集合に対する$\min$は適当に$\infty$であるとする (これが無効値となる)

Monotone Minima によりこれは $O(N M \log M)$で計算できる

# 条件を満たすための十分条件

まず，$k \lt j$ という制約から $w_i[k + 1, j]$ は 上三角についてのみ定義されていればいい．この上三角について [Concave Quadratic Inequality]({{ "math/Monge#convex-qi" | absolute_url }}) が満たされるならば$(\spadesuit)$が成立する

### 証明

$a \lt b \lt c \lt d$とする．$i$には依存しないため，$w \coloneqq w_i, f(x) \coloneqq f(i, x)$とする

![illust]({{ "img/dac-opt2.png" | absolute_url }})

今，$\textcolor{red}{d \rightarrow a}$ が最適であるとわかったとして，$c \rightarrow b$ より $c \rightarrow a$ のほうが良い値となることを示す

すなわち，

$$
f(a) + w[a + 1, d] \leq f(b) + w[b+1,d]
$$

を仮定して

$$
f(a) + w[a + 1, c] \leq f(b) + w[b+1,c]
$$

を導く．わかりやすさのために，  
$f(a)=$`X`,$f(b)=$`Y`,  
$w[a+1, d]=$`[===]`,  
$w[b+1, d]=$`[-==]`,  
$w[a+1, c]=$`[==-]`,  
$w[b+1, c]=$`[-=-]`

というふうに直感的な記号を割り当てる (あくまでも記号，区間を視覚化したつもり)

仮定より `X + [===] ≦ Y + [-==]` (1)

Convex QIより `[===] + [-=-] ≦ [==-] + [-==]` (2)

`(1) - (2)`より `X + [==-] ≦ Y + [-=-]` ■


# 例

[ネタバレを飛ばす](#実装)

[F - Yet Another Minimization Problem](https://codeforces.com/contest/868/problem/F){:target="_blank"} を例に挙げる．[ei1333さんの解説](https://ei1333.hateblo.jp/entry/2017/10/06/115551){:target="_blank"} を参考にした

ネタバレを含むため注意

### 問題概要

長さ$N~(\leq10^5)$ の数列$1 \leq a_i \leq N$が与えられます．ちょうど$K ~(\leq \min(N, 20))$ 個の(連続した)空ではない区間に分割します．各区間について，その中から2つを取り出してその数が等しいと言えるような，ペアの数をスコアとします．スコアの合計を最小化した値はいくつか求めなさい．全ての要素$a_i$はいずれかの区間に属している必要があります

ネタバレここから
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

### 解説

$$
f(i, j) \coloneqq j\text{-th}までをi+1個に分割したときの最小値 \\
w[l, r] \coloneqq [l, r]のスコア
$$

とすると

$$
f(i, j) = \min_{0 \leq k \lt j} \{f(i-1, k) + w[k, j]\} \\
f(0, j) = w[0, j]
$$

となります (これはページ上部の式に合致するので$w$を調べれば良いです)

$w$が$w_i$ではないのは，$i$に依存しないからです

$w$がConvex QI (上三角) であることを言えればDAC Opt.を適用できます

上三角だけ考えればいいので $a \lt b \lt c \lt d$として$X = [a, b], Y = [b, c], Z = [c, d]$とおく

区間$X, Y$で1つずつ採用するペア組を数えたものを$XY$などというふうに表記すると，

$$
\begin{aligned}
w[a, d] + w[b, c] = 
&(XX+XY+XZ+ \\
&YY+YZ+ZZ)+ \\
&(YY)
\end{aligned}
$$

$$
\begin{aligned}
w[a, c] + w[b, d] = 
&(XX+XY+YY) \\
&(YY+YZ+ZZ) \\
\end{aligned}
$$

となり，上のほうが$XZ$の分だけ大きい．よってConvex QIが (上三角に対して) 示されたのでDAC Opt.が適用できる

$w$は [Monotone Minima]({{ "dynamic-programming/speedup/Monotone-Minima" | absolute_url }}) に書いてあるが，$l, r$ の移動が準線形の回数で押さえられるため [Mo]({{ "algorithm/Mo" | absolute_url }}) のような，しゃくとりのようなことをすればよい

[submission](https://codeforces.com/contest/868/submission/48876868){:target="_blank"} ([mirror](https://gist.github.com/LumaKernel/2701c70245296cb9a3932d8885ab1efb){:target="_blank"})

<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
ネタバレここまで

# 実装

[Monotone Minima]({{ "dynamic-programming/speedup/Monotone-Minima" | absolute_url }}) が必要

// @ Divide and Conquer Optimization

# 検証

* [F - Yet Another Minimization Problem - codeforces](https://codeforces.com/contest/868/submission/48876868){:target="_blank"}<!--_-->

# 練習問題

* [F - Yet Another Minimization Problem - codeforces](https://codeforces.com/contest/868/problem/F){:target="_blank"}<!--_-->
* [#426 div1 B - The Bakery - codeforces](https://codeforces.com/contest/833/problem/B){:target="_blank"}<!--_-->

# 参考

* [ei1333さんの解説](https://ei1333.hateblo.jp/entry/2017/10/06/115551){:target="_blank"}<!--_-->
* [codeforcesのDP高速化まとめ記事](https://codeforces.com/blog/entry/8219#comment-139242){:target="_blank"}<!--_-->
* [codeforcesのDP高速化問題まとめ記事](https://codeforces.com/blog/entry/47932){:target="_blank"}<!--_-->
* [Totally Monotone Matrix Searching (SMAWK algorithm) - 週刊 spaghetti_source](https://topcoder.g.hatena.ne.jp/spaghetti_source/20120923/1348327542){:target="_blank"}<!--_-->
* [DP高速化 - ferinの競プロ帳](https://ferin-tech.hatenablog.com/entry/2018/02/23/071343){:target="_blank"}<!--_-->
* [競技プログラミングにおける動的計画法更新最適化まとめ（CHT, MongeDP, AlianDP, インラインDP, きたまさ法, 行列累乗） - はまやんはまやんはまやん](https://www.hamayanhamayan.com/entry/2017/03/20/234711){:target="_blank"}<!--_-->



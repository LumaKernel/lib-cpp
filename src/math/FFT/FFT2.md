---
title: 2次元FFT
---

[2変数の多項式](https://ja.wikipedia.org/wiki/多変数多項式){:target="_blank"}<!--_--> $f(x, y) = \sum\_{i,j} a\_{i, j}x^i y^j$ 2つをかけ合わせます

係数 $a$ は実数，$N \times M$ の行列 ( = 2次元配列 ) とします

# 要約

* 1次元のDFT, 畳み込みをそのまま2次元に自然に拡張できる
* 2次元FFTは1次元FFTを各行に行った後，各列に行うだけ．IFFTも同様

# 2次元DFT

2次元DFTは

$$\hat f (x, y) = \mathrm{DFT}_{N, M} (f) (x, y) = \sum_{i = 0}^{N-1} \sum_{j = 0}^{M-1} f(\zeta_N^i, \zeta_M^j) x^i y^j$$

と定義され，2次元IDFTは

$$\mathrm{DFT}_{N, M}^{-1} (f) (x, y) = \frac{1}{NM} \sum_{i = 0}^{N-1} \sum_{j = 0}^{M-1} \hat f(\zeta\_N^{-i}, \zeta_M^{-j}) x^i y^j$$

### 係数による表示

証明に移る前に，係数での表示がわかりやすいので，係数行列 $a$ とそれをDFTした $A = \mathrm{DFT}(a)$ を定義する

#### 1次元の場合

通常のDFTを係数で表示すると以下のようになる

$$A_i = \sum_{j=0}^{N-1} a_j \zeta_N^{ij}$$

$$a_k = \frac{1}{N} \sum_{i=0}^{N-1} A_i \zeta_N^{-jk}$$

#### 2次元の場合

2次元DFTの定義より，以下のようになる

$$\text{(DFT) } A_{i, j} = \sum_{k=0}^{N-1} \sum_{l=0}^{M-1} a_{k, l} \zeta_N^{ik} \zeta_M^{jl}$$

$$\text{(IDFT) } a_{m, n} = \frac{1}{NM} \sum_{i=0}^{N-1} \sum_{j=0}^{M-1} A_{i, j} \zeta_N^{-im}\zeta_M^{-jn}$$

### 証明

**DFTの定義を仮定**して**IDFTの定義が成り立つ**ことを証明する． IDFTの式にDFTの式を代入する

$$
\begin{aligned}
&&&(\text{IDFTの右辺}) &&\\
&&=& \frac{1}{NM} \sum_{i, j, k, l} a_{k, l} \times \zeta_N^{i(k-m)} \times \zeta_M^{j(l-n)} && \text{(ループ範囲は省略している)}\\
&&=& \frac{1}{NM} \sum_{k, l} a_{k, l} \sum_i \zeta_N^{i(k-m)} \sum_j \zeta_M^{j(l-n)} && \text{(シグマを潜り込ませた)}\\
&&=& \frac{1}{NM} \sum_{k, l} a_{k, l}
\left(\begin{cases}
N & (k = m)\\
0 & (k \not= m)\\
\end{cases}\right)
\left(\begin{cases}
M & (l = n)\\
0 & (l \not= n)\\
\end{cases}\right)
&& (\spadesuit : m,n\text{は定数})\\
&&=\ & a_{m, n} = (\text{IDFTの左辺})\\
\end{aligned}
$$

$(\spadesuit)$ の行での式変形については [FFT導入]({{ "FFT/introduction" | absolute_url }}) で説明している

# 2次元畳み込み

$$(f * g) = \mathrm{DFT}_{N, M}^{-1} (\mathrm{DFT}_{N, M} (f) \cdot \mathrm{DFT}_{N, M} (g))$$

なお，多項式同士の演算 $\cdot$ は係数ごとの掛け算 (component-wise multiplication)

$$a_{i, j} = \mathrm{DFT}_{N, M}^{-1} (\mathrm{DFT}_{N, M} (f) \cdot \mathrm{DFT}_{N, M} (g))$$

### 証明

$f, g, (f*g)$ のそれぞれの係数行列を$a, b, c$ とし，それらのDFTをそれぞれ $A, B, C$ とする

$$
\begin{aligned}
\widehat{(f * g)}(x, y)  
&&=& \sum_{i, j} (f * g) (\zeta_N^i, \zeta_M^j)x^iy^j && (\text{DFTの定義より})\\
&&=& \sum_{i, j} f(\zeta_N^i, \zeta_M^j)g(\zeta_N^i, \zeta_M^j)x^iy^j && (\text{畳み込みの定義より})\\
&&=& \sum_{i, j} A_{i, j} B_{i, j} x^iy^j \\
\end{aligned}
$$

ところで，$$\widehat{(f * g)}(x, y) = \sum_{i, j} C_{i, j}x^i y^j$$ より，  
$$C_{i, j} = A_{i, j} B_{i, j}$$ が言えます

これを多項式での表示に戻すと上記の畳込みの式となります

# 2次元FFT

係数行列 $a$ を $N \times M$ の行列とし，$N, M$ は2冪とする

1次元のDFTにより2次元のDFTを計算できる

各行，各列に対して1次元の係数列とみて$N + M$ 回のFFTをすればよい．IDFTも同様

計算量は $O(NM \log NM)$

### 証明

$a$ の各列をDFTしたものを $$a'$$，$$a'$$ の各行をFFTしたものを $$a''$$ とする

わかりやすくするために，1次元DFTに色付けする

$$(\mathrm{DFT}_\textcolor{green}N(a))_{\textcolor{red}i} = \sum_{\textcolor{blue}j=0}^{\textcolor{green}N-1} a_\textcolor{blue}j \zeta_\textcolor{green}N^{\textcolor{red}i\textcolor{blue}j}$$

以下の式変形では，対応する文字を同じ色にした

$$
\begin{aligned}

&A_{i, j}
&=& \sum_{k=0}^{N-1} \sum_{l=0}^{M-1} a_{k, l} \zeta_N^{ik} \zeta_M^{jl} \\

&A_{\textcolor{red}i, j}
&=& \sum_{l=0}^{M-1}
\left( \sum_{\textcolor{blue}k=0}^{\textcolor{green}N-1} a_{\textcolor{blue}k, l} \zeta_\textcolor{green}N^{\textcolor{red}i\textcolor{blue}k} \right)
\zeta_M^{jl}
&& (\textcolor{green}N\text{に注目})\\

&
&=& \sum_{l=0}^{M-1}
a'_{i, l}
\zeta_M^{jl}
&& (a'\text{の定義より})\\

&A_{i, \textcolor{red}j}
&=& \sum_{\textcolor{blue}l=0}^{\textcolor{green}M-1}
a'_{i, \textcolor{blue}l}
\zeta_\textcolor{green}M^{\textcolor{red}j\textcolor{blue}l}
&& (\textcolor{green}M\text{に注目})\\

&
&=\ &
a''_{i, j}
&& (a''\text{の定義より})\\

\end{aligned}
$$

よって $A$ と $$a''$$ が同じ行列であることが示された

行，列の順にDFTした場合も同様．IDFTも同様

---

無理やりラムダ式で書くとこんな感じ

$$
a'_{i, j} = (\mathrm{DFT}_N(\lambda y \rightarrow a_{y,j}))_i
\\
a''_{i, j} = (\mathrm{DFT}_M(\lambda x \rightarrow a'_{i,x}))_j
$$

# 実装

[複素数によるFFT]({{ "math/FFT/standard" | absolute_url }}) が必要

畳み込みについては [DFTを同時に求める高速化]({{ "math/FFT/standard#畳み込み高速化" | absolute_url }}) をしています

// @ FFT2

# 2次元NTT

[NTT]({{ "math/FFT/NTT" | absolute_url }}) が必要

// @ NTT2

ほぼ [NTT]({{ "math/FFT/NTT" | absolute_url }}) のコピペなので少し長くなった

# 検証

* FFT2 - [JAG2013Spring - F - Point Distance - AtCoder](https://beta.atcoder.jp/contests/jag2013spring/submissions/3684135){:target="_blank"}<!--_-->
* NTT2 - [JAG2013Spring - F - Point Distance - AtCoder](https://beta.atcoder.jp/contests/jag2013spring/submissions/3686678){:target="_blank"}<!--_-->

# 参考

* [2次元FFT - とどの日記](http://d.hatena.ne.jp/todo314/touch/20130811/1376221445){:target="_blank"}<!--_-->
* [2-D fast Fourier transform - MATLAB](https://jp.mathworks.com/help/matlab/ref/fft2.html?lang=en){:target="_blank"}<!--_-->
* [多変数多項式 - Wikipedia](https://ja.wikipedia.org/wiki/多変数多項式){:target="_blank"}<!--_-->


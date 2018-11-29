---
title: 2次元FFT
---

[2変数の多項式](https://ja.wikipedia.org/wiki/多変数多項式){:target="_blank"}<!--_--> $f(x, y) = \sum\_{i,j} a\_{i, j}x^i y^j$ 2つをかけ合わせます．係数 $a$ は実数，$N \times M$ の行列 ( = 2次元配列 ) とします

# 2次元DFT

2次元DFTは

$\hat f (x, y) = \mathrm{DFT}\_{N, M} (f) (x, y) = \sum\_{i = 0}^{N-1} \sum\_{j = 0}^{M-1} f(\zeta\_N^i, \zeta\_N^j) x^i y^j$

と定義され，2次元IDFTは

$\mathrm{DFT}\_{N, M}^{-1} (f) (x, y) = \frac{1}{NM} \sum\_{i = 0}^{N-1} \sum\_{j = 0}^{M-1} \hat f(\zeta\_N^{-i}, \zeta\_N^{-j}) x^i y^j$

# 2次元畳み込み

# 実装

// @ FFT 2D

# 検証

[JAG2013Spring - F - Point Distance - AtCoder](https://beta.atcoder.jp/contests/jag2013spring/submissions/3684135){:target="_blank"}<!--_-->

# 参考

* [2次元FFT - とどの日記](http://d.hatena.ne.jp/todo314/touch/20130811/1376221445){:target="_blank"}<!--_-->
* [2-D fast Fourier transform - MATLAB](https://jp.mathworks.com/help/matlab/ref/fft2.html?lang=en){:target="_blank"}<!--_-->


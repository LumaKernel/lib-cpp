---
title: Cooley-Tukey FFT
---

数列を高速に畳み込みます (多項式の掛け算)

2基底で，in-place (余分なメモリを使わない) なFFTです

FFTの基本については[FFT導入]({{ "math/FFT/introduction" | absolute_url }}) も参照してみてください

上記で紹介した，インデックスのパリティで分ける方法と違い，前半と後半に分けます．$N$ は同様に2ベキとします

DFTで求めたい各係数は以下のような形をしています

$$
\begin{aligned}
f(\zeta_N^i) = \sum_{j=0}^{N-1} a_j (\zeta_N^i)^j \\
\end{aligned}
$$

これを，左辺の$i$のパリティ (偶奇) で分けます．まず偶数の場合を考えます

$$
\begin{aligned}
f(\zeta_N^{2i})
&= \sum_{j=0}^{N} a_j \zeta_N^{2ij}
\\
&= \sum_{j=0}^{N/2-1} a_j \zeta_N^{2ij}
+ \sum_{j=N/2}^{N} a_j \zeta_N^{2ij}
\\
&= \sum_{j=0}^{N/2-1} a_j \zeta_N^{2ij}
+ \sum_{j=0}^{N/2-1} a_{\overline{j+N/2}} \zeta_N^{2i(j+N/2)}
\\
&= \sum_{j=0}^{N/2 - 1} \left\{
  a_j \zeta_N^{2ij}
  + a_{\overline{j+N/2}} \zeta_N^{2i(j + N/2)}
\right\}
\\
&= \sum_{j=0}^{N/2 - 1} \left\{
  a_j \zeta_{N/2}^{ij}
  + a_{\overline{j+N/2}} \zeta_{N/2}^{ij}
\right\}
\\
&= \sum_{j=0}^{N/2 - 1} (a_j +  a_{\overline{j+N/2}})\zeta_{N/2}^{ij}
\end{aligned}
$$

例えば，$b_i = a_i + a_{i + N/2}$ という長さ $N/2$ の数列を作ると，

$$a_{2i} = (\mathrm{DFT}_{N/2}(b))_i$$

であると言えます．同様に奇数の場合を考えます

$$
\begin{aligned}
f(\zeta_N^{2i+1})
&= \sum_{j=0}^{N} a_j \zeta_N^{(2i+1)j}
\\
&= \sum_{j=0}^{N/2-1} a_j \zeta_N^{(2i+1)j}
+ \sum_{j=N/2}^{N} a_j \zeta_N^{(2i+1)j}
\\
&= \sum_{j=0}^{N/2-1} a_j \zeta_N^{(2i+1)j}
+ \sum_{j=0}^{N/2-1} a_{\overline {j+N/2}} \zeta_N^{(2i+1)(j+N/2)}
\\
&= \sum_{j=0}^{N/2 - 1} \left\{
  a_j \zeta_N^{(2i+1)j}
  + a_{\overline{j+N/2}} \zeta_N^{(2i+1)(j + N/2)}
\right\}
\\
&= \sum_{j=0}^{N/2 - 1} \left\{
  a_j \zeta_{N/2}^{ij}\zeta_{N}^j
  - a_{\overline{j+N/2}} \zeta_{N/2}^{ij}\zeta_{N}^j
\right\} & (注1)
\\
&= \sum_{j=0}^{N/2 - 1} ((a_j - a_{\overline{j+N/2}})\zeta_N^j)\zeta_{N/2}^{ij}
\end{aligned}

\\

注1 : 指数法則, 原始根の約分みたいな性質, \zeta_1=1,\zeta_2=-1より
$$

例えば，$c_i = (a_i - a_{i + N/2})\zeta_N^i$ という長さ $N/2$ の数列を作ると，

$$a_{2i + 1} = (\mathrm{DFT}_{N/2}(c))_i$$

であると言えます．よって，長さが半分の問題２つを解くことでDFTが求められるため，通常のFFTと同じ計算量 $O(N \log N)$ となります

# 実装

[FFT導入]({{ "math/FFT/introduction" | absolute_url }}) で書いたDFTの部分をCooley-Tukey FFTに変更したものです

```cpp
vector<Complex> DFT(vector<Complex> a) {
  int n = a.size();
  if(n == 1) return a;

  vector<Complex> a0(n/2);
  vector<Complex> a1(n/2);

  for(int i = 0; i < n / 2; i++) a0[i] = a[i] + a[i + n/2];
  for(int i = 0; i < n / 2; i++) {
    Complex zeta_n_i = Complex(cos(2 * PI * i / n), sin(2 * PI * i / n));
    a1[i] = (a[i] - a[i + n/2]) * zeta_n_i;
  }

  // 小さいサイズのDFTを求める
  vector<Complex> inversed_a0 = DFT(a0);
  vector<Complex> inversed_a1 = DFT(a1);

  vector<Complex> inversed_a(n);
  for(int i = 0; i < n / 2; i++) {
    inversed_a[i * 2] = inversed_a0[i];
    inversed_a[i * 2 + 1] = inversed_a1[i];
  }

  return inversed_a;
}
```

# 参考

* [Cooley-Tukey 型 FFT](http://www.kurims.kyoto-u.ac.jp/~ooura/fftman/ftmn1_2.html){:target="_blank"}<!--_-->


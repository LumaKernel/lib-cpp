---
title: FFT導入
---

FFTは，Fast Fourier Transform（高速フーリエ変換）の略です

一般に波形などに適用するようですがそちらはよくわからないため，競プロでの用途限定で書いていきます

もし，ここでFFTを1から学ぶという方は，ノートなどを用意すると良いと思います

($\zeta$(ゼータ)が書きにくい場合は$\omega$(オメガ)などで代用してください)

# FFTとは

FFTは数列同士の畳込み(=多項式の掛け算)を$O(N \log N)$で行うアルゴリズムです

詳しく書くと，DFTを用いる畳み込みにおいて，DFTのアルゴリズムにFFTを用いることで$O(N \log N)$が達成できます

ひとつひとつ噛み砕いて説明していきます

# 前提知識

その前に，いくつか前提知識を書いておきます

* 高校数学
  * 虚数とか，複素数とか
    * $\omega^3=1$とかがわかればいいと思います
    * [1の三乗根オメガを用いた計算と因数分解](https://mathtrain.jp/omega){:target="_blank"}<!--_-->
    * 以下の記事にあるように，複素数を図形でイメージできるとなお良いです
    * [1のn乗根の導出と複素数平面](https://mathtrain.jp/njokonof1){:target="_blank"}<!--_-->
    * [直交座標と極座標（２次元）の変換とメリットの比較](https://mathtrain.jp/kyokuzahyo){:target="_blank"}<!--_-->
  * 等比数列の和
    * 一部の証明にちょっとだけ使います
    * [等比数列の和の公式の証明といろいろな例](https://mathtrain.jp/sumtouhi){:target="_blank"}<!--_-->
* $\sum$を入れ替えられることとか
  * [シグマ計算を機械的に行うための３つの公式](https://mathtrain.jp/sigma){:target="_blank"}<!--_-->
* 分割統治法の考え方と，その計算量
  * $T(n)=2T(n/2)+O(n)$ の時，$T(n)=O(n\log n)$ です
* 多項式
  * [単項式，多項式，整式](https://mathtrain.jp/seishiki){:target="_blank"}<!--_-->
  * この記事内でも少し説明します

上記のリンクはすべて「高校数学の美しい物語」です．復習用にご参照ください

以下，虚数単位を $i$ と書くことは**ありません**．添字の整数として用います

# 多項式

多項式とは，$x^2 + x - 1$みたいな式のことで，$x$ についての多項式は，係数 $a_i(i \geq 0)$を用いて $a_ix^i$ と書ける項を足していったものです

$i$は虚数単位ではなく，整数です

$x^i$の$i$の部分を次数といいます

多項式は次数が$0$以上なので，$x^2 + x - 1$ではなく，$-1 + x + x^2$の順序で書くことにします

多項式の次数とは，その多項式の中で最高次の項の次数をいいます

多項式は，関数みたいに $f(x) = -1 + x + x^2$と書くようにします

$f(x) = -1 + x + x^2$ の次数は $2$ です

$\log x$や$2^x + 3\sqrt x$ は多項式ではありません

---

多項式と数列を1対1対応させることができます

多項式は係数によって決まるので，係数数列を多項式の代わりに保持することができます

例えば，$f(x) = -1 + 2x + x^2$の係数数列は $$a =\{-1, 2, 1\}$$ です

数列はこの記事では $a = (a_i)_{i=0}^{N-1}$のように書いたりします

$k$次の多項式は一般に

$\displaystyle f(x) = a_0x^0 + a\_1x^1 + \cdots + a\_kx^k = \sum_{i=0}^k a_ix^i$

とかけます

この時，$a_k\not=0$でなければいけませんが，この記事ではしばしば$a_k=0$である可能性があるものに対しても，$k$次であると呼ぶことがあります

それは，$i \gt k$にたいして$a_i = 0$であればよい，程度の意味だと捉えてください

また，サイズ $N$ の多項式を，次数が $N-1$ 以下の多項式とします

$-1$ は $x^0$ の分です (0-indexedだから，ということ)

# 畳み込み

ここでは，畳み込みとは 数列 $$a = (a_i)_{i=0}^{N-1}$$ と $$b = (b_i)_{i=0}^{M-1}$$ から新たな数列 $$c = (c_i)_{i=0}^{N + M - 2}$$ を求めることです

$c$ は $0 \leq k \leq N + M - 2$ について以下を満たします

$\displaystyle c_k = \sum_{i=0}^{k}a_ib_{k - i}$

ただし，範囲外については$a,b$どちらも$0$を返すとします ($a_{-1}=0$など)

$a,b,c$を係数とする多項式をそれぞれ$f,g,h$としましょう

すなわち，

$$
\begin{aligned}
&f(x) = a_0 + a_1x + a_2x^2 + \cdots + a_{N-1}x^{N-1} \\
&g(x) = b_0 + b_1x + b_2x^2 + \cdots + b_{M-1}x^{M-1} \\
&h(x) = c_0 + c_1x + c_2x^2 + \cdots + c_{N + M -2}x^{N + M - 2} \\
\end{aligned}
$$

です

$f(x) \times g(x) = h(x)$ となるのがわかりますか?

簡単な例を示します

$f(x) = 1 + 3x + 2x^2$と$g(x) = 2 -  x^2$を考えます

$$
\begin{aligned}
f(x) \times g(x) &=&&(1 + 3x + 2x^2)(2 -  x^2) \\
&=&& (1\cdot 2) x^0 \\
&&&+ (3 \cdot 2)x^1 \\
&&&+ (1 \cdot (-1) + 2 \cdot 2)x^2 \\
&&&+ (3 \cdot (-1))x^3  \\
&&&+ (2 \cdot (-1) )x^4  \\
&=&& 2 + 6x + 3x^2 - 3x^3 - 2x^4 \\
\end{aligned}
$$

これが多項式同士の掛け算です


もう一つ， $f(x) = a_0 + a_1x + a_2x^2$ と $f(x) = b_0 + b_1x + b_2x^2$ を考えます

$$
\begin{aligned}
f(x) \times g(x) &=&&(a_0 + a_1x + a_2x^2)(b_0 + b_1x + b_2x^2) \\
&=&& (a_0b_0)x^0 \\
&&& + (a_0b_1 + a_1b_0)x^1 \\
&&&+ (a_0b_2 + a_1b_1+a_2b_0)x^2 \\
&&&+ (a_1b_2 + a_2b_1)x^3 \\
&&&+ (a_2b_2)x^4 \\
\end{aligned}
$$

えーわかりますでしょうか

$x^k$の係数は$i + j = k$という条件を満たす全ての$i,j$についての，$a_ib_j$を足したものになっています

一般的にかくと，

$$
\begin{aligned} &f(x) = \sum_{i=0}^{N-1}a_ix^i \\
&g(x) = \sum_{j=0}^{M-1}b_jx^j \\
&f(x)\times g(x) = h(x) = \sum_{i=0}^{N+M-2}c_ix^i \\
&h(x) = \sum_{i=0}^{N-1}\sum_{j=0}^{M-1}a_ib_jx^{i+j} \\
\end{aligned}
$$

というところまでいきます．なぜそうなるか，という点については，素直に掛け合わせてシグマを入れ替えるとそうなるからです

上記の式により，$h$ のサイズが $N+M-1$ であることにも納得がいくかと思います

また次のように言い換えることができます

$\displaystyle h(x) = \sum_{k=0}^{N+M-2}\sum_{i=0}^{k}a_ib_{k-i}x^k$

ただし，範囲外の添字に対しては係数は0とします

---

以上，<strong style="color:red">数列の畳み込みと，それが多項式において掛け算と等しくなる</strong>，ということを説明しました

$h(x) = f(x) \times g(x) = (f \ast g) (x)$ と書きます

# 愚直に求める

```cpp
vector<int> conv(vector<int> a, vector<int> b) {
  int deg = a.size() + b.size() - 1;
  vector<int> c(deg);
  for(int i = 0; i < a.size(); i++)
    for(int j = 0; j < b.size(); j++)
      c[i + j] += a[i] * b[j];
  return c;
}
```

なお，convはconvolution(畳み込み)の略である

これは見たまま，$O(N^2)$となる

# 1の原始N乗根

簡単のため, $\|a\| = \|b\| = N$ とする

離散フーリエ変換に行く前に， $\zeta_N$ について説明する

$x^N = 1$ の解が $\zeta_N$ である

$\zeta_3 = \omega$ だ

ただし，解は複素数全体で$N$個あるが，それらすべてを$1, \zeta_N^1, \zeta_N^2, \cdots ,\zeta_N^{N-1}$ で表せる必要がある

位数なんて難しい話は抜きにして，

$\displaystyle \zeta_N = \cos(\frac{2\pi}{N}) +\sqrt {-1}\sin(\frac{2\pi}{N}) = \exp(\frac{2\pi}{N})$

と定めれば条件を満たす

こうするといろんな特徴があって，

* $\displaystyle \zeta_N^i = \zeta_N^j$と$\displaystyle i \equiv j \mod N$は同値
* $\displaystyle \zeta_{nk}^{ik}=\zeta_n^i$ (分数の約分のようなもの)

これらは複素平面を考えると納得がいく (もしくは$\omega$の特徴が拡張された，と考えることもできる)

また，以下が成り立つ

$\displaystyle \sum_{i=0}^{N-1}\zeta_N^{ki} = \begin{cases} N & (k \equiv 0 \mod N) \\\\ 0 & (otherwise) \end{cases}$

$k\equiv 0$は簡単なので，$otherwise$について示す

$$
\begin{aligned}
\sum_{i=0}^{N-1}\zeta_N^{ki} &= \frac{\zeta_N^N - 1}{\zeta_N - 1}& (\text{等比数列の和より}) \\
&= \frac{\zeta_N^0 - 1}{\zeta_N - 1}& (\mathrm{mod}\ Nにより) \\
&= \frac{1 - 1}{\zeta_N - 1} = 0
\end{aligned}
$$

等比数列の和の公式が複素数に適用できるかというのは，自分で複素数考慮で求めなおしたりすれば自明

---


ところで$\zeta$(ゼータ)は書きにくいと感じるかもしれません  
$\omega$(オメガ)などで代用しても大丈夫ですし，書いているうちに慣れてくるかもしれないので，使ってみるのもいいかもしれません

# 離散フーリエ変換

$\displaystyle \hat{f}(x) = f(\zeta_N^0)x^0 + f(\zeta_N^1)x^1 +\cdots + f(\zeta_N^{N-1})x^{N-1} = \sum_{i=0}^{N-1} f(\zeta_N^i)x^i$

と定義します

$\hat{f}$ が $f$ の離散フーリエ変換です

関数的に書くと，$\mathrm{DFT}_{N}(f) = \hat{f}$です．$N$はサイズを表し，多項式をどのようなサイズで捉えるかによってDFTの結果が変わるということは押さえておいてください

DFTとはDiscrete Fourier Transform (離散フーリエ変換) です．ここではその本質には迫らず，**特性**，**アルゴリズムの正しさ**について焦点をあてていきます

$\hat{f}$も多項式になっているので，数列と対応させることができます．FFTはこのDFTを高速に行うためのアルゴリズムです

---

まず，

$\displaystyle f(x) = \textcolor{red}{\frac{1}{N}}\sum_{i=0}^{N-1} \hat{f}(\zeta_N^{\textcolor{red}{-i}})x^i$

を示します．式の中にある， $\hat{f}(\zeta_N^{\textcolor{red}{-i}})$ について考えます

$\displaystyle \text{DFTの定義 : }\hat{f}(x) = \sum_{j=0}^{N-1} f(\zeta_N^j)x^j$

に $x=\zeta_N^{\textcolor{red}{-i}}$ を代入すると，

$\displaystyle \hat{f}(\zeta\_N^{\textcolor{red}{-i}}) = \sum_{j=0}^{N-1} f(\zeta_N^j)\zeta\_N^{-ij}$

さらに，$f(x) = \sum_{k=0}^{N-1}a_kx^k$を代入してやります

$\displaystyle \begin{aligned} \hat{f}(\zeta_N^{\textcolor{red}{-i}}) &= \sum_{j=0}^{N-1} \sum_{k=0}^{N-1}a_k\zeta_N^{jk}\zeta_N^{-ij}\\ &= \sum_{k=0}^{N-1}a_k\sum_{j=0}^{N-1} \zeta_N^{(k-i)j}\\ \end{aligned}$

一番内側について，

$\displaystyle \sum_{i=0}^{N-1}\zeta_N^{ki} = \begin{cases} N & (k \equiv 0 \mod N) \\\\ 0 & (otherwise) \end{cases}$

を使います

$(k - i) \not\equiv 0 \mod N$ならば，全体で$a_k$倍されるものの，$0$なので，消えます

$\|k-i\|\leq N$ に注意して丁寧に書くと，

$\displaystyle \begin{aligned} \hat{f}(\zeta_N^{\textcolor{red}{-i}}) &= \sum_{k=0}^{N-1}a_k \left( \begin{cases} N & (k=i) \\\\ 0 & (otherwise) \end{cases} \right) \\\\ & = Na_i \end{aligned}$

が導かれます

これを右辺に代入すると，

$\displaystyle \begin{aligned} \textcolor{red}{\frac{1}{N}}\sum_{i=0}^{N-1} \hat{f}(\zeta_N^{\textcolor{red}{-i}})x^i &=\frac{1}{N}\sum_{i=0}^{N-1} Na_ix^i\\ &=\sum_{i=0}^{N-1}a_ix^i\\ &=f(x) = \text{(左辺)}\\ \end{aligned}$

が言えました

---

再掲

$\displaystyle f(x) = \textcolor{red}{\frac{1}{N}}\sum_{i=0}^{N-1} \hat{f}(\zeta_N^{\textcolor{red}{-i}})x^i$

ところでこれはDFTの定義に似ていませんか?

DFT:

$\displaystyle \hat{f}(x) = \sum_{i=0}^{N-1} f(\zeta_N^i)x^i$

上のものを，逆離散フーリエ変換（IDFT; Inversed Discrete Fourier Transform）といいます

関数的に書くと，

$\displaystyle \mathrm{DFT}_N^{-1}(\mathrm{DFT}_N(f))=f$

です

ちょうど逆関数の関係になっています

逆関数が似たような処理になっていることにより，実際にプログラムを書く際に少し楽になるということです

---

DFTを使って畳み込みを計算することをかんがえます

$\widehat{(f\*g)}$ が計算できれば，IDFTすることで目的の $(f\*g)$ が得られます．DFTの定義より，

$\displaystyle \widehat{(f\*g)}(x) = \sum\_{i=0}^{N-1} (f\*g)(\zeta\_N^i)x^i$

ここで，定義である $(f*g)(x)=f(x)\cdot g(x)$ を代入すると，

$\displaystyle \widehat{(f\*g)}(x) = \sum\_{i=0}^{N-1} f(\zeta\_N^i)g(\zeta\_N^i)x^i$

ところで，$f(\zeta_N^i)$と$g(\zeta_N^i)$は，$\hat f$と$\hat g$という多項式の係数です

よって，この係数がDFTによって得られれば，$O(N)$ で $\widehat{(f*g)}(x)$ が得られます

（ここでいう「ある多項式が求まる」とは，「その係数の数列がもとまる」ということです）

あとはIDFTしてやればよいです

よって，まとめると，

$\displaystyle (f*g) = \mathrm{DFT}_N^{-1}(\mathrm{DFT}_N(f) \cdot \mathrm{DFT}_N(g))$

ということになります

ただし，関数同士に対する演算子$\cdot$とは，係数単位で掛け合わせる操作です (数列としてのアダマール積, component-wise multiplication)

以下，疑似コードです

```cpp
using Real = long double;
using Complex = complex<Real>;

// これから説明する
vector<Complex> DFT(vector<Complex>);
vector<Complex> IDFT(vector<Complex>);

vector<Complex> conv(vector<Complex> a, vector<Complex> b) {
  int deg = a.size() + b.size() - 1;
  vector<Complex> inversed_c(deg);

  // f, g に対してDFTを行う
  vector<Complex> inversed_a = DFT(a);
  vector<Complex> inversed_b = DFT(b);

  // 係数どうしをかけ合わせる
  for(int i = 0; i < deg; i++)
      inversed_c[i] = inversed_a[i] * inversed_b[i];
  vector<Complex> c = IDFT(inversed_c);
  return c;
}
```

入力の虚部はすべて0です．また，無限の精度があれば，返ってくる値の虚部は0です

# DFTを高速に求める

再掲

DFT:

$\displaystyle \hat{f}(x) = \sum_{i=0}^{N-1} f(\zeta_N^i)x^i$

DFTを求めることというのは，$f(\zeta_N^0), f(\zeta_N^1),\cdots ,f(\zeta_N^{N-1})$を求めることです．FFTによってこいつを高速に求めます．FFTのアイデアは分割統治です

---

$f$ の係数を添字のパリティ（偶奇）で分けます

$\displaystyle \begin{aligned} &f_0(x) &= a_0 + a_2x + a_4x^2 + \cdots &= \sum_{i=0}^{N/2-1}a_{2i}x^i \\\\ &f_1(x) &= a_1 + a_3x + a_5x^2 + \cdots &= \sum_{i=0}^{N/2-1}a_{2i+1}x^i \end{aligned}$

$N$ は後々のために2べきとします

$f(x) = f_0(x^2) + xf_1(x^2)$ になることが分かるかと思います．$x = \zeta_N^i$ を代入します

$\displaystyle f(\zeta_N^i) = f_0(\zeta_N^{2i}) + \zeta_N^i\cdot f_1(\zeta_N^{2i})$

ここで， $\zeta_{nk}^{ik}=\zeta_n^i$ を思い出してください（約分みたいなもの）

$\displaystyle f(\zeta_N^i) = f_0(\zeta_{N/2}^i) + \zeta_N^i\cdot f_1(\zeta_{N/2}^i)$

よって，

|求めたいもの|$f(\zeta_N^0)$|$f(\zeta_N^1)$|$\cdots$|$f(\zeta_N^{N/2-1})$|$f(\zeta_N^{N/2})$|$\cdots$|$f(\zeta_N^{N-1})$|
|--|--|--|--|--|--|--|--|
|必要なもの1|$f_0(\zeta_{N/2}^0)$|$f_0(\zeta_{N/2}^1)$|$\cdots$|$f_0(\zeta_{N/2}^{N/2-1})$|$f_0(\zeta_{N/2}^{N/2})$|$\cdots$|$f_0(\zeta_{N/2}^{N-1})$
|必要なもの2|$f_1(\zeta_{1N/2}^0)$|$f_1(\zeta_{N/2}^1)$|$\cdots$|$f_1(\zeta_{N/2}^{N/2-1})$|$f_1(\zeta_{N/2}^{N/2})$|$\cdots$|$f_1(\zeta_{N/2}^{N-1})$

となりました

ところで，$\mathrm{mod}\ \frac{N}{2}$を考えると，


|求めたいもの|$f(\zeta_N^0)$|$f(\zeta_N^1)$|$\cdots$|$f(\zeta_N^{N/2-1})$|$f(\zeta_N^{N/2})$|$\cdots$|$f(\zeta_N^{N-1})$|
|--|--|--|--|--|--|--|--|
|必要なもの1|$f_0(\zeta_{N/2}^0)$|$f_0(\zeta_{N/2}^1)$|$\cdots$|$f_0(\zeta_{N/2}^{N/2-1})$|$f_0(\zeta_{N/2}^{\textcolor{red}0})$|$\textcolor{red}{\cdots}$|$f_0(\zeta_{N/2}^{\textcolor{red}{N/2-1}})$
|必要なもの2|$f_1(\zeta_{N/2}^0)$|$f_1(\zeta_{N/2}^1)$|$\cdots$|$f_1(\zeta_{N/2}^{N/2-1})$|$f_1(\zeta_{N/2}^{\textcolor{red}0})$|$\textcolor{red}{\cdots}$|$f_1(\zeta_{N/2}^{\textcolor{red}{N/2-1}})$

何が言いたいかというと， $f_0(\zeta_{N/2}^0),f_0(\zeta_{N/2}^1),\cdots,f_0(\zeta_{N/2}^{N/2-1})$と$f_1(\zeta_{N/2}^0),f_1(\zeta_{N/2}^1),\cdots,f_1(\zeta_{N/2}^{N/2-1})$ さえわかれば良いです

そしてこれらは $f_0,f_1$ のDFT (によって求まる係数の数列) そのものです．よって，サイズが $1/2$ のDFTを2つ求めて，$O(N)$ で求めたい多項式のDFTが求まります

---

サイズが$1$であるときについて考えます

$f(x) = a_0$ です．$f(\zeta_1^0) = f(1) = a_0$ なので係数は変わりません．$\hat f (x) = a_0$ となります

---

計算量を考えてみます

$T(N)$ を次数$N$の多項式のFFTの最悪実行時間とします

$T(N) = 2T(N/2) + O(N)$

この形は，分割統治と同じです．なので，$T(N) = O(N \log N)$ がわかります

[分割統治とマスター定理の紹介 - るまブログ](https://tomorinao.blogspot.com/2018/10/devide-and-conquer-and-master-theorem.html){:target="_blank"}<!--_-->

---

FFTを用いてDFTを求める疑似コードです

```cpp
const double PI = 3.1415926535897932384626433832795028841971;
vector<Complex> DFT(vector<Complex> a) {
  int n = a.size();
  vector<Complex> a0(n/2);
  vector<Complex> a1(n/2);

  // パリティで分ける
  for(int i = 0; i < n / 2; i++) a0[i] = a[i * 2];
  for(int i = 0; i < n / 2; i++) a1[i] = a[i * 2 + 1];

  // 小さいサイズのDFTを求める
  vector<Complex> inversed_a0 = DFT(a0);
  vector<Complex> inversed_a1 = DFT(a1);

  // f(x) = f0(x^2) + x f1(x^2) に従いDFTを求める
  vector<Complex> inversed_a(n);
  for(int i = 0; i < n; i++) {
    Complex zeta_n_i = Complex(cos(2 * PI * i / n), sin(2 * PI * i / n));
    inversed_a[i] = inversed_a0[i % (n /2)] + zeta_n_i * inversed_a1[i % (n / 2)];
  }

  return inversed_a;
}
```

$N$ は2べきです (convで適当に調整します)

`zeta_n_i` は $\zeta_N^i$ です

$\zeta_N^i$ を上記コードのようにその場で求めることをせずに，掛け算によって $\zeta_N$ から求めようとすると誤差が大きくなるので注意してください

# 逆離散フーリエ変換

再掲

IDFT:

$\displaystyle f(x) = \textcolor{red}{\frac{1}{N}}\sum_{i=0}^{N-1} \hat{f}(\zeta_N^{\textcolor{red}{-i}})x^i$

関数的に書いたほうが，入力・出力がはっきりとわかりやすいと思うので，書き換えます

$\displaystyle DFT\_N^{-1}(f)(x) = \textcolor{red}{\frac{1}{N}}\sum_{i=0}^{N-1} f(\zeta_N^{\textcolor{red}{-i}})x^i$

DFTと同様に，何を求めればいいかを考えます

$\frac{1}{N}$ は後から掛ければどうにでもなるので一旦無視します．以下が求まればいいです．

$\displaystyle f(\zeta_N^{-0}), f(\zeta_N^{-1}), \cdots, f(\zeta_N^{-(N-1)})$

$\mathrm{mod}\ N$ で$\zeta_N^i$ は同値なので，

$\displaystyle f(\zeta_N^{N-0}), f(\zeta_N^{N-1}), \cdots, f(\zeta_N^{-(N - (N - 1))})$

すなわち，

$\displaystyle f(\zeta_N^0), f(\zeta_N^{N-1}), \cdots, f(\zeta_N^1)$

よって，DFTと同様に求めて，入れ替えをしてやれば良いです

---

他にも，DFTにおいて $\zeta_N^i$ を用いている部分を $\zeta_N^{-i}$ に差し替える，という方法もあります (というか差し替えしか見かけない，以下では入れ替えで説明します)

---

最後に各係数を $N$ で割ってやります

$O(N \log N)$ のDFTに加えて，反転と $N$ で割ることに $O(N)$ かかるので，$O(N \log N)$ でIDFTは実行できます

IDFTの疑似コードです

```cpp
vector<Complex> IDFT(vector<Complex> inversed_a) {
  int n = inversed_a.size();
  // まずふつうにDFT
  vector<Complex> arranged = DFT(inversed_a);

  // 係数を入れ替える
  vector<Complex> swaped(n);
  for(int i = 0; i < n; i++) swaped[i] = arranged[(n - i) % n];

  // サイズnで各要素を割る
  vector<Complex> a(n);
  for(int i = 0; i < n; i++) a[i] = swaped[i] / Complex(n, 0);

  return a;
}
```

# FFT

最後にサイズ$N$を2べきに丸めるようにconvを書き換えます

書き換えた擬似コード全体が以下になります

```cpp
using Real = double;
using Complex = complex<Real>;

const Real PI = 3.1415926535897932384626433832795028841971;
vector<Complex> DFT(vector<Complex> a) {
  int n = a.size();
  if(n == 1) return a;

  vector<Complex> a0(n/2);
  vector<Complex> a1(n/2);

  // パリティで分ける
  for(int i = 0; i < n / 2; i++) a0[i] = a[i * 2];
  for(int i = 0; i < n / 2; i++) a1[i] = a[i * 2 + 1];

  // 小さいサイズのDFTを求める
  vector<Complex> inversed_a0 = DFT(a0);
  vector<Complex> inversed_a1 = DFT(a1);

  // f(x) = f0(x^2) + x f1(x^2) に従いDFTを求める
  vector<Complex> inversed_a(n);
  for(int i = 0; i < n; i++) {
    Complex zeta_n_i = Complex(cos(2 * PI * i / n), sin(2 * PI * i / n));
    inversed_a[i] = inversed_a0[i % (n / 2)] + zeta_n_i * inversed_a1[i % (n / 2)];
  }

  return inversed_a;
}

vector<Complex> IDFT(vector<Complex> inversed_a) {
  int n = inversed_a.size();
  // まずふつうにDFT
  vector<Complex> arranged = DFT(inversed_a);

  // 係数を入れ替える
  vector<Complex> swaped(n);
  for(int i = 0; i < n; i++) swaped[i] = arranged[(n - i) % n];

  // サイズnで各要素を割る
  vector<Complex> a(n);
  for(int i = 0; i < n; i++) a[i] = swaped[i] / Complex(n, 0);

  return a;
}

vector<Complex> conv(vector<Complex> a, vector<Complex> b) {
  int deg = a.size() + b.size() - 1;
  int n = 1;
  // 2べきを用いる
  while(n < deg) n <<= 1;
  // サイズを変更する (0で埋める)
  a.resize(n); b.resize(n);

  // f, g に対してDFTを行う
  vector<Complex> inversed_a = DFT(a);
  vector<Complex> inversed_b = DFT(b);

  vector<Complex> inversed_c(n);
  // 係数どうしをかけ合わせる
  for(int i = 0; i < n; i++)
      inversed_c[i] = inversed_a[i] * inversed_b[i];
  vector<Complex> c = IDFT(inversed_c);
  return c;
}
```

この実装は実際に動きます ([C - 高速フーリエ変換 - AtCoder での提出](https://beta.atcoder.jp/contests/atc001/submissions/3337540){:target="_blank"}<!--_-->)

FFTの話は以上になります

DFTとIDFTをまとめてやる方法がよく用いられています

小数を整数に丸めるときは，出力が `-0` にならないようにしたり，intにキャストするよう気をつけてください

誤差をちゃんとごまかすこと，そしてその手法も大切です

# 発展

以下では競プロに役立つような発展的話題を紹介します

* $\zeta_N$ に複素数以外を用いる
* DFTで発展したFFTを使う

の2つの発展が考えられます

両方を変更することもできます

## 複素数以外を用いる

複素数以外でいい性質を示すものがあります

それは，

* 1の原始N乗根が存在するような
* 可換環

で可能です

素数を法とする整数環は上記の性質を満たします

このような整数環上で行うFFTのことをNTTといいます (NTTで使える素数はもう少し制約があります (これもちょっと違うけど) )

詳しくは [数論変換(Number Theoretic Transform; NTT)]({{ "math/FFT/NTT" | absolute_url }}) を参照してください

## FFTの発展

まず，基本的なFFTの高速化，非再帰化については [基本的なFFT]({{ "math/FFT/standard" | absolute_url }}) を参照してください

FFTのアルゴリズムには色々とあり，基底 (いくつに分けるか) を2以外にしたものなど色々あります．実用面で有利であったり，並列化するときに有利であるようなものがあるようです． ここでは Cooley-Tukey FFT を紹介します

### Cooley-Tukey(CT) FFT

2基底で，この記事で紹介した方法とは違う分割の仕方をする，in-place (余分なメモリを使わない) なFFTです

詳しくは [Cooley-Tukey FFT]({{ "math/FFT/Cooley-Tukey-FFT" | absolute_url }}) を参照してください

## [二次元FFT]({{ "math/FFT/FFT2" | absolute_url }})

難しそうと思うかもしれませんが，FFTへの理解を深める手助けになるかと思います

DFTを係数による表示で紹介しています．それによりDFTをより扱いやすくなるかと思います


---

長文になりましたが，読んでいただきありがとうございました．700行近くになってしまいました．不明瞭な部分があれば下のコメントか[twitter](https://twitter.com/lumc_){:target="_blank"}<!--_-->にて教えてくださると助かります．修正まで時間がかかるかもしれません，ご了承下さい

# 参考

* [高速フーリエ変換 (AtCoder) - SlideShare](https://www.slideshare.net/chokudai/fft-49066791){:target="_blank"}<!--_-->
* [多項式 - wikipedia](https://ja.wikipedia.org/wiki/多項式){:target="_blank"}<!--_-->
* [多項式を使うテクニックたち - yukicoder](https://yukicoder.me/wiki/polynomial_techniques){:target="_blank"}<!--_-->


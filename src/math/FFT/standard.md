---
title: 基本的なFFT
---

多項式2つを高速にかけ合わせます

[FFT導入]({{ "math/FFT/introduction" | absolute_url }}) では再帰による2基底のFFTを紹介しましたが，ここではそのFFTを色々と改善していきます

まず，DFTとIDFTは同じ関数内で処理することが多いです

IDFTはDFTの結果を，$1 \leq i \leq \frac{N}{2}$ に対して `swap(a[i], a[N - i])` することでも求まりますが，DFTで $\zeta_N^i$ を使う部分を $\zeta_N^{-i}$ に差し替えるという方法でもいいです

# 非再帰化

FFTの演算を図式化してみると，なんかかっこいい感じになり，それが蝶に似ているため，バタフライ演算と呼ばれています

図式化すると，求める方法を工夫することで上記の再帰型のFFTを非再帰にできます

バタフライ演算とFFTの非再帰化については [高速フーリエ変換 (FFT) - pekempey's blog](https://pekempey.hatenablog.com/entry/2016/10/24/171936){:target="_blank"}<!--_--> がとてもわかりやすいです

ここで，偶数インデックスに関しては左側で，奇数インデックスに関しては右側で計算する (し終わっている) という形になっています．こうすることで bit が反転してしまいますが，in-placeで非再帰のFFTとなります (以下の説明はコードを見てからのほうがわかりやすいかもしれません)

このインデックス入れ替えが起こらないようにするとどうでしょう

$f_T(\zeta_{2^t}^i) = f_{0T}(\zeta_{2^{t-1}}^i) + \zeta_{2^t}^if_{1T}(\zeta_{2^{t-1}}^i$) と定義します．ここで，$T, i$は二進表記だと思ってください．$0T$ などは，二進表記で結合したものです (掛け算ではありません)

例えば， $f_{01}(\zeta_{2^t}^{10}) = f_{001}(\zeta_{2^{t-1}}^{10}) + \zeta_4^{10} f_{101}(\zeta_{2^{t-1}}^{10})$ とかになります

ここで，$f_T(\zeta_{2^t}^i)$ がどこにあるか考えると，$t = h - 1$ から考えると，$iT$ の位置にあることがわかります

つまり， $iT$ は $i0T$ と $i1T$ から求まります．必要となる２つの数が小さいことも大きいこともあるので，配列を２つ用意して交互に使う必要があります．インデックス範囲からはみ出た分は無視します (ビットマスクをかけます)

新しいインデックス $iT$ の昇順にもとめていくことで，$\zeta$ を求めるための三角関数を呼び出す回数を少なくすることができます

$T$ の桁数 ( = $t$ ) を減らしながら求めていきます．$N = 2^h$ であるなら $T$ は $h - 1$ 桁，つまり $t = h - 1$ からです

```cpp
vector< Complex > dft(vector< Complex > a, size_t h, bool inverse) {
  constexpr Real PI = 3.14159265358979323846;
  size_t n = a.size(), mask = n - 1;
  static vector< Complex > tmp;
  tmp.resize(n);
  for(size_t j = n >> 1, t = h - 1; j >= 1; j >>= 1, --t) {
    for(size_t k = 0; k < n; k++) {
      size_t T = k & (j - 1); // T は 下 t 桁
      size_t i = k >> t; // i は 上 h - t 桁
      Real theta = 2 * PI * j * i * (inverse ? -1 : 1) / n;
      Complex zeta_i(cos(theta), sin(theta)); // ζ_(2^(h - t))^i
      tmp[k] = a[((i << (t + 1)) | T) & mask] + zeta_i * a[((i << (t + 1)) | j | T) & mask];
    }
    swap(a, tmp);
  }
  if(inverse)
    for(size_t i = 0; i < n; ++i) a[i] /= n;
  return a;
}
```

コード中の `zeta_i` は $\zeta_{2^{h-t}}^i$ です

これを書き換えると以下のようになります．in-placeではなくなります

// @ FFT standard

# 検証

* [C - 高速フーリエ変換 - AC](https://beta.atcoder.jp/contests/atc001/submissions/3377830){:target="_blank"}<!--_-->

# 練習問題

* [C - 高速フーリエ変換 - AC](https://beta.atcoder.jp/contests/atc001/tasks/fft_c){:target="_blank"}<!--_-->
* [E - Couple - AC](https://beta.atcoder.jp/contests/ukuku09/tasks/ukuku09_e){:target="_blank"}<!--_-->
* [0025 - のえるちゃん選び - ねねじゃっじ](https://luzhiled.me/problems/25){:target="_blank"}<!--_-->

# 参考

* [FFT (高速フーリエ変換) - satanic0258.github.io](https://satanic0258.github.io/snippets/math/FFT.html){:target="_blank"}<!--_-->


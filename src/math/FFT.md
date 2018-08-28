---
title: 高速フーリエ変換(FFT)，数論変換(NTT)
---

Fast Fourier Transform; FFT
Number Theoretic Transform; NTT

多項式2つを高速にかけ合わせます．

多項式の高い方の次数を $N$ と置きます．

DFTのアルゴリズムの選び方（再帰 or 非再帰），  
どのようなものをつかって（なんて表現すればいいの），N乗するともとに戻るようなものを用意するか(1の原始根 or 1の原始根(は？))

どうせここでは説明しきらない．

# 複素数
再帰．最も基本的．
なんかzetaを計算するタイミングが悪いせい精度が死んだため`long double`にしている．  
そのうち書き直す．

// @ FFT with long double Library

# 整数

$ k = 2^nm + 1$ というもので， $ 2^n \gteq N$ であるような**素数** $k$ でのmoduloでFFTができる．  
掛け算でのオーバーフローも考えて，コード中にあるものはすべて $k \lteq 2^31$．

// @ NTT Library

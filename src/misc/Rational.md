---
title: 有理数ライブラリ (Rational)
---

整数 / 整数 の形で有理数を保持することで欠損なく値を保持できる．分数

# boost

// @ boost-rational

# 自作

別にboostに似せたりはしていない

// @ Rational Library

分母が必ず正になるように保持

各種比較・算術演算が可能

コンストラクタ : Rational(Integer numer = 0, Integer denom = 1)

一項演算 : `+`, `-`, 明示的な `(cast)`  
二項演算 : `+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=`  
右辺の対象は `Rational<Integer>` クラスか `Integer` にキャスト可能なもの  

分子取得: `.numer` or `.bunsi()`  
分母取得: `.denom` or `.bunbo()`  

約分 (正規化) : `.reduce()`  
`.numer` か `.denom` を自分で変更したときのみ

# 検証

* いくつかの演算子 [E - Game of +- (800) - AtCoder](https://beta.atcoder.jp/contests/code-festival-2018-qualb/submissions/3411192){:target="_blank"}<!--_-->


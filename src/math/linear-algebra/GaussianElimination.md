---
title: 連立一次方程式, 行列式 (ガウスの消去法)
---

Gaussian Elimination

ガウスの消去法 : 連立方程式を解くアルゴリズム

ガウス・ジョルダンの消去法 : 行基本変形を用いて行列を行階段形にすること．ガウスの消去法において後退代入を行わずに対角化を目指して直接解を求めること
 
# 行標準形

**一意に定まり**，算出方法に依存しない

ガウスの消去法で求めることができる

行簡約階段形とも

行階段形とは違って，主成分が1であるという条件，主成分がある列については，主成分以外は0であるといった条件がある

# ガウスの消去法

$N \times M$ 行列と サイズ $N$ のベクトルで表される方程式を解く

ガウス・ジョーダンの消去法をする

与えられた行列を破壊する (行標準形にする)．不定の場合はそれを自分でどうにかする

不能の場合はpairのsecondの値がfalseになる

// @ Gaussian Elimination

# 行列式

ガウスの消去法と同様に，行階段形を作ることを目標にして行列式を求める

// @ Matrix Determinant

# 行列のランク

ガウスの消去法と同様に，行階段形を目指す

少数に対して求めるのは現実的ではないので，整数は有理数に変換するなどしたほうがよさそう

// @ Matrix Rank

# 前進消去と後退代入

ガウスの消去法に置いて，前進消去は行階段形にするステップ，後退代入は値を後ろから代入していく

# 部分選択法と完全選択法

pivottingの方法で，部分選択はその列についてのみ見る，完全選択は右下の領域全てをみる

# 検証

* [Strange Couple - AOJ](http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3349472#1){:target="_blank"}<!--_-->

# 練習問題

* [Strange Couple - AOJ](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2171){:target="_blank"}<!--_-->
* [D - 数列 XOR (600) - AtCoder](https://beta.atcoder.jp/contests/bitflyer2018-final-open/tasks/bitflyer2018_final_d){:target="_blank"}<!--_-->

# 参考

* [ガウスの消去法 - Wikipedia](https://ja.wikipedia.org/wiki/ガウスの消去法){:target="_blank"}<!--_-->
* [行階段形 - Wikipedia](https://ja.wikipedia.org/wiki/行階段形){:target="_blank"}<!--_-->


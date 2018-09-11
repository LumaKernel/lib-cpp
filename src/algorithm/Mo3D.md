---
title: 時空間Mo (三次元Mo，Mo with Update)
---

時空間Moって名前が好き

三次元っていうのは，Left, Right, Timeの三軸．

[通常のMo]({{ "algorithm/Mo" | absolute_url }})に加え，更新をする．

計算量は $O(N^{5/3})$ なので，いつでも使えるというわけではないが，強い．

バケットのサイズを $B$ とおくと，

* 左端Leftが動く回数は $O(QB)$，
* 右端Rightが動く回数は $O(QB + \frac{N^2}{B})$
* Timeが動く回数は $O(\frac{N^3}{B^2})$

$N = Q$ と仮定すると， $B=N^{2/3}$ とすることで上記の $O(N^{5/3})$ が得られます．

詳細・図解が[うしさんの解説記事](https://ei1333.hateblo.jp/entry/2017/09/11/211011){:target="_blank"}<!--_-->に詳しく書いてあるので見てみてください…

Moに加えて，変数 $time$ を，$[0, time]$ を処理済みとして保持します．

# 実装

// @ Mo3D Library

# 検証

* [F - Machine Learning - CF](https://codeforces.com/contest/940/submission/42752956){:target="_blank"}<!--_-->

# 練習

* [F - Machine Learning - CF](https://codeforces.com/contest/940/problem/F){:target="_blank"}<!--_-->

# 参考

* [Mo's algorithm - ei1333の日記](https://ei1333.hateblo.jp/entry/2017/09/11/211011){:target="_blank"}<!--_-->

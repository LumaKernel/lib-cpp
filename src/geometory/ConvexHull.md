---
title: 凸包 (Graham Scan, Andrew Scan)
---

二次元平面上の $N$ この点が与えられたときの，凸包 (を成す頂点) を $O(N \log N)$ で求めます

凸法とは，与えられた点に釘をうって，輪ゴムをかけたような図形のことです

(x, y)辞書順最小を原点とし，角度 = 傾き でソートして，ccwで調整

キャリパー法は上記リンク先にあります

格子点にのみ点がある時，座標の幅を $M$ とすると凸包の頂点数は $O(\sqrt{M})$ 個 (TODO : なにかしらの証明のリンク

あと，Graham ScanとAndrew Scanの違いはというと，角度ソートか座標ソートかの違いのようです [Graham scan - Wikipedia(en)](https://en.wikipedia.org/wiki/Graham_scan){:target="_blank"}<!--_-->

凸包が右・左から見えるかどうかによって「右側チェイン」「左側チェイン」と言ったりします (上下で分けることもできます)

[三次元凸包はここ]({{ "geometory/ConvexHull3D" | absolute_url }})

### 凸包構築の一般的なアルゴリズムついて

任意のケースに対する最良実行時間は$\Omega(N \log N)$で，漸近的に最速なアルゴリズムは $O(N \log H)$，$H$ は結果の凸包の頂点数

# 実装

[幾何基本ライブラリ]({{ "geometory/geometory" | absolute_url }})が必要

$O(N \log N)$

同一直線上にある場合は結構適当になっているので，そのような場合はAndrewScanのほうがいいかもしれない

// @ Graham Scan Library

## $O(N^2)$で構築する方法

全頂点について，他の頂点を偏角でソートして，隣り合う２つの点への角度が$\pi$を超えるかどうかで，「凸包上の点かどうか」が判定できます

# 検証

* [村の道路計画 (PCK) - AOJ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/12/0342/judge/2473617/C++){:target="_blank"}<!--_-->
  * まるで検証しているようで，その場で書いたコードなので検証になっていない
* [B - Holes (600) - AtCoder](https://beta.atcoder.jp/contests/agc021/submissions/2145093){:target="_blank"}
  * この問題は $O(N^2)$ でもよい

# 参考

* 蟻本
* アルゴリズム・イントロダクション


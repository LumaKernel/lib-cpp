---
title: Convex Hull Trick (動的も)
---

直線の集合 $L = \{f_i(x) = a_i x + b_i\}$ に，  
直線 $f(x) = ax + b$ を追加するクエリ(add)と，  
$x$ に対して，最小値を取るような直線に対するその最小値を返すクエリ(query)，  
これらをそれぞれ高速に求めることができます．

addが単調か，queryが単調か，によってざっくり3パターンありますが，  
それを2つにわけています．

参考も見てください．

DPのoptimizationにもつかえるらしい(要勉強)

# 通常

直線の数を$N$，クエリの数を$Q$ とする．

add( $f(x) = ax + b$ )のaが狭義単調減少であることを前提．  
直線の追加は全体で $O(N)$

addし終わってからqueryを行う(static)

queryはxが単調増加かどうかによってかわってくる.  
(広義)単調増加なら全体 $O(N + Q)$ で，  
そうでないなら一回 $O(log N)$ で可能

* コンストラクタ CHT(bool increasing, Compare comp?)
  * increasing : queryが単調増加かどうか
  * comp : 最大値クエリなら `[](ll a, ll b){return a >= b;}`
* add(a, b)
  * $f(x) = ax + b$を追加する

最大値クエリはマイナスにするとかのほうがよさそう．

// @ Convex Hull Trick Library

## 検証

https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/2171456

# 動的

[http://d.hatena.ne.jp/sune2/20140310/1394440369](http://d.hatena.ne.jp/sune2/20140310/1394440369){:target="_blank"} にあるものをそのまま

とりあえず動くからそのまま，そのうち整理する．

// @ Dynamic Convex Hull Trick Library

## 検証

したけどどっかいった

# 参考

* [Convex-Hull Trick \| SATANIC++](http://satanic0258.hatenablog.com/entry/2016/08/16/181331){:target="_blank"}
  * 最強解説


---
title: 単調なクエリに対するCHT
---

直線の集合 $L = \\{f_i(x) = a_i x + b_i\\}$ に対し，以下のクエリを高速に行えます
* add(a, b) : 直線 $f(x) = ax + b$ を追加するクエリ
* query(x) : $x$ に対して，最小値を取るような直線に対するその最小値を返すクエリ
  * $\displaystyle\min\_{f\in L}{f(x)}$

DPを高速化するのに使ったりする (ページ下部の参考も参照してください)

直線の数を$N$，クエリの数を$Q$ とする

# 実装

使い方はコードの下．オンラインクエリ可能

// @ Convex Hull Trick

* `CHT<bool a-increasing, class T, int x-type = 0, bool is-minimize = true, class D = T>`
  * `x-type` : クエリ (`get`, `query`) に渡す `x` が
    * 広義単調増加なら `+1`
    * 広義単調減少なら `-1`
    * それ以外なら `0`
    * を指定する
  * 最大化は `is-minimize` に `false` を指定する
* `add(a, b [, id])` : ならし $O(1)$
  * `f(x) = ax + b` を追加する
  * aは広義単調増加，もしくは広義単調減少で追加する (`a-increasing` で指定する)
  * `b` は自由
  * 違反すると `assert` に引っかかる
  * この順序を任意の順で行うこともできる ([追加順序任意のCHT]({{ "dynamic-programming/convex-hull-trick/CHT-Ex" | absolute_url }}))
* `get(x) : Line(a, b)`
  * 単調 (`x-type = +1, -1`) なら 全体 $O(N + Q)$. 違反すると `assert` に引っかかる
  * そうでないなら (`x-type = 0`) 1回 $O(\log N)$
  * `x` を代入したときの値が最小 (最大) となる直線を返す
* `query(x)` : getと同様の計算量
  * `x` での最小 (最大) 値
* overflowを防ぐために `D = double` のようにすることができます
  * a * 

# メモ

### 直線が不必要な条件

$\displaystyle-\frac{b_3-b_2}{a_3-a_2} \leq -\frac{b_2-b_1}{a_2-a_1}$

について，最小化なら $a_3 \gt a_2 \gt a_1$ という条件が成り立っているので，
最小・最大化どちらでも $(a_3-a_2)(a_2-a_1) \gt 0$ となり，

$(b_3-b_2)(a_2-a_1) \geq (b_2-b_1)(a_3-a_2)$ へ一意に変形できる

### x-type = +-1の時

`a` が単調増加か単調減少かによらずCHTを行うことができる

内部で`head`が昇順なのか降順なのかを `headIncreasing` で保持している (`cout << cht;` などでも確認できる)

降順の場合は `pop_back` が行われたときに `head--` するのを忘れないように

`bool headIncreasing` の求め方については全8パターンの表を書くとわかります

# EPSについて

`(aの正の最小値)(bの正の最小値)` より小さな正の値を採用するといい

たとえばデフォルトでは `1e-19` になっているが，これは両方が小数9桁ずつを想定している

# overflow対策

TLに余裕がある場合は [多倍長整数]({{ "misc/BigInteger" | absolute_url }})，

`4(aの絶対値の最大値)(bの絶対値の最大値)` が `T` でoverflowする場合は対策が必要

TLが厳しい場合はテンプレートの `D` に `double` などの浮動小数点数を入れて掛け算するときだけ `double` で計算するというものです

# 検証

* [C - スペースエクスプローラー高橋君 - AtCoder](https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/2171456){:target="_blank"}<!--_-->
  * このときの実装は少々バグがあります
* [D - Computer Game - codeforces](https://codeforces.com/contest/1067/submission/45446448){:target="_blank"}<!--_-->
* [C - Kalila and Dimna in the Logging Industry - codeforces](https://codeforces.com/contest/319/submission/48890326){:target="_blank"}<!--_-->
  * overflow対策で `D = double` としています
* [ARC066 F - Contest with Drinks Hard (1400) - AtCoder](https://atcoder.jp/contests/arc066/submissions/4253139){:target="_blank"}<!--_-->
  * a昇順, 最大化, x昇順 (headが降順)

# 参考

* [Convex-Hull Trick - SATANIC++](http://satanic0258.hatenablog.com/entry/2016/08/16/181331){:target="_blank"}<!--_-->
* [Dynamic Programming Optimizations - codeforcesの記事](https://codeforces.com/blog/entry/8219){:target="_blank"}<!--_-->


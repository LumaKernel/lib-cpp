---
title: Convex Hull Trick; CHT
---

直線の集合 $L = \{f_i(x) = a_i x + b_i\}$ に対し，以下のクエリを高速に行えます
* add(a, b) : 直線 $f(x) = ax + b$ を追加するクエリ
* query(x) : $x$ に対して，最小値を取るような直線に対するその最小値を返すクエリ ($\min{f(x)|f\in L}$)

DPにも使える (ページ下部の参考も参照してください)

直線の数を$N$，クエリの数を$Q$ とする

# 通常

使い方はコードの下．オンラインクエリ可能

// @ Convex Hull Trick Library

* `CHT<T, bool xIncreasing, Comp>`
  * `xIncreasing` : クエリ (get, query) の `x` が広義単調増加かどうか
  * デフォルトで最小値．`Comp = greater<T>` とすれば最大値
* `add(a, b)` : ならし $O(1)$
  * `f(x) = ax + b` を追加する
  * 最小化 : `a` の広義降順，`b` は自由
  * 最大化 : `a` の広義昇順，`b` は自由
  * 違反すると `assert` に引っかかる
  * この順序を任意の順で行うこともできる ([#追加順序任意のCHT](#追加順序任意のCHT))
* `get(x) : (a, b)`
  * 単調 (x-increasing) なら 全体 $O(N + Q)$．そうでないなら 1回 $O(\log N)$
  * `x` を代入したときの値が最小 (最大) となる直線を `(a, b)` の形で返す
* `query(x)` : getと同様の計算量
  * `x` での最小 (最大) 値

## 検証

* [C - スペースエクスプローラー高橋君 - AtCoder](https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/2171456){:target="_blank"}<!--_-->
  * このときの実装は少々バグがあります
* [D - Computer Game - Codeforces](https://codeforces.com/contest/1067/submission/45446448){:target="_blank"}<!--_-->

# 追加順序任意のCHT

Dynamic CHT; DCHT と呼ぶことにしておく．こいつが動的CHTなのか削除可能なものがそうなのか，よくわかっていない

オンラインクエリ可能

[http://d.hatena.ne.jp/sune2/20140310/1394440369](http://d.hatena.ne.jp/sune2/20140310/1394440369){:target="_blank"}<!--_--> にあるものに手を加えたもの

// @ Dynamic Convex Hull Trick Library

インターフェースは通常と同じ

* $k$ を採用された直線の数とすると
* `add` : $O(\log k)$
* `get` : $O(\log k)$

## 検証

* [D - Computer Game - Codeforces](https://codeforces.com/contest/1067/submission/45442782){:target="_blank"}<!--_-->

# 削除可能なConvexHullTrick

TODO : 理解

* [yosupoさんの記事](http://yosupo.hatenablog.com/entry/2015/12/02/235855){:target="_blank"}<!--_-->

---

通常のCHTが既に動的なのでね，動的CHTってなんだろうね

sort + CHTよりDCHTのほうが漸近的に速いが，sort + CHTのほうがちょっと速いかなと言う感じ

# 自分用のメモ

直線が不必要な条件

$-\frac{b_3-b_2}{a_3-a_2} \leq -\frac{b_2-b_1}{a_2-a_1}$

について，最小化なら $a_3 \gt a_2 \gt a_1$ という条件が成り立っているので，
最小・最大化どちらでも $(a_3-a_2)(a_2-a_1) \gt 0$ となり，

$(b_3-b_2)(a_2-a_1) \geq (b_2-b_1)(a_3-a_2)$ へ一意に変形できる

# EPSについて

`(aの正の最小値)(bの正の最小値)` より小さな正の値を採用するといい

たとえばデフォルトでは `1e-19` になっているが，両方が小数9桁ずつを想定

# 参考

* [Convex-Hull Trick - SATANIC++](http://satanic0258.hatenablog.com/entry/2016/08/16/181331){:target="_blank"<!--_-->
* [Dynamic Programming Optimizations - Codeforcesの記事](https://codeforces.com/blog/entry/8219){:target="_blank"}<!--_-->


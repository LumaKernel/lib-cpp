---
title: QI性を利用したDP高速化
---

文献 [^1] が全てです．そのうち詳しい解説を書くかもしれません

Convex/Concave QI Speedupという名前は適当につけました


$$
D(i) = g\left(\min_{0 \leq j \lt i}\{D(j) + w(j, i)\}\right)
$$

$D(0)$は分かっているとし，$D(N)$が求めたい (引数は全て整数です)

というDPを考えます．$g$は任意の関数で，何でもいいです (時間がかからなければ)
<!--_-->

愚直にやると$O(N^2)$ですが，$w$が [Concave Quadrangle Inequality]({{ "math/Monge#monge" | absolute_url }}) か [Convex Quadrangle Inequality]({{ "math/Monge#convex-qi" | absolute_url }}) を満たす時，これは$O(N \log N)$で求められます

$\min$ではなく$\max$という場合でも，$$w'(j, i)=-w(j, i)$$を考えることにより ($w$がConvex QIなら$$w'$$はConcave QIといった具合に) 計算することができます

# メモ

そのうち書くかもしれない解説のためのメモ

$w$がConvex QIとする

$C(j, i) = f(j) + w(j, i)$ は 「$i$ から $j$ を採用したときの損」と考える．損を最小化するのが目的

$l \lt k$ について $f(r) = C(l, r) - C(k, r)$ とは 「$k$ではなく$l$を選んだときの損」であり，これはConvex QIから (広義) 単調減少であることが分かる

つまり，「大きい方 ( = $k$) を採用する得はだんだん小さくなる」といえる

ここで，「大きい方はいつから採用することで得するか」に二分探索で答えられる

あとはstackやdequeを用いることで，これらが「いい性質」を保持し続けるように管理すればよい


# 実装

// @ Convex QI Speedup

// @ Concave QI ( = Monge ) Speedup

# 検証

* [No.705 ゴミ拾い Hard - yukicoder(submission)](https://yukicoder.me/submissions/312784){:target="_blank"}<!--_-->


# 練習問題

* [No.705 ゴミ拾い Hard - yukicoder](https://yukicoder.me/problems/no/705){:target="_blank"}<!--_-->

# 参考

[^1]: [Speeding up dynamic programming with applications to molecular biology](https://www.sciencedirect.com/science/article/pii/0304397589901011){:target="_blank"}<!--_-->


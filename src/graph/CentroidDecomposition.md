---
title: 重心分解 (Centroid Decomposition)
---

# キーワード

* ある点を始点とするパスのなかで 最適なものを答えよ / 条件をみたすものを数え上げよ
* ある条件を満たすパスを数え上げよ

# メモ

始点指定なしのものはすべての点を始点とするクエリに置き換えることで **始点指定あり** に帰着できる (この帰着は必ずしも必要とは限らない)

重心を選択，排除を繰り返すことにより同じサイズの (有向) 木 (**重心木** と呼ぶことにする) が出来上がる

重心木は高さが $O(\log N)$ となる

また，各頂点$v$についてその頂点を重心とするような部分木を $v$**が支配する部分木** と呼ぶことにする

すべての頂点について，その頂点が支配する部分木を探索すると $O(N \log N)$ となる

以下，重心木を top-down に処理するか bottom-up に処理するかで何が変わるかのメモ

### top-downに処理する

DFSすればよい

各頂点，子 ([実装](#実装) の `.child[v]`) を探索する前にその頂点をdeadにしてから潜ると良い

分割統治や，予めそこを始点とするクエリを集めておく (オフラインクエリ) ことによって求められる

### bottom-upに処理する

各頂点について親 ([実装](#実装) の `.par[v]`) へとたどっていけばいい

以前いた頂点を含む部分木について省かなかればいけない場合は気をつける (数え上げなど; [検証](#検証) の "木の問題" を参照)

ダブリングなどを用いて二点間の距離を計算すると，オンラインでクエリを処理できる

# 実装

// @ Centroid Decomposition

# 検証

すべて bottom-up に書いている

* [#199 div2 E - Xenia and Tree - codefroces](https://codeforces.com/contest/342/submission/50313110){:target="_blank"}<!--_-->
* [みんプロ2018 決勝 C - 木の問題 (1200) - AtCoder](https://atcoder.jp/contests/yahoo-procon2018-final-open/submissions/4349163){:target="_blank"}<!--_-->

# 練習問題

* [#199 div2 E - Xenia and Tree - codefroces](https://codeforces.com/contest/342/problem/E){:target="_blank"}<!--_-->
* [#190 div1 C - Ciel the Commander - codeforces](https://codeforces.com/problemset/problem/321/C){:target="_blank"}<!--_-->
* [NIKKEI 2019本選 G - Greatest Journey (1200) - AtCoder](https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_g){:target="_blank"}<!--_-->
* [みんプロ2018 決勝 C - 木の問題 (1200) - AtCoder](https://atcoder.jp/contests/yahoo-procon2018-final-open/tasks/yahoo_procon2018_final_c){:target="_blank"}<!--_-->

# 参考

* [木の重心列挙アルゴリズム - Learning Algorithms](http://www.learning-algorithms.com/entry/2018/01/03/215559){:target="_blank"}<!--_-->
* [重心分解による分割統治法の一般形について - Learning Algorithms](http://www.learning-algorithms.com/entry/2018/01/20/031005){:target="_blank"}<!--_-->
* [ツリーの重心分解 (木の重心分解) の図解 - Qiita (@drken)](https://qiita.com/drken/items/4b4c3f1824339b090202){:target="_blank"}<!--_-->
* [木の重心分解(Centroid-Decomposition) - ei1333.github.io/luzhiled](https://ei1333.github.io/luzhiled/snippets/tree/centroid-decomposition.html){:target="_blank"}<!--_-->


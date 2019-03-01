---
title: HL分解 (Heavy-Light Decomposition)
---

木を**パスを頂点とする木**に分解します

新しい木は高さが $O(\log N)$ となります

頂点にデータを乗せて，パスクエリと部分木クエリをこなすことができます

パスクエリだけであれば順序 (親から子への**方向**) を保つことができます (すなわち [モノイド]({{ "math/Monoid" | absolute_url }}) を処理できるということ．遅延セグメントツリーを用いてパス更新も可能．[#練習問題](#練習問題) の [ネットワークの課金システム](https://onlinejudge.u-aizu.ac.jp/problems/0367){:target="_blank"}<!--_--> などがこの性質を使います)

副産物としてLCAなどを求めることができます

---

もし根付きでなければ適当に根を決める．全ての頂点からその子へと伸びる辺について，**一番部分木のサイズが大きい頂点へとつながる辺** を Heavy Edge, それ以外を Light Edge と呼びます

そうすると，根から順にLight Edgeをたどることは $O(\log N)$ 回しかできません．なぜなら，Light Edgeを選ぶと部分木のサイズが $1/2$ 以下になるからです

Heavy Edgeによるパスを考えます．これを一つの頂点と捉え，Light Edgeが新たな辺として木を成していると捉えることができます

Heavy Edgeの処理は Euler Tour と同様にして [セグメントツリー]({{ "data-structure/SegmentTree/SegmentTree" | absolute_url }}) などを用いればよいです

# ダブリングと比べて

||HLD with 遅延セグ木|[ダブリング]({{ "graph/DoublingTree" | absolute_url }})|
|---|---|---|---|
|クエリあたり時間計算量|$O(\log ^ 2 N)$|$O(\log N)$|
|メモリ|$O(N)$|$O(N \log N)$|
|区間更新|**できる**|できない|
|点更新|**できる**|できない|

# 実装

// @ HL-Decomposition Library

# 検証

* [PCK 2017 pre 12 ネットワークの課金システム - AOJ](https://onlinejudge.u-aizu.ac.jp/solutions/problem/0367/review/3114389/luma/C++14){:target="_blank"}<!--_-->
* [No.235 めぐるはめぐる (5) - yukicoder](https://yukicoder.me/submissions/278941){:target="_blank"}<!--_-->

# 練習問題

* [PCK 2017 pre 12 ネットワークの課金システム - AOJ](https://onlinejudge.u-aizu.ac.jp/problems/0367){:target="_blank"}<!--_-->
* [No.235 めぐるはめぐる (5) - yukicoder](https://yukicoder.me/problems/no/235){:target="_blank"}<!--_-->


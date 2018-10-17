---
title: 三次元凸包
---

# 使い方

[幾何基本ライブラリ]({{ "geometory/geometory" | absolute_url }}) と [三次元幾何ライブラリ]({{ "geometory/geometory3D" | absolute_url }}) が必要

与えられた点に対して，凸包をなす頂点集合を求める．ついでに副産物を色々求める

与えられる点は，4つ以上の点で，同一平面上ではないことが条件

すべての面が三角形になるように保持・計算する

同一平面上の点については表面であれば通常通り三角形を形成し，内部であれば内部であると判定される

同じ点については自分で，`unique` すること

`insert(a, b, c)` で点を追加  
`build(a, b, c)` で凸包を構築  

`vertexSize(), edgeSize(), faceSize()` で各種サイズ取得  
`vector< int > getVertexIds()` で凸包の頂点のid集合を取得．もとの頂点番号と対応していることを保証しません  
`valarray< Scalar > getVertex(int id) const` でidに対応する頂点取得  
`vector< array< int, 3 > > getPolygons() const` で凸包を構成する，頂点のid3つからなるポリゴン全取得  
`array< int, 3 > getPolygon(int id) const` ポリゴンIDからポリゴンを取得  
`array< valarray< Scalar >, 3 > getPolygonPoints(int id) const` ポリゴンIDから頂点をそのまま取得  
`valarray< Scalar > getPolygonOuterNormalVector(int id) const` ポリゴンIDから，そのポリゴン面と垂直で，サイズがその面の面積の二倍の外側向きのベクトルを取得


入力が整数であれば，すべて整数の範囲で計算可能

# 実装

// @ Convex Hull 3D

参考にしたスライドの通り実装しようとしたが，`set`や`map`でlogがついてたり，なんか細かいやり方については書かれていなかったのでなるべく計算量が小さくなるように書いたつもり

各座標成分 $[-10^5,10^5]$ でランダムに生成した入力をよませてみると，$10^5$ 個のとき4秒ぐらい，$10^4$個のとき0.3秒ぐらいと， $\Omega(N^2)$ よりは明らかに速い結果が得られたので良しとした (両ケースとも凸包を成す頂点数は150程度だった)．改良については詳細が分かったらまたするかもしれない

最悪ケースに対しては，これもちょっとよく分かっていないが，$O(N^3)$ ぐらいだと信じている

# 応用

* もとの頂点の番号が知りたい : swapは2回しか無いのでそれを保持しとく

# 検証

* [L - 凸包が映し出される平面 (KUPC2018) - AtCoder](https://beta.atcoder.jp/contests/kupc2018/submissions/3420739){:target="_blank"}<!--_-->
  * コメントを日本語で書いているのでこっちの方がわかりやすいかもしれない

# 参考

* [3次元の凸包を求める - SlideShare](https://www.slideshare.net/abc3141/3-65377198){:target="_blank"}<!--_-->

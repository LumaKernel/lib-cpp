---
title: 幾何基本
---

# 使い方

## 定数

* EPS : イプシロン．誤差がどこまでか

## クラス

* Scalar : スカラー
* Point(Scalar, Scalar) : 点，ベクトルとしても使う
* Circle(Point, Scalar radius) : 円
* Line(Point, Point) : 直線
* Segment(Point, Point) : 線分
  * 交点求めるときの端点の扱いなどに注意
* Polygon : 多角形，vector\<Point>，ccwである必要があったりなかったり

## 関数

### 色々

* sign(Scalar) : EPS考慮のsign
* ccw(Point a, Point b, Point c) : 三点の並び方，コメントのメモを参照
* normalize(Point) : 正規化．そのベクトルの方向の単位ベクトル
* normal(Point) : 法線ベクトル
* arg(Point a, Point b) : [0, PI]の範囲で2つのベクトルの角度を返す
* arg(Scalar a, Scalar b, Scalar c) : 三角形の長さから角度Aを返す
* area3(Point a, Point b) : 三角形の面積
* area3(Scalar a, Scalar b, Scalar c) : 三角形の三辺の長さから三角形の面積
* dist(~, ~) : 距離
* isCrossing(Segment, Segment) : 2つの線分が交差しているか
* intersection(Line, Line) : 直線の交点

### 円

* cpr(Circle, Circle) : 円と円の関係，コメントのメモを参照
* intersections(Circle, Circle)
* intersections(Circle, Line)
* area(Circle) : 円の面積
* ajacentLine(Circle, Point) : 円周上のある点を通る接線
* tangentLines(Circle, Point) : 円の外のある点を通る接線
* commonTangentLines(Circle, Circle) : 円と円の共通接線

### 多角形

* area(Polygon) : 面積
* inside(Polygon, Point) : ある点が多角形の内部にあるかどうか
  * 0 : 外側にある
  * 1 : 内側にある
  * -1 : 多角形の頂点上にある
  * -2 : 多角形の辺上にある
* caliper(Polygon ccwConvex) : 最遠点対を求めその距離を返す
  * ccwConvexはGrahamScanで生成されるようなccw順で凸包であるようなもの

HCPCのスライド[kika1](https://www.slideshare.net/hcpc_hokudai/kika-80076550){:target="_blank"},[kika2](https://www.slideshare.net/hcpc_hokudai/kika2-80076551){:target="_blank"},[kika3](https://www.slideshare.net/hcpc_hokudai/kika3-80076552){:target="_blank"}を見ながら大体計算しながら作ったが，間違っている可能性はあるので注意．
スライドにも間違い(たぶん)があったりしたので注意．  

// @ Geometory Library
// @ Geometory Circle Library
// @ Geometory Polygon Library

---
title: Rollback可能なデータ構造とクエリ平方分割（Moの上位互換）
---

参考: [Mo's algorithm の上位互換の話 - あなたは嘘つきですかと聞かれたら「YES」と答えるブログ](http://snuke.hatenablog.com/entry/2016/07/01/000000){:target="_blank"}<!--_-->

基本的なアイデアはMoと似ていて，  
ある瞬間を記録するsnapshotと，  
記録した状態に戻すrollbackを定義できればいいです．

追加操作は残りますが，削除操作は必要なくなります．

追加操作の計算量は均しが $O(1)$ とかだとしても，  
ある瞬間に $O(N)$ とかかかる場合，その瞬間を何回も繰り返されると死にます．

Rollback可能なことを永続というかちょっとわからないんですが，wikipedia見る限りではちょっと違うなと思いました．(過去の任意の時間のものを参照できるというのが必要そう)

# 実装

区間はすべて $[l, r)$ (半開区間) です
<!--]-->

MoのCFでの記事の[コメント](https://codeforces.com/blog/entry/7383?#comment-161520){:target="_blank"}<!--_-->を参考に書いてみました．

// @ Mo with Persistent Data Structure Library

## UnionFindを使う例

検証にもあります

// @ MoEx UF example

# 検証

* [A - Nasta Rabbara - CF](https://codeforces.com/gym/100513/submission/42741944){:target="_blank"}<!--_-->
  * rollback可能なUFを使います
  * みんな5000ms前後かなーという印象ですがなんか200msとかいうヤバも見えます

# 練習

* [A - Nasta Rabbara - CF](https://codeforces.com/gym/100513/problem/A){:target="_blank"}<!--_-->


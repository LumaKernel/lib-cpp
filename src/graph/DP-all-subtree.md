---
title: 全方位木DP (るま式)
---

基本アイデアの説明は端折ります．（そのうち書くかもね）

従来の全方位木DPを簡潔に，書きやすくした全方位木DPをつくり，  
なんとなく**るま式**と名付けましたが，解説記事を書いてる途中でめんどくさくなったため，  
解説の無いコードがただ残るのみです

ところで全方位木DPという名前，嫌いではないのですが，全部分木DP，とかのほうがしっくりします．（英語圏では何ていうでしょう）

# るま式全方木DP特徴

* DFS一個（一回とは言っていない）
  * 大抵は2個以上のDFSを使うと思いますが，一個で足ります
* ずっしりした問題にも使える
* DPテーブル最低限（最低1個）
* 場合分けがいらない（N = 1, 2の場合分けがいらない）
* 実装時の思考がスッキリ
* 森にも対応できる

# 基本

// @ all tree dp - type luma

# 高速化

準備中

`map` を `vector` に変えるだけです

# 検証

* [D - Driving on a Tree (800) - AC](https://beta.atcoder.jp/contests/s8pc-4/submissions/3232753){:target="_blank"}<!--_-->
  * 簡単です．全方位木DPの基本だと思います
* [F - Monochrome Cat () - AC](https://beta.atcoder.jp/contests/arc097/submissions/3233286){:target="_blank"}<!--_-->
  * 僕が思う，「ずっしりした問題」です
  * 使わない部分木があったり，計算途中を引き継いだりといったことが，  
るま式ではスッキリ書けます
  * 全方位木DP使わなくても解けるためなんか短いコードが結構ありますね
* [F - Distance Sums (900) - AC](https://beta.atcoder.jp/contests/arc103/submissions/3305207){:target="_blank"}<!--_-->


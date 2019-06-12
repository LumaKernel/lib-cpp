---
titile: 線形代数
---

線形代数とは, 線形空間と線形変換を中心とした理論を研究する代数学のいち分野である. (引用: Wikipedia)


競技プログラミングでは, 行列累乗から, 回転行列, 線形方程式, ランク, グラフとの関係, 諸公式 などが広く出題されている. 


# おすすめ参考資料

## Web

* [線形代数Ｉ - 武内修＠筑波大](https://dora.bk.tsukuba.ac.jp/~takeuchi/?%E7%B7%9A%E5%BD%A2%E4%BB%A3%E6%95%B0%EF%BC%A9){:target="_blank"}<!--_-->
  * ここをベースとして, 他のサイトを参考にしながら進めると良い
* [線形代数 - 理数アラカルト](https://risalc.info/#la){:target="_blank"}<!--_-->


## Wikipedia

辞書程度. 新しい言葉を知ったら都度調べて, 線形代数の深淵をちら見するやつをしている.

* [計量ベクトル空間](https://ja.wikipedia.org/wiki/%E8%A8%88%E9%87%8F%E3%83%99%E3%82%AF%E3%83%88%E3%83%AB%E7%A9%BA%E9%96%93){:target="_blank"}<!--_-->
* [距離函数](https://ja.wikipedia.org/wiki/%E8%B7%9D%E9%9B%A2%E5%87%BD%E6%95%B0){:target="_blank"}<!--_-->
* [ノルム線型空間](https://ja.wikipedia.org/wiki/%E3%83%8E%E3%83%AB%E3%83%A0%E7%B7%9A%E5%9E%8B%E7%A9%BA%E9%96%93){:target="_blank"}<!--_-->


# 行標準形の一意性

検索して探してもそんなに見つからない

* [PDF: 簡約行列の一意性](http://www.yyyamada.e-one.uec.ac.jp/Lecture/Slide/SLin1_Kuniq.pdf){:target="_blank"}<!--_-->
  * 具体例で示されており, 一般化する一歩手前まで書かれている. わかりやすい.
  * 一意性を証明する, よくある, ２つあると仮定したら一致する, という証明.
* [簡約化された行列の満たす諸性質#簡約化された行列は唯一つ - 理数アラカルト](https://risalc.info/src/reduced-row-echelon-form-properties.html#uni){:target="_blank"}<!--_-->
  * 見つからないと思ったらすごくわかりやすいのがあった
* [PDF: 線形代数](http://www.math.okayama-u.ac.jp/~hashimoto/paper/class/linear.pdf){:target="_blank"}<!--_-->
  * 帰納法で一意性と存在性を証明している


余談

ランクの定義とかを厳密に見ていくときに, 循環論法になってないか, とかも気をつけながら勉強していくといいと思う. 多分, 線形独立な列数で定義するのがいいと思うんだけど, 順序の関係上, 線形独立はあとに出てくる. (同値であるという証明で橋渡ししてあげるのがいいのかな)



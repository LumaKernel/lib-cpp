---
title: 動的セグメントツリー
---

座圧して通常のセグ木で処理する，といったことをする必要なくオンラインでクエリを処理できる．その分定数が重い

# 実装

範囲を与えないこともできるが，与えたほうが速い

初期値を与えると一回あたりのクエリにかかる時間が $O(\log^2 N)$ になるので注意が必要

* 範囲を与えた場合
  * その範囲内は初期値で埋まっていることに，
  * その範囲外は単位元で埋まっていることになる
* 範囲を与えなかった場合
  * 全域が初期値で埋まっていることになる

初期値を得る関数を与えた場合その関数の実行時間を $f$ としたとき，クエリあたりに $O(f \log N)$ の時間がかかる

いずれの場合でも負のインデックスに対応している (overflowには注意)

// @ Dynamic SegmentTree

# 検証

* [みんぷろ2019 決勝 A D - Dangerous Hopscotch (900) - AtCoder](https://atcoder.jp/contests/yahoo-procon2019-final-open/tasks/yahoo_procon2019_final_d){:target="_blank"}<!--_-->
  * 初期値を与える - [submission (1843ms)](https://atcoder.jp/contests/yahoo-procon2019-final-open/submissions/4586571){:target="_blank"}<!--_-->
  * 初期値を与える + 範囲指定 - [submission (1604ms)](https://atcoder.jp/contests/yahoo-procon2019-final-open/submissions/4586699){:target="_blank"}<!--_-->
  * 初期値を得る関数を与える - [submission (4000ms TLE)](https://atcoder.jp/contests/yahoo-procon2019-final-open/submissions/4587351){:target="_blank"}<!--_-->
  * 初期値を得る関数を与える + 範囲指定 - [submission (4000ms TLE)](https://atcoder.jp/contests/yahoo-procon2019-final-open/submissions/4587361){:target="_blank"}<!--_-->
  * TLEの原因は問題特有のところもあると思う

# 練習問題

* [みんぷろ2019 決勝 A D - Dangerous Hopscotch (900) - AtCoder](https://atcoder.jp/contests/yahoo-procon2019-final-open/tasks/yahoo_procon2019_final_d){:target="_blank"}<!--_-->


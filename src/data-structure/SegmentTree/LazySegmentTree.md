---
title: 遅延セグメントツリー
---

# 実装

// @ LazySegmentTree

# そらで書くときのメモ

* 0-indexed, topdownでかく場合
* 子どもは 2 * k + 1, 2 * k + 2
* evalは入ったノードですぐ，必ず行う
  * 更新がないノードでもやる．上のノードが値を使うかもしれない
* restore系は順序を気をつける

# 練習問題

* [JAG夏 2018 Day2 I - ADD DIV MAX RESTORE - AtCoder](https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_i){:target="_blank"}<!--_-->

# 参考

* [データ構造と代数(後編)](https://tomcatowl.github.io/post/ds-and-alg-2/){:target="_blank"}<!--_-->
* [遅延評価セグメント木をソラで書きたいあなたに - hogecoder](https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_i){:target="_blank"}<!--_-->


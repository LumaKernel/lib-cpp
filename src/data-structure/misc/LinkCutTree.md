---
title: Link/Cut Tree
---

**森** (もしくは **根付き有向木 (Arborescence) の集合**) への更新とクエリを順不同で高速に

根の変更クエリ(evert)には乗せるモノイドに対する要求があり，その条件は平衡二分探索木がreverseで要求するものと同じ([モノイド]({{ "math/Monoid" | absolute_url }})を参照)

IOIで常勝できることはあまりにも有名

参考になるものを準備しています

TODO : 区間に対する更新に対し，leftを求めるの，ちょっとどうすればいいかわからないけど，やっている人がいるのでそのうち見てみようと思います

// @ LinkCutTree

# 検証

* RMQとRUQ - [AOJのなんか](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/DSL_2_F/judge/3092002/C++14){:target="_blank"}<!--_-->
  * 遅延セグ木でできることがevert付きでできる
* LCA - [AOJのなんか](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/GRL_5_C/judge/3092319/C++14){:target="_blank"}<!--_-->
* HL-Decomp(TLE) [E. The Number Games - CF](https://codeforces.com/contest/980/submission/41594330){:target="_blank"}<!--_-->
* HL-Decomp [PCKの問題 - AOJ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/0367/judge/3093506/C++14){:target="_blank"}<!--_-->
* 部分木サイズ，link/cut，部分木root [E - Black Cats Deployment - AtCoder](https://beta.atcoder.jp/contests/cf17-tournament-round3-open/submissions/3128272){:target="_blank"}<!--_-->
  * なんかいい感じのLCT向け問題を見つけてしまった (想定解ではない)
  * cutができて，サイズが分かるUnionFind的な扱いをする
  * evertがないとき，部分木のサイズを計算できる
  * (cutの後にlinkがあるとかは，部分木のサイズは対応が難しいかも)
  * 部分木のroot取得もある

# 練習

* [JOI春13-day4 - 3 - 宇宙船 (Spaceships) - AtCoder](https://beta.atcoder.jp/contests/joisc2013-day4/tasks/joisc2013_spaceships){:target="_blank"}<!--_-->
* [E - Black Cats Deployment - AtCoder](https://beta.atcoder.jp/contests/cf17-tournament-round3-open/tasks/asaporo2_e){:target="_blank"}<!--_-->

# 参照

* [プログラミングコンテストでのデータ構造 2 ～動的木編～ - SlideShare](https://www.slideshare.net/iwiwi/2-12188845){:target="_blank"}<!--_-->
* [Spaceships 解説 - SlideShare](https://www.slideshare.net/qnighy/2013-spaceships2){:target="_blank"}<!--_-->
  * SplayやLCTのポテンシャルを用いた計算量の評価と証明が書かれています


---
title: 凸包 (Graham Scan, Andrew Scan)
---

蟻本は左右に行って帰って，と走査しますが，  
ぼくはなんとなく角度でソートします．

一番左を捉えて原点とし，角度 = 傾き でソートして，ccwをたよりに調整します．

[幾何基本ライブラリ]({{ "geometory/geometory" | absolute_url }})が必要です．

なぜかキャリパー法が基本に入っててよくわかりません．（んぇ

蟻本には，座標値の幅が $M$ であるおうな凸多角形の頂点数は $O(\sqrt{M})$ 個しかない，とあるので押さえておいて損はないでしょう．（TODO : なにかしらの証明のリンク

あと，Graham ScanとAndrew Scanの違いはというと，角度ソートかx座標ソートかの違いのようです． [Graham scan \| Wikipedia(en)](https://en.wikipedia.org/wiki/Graham_scan){:target="_blank"}

// @ Graham Scan - Polar Sort - Library

# 検証

* [村の道路計画 \| PCK \| AOJ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/12/0342/judge/2473617/C++){:target="_blank"}
  * まるで検証しているようで，その場で書いたコードなので検証になっていない
* [B - Holes \| AC](https://beta.atcoder.jp/contests/agc021/submissions/2145093){:target="_blank"}
  * この問題はもっと低速な方法でいい



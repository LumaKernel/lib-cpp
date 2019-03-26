---
title: s[0,i-1]の接頭辞と接尾辞が一致する最大の長さ (最長ボーダー, KMP法)
---

Knuth-Morris-Pratt法

s[0,i-1]の文字全部と全部は当然一致するので，**1文字以上少ないもの**のみ考慮．

KMPのKはKnuthのKだけど，  
これがあることによって均し計算量は変わらないけど一回あたりの計算量（なんとなく瞬間最悪計算量とよんでいる）が落ちるらしく，それを使う問題があるらしい（らしい

# MP

// @ mp

# KMP

// @ kmp

# 最小周期

**何文字ごとに同じ文字列が現れるか**\[文字/回]

"abababa" であれば "ab" "ab" "ab" "a" で最小単位は "ab" なので最小周期は 2 = "ab".length  

注意点

* 4や6は最小ではない．
* 最後は "a" で終わっているがokとなる (問題によって扱いが変わる)
* frequency\[回/文字]とごっちゃにならないように (物理感)

KMPを用いて各iについてs[0,i]の最小周期がわかる．

最小周期 = 何文字ずらしたら初めて自分自身と一致するか

[k文字ずらものがもとの文字列と一致するようなhogehogeというのがKMPっぽいらしい](http://snuke.hatenablog.com/entry/2015/04/05/184819)

// @ cycle

# 文字列検索

`a.find(b [, pos])` と同等のことを $O(N+M)$でできます

// @ findstr with KMP

# 検証

* MP/cycle - [F - 最良表現 - AtCoder](https://beta.atcoder.jp/contests/arc060/submissions/2179734){:target="_blank"}<!--_-->
* KMP/cycle - [F - 最良表現 - AtCoder](https://beta.atcoder.jp/contests/arc060/submissions/2213473){:target="_blank"}<!--_-->
* 文字列検索 - [D - Refactoring - codeforces](https://codeforces.com/contest/1055/submission/45542889){:target="_blank"}<!--_-->

# 練習問題

* [F - 最良表現 (900) - AtCoder](https://beta.atcoder.jp/contests/arc060/tasks/arc060_d){:target="_blank"}<!--_-->
* [D - Refactoring - codeforces](https://codeforces.com/contest/1055/problem/D){:target="_blank"}<!--_-->
* [#545 div1 B - Camp Schedule - codeforces](https://codeforces.com/contest/1137/problem/B){:target="_blank"}<!--_-->

* https://xmascontest2015.contest.atcoder.jp/tasks/xmascontest2015_d

# 参考

* [文字列の頭良い感じの線形アルゴリズムたち - あなたは嘘つきですかと聞かれたら「YES」と答えるブログ](http://snuke.hatenablog.com/entry/2014/12/01/235807){:target="_blank"}
* [KMPのK \| あなたは嘘つきですかと聞かれたら「YES」と答えるブログ](http://snuke.hatenablog.com/entry/2017/07/18/101026){:target="_blank"}<!--_-->
* [文字列の周期性判定 - あなたは嘘つきですかと聞かれたら「YES」と答えるブログ](http://snuke.hatenablog.com/entry/2015/04/05/184819){:target="_blank"}<!--_-->
* [アルゴリズムは女の子#1 - るまブログ](https://tomorinao.blogspot.com/2018/03/1_20.html){:target="_blank"}<!--_-->
  * なにこれ


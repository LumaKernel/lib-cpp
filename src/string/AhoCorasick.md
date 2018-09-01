---
title: 文字列検索 (Aho-Corasick法)
---

複数パターンを事前に用意するタイプの検索．


構築は 辞書の大きさ，各文字列の長さに対して線形．

検索は 検索する文字列に対しても，みつかったマッチングの数に対しても線形．

解説は [ここ](http://d.hatena.ne.jp/naoya/touch/20090405/aho_corasick){:target="_blank"} がとてもわかりやすいです．<!--_-->

問題によって要求されるものがかわってくるので，それに合わせていきます．

// @ AhoCorasick Library

# 検証

* [No.430 文字列検索 - yukicoder](https://yukicoder.me/submissions/281765){:target="blank"}<!--_-->
  * 貼(って少しいじ)るだけ
  * 修正し，いじる必要がないようにしました．いじってもいいです．
* [G： 検閲により置換 (Censored String) - AOJ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/2873/judge/3116720/C++14){:target="_blank"}<!--_-->
  * 問題に合わせて少し変える必要があります．
* [H - Separate String - AC](https://beta.atcoder.jp/contests/jag2017autumn/submissions/3107157)
  * この問題でいろいろもとの実装を見直しました．いい感じです．

# 参考

* [http://d.hatena.ne.jp/naoya/touch/20090405/aho_corasick](http://d.hatena.ne.jp/naoya/touch/20090405/aho_corasick){:target="_blank"}<!--_-->



---
title: 文字列検索 (Aho-Corasick法)
---

複数パターンを事前に用意するタイプの検索


構築は 辞書の大きさ，各文字列の長さに対して線形

検索は 検索する文字列に対しても，みつかったマッチングの数に対しても線形

解説は [ここ](http://d.hatena.ne.jp/naoya/touch/20090405/aho_corasick){:target="_blank"} がとてもわかりやすいです．<!--_-->

問題によって要求されるものがかわってくるので，それに合わせていきます

// @ AhoCorasick Library

MLが厳しい場合は自分で `delete` の行のコメントを取る

# 検証

* [No.430 文字列検索 - yukicoder](https://yukicoder.me/submissions/281765){:target="_blank"}<!--_-->
  * 貼 (って少しいじ) るだけ
  * ライブラリを修正し，いじる必要がないようにしました．いじってもいいです
* [G： 検閲により置換 (Censored String) - AOJ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/2873/judge/3116720/C++14){:target="_blank"}<!--_-->
  * 問題に合わせて少し変える必要があります．
* [H - Separate String - AtCoder](https://beta.atcoder.jp/contests/jag2017autumn/submissions/3107157){:target="_blank"}<!--_-->
  * この問題でいろいろもとの実装を見直しました

# 練習問題

* [No.430 文字列検索 - yukicoder](https://yukicoder.me/problems/no/430){:target="_blank"}<!--_-->
* [G： 検閲により置換 (Censored String) - AOJ](https://onlinejudge.u-aizu.ac.jp/problems/2873){:target="_blank"}<!--_-->
* [H - Separate String - AtCoder](https://beta.atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_h){:target="_blank"}

# 参考

* [Aho Corasick 法 - naoyaのはてなダイアリー](http://d.hatena.ne.jp/naoya/touch/20090405/aho_corasick){:target="_blank"}<!--_-->



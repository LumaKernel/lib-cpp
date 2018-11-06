---
title: ゲーム問題まとめ
---

# Misere Nim

勝敗反転Nim (参考 : [Nim - sigma425のブログ](http://sigma425.hatenablog.com/entry/2014/12/07/132702){:target="_blank"}<!--_-->)

* すべての山が1個なら，山が奇数個のときlosing
* そうでないなら通常のNim同様，xorが0ならlosing

上の状態だった場合は明らかである

下の状態から上の状態に綺麗に推移できることを説明する

初期状態が下の状態でwinningだったひとに，Nimの戦略を続けたまま「山が石1個で山の個数が2k+1個」というlosingで手番が渡ったとする

このとき，一個前 (相手番) は「石1個山2k+1個と石a(>1)個山」か「石1個山2k+2個」となる

Nimの戦略で回ってきたのでxorが0なので後者である

さらにその一個前 (自分手番) は「石1個山2k+3個」か「石1個山2k+2個と石a(>1)個山」となる

前者の場合は同様の議論を繰り返す．「初期状態が下の状態」という条件からいつかは後者の状況になっているということになる

このとき，a個ではなく(a-1)個取ればwinningである

---

最終的に戦略としては「自明な場合ははい」「石a_i(>1)個の山が1つだけならa個か(a-1)個とるか考える」「あとはNimの戦略でやる」となる

```cpp
// winning : true
template<class T>
bool misereNim(const vector<T>& a) {
  T x = 0, y = 1;
  for(T &e : a) x ^= e, y &= e == 1;
  return x ^ y;
}
```

# 練習問題

ゲーム問題まとめ

* [KUPC2018 - J - ニム?](https://beta.atcoder.jp/contests/kupc2018/tasks/kupc2018_j){:target="_blank"}<!--_-->
  * [解説](https://tomorinao.blogspot.com/2018/10/kupc2018-j.html){:target="_blank"}<!--_-->
* [E - Prefix-free Game (700) - AtCoder](https://beta.atcoder.jp/contests/arc087/submissions/1883596){:target="_blank"}<!--_-->
* [HR - Misère Nim](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/misere-nim/problem){:target="_blank"}<!--_-->


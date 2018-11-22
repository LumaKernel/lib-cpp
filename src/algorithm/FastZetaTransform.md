---
title: 高速ゼータ変換, 高速メビウス変換
---

添字は二進法で捉え，集合として扱う

入門しようという人はページ下部の参考をまず見てほしい

---

高速ゼータ変換・高速メビウス変換は添字の包含関係での畳み込みをする

ゼータ変換とメビウス変換は逆操作の関係にあるが，高速ゼータ・メビウス変換は [隣接代数](https%3A%2F%2Fja.wikipedia.org%2Fwiki%2F%E9%9A%A3%E6%8E%A5%E4%BB%A3%E6%95%B0_%28%E9%A0%86%E5%BA%8F%E7%90%86%E8%AB%96%29){:target="_blank"}<!--_--> というもののなかで，順序として包含関係を用いたものになっているようだ

集合の包含関係以外でもいろいろあり，例えば自然数と約数の関係を用いるとメビウス変換が [メビウスの反転公式]({{ "math/number-theory/mobius-inversion" | absolute_url }}) となる

# 高速ゼータ変換

$a$ から $b$ を求める

### 上位集合に対するゼータ変換

$\displaystyle b\_j = \sum\_{j \in i} a\_i$

### 下位集合に対するゼータ変換

$\displaystyle b\_j = \sum\_{i \in j} a\_i$

---

// @ FastZetaTransform

---

`dp[S][i] = Sをi bitまですべて包含している集合の和` というbitDPをしていると考えることができる

必ずしも足し算である必要はなく，`max` などでもいける

# 高速メビウス変換

メビウス変換はゼータ変換の逆操作にあたる

### 上位集合に対するメビウス変換

$\displaystyle b\_j = \sum\_{j \subset i} (-1)^{\|A \setminus S\|} a\_i$

### 下位集合に対するメビウス変換

$\displaystyle b\_j = \sum\_{i \subset j} (-1)^{\|A \setminus S\|} a\_i$

上記の式は [一般化された包除原理]({{ "math/PIE#一般化された包除原理" | absolute_url }}) そのものである

---

// @ FastMobiusTransform

---

少し特殊な式だが，まとめて [包除原理]({{ "math/PIE" | absolute_url }}) を行う，といったことができる

注意すべきは，このときの「包除原理」は上記の「一般化された包除原理」と区別すべきで，メビウス変換は「包除原理」ありきではないこと．あくまで，「包除原理」を「一般化された包除原理」と似た式として使える，と考えるとわかりやすい

# 練習問題

高速ゼータ変換

* [E - Or Plus Max (700) - AtCoder](https://beta.atcoder.jp/contests/arc100/tasks/arc100_c){:target="_blank"}<!--_-->

高速メビウス変換

* なし

# 参考

* [高速ゼータ変換 - とどの日記](http://d.hatena.ne.jp/todo314/touch/20120614/1339695202){:target="_blank"}<!--_-->
* [色々な畳み込み - kazuma8128’s blog](http://kazuma8128.hatenablog.com/entry/2018/05/31/144519){:target="_blank"}<!--_-->


---
title: 包除原理
---

Principle of Inclusion and Exclusion; PIE

大事なのはORをANDに変えるということ

$$
\begin{aligned}
\left|\bigcup_{i=1}^n A_i\right|
= \sum_{i_0} |A_{i_0}| - \sum_{i_0, i_1} |A_{i_0} \cap A_{i_1}| + \cdots
\end{aligned}
$$

下手に一般化した形を覚えようとすると本番で使いづらいだろうから，

$\|A_1\cup A_2 \cup\cdots\| = \sum \|A_{i_0}\| - \sum \|A_{i_0} \cap A_{i_1}\| + \cdots$ と書くようにしています

# 練習問題

* [E - Couple (うくこん) - AtCoder](https://beta.atcoder.jp/contests/ukuku09/tasks/ukuku09_e){:target="_blank"}<!--_-->
* [F - Squirrel Migration (800) - AtCoder](https://beta.atcoder.jp/contests/arc087/tasks/arc087_d){:target="_blank"}<!--_-->
  * 難しいです，解説は (僕が解いたときは) 少し間違いがあったため注意してください

# 参考

* [包除原理の2通りの証明 - 高校数学の美しい物語](https://mathtrain.jp/hojo){:target="_blank"}<!--_-->


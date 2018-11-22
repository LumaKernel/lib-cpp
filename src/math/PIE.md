---
title: 包除原理
---

Principle of Inclusion and Exclusion; PIE

大事なのはORをANDに変えるということ (ド・モルガンの定理よりANDをORに変えることもできる)

$\displaystyle \begin{aligned} \left\|\bigcup\_{i=1}^n A\_i\right\| = \sum\_{i\_0} \|A\_{i\_0}\| - \sum\_{i\_0, i\_1} \|A\_{i\_0} \cap A\_{i\_1}\| + \cdots \end{aligned}$

$\|A\_1\cup A\_2 \cup\cdots\| = \sum \|A\_{i\_0}\| - \sum \|A\_{i\_0} \cap A\_{i\_1}\| + \cdots$ と書くようにしている

# 一般化された包除原理

$A, S$ は有限集合とし，集合を受け取る関数 $f, g$ について，以下2つの命題が同値

$\displaystyle g(A) = \sum\_{S \subset A} f(S)$

$\displaystyle f(A) = \sum\_{S \subset A} (-1)^{\|A \setminus S\|} g(S)$

---

参考 : [PDF: The Inclusion Exclusion Principle and Its More General Version](http://www.compsci.hunter.cuny.edu/~sweiss/resources/inclusion_exclusion.pdf){:target="_blank"}<!--_-->

上記PDFに一般化版の証明が載っている．また，このことはそんなに自明のことではない

wikipediaなどでは「包除原理の別の形式」として紹介されているが，分けて考えたほうが混乱しない

上の式について $f$ から $g$ を得るのがゼータ変換

下の式について $g$ から $f$ を得るのがメビウス変換

それぞれ，すべての集合に対する値が分かっているとき，[高速ゼータ変換・高速メビウス変換]({{ "algorithm/FastZetaTransform" | absolute_url }}) が使える

ゼータ変換とメビウス変換はさらに一般化された考え方があるが，それについては [高速ゼータ変換]({{ "algorithm/FastZetaTransform" | absolute_url }}) に書いた

# 練習問題

* [E - Couple (うくこん) - AtCoder](https://beta.atcoder.jp/contests/ukuku09/tasks/ukuku09_e){:target="_blank"}<!--_-->
  * [解説](https://tomorinao.blogspot.com/2018/10/divide-and-conquer-fft.html){:target="_blank"}<!--_-->
* [F - Squirrel Migration (800) - AtCoder](https://beta.atcoder.jp/contests/arc087/tasks/arc087_d){:target="_blank"}<!--_-->
  * 一般化されたPIE
  * 難しいです，解説PDFは (僕が解いたときは) 少し間違いがあったため注意してください
* [「みんなのプロコン 2018」決勝 - A - Uncommon (600) - AtCoder](https://beta.atcoder.jp/contests/yahoo-procon2018-final/tasks/yahoo_procon2018_final_a){:target="_blank"}<!--_-->

# 参考

* [包除原理の2通りの証明 - 高校数学の美しい物語](https://mathtrain.jp/hojo){:target="_blank"}<!--_-->
* [隣接代数 (順序理論) - Wikipedia](https%3A%2F%2Fja.wikipedia.org%2Fwiki%2F%E9%9A%A3%E6%8E%A5%E4%BB%A3%E6%95%B0_%28%E9%A0%86%E5%BA%8F%E7%90%86%E8%AB%96%29){:target="_blank"}<!--_-->
* [Inclusion–exclusion principle - Wikipedia (en)](https://en.wikipedia.org/wiki/Inclusion–exclusion_principle){:target="_blank"}<!--_-->


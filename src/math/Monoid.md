---
title: モノイド，モノイド作用

---

データにも構造があるように，数学にも構造がある（適当）．

雑な認識で書きます．

セグメントツリーっていうのはRMQやRSQができることで有名だけど，  
"$ax + b$に変更する"みたいなのをもつこともできる．  
蟻本に乗ってるクレーンのやつとか?  
それらを少しでも同じ舞台に乗せるために十分条件としてモノイドというものが挙げられる．

モノイドは集合 $X$ と演算子 $\bullet$ ふたつでひとつの $(X, \bullet)$ を考える．  
そして任意の元 $a,b,c \in X$ に対して以下を満たす．

* 閉じている ($a \bullet b \in X$)
* 結合律がある ($(a \bullet b) \bullet c=a \bullet (b \bullet c)$)
* 単位元がある ($e \bullet a=a \bullet e=a$となるような$e$の存在(閉じているので当然 $e \in X$ ))

$X = \bm{Z}$ (整数ね), $\bullet = +$ (たしざん)などが，ま，いけるね．

そして列 $a_1, a_1, \cdots , a_n \in X$ がありましたら，  
セグメントツリーにこれを乗せることで，任意の有効な $l \lt r$に対して，  
$a_l \bullet \cdots \bullet a_{r-1}$ をもともめることが  
$O(log(r-l))$ でできると一般化できるわけですね．(必要十分かどうかよくわからないけど)

あと，[0, r]しか求めないBITでも使えます．

* 逆元がある ($a \bullet a^{-1} = a^{-1} \bullet a = e$となるような $a^{-1}$ の存在)

が追加されることで群，

* 交換則がある ($a \bullet b = b \bullet a$)

がさらに追加されてアーベル群となるわけですが，

アーベル群のとき，[l, r]を求めることのできるBITになります．  
[0, r]を求めて，[0, l - 1]を引けばいいわけです．

SparseTableは少しかわっていて，なんかよくわからない名前のアだったのであんま触れません．(参考を参照)

ほかのデータ構造では，さらに追加の条件を加えて，  
いろいろなことができちゃったりします．  
わーすごーい．

## モノイドであって群ではないもの

あんま書きたいこととは関係なのでざっくりいうと，  
フィボナッチ数列の行列二分累乗のときの行列とか，  
さっき書いた $x$ を $ax + b$ に変えちゃうやつ（演算子 $\bullet$の話)とか，  
(参考: [DEGwerさんの記事](http://d.hatena.ne.jp/DEGwer/20131211/1386757368){:target="_blank"}, [kirikaさんの整数論集](https://github.com/kirika-comp/articles){:target="_blank"})
まーそのうち足すかもね．

# モノイド作用

なんやかんやありましてモノイド作用というのが綺麗に，  
遅延セグ木に乗る十分条件になるということです．

モノイド $(X, \bullet)$ と $(M, *)$ ,   
外部演算 $\circ:M \times X \to X$ というのを考えます．  
データに使うのが前者，遅延伝播に使うのが後者のモノイドです．

そして任意の元 $x \in X$ と $a, b \in M$ について，
* $e \circ x = x$ が成り立つ
* $a \circ (b \circ x) = (a * b) \circ x$ が成り立つ

ことが条件です．( $e$ は単位元)

## 遅延セグメントツリーでさらに要求されること

$a_1, \cdots ,a_n \in X$, $m \in M$ とします．  
$x = (a_l \bullet \cdots \bullet a_{r-1})$ と $l$ , $r$, $m$ から，  
$y = ((m \circ a_l) \bullet \cdots \bullet (m \circ a_r))$を求める高速な関数  
$f(X, integer, integer, M): X$ があるといい．

設計としては$r-l=sz$として$l$, $sz$を使うようにしている．

また，この関数には $actInto$ という名前をなんとなくつけた．  
$m$が潜り込んでいる感じがしたのでそうした．

はたして $l$と$sz$を両方使う問題があるのかということだが，  
この前出会った([めぐるはめぐる (5) \| yukicoder](https://yukicoder.me/problems/no/235){:target="_blank"}, TODO : 解説)

## BBSTのreverseでさらに要求されること

[Link/Cut Tree]({{ "data-structure/misc/LinkCutTree" | absolute_url }})の evert の要求も同じ．

$x = (a_l \bullet \cdots \bullet a_{r-1})$ と $l$ , $r$ から，  
$y = a_{r-1} \bullet \cdots \bullet a_l$を求める高速な関数  
$f(X, integer, integer): X$ があるといい．
$reverse$ と名付けた．

これが`X reverse(X x, int, int) { return x; }`以外だったら自分でその場で書くような設計にしておいた．

# 実装

## モノイドの例

// @ Monoid examples

## モノイド，モノイド作用の例

// @ Monoid, M_act examples

# 参考

* [データ構造と代数(前編)](https://tomcatowl.github.io/post/ds-and-alg-1/){:target="_blank"}
* [データ構造と代数(後編)](https://tomcatowl.github.io/post/ds-and-alg-2/){:target="_blank"}

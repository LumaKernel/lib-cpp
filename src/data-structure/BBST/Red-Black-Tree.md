---
title: 赤黒木 (Red-Black Tree; RBT)
---

[BBST]({{ "data-structure/BBST" | absolute_url }}) のひとつ

# Sequenceタイプ

遅延セグ木にできることが基本できて，reverseも条件付きでできる

永続化はコメントを切り替えるだけ (デフォルトで永続化)

// @ Red-Black Tree Sequence

## 使い方

`操作(obj, ...)` の順序．BBST共通の関数は [BBST]({{ "data-structure/BBST" | absolute_url }}) を参照

`build( Node*&, first, last)` で線形時間で構築

`Node::rebuildCheck( <node>, threshold = 1e4)` でプールの残りがしきい値を下回ったら `rebuild` してくれる．`<node>`は `Node*&` か `vector<Node*>&`

`mfree( Node* )` でノードのメモリを解法 (メモリプールに返却)

永続時は `clone( Node*& )` でノードを複製できる

## メモ

赤黒木そのものについては参考に貼ったスライドがわかりやすいのでそちらを参照してほしい

Persistentとそうでないものを一緒にした

生ポインタは基本的に `unique_ptr` と同等で，所有権ごと渡していると考えていい

関数を抜けた後は全てのノードは `proped` が保証されるが `evaled` は保証されない (用語については[BBST]({{ "data-structure/BBST" | absolute_url }}))

(永続化の場合) 子どもに対するポインタは基本 `shared_ptr` であると考え， `copy` したら `unique` であると考える．永続化でなければずっと `unique`

`merge` の計算量は2つの `rank` (実装内では `level` ) 差に対し線形時間となる．他の関数もだいたい同じで， `split` も自明ではないものの同様のことが言える．`copy` の回数は `rank` 差を $L$ とおくと， $50L$ ぐらいが目安だと感じた (数命令1セットと考えて実装では大きめに `1e4` をデフォルト値にしている)

どのような実装でも，メモリプールがないと速度面で競プロで使いにくいと思う

### shared_ptrをつかう版

メモリプールは使うとして，`shared_ptr` を使うか使わないか選ぶ余地がある

[my_shared_ptrを使った D - グラフではない への提出](https://beta.atcoder.jp/contests/arc030/submissions/3628654){:target="_blank"}<!--_--> (約4s)

使う場合は `free` されるノードを `destroy` することでメモリを必要な分だけ賄える

これは採用せず，`rebuild` 型のみにした (ちなみに**ぶっ壊し型**と呼んでいる)

### 永続RBSTについて

全体の提出を見てみると，最速帯は [RBST]({{ "data-structure/BBST/RBST" | absolute_url }}) というBBSTを永続化した**ぶっ壊し型**のものが多い

だが，[RBSTはコピー可能は嘘 - よすぽの日記](http://yosupo.hatenablog.com/entry/2015/10/30/115910){:target="_blank"}<!--_--> や [永続 RBST を撃墜するケース - mitaki28.info blog](http://blog.mitaki28.info/1446205599273/){:target="_blank"}<!--_--> などで紹介されているように，実装と入力が相まって遅くなる可能性がある

それでもぶっ壊し型は強いようだし，ライブラリ禁止下ではRBSTを書きたくなるかもしれないが，hack, systesのあるコンテストなどでは控えたほうがいいかもしれない

多くのコンテストが，想定が永続BBSTならRBTでも大丈夫なTLになっているはずだ

## 検証

* BBST - [E - Hash Swapping (800) - AtCoder](https://beta.atcoder.jp/contests/soundhound2018-summer-final-open/submissions/3632794){:target="_blank"}<!--_-->
* 永続 - [D - グラフではない (ARC) - AtCoder](https://beta.atcoder.jp/contests/arc030/submissions/3632475){:target="_blank"}<!--_-->
  * 約1400ms
* 永続 - [JOI春 - コピー＆ペースト - AtCoder](https://beta.atcoder.jp/contests/joisc2012/submissions/3632712){:target="_blank"}<!--_-->

# Multisetタイプ

書いてないよ

# 参考

* [PDF: アルゴリズムとデータ構造 2-3-4木](http://web-ext.u-aizu.ac.jp/~qf-zhao/TEACHING/Alg-1/lec11-1.pdf){:target="_blank"}<!--_-->
  * とてもわかり易いです
* [PDF: 赤黒木](https://www.ioi-jp.org/camp/2012/2012-sp-tasks/2012-sp-day4-copypaste-slides.pdf){:target="_blank"}<!--_-->
  * JOI春 - コピー＆ペースト の解説スライド
* [平衡二分探索木(Red-Black-Tree) - Luzhiled's memo](https://ei1333.github.io/luzhiled/snippets/structure/red-black-tree.html){:target="_blank"}<!--_-->
* [Red–black tree - Wikipedia (en)](https://en.wikipedia.org/wiki/Red–black_tree){:target="_blank"}<!--_-->


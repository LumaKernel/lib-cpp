---
title: Treap
---

[iwiさんの最強解説](https://www.slideshare.net/iwiwi/2-12188757){:target="_blank"}

# Sequenceタイプ

まずlazy-segにできることができる．  
条件付きで範囲の要素をreverseできる．

条件とは，モノイド $(M, \bullet)$ が，  
$a_l , \codts , a_r \in M$ とおいたとき，
$a_l \bullet \codts \bullet a_r$ と $l$, $r$ から $a_r \bullet \codts \bullet a_l$ が高速に求められること．

minやmax, sumなどは恒等写像でいい．  
この性質を使う問題が出たらわかるだろうということで，  
とりあえずこの性質についてはでたらその場で実装，という感じにした．

// @ Treap Sequence Library

## 検証

* [AOJのやつ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/DSL_2_F/judge/3086418/C++14){:target="_blank"}
* reverse?(無理やり(実質未検証)) - [AOJのやつ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/DSL_2_G/judge/3086622/C++14){:target="_blank"}
* RMQ [AOJのやつ]((https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/DSL_2_A/judge/3086780/C++14)


# Multisetタイプ

こいつにだけにできることが思いつかない

// @ Treap Multiset Library

## 検証

* [C - データ構造 \| AC](https://beta.atcoder.jp/contests/arc033/submissions/2978660){:target="_blank"}


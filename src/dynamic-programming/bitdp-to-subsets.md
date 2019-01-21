---
title: 部分集合に対するbitDP
---

愚直に書くと $O(4^n)$ かかりますが必要なところだけ回すと $O(3^n)$ になります

bitDPでなくとも，単純に高速化として使うことができます

## 0を使わない

部分集合として空集合を使わないものです

// @ bitdp subsets non-zero

全ての集合 `i` について，その部分集合 `j` を見ています

## 0を使う

// @ bitdp subsets zero

## 上位集合に対して

自分を含む集合全てを見ます

// @ bitdp supset

## 計算量について

一番内側のループがどのような `i, j` で呼ばれるか考えます

二進法における各桁 `k` を見ると `(i[k], j[k]) = (0, 0), (1, 0), (1, 1)` の3パターンで呼ばれます

全ての組み合わせが高々1回，他の桁と合わせて登場するので，$O(3^n)$ となります

## 計算順序について

`i`のループ順序についてですが，下位集合は数として小さく，上位集合は数として大きいので上記のようなループ順になっています

# 練習問題

* [APC001 F - XOR Tree (1000) - AtCoder](https://atcoder.jp/contests/apc001/tasks/apc001_f){:target="_blank"}<!--_-->
* [ARC078 F - Mole and Abandoned Mine (900) - AtCoder](https://atcoder.jp/contests/arc078/tasks/arc078_d){:target="_blank"}<!--_-->

# 参考

* [ビットによる部分集合の列挙 - SRM diary(Sigmar) - TopCoder部](https://topcoder.g.hatena.ne.jp/jackpersel/20100804/1281196966){:target="_blank"}<!--_-->


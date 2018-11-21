---
title: Li-Chao Tree (線分など)
---

[この解説](http://smijake3.hatenablog.com/entry/2018/06/16/144548){:target="_blank"}<!--_--> が大変わかり易いです

CHT-Exの代わりにもなり，線分追加クエリもできます．結構速い

読み方は多分リー・チャオです

# 実装

線分も直線も一緒に処理できるようにしました

// @ Li-Chao Tree

## 使い方

インターフェースはCHTと同じですが，事前にクエリを飛ばす座標をわたしておく必要があります

`x(x)` で渡して `.prebuild()` すれば準備完了です．その後は `add`, `query` の順序は任意です

`add(a, b)` で $f(x) = ax + b$ を追加．`add(a, b, l, r)` で $f(x) = ax + b \\ \\ (l \leq x \leq b$ を追加

小数なら `(a, b, l-eps, r+eps)` で渡すようにしたほうがいいかもしれない


# 検証

* [C - スペースエクスプローラー高橋君 - AtCoder](https://beta.atcoder.jp/contests/colopl2018-final-open/submissions/3596655){:target="_blank"}<!--_-->
* 線分追加 - [C - Telephone Charge (300) - AtCoder](https://beta.atcoder.jp/contests/code-festival-2018-final-open/submissions/3610515){:target="_blank"}<!--_-->

# 練習問題

# 参考

* [Li Chao Treeのメモ - 日々ｄｒｄｒする人のメモ](http://smijake3.hatenablog.com/entry/2018/06/16/144548){:target="_blank"}<!--_-->
* [codeforcesでのコメント](https://codeforces.com/blog/entry/51275?#comment-351413){:target="_blank"}<!--_-->


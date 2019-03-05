---
title: 半群も乗る Sparse Table (Disjoint Sparse Table)
---

[noshiさんの解説記事](http://noshi91.hatenablog.com/entry/2018/05/08/183946#f-8405daed){:target="_blank"}<!--_--> がわかりやすい

[Sparse Table]({{ "data-structure/mist/SparseTable" | absolute_url }}) は `min` などの同じ数を複数回適用しても大丈夫な演算でないとダメだった

Disjoint Sparse Tableは計算量はそのままで，足し算など複数回適用してはダメな演算でも乗せることのできるデータ構造

前計算 : $O(N \log N)$  
クエリあたり : $O(1)$

# 実装

// @ Disjoint Sparse Talbe

# 参考

* [Disjoint Sparse Table と セグ木に関するポエム - noshi91のメモ](http://noshi91.hatenablog.com/entry/2018/05/08/183946#f-8405daed){:target="_blank"}<!--_-->


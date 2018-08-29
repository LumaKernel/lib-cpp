---
title: 木を文字列に変換する
id: tree-to-string
---

TODO

根を決めてDFSすると木を一意な文字列に変換でき，
根付き木として同型でなければ一致しない．

fを木を文字列に変換する関数だとすると，

1. f(葉)は `"()"`
2. 頂点vでは `"(" + [hash(f(c)) | c∈vの子] |> sort |> join + ")"`

これを使って[木の同型判定]({{ "/graph/is-same-tree" | absolute_url }})などが行える．  
まだちょっとよくわかっていない(ア

# 参考

* [木の同型性判定のお話 \| kazu0x17’s diary](http://chocobaby-aporo.hatenablog.com/entry/2017/12/05/233027){:target="_blank"}


---
title: 接尾辞配列 (Suffix Array) (Manber & Myers)
---

長さ$N$の文字列 $s$ を考える．また，$s \text{区間}$ で区間内の部分文字列とし，$s[i, -1]$ は $s[i, N-1]$ とする

# 接尾辞配列

Manber & Myersは$O(N \log^2 N)$ で構築

$O(N)$ で構築する速いやつは [SA-IS]({{ "string/SA-IS" | absolute_url }}) を参照．  
実装を素早くするならこれ．愚直にやれば $O(N^2 \log N)$ 

接尾辞配列とは，文字列sについて，  
$0 \cdots (n-1)$ を各数 $i$ について $s[i,-1]$ に置き換えたとき辞書順昇順になるように並べた (ソートした) ものである

$s[i,-1]$ はそれぞれ長さが違うのでsa, rankはdistinct(狭義単調増加)

それがsuffix array (sa)  
蟻本の表を見ていると分かってくる．ので以下に貼る

"abracadabra" の例．（空文字列なし）

| i | sa[i] | $s[sa[i], -1]$ |
|--|--|--|
| 0 | 10 | "a" |
| 1 | 7 | "abra" |
| 2 | 0 | "abracadabra" |
| 3 | 3 | "acadabra" |
| 4 | 5 | "adabra" |
| 5 | 8 | "bra" |
| 6 | 1 | "bracadabra" |
| 7 | 4 | "cadabra" |
| 8 | 6 | "dabra" |
| 9 | 9 | "ra" |
| 10 | 2 | "racadabra" |

長さが全て違います．

[LCP配列]({{ "string/LCP-Array" | absolute_url }})まで見ると，使い方を含めたことが，よりわかると思います

# Manber & Myersがどうやって構築しているか

## メインアイデアはダブリング

saの逆関数に当たるものをrankとする  
(rank[sa[i]] = i, distinctなので当然sa[rank[i]] = i)

まず1文字分以下を考慮してソートし，  
rankを計算  
(この途中計算中のrankはdistinctではない，後述)

k文字を考慮しているsaのrank である $rank_k$ が分かっているとする  

* 2k文字を考慮したsaは 例えば $s[i,i+k)$ と $s[j,i+k)$ の比較は
* $s[i,i+k) + s[i+k,-1]$ と $s[j,j+k) + s[j+k,-1]$ の比較と言え，
* $(rank_k[i], rank_k[i + k])$ と $(rank_k, rank_k[j + k])$ の辞書順比較と言える．

## ただし

* 存在しない範囲への文字列アクセスは空文字列であるとし，(実装には関係ない)
* 存在しないrankは-1を返すとする．(実装に関係している)

考慮する文字数がもとの文字列の長さ $N$ 以上になればいい

## また

計算途中のrankは次で正しく比較できさえすれば良くて，  

* 順序があっている
* 同じものは同じ数値 <span style="color:red">\*1</span>

を満たせばいい  
なので，

* 1文字を求めるときはその文字自体をrankに，
* 2文字以降はこう，やるだけ（実装見て）

## <span style="color:red">\*1</span>について

なぜこれが必要か？ということだが，例えば，

* "abcd" と "ab" を比較しようというときに，  
* (4, 2) と (5, -1) とかだと，"abcd" < "ab" になる．
* (4, 2) と (4, -1) ならちゃんと後半が比較され，"abcd" > "ab"となる．

# 使いみち

[LCP配列]({{ "string/LCP-Array" | absolute_url }})に使ったり，文字列検索をしたり(蟻本参照)(TODO : 書く)

# 実装

// @ Suffix Array with Manber & Myers

# 検証

TLEしかない

# 参考

* 蟻本


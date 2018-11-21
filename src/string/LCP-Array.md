---
title: LCP配列 (Kasai's algorithm)
---

# LCP

最長共通接頭辞 (Longest Common Prefix)

例えば "luma" と "lune" のLCPは "<span style="color:red">lu</span>"

# LCP配列

"Suffix Arrayにおいて隣接する2つの文字列のLCP" の長さ配列

Suffix Arrayはここでは文字列自体が入ってると考えてもらって大丈夫です (実際は $s[i, -1]$ に対応する $i$ が入っている配列，詳しくは [SA (Manber & Myers)]({{ "string/SA-with-Manber-Myers" | absolute_url }})

# 隣接するSAが持つ特徴

[SA (Manber & Myers)]({{ "string/SA-with-Manber-Myers" | absolute_url }})の続きみたいに書いていきます

**単に文字列が昇順に並んでいる配列**とは違い，嬉しい特徴があります

LCP配列を構築するときは，その特徴を利用して $O(N)$ で構築します

$i$ を昇順に調べていきます．$s[i, -1]$ を見ているとします

SA上で隣接，ですが，このとき，後ろを見ます

**SA上で後ろ**というのは，$j = sa[rank[i] - 1]$ とおくと，$s[j, -1]$ になります

↓こゆこと↓

|index| sa[index] | $s[sa[index], -1]$ |
|--|--|
| $rank[i] - 1$ ( = $rank[j]$) | $j$ | "<span style="color:red">abc</span>..." |
| $rank[i]$ | $i$ | "<span style="color:red">abc</span>def" |

たとえば上記の表のように $s[i, -1]$ が "<span style="color:red">abc</span>def" だったとしてLCPの長さが 3 だったとしましょう

つまり，"<span style="color:red">abc</span>..." といったものがSAに含まれることになります (そしてそれは $s[j, -1]$)

$i + 1$に移行します

$s[i + 1, -1]$ は "bcdef" です

$s[j + 1, -1]$ は "bc..." です

ここで， $i+1$ の**SA上で後ろ**のそのインデックス は $rank[j + 1]$以上 $rank[i + 1]$未満となります (これが嬉しい性質)

まず，もともと $rank[j] \lt rank[i]$ というのはいいでしょうか ($rank[j] + 1 = rank[i]$)

そしたら1文字削ったそれぞれが順序を保つのは自明です (下記表参照)

さて，SA上では

|index| sa[index] | $s[sa[index], -1]$ |
|--|--|
| $rank[j + 1]$ | j + 1 | "<span style="color:red">bc</span>..." |
| $rank[j + 1] + 1$ | ?? | "<span style="color:red">bc</span>..." |
| $rank[j + 1]$ + ... | ?? | "<span style="color:red">bc</span>..." |
| $rank[i + 1]$ | i + 1 | "<span style="color:red">bc</span>def" |

となっており，"<span style="color:red">bc</span>"，つまり $i$ で一致した3文字 "<span style="color:red">abc</span>" から，一個落とした "<span style="color:red">bc</span>" の2文字が必ず一致する

よって，手前から**SA上で後ろ**のLCP配列の値を求めていくのが効率が良い

# $O(N)$ の証明

心配なのは `h++` のよばれる回数

`h--` が最大で $N$ 回しかよばれず，$i \geq 0$ である

$i + h \leq N$ であり，`h`の初期値が`0`であることから，どうあがいても $2N$ 回までしか`h++`がよばれない

# 配列内の任意の2つの要素のLCP

これはSAからつくったLCPでなくとも言える話ですが，2つの間の最小値を求めれば良いです

ゆっくりいきます

文字列の**昇順**の配列$S = \{S_1, \cdots , S_M\}$があるとします

また，LCPの長さの列 $L = \{LCP(S_1, S_2), LCP(S_2, S_3), \cdots, LCP(S_{M-1}, S_M)\}$ があるとします

$LCP(S_i, S_j)$ は $[\min(i, j), \max(i, j))$ の最小値ということです<!-- ] -->

なぜか

帰納法が直感的で，証明もできそうです

---

Kasaiって日本人っぽい名前だなと思って調べたら，
[日本人っぽい名前](https://dblp.org/pers/hd/k/Kasai:Toru){:target="_blank"}<!--_-->でした

# 実装

SA([Manber & Myers]({{ "string/SA-with-Manber-Myers" | absolute_url }}), [SA-IS]({{ "string/SA-IS" | absolute_url }}))を必要とします．僕のSAは空文字列を含みません

蟻本のLCP配列は番兵 (空文字列) を必要としますが，この実装は必要としません

// @ LCP Array Library

# 検証

* [No.515 典型LCP - yukicoder](https://yukicoder.me/submissions/281621){:target="_blank"}<!--_-->
  * 実はSAによるLCP配列はいらない
  * 直接，LCPの配列がつくれる

# 練習問題

* [ECR - G - Yet Another LCP Problem - codeforces](https://codeforces.com/contest/1073/problem/G){:target="_blank"}<!--_-->

# 参考

* 蟻本


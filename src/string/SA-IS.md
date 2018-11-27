---
title: 接尾辞配列 (Suffix Array) (SA-IS)
---

IS; Induced Sorting

SAを $O(N)$ で構築する．すごい  
SA自体の説明は[Manber & Mayersのところ]({{ "string/SA-with-Manber-Myers" | absolute_url }})に

番兵を足すと楽になるのでかってに足してあとで消す

rankは必要ないのだが，SAを考える上でrankを考えたほうが僕がわかりやすいというのと，  
[LCP配列]({{ "string/LCP-Array" | absolute_url }}) がSAにrankの実装を必要とするようにしたから

注意

* 文字種の変更がある場合は忘れずに

// @ SA-IS

# 検証

* [No.515 典型LCP - yukicoder](https://yukicoder.me/submissions/281621){:target="_blank"}<!--_-->
  * SAいらなかった．ふえぇん
  * SA使う場合， $O(N \log^2 N)$ だと間に合わなかった
  * 合計800'000文字，文字種26
* [C - アメージングな文字列は、きみが作る！ - AtCoder](https://beta.atcoder.jp/contests/discovery2016-qual/submissions/3123557){:target="_blank"}<!--_-->

# 練習問題

* [ECR - E Vasya and Big Integers - codeforces](https://codeforces.com/contest/1051/problem/E){:target="_blank"}<!--_-->
  * SA-ISの速さを信じれば通せる (想定は少し違います)

# 参考

* [SA-IS 法のメモ - まめめも](http://d.hatena.ne.jp/ku-ma-me/20180130/p1){:target="_blank"}<!--_-->


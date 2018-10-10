---
title: 接尾辞配列 (Suffix Array) (SA-IS)
---

IS; Induced Sorting

SAを $O(N)$ で構築する．すごい．  
SA自体の説明は[Manber & Mayersのところ]({{ "string/SA-with-Manber-Myers" | absolute_url }})に．

番兵を足すと楽になるのでかってに足してあとで消す．

rankは必要ないのだが，SAを考える上でrankを考えたほうが僕がわかりやすいというのと，  
[LCP配列]({{ "string/LCP-Array" | absolute_url }})がSAにrankの実装を必要とするようにしたから．

注意

* string以外で使うときは番兵足す処理を変更する必要がある
* 文字種の変更も忘れずに

// @ SA-IS

# 検証

* [No.515 典型LCP - yukicoder](https://yukicoder.me/submissions/281621){:target="_blank"}
  * SAいらなかった．ふえぇん．
  * SA使う場合， $O(N log^2 N)$ だと間に合わなかった．
  * 合計800'000文字 26種
* [C - アメージングな文字列は、きみが作る！ - AtCoder](https://beta.atcoder.jp/contests/discovery2016-qual/submissions/3123557){:target="_blank"}<!--_-->

# 参考

* [SA-IS 法のメモ - まめめも](http://d.hatena.ne.jp/ku-ma-me/20180130/p1){:target="_blank"}
  * わかりやすい


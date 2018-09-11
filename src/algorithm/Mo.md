---
title: クエリ平方分割 (Mo's Algorithm)
---

Moのアルゴリズム（クエリの平方分割）

オフラインでstaticなデータに対するクエリに答えられます．

配列の長さが $N$ のとき，  
区間について答えるクエリ $Q$ 個に，  
$O(N \sqrt{Q} f(N))$ で答えることができる．

ただし，$f(N)$ とは 区間 $[l, r)$ に対する答えから，  
$[l + 1, r), [l - 1, r), [l, r + 1), [l, r - 1)$ を答える(伸縮する，と呼ぶことにする)のにかかる時間である．
<!--]-->

伸縮にかかる時間は $O(1)$ や $O(\log N)$ だが， $O(\log N)$ はTLEになるかもしれない．

"出現した種類数"，"k個以上出現するもの" とかが基本的なキーワード．(あくまでも基本なのでね)

# 参考

* [Mo's algorithm - ei1333の日記](https://ei1333.hateblo.jp/entry/2017/09/11/211011){:target="_blank"}<!--_-->
* [Mo's algorithm の上位互換の話 - あなたは嘘つきですかと聞かれたら「YES」と答えるブログ](http://snuke.hatenablog.com/entry/2016/07/01/000000){:target="_blank"}<!--_-->
  * Mo自体についてもガッツリ書かれています
  * 計算量の証明はここを参照
  * このライブラリは別のところ( [Rollback可能なデータ構造とMo]({{ "algorithm/MoEx" | absolute_url }}) )においてあります


# Moの高速化

以下で議論されていた内容など．

* [Query regarding Mo's Algorithm - CodeChef Discussion](https://discuss.codechef.com/questions/119615/query-regarding-mos-algorithm){:target="_blank"}<!--_-->

1. <span style="color:red">ソートの比較関数を変える</span>
  * ブロックのパリティによって，右端をleft to rightにするかその逆にするかを交互にすれば，右端の移動回数が1/2になります．
  * コードもほんの少し変更するだけでよく，目に見えて速くなるのでおすすめです．
  * 不適切な評価関数を使わないように気をつけてください ([詳細]({{ "trap/improper-comparison" | absolute_url }}))
2. ブロックのサイズを変える
  * これは必ずしも速くなるとは言えず，  
  試してみるしかない．係数を2,3などにする．
3. add, remのクロック数を減らす
  * これはかなり有効ですが，同じ $O(1)$ であれば，  
  想定回であれば大抵大丈夫で，余計に考察することになるかもしれません．
4. ベタ書きする
  * 問題に合わせて最適な実装にします
  * うーん，コンテスト終わった後のお楽しみ程度の認識．

ただ，これらを組み合わせると3,4倍にも高速になります．  
(なりますというか，これができるのはだいぶ変態)

# 木上のMo

詳しくはうしさんの記事を見てください．

オイラーツアーすると，部分木に対するクエリが 区間 $[in_v, out_v)$ に対するクエリに変わります．
<!--]-->

パスに対するクエリは，頂点にデータがあるときは，亜種オイラーツアーみたいなのをして区間クエリと一点（LCA）の更新に置き換えます

# 実装

区間はすべて $[l, r)$ (半開区間) です

全部に `inline` がついてて気持ち悪いという気持ちになるが，ほんとそう

// @ Mo Library

## 木上の頂点にデータがあるパスクエリMo

うしさんの解説を見てください

// @ MoTreeVertex Library

# 注意点

代入演算子の評価順序に注意してください．

C++において，以下のような書き方は結構危険です．

```
// bad
ans[mo.next()] = sum;
```

左辺の評価値は一意ですが，右辺はどちらを先に評価するかによってかわってきます．

mo.next()は変数に入れてから，としておきましょう．

```
// good
int id = mo.next();
ans[id] = sum;
```

また，比較関数が `operator<` 相当ではなく `operator<=` 相当にならないように気をつけてください．(実装を参照) ([詳細]({{ "trap/improper-comparison" | absolute_url }}))

# 検証

* [D - Powerful array - CF (4334ms)](https://codeforces.com/contest/86/submission/42720275){:target="_blank"}<!--_-->
  * [meooowさんの高速化された1058ms解](https://codeforces.com/contest/86/submission/33239378){:target="_blank"}<!--_-->
* 木上のMo - [D - Tree and Queries - CF](https://codeforces.com/contest/375/submission/42721054){:target="_blank"}<!--_-->
  * $N \leq 10^5$ はだいぶ安心してMoを投げられます
* 木上の頂点にデータがあるパスクエリMo - [COT2 - Count on a tree II - SPOJ](https://www.spoj.com/files/src/22296870/){:target="_blank"}<!--_-->
* 同上 - [The L-th Number - AOJ](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/2270/judge/3127075/C++14){:target="_blank"}<!--_-->

# 練習

* [D - Powerful array - CF](https://codeforces.com/contest/86/problem/D){:target="_blank"}<!--_-->
* [D - Tree and Queries - CF](https://codeforces.com/contest/375/problem/D){:target="_blank"}<!--_-->
* [COT2 - Count on a tree II - SPOJ](https://www.spoj.com/problems/COT2/){:target="_blank"}<!--_-->
* [The L-th Number - AOJ](https://onlinejudge.u-aizu.ac.jp/problems/2270){:target="_blank"}<!--_-->



森(もしくは根付き有向木(Arborescence)の集合)への更新とクエリを順不同で高速に．

根の変更クエリ(evert)には乗せるモノイドに対する要求があり，その条件は平衡二分探索木がreverseで要求するものと同じ([モノイド]()をみて)．

動的木の一種．

IOIで常勝できることはあまりにも有名．

参考になるものを準備しています…

TODO : 区間に対する更新に対し，leftを求めるの，ちょっとどうすればいいかわからないけど，  
やっている人がいるのでそのうち見てみようと思います．

// @ LinkCutTree Library

# 検証

* RMQとRUQ - [AOJのなんか](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/DSL_2_F/judge/3092002/C++14){:target="_blank"}
  * 遅延セグ木でできることがevert付きでできる
* LCA - [AOJのなんか](https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/GRL_5_C/judge/3092319/C++14){:target="_blank"}
* HL-Decomp(TLE) [E. The Number Games \| CF](https://codeforces.com/contest/980/submission/41594330){:target="_blank"}
* HL-Decomp [PCKの問題 \| AOJ]( https://onlinejudge.u-aizu.ac.jp/status/users/luma/submissions/1/0367/judge/3093506/C++14)


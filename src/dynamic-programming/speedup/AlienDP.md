---
title: AlienDP (Parametric Binary Search)
---

中国では WQS Binary Search と呼ばれている

AlienDPという名前は [IOI 2016 Aliens](https://www.ioi-jp.org/ioi/2016/tasks/day2-aliens-ISC.pdf){:target="_blank"}<!--_--> という問題から来ている

---

AlienDPの本質はDAG上の**2頂点対(単一パス)k辺最短経路問題**である

# 執筆中

解説書きます，しばしお待ちを！

# 実装

// @ PenalizeSpeedup

# 検証

* IOI2016 day2 Aliens
  * [PDF: 公式 statement](https://www.ioi-jp.org/ioi/2016/tasks/day2-aliens-ISC.pdf){:target="_blank"}<!--_-->
  * [PEG Online Judge (statement)](https://wcipeg.com/problem/ioi1623){:target="_blank"}<!--_-->
  * [PEG Online Judge (submission)](https://wcipeg.com/submissions/src/613303){:target="_blank"}<!--_--> ([mirror](https://gist.github.com/LumaKernel/e8c771f3ccc1c865112a157835915284#file-ioi2016-aliens-cpp){:target="_blank"}<!--_-->)

* ルーマニアIOI選抜2017 2 - Popcorn
  * [CSAcademy (statement)](https://csacademy.com/contest/romanian-ioi-2017-selection-2/task/popcorn/statement/){:target="_blank"}<!--_-->
  * [CSAcademy (code)](https://csacademy.com/code/J8qmEbff/){:target="_blank"}<!--_--> ([mirror](https://gist.github.com/LumaKernel/e8c771f3ccc1c865112a157835915284#file-romanian-ioi-2017-selection-2-popcorn-cpp){:target="_blank"}<!--_-->)


# 参考

* [Round #56 (Div. 1 + Div. 2) with prizes - codeforces](https://codeforces.com/blog/entry/55638){:target="_blank"}<!--_-->
* [Computing a Minimum Weight k-Link Path in Graphs with the Concave Monge Property](http://www.cs.ust.hk/mjg_lib/bibs/DPSu/DPSu.Files/sdarticle_204.pdf){:target="_blank"}<!--_-->
  * 完全DAG上での話だが，内容はAlienDPと捉えて問題ない
* [Incredibly beautiful DP optimization from N^3 to N log^2 N - codeforces](https://codeforces.com/blog/entry/49691){:target="_blank"}<!--_-->
  * やっていることはAlienDPだが，誰も $f(b) \coloneqq dp[i][a][b]$ が上に凸である事を証明できていない
  * 証明については，直感的に，得する順にソートするといったことを考えると良さそうだが，使えるbが増えたときに，他の組合せを変えて得することがあり，それも含めた証明は，そんなに自明なことではない
  * (コメントを見る限り) 誰も証明できていないが，おそらく上に凸だと思われる
* [競技プログラミングにおける動的計画法更新最適化まとめ - はまやんはまやんはまやん](https://www.hamayanhamayan.com/entry/2017/03/20/234711){:target="_blank"}<!--_-->


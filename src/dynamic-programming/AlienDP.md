---
title: AlienDP (Parametric Binary Search)
---

中国では WQS Binary Search と呼ばれている

AlienDPという名前は [IOI 2016 Aliens](https://www.ioi-jp.org/ioi/2016/tasks/day2-aliens-ISC.pdf){:target="_blank"}<!--_--> という問題から来ている

---

AlienDPの本質はDAG上の**2頂点対間k辺最短経路問題**である




# 参考

* [Round #56 (Div. 1 + Div. 2) with prizes - codeforces](https://codeforces.com/blog/entry/55638){:target="_blank"}<!--_-->
* [Computing a Minimum Weight k-Link Path in Graphs with the Concave Monge Property](http://www.cs.ust.hk/mjg_lib/bibs/DPSu/DPSu.Files/sdarticle_204.pdf){:target="_blank"}<!--_-->
  * 完全DAG上での話だが，内容はAlienDPと捉えて問題ない
* [Incredibly beautiful DP optimization from N^3 to N log^2 N - codeforces](https://codeforces.com/blog/entry/49691){:target="_blank"}<!--_-->
  * やっていることはAlienDPだが，誰も $f(b) \coloneqq dp[i][a][b]$ が上に凸である事を証明できていない
  * 証明については，直感的に，得する順にソートするといったことを考えると良さそうだが，使えるbが増えたときに，他の組合せを変えて得することがあり，それも含めた時，そんなに自明なことではない
  * 誰も証明できていないが，おそらく上に凸だと思われる


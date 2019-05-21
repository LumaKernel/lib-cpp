---
title: AlienDP (Parametric Binary Search)
---

TODO : ですます

中国では WQS Binary Search と呼ばれている

AlienDPという名前は [IOI 2016 Aliens](https://www.ioi-jp.org/ioi/2016/tasks/day2-aliens-ISC.pdf){:target="_blank"}<!--_--> という問題から来ている

---

AlienDPはローカルネーム感が強い気がするので PenalizeSpeedup みたいな名前で個人的には呼んでいます.

この記事では, PenalizeSpeedupというテクニックとして紹介します. そして, Alienを始めとする, AlienDPと呼ばれる特殊な形をしたDPは, PenalizeSpeedupに帰着できる, という扱いをしようと思います. (つまり, PenalizeSpeedupはAlienDPの一般化みたいに扱います)

# PenalizeSpeedupとは?

PenalizeSpeedupの本質はDAG上の**2頂点対(単一パス)k辺最短経路問題**である.

そして多くの場合, このDAGは完全グラフであり, この完全グラフ上の距離について [Monge性](TODO) があるならば PenalizeSpeedup が必ず適用できると言える.

一般性を失わず, 頂点 $s$ から 頂点 $t$ へのk辺最短経路問題とする.

# 前提

DAG (Directed Acyclic Graph) とは閉路のない有向グラフのことである.

辺に実数の重みがある DAG $G$ が与えられる. 単純でも連結でもなくてよい. すなわち, 多重辺や孤立点があってもよいということ.

$N = \|G\|$ としておく.

$dist(v, k)$ を $G$ における頂点 $v$ から頂点 $t$ までのk辺最短路長とする. k辺最短路とは, $v$ から $t$ まで **ちょうど** k本の辺を使って行くような経路のうち, 経路上の辺の重みの和が最小のもののことをいう. (そのようなものがなければ $\infty$ であるとする.)

$dist(s, k)$ を求めるのが PenalizeSpeedup.

$G$の例

![graph]({{ "img/penalize-speedup-graph.png" | absolute_url }})

$t = 0$ であると考えられる.


# 注意点

k辺最短路というが, 問題によってはk本以下最短路問題であったりする.  
それらのうちいくつかは, k本中何本かを無駄にすることが特別な考察なしに出来たりする.  
しかし, そうでない場合についても常に問題ない. これについては後で議論 (TODO) するが,  k辺最適化問題が PenalizeSpeedup で解けるとき, 常にk辺以下最短路問題が解けることを示す.


# メインアイデア

いくつかの問題では，直感的には，**より多くの辺を経由したほうが得する**がそんなに**たくさんの辺を経由できない**, と言えるDAG上のk辺最短路問題に帰着できる. (以下, DAGに帰着するのは前提として, もともとDAG上のk辺最短路を求める問題であるとする)

すべての辺にペナルティを課した (重さをいくらか追加した) グラフでの最短距離を考える.

ペナルティを増やすことで, 辺を多く使うことが難しくなる. **k本使うのが最適**であるようにペナルティを調整する.

**辺の重み**と**最短経路における使う辺の数**に単調性があれば二分探索ができる. そして, 実際に単調性がある.

あとは最短路を求めることを, ペナルティを課したグラフ上で, **辺をいくつ使ったかを気にせず**, ただ, 使った辺の数の記録だけをして, **距離の最小化をする**.

# TODO

各辺の重みが, 実数 $penalty$ だけ増えたグラフを考える. 新しくできたグラフを $G^\prime(penalty)$ と書くことにする. 例えば, $G = G^\prime(0)$ である. TODO

例 : $G^\prime(10)$ の図

![graph-dash1]({{ "img/penalize-speedup-graph-dash1.png" | absolute_url }})

始点となる, ある頂点 $v$ を固定して考える.

$G^\prime(penalty)$ における $dist(v, k)$ を $dist^\prime_{penalty}(v, k)$ とする. すると, $dist^\prime_{penalty}(v, k) = dist(v, k) + k \cdot penalty$ となる.

ここで, $G^\prime(penalty)$ 上で, 辺の数を考慮せず $v-t$ 間最短路を求めたときの, その距離と, 使った辺の数をそれぞれ $d_{penalty}(v)$, $e\_{penalty}(v)$ とする. ($e\_{penalty}(v)$ は一意に定まらないかもしれない. これについては後で議論する.)

ここで, $$\displaystyle d(penalty) = \min_k \{dist^\prime_{penalty}(v, k)\}$$ である. <!--_-->

横軸に $penalty$, 縦軸に $dist^\prime_{penalty}(v, k) = dist(v, k) + k \cdot penalty$ をとったグラフを考える. これらは1次関数の形をしていることに注意してほしい.<!--_-->

以下の図では, `penalty` を `p` と略記していたりする.

![lines-01]({{ "img/penalize-speedup-lines-01.png" | absolute_url }})

$d_{penalty}(v)$ となる部分を, 太線で強調すると以下のようになる.<!--_-->

![lines-02]({{ "img/penalize-speedup-lines-02.png" | absolute_url }})

今求めたい値, $dist(v, k)$ というのは, その $k$ に対応する直線のy切片であることにも注意してほしい.

上記の図の赤い直線 ($k = 2$) に注目してほしい. このとき, $dist(v, 1)$ や $dist(v, 3)$ は, $d_{penalty}(v)$ から求めることが可能だ. $penalty$ をうまく調整することで求められる (この調整には二分探索を用いる. これについては後で説明する). 例えば, $dist(v, 1)$ を求めたいなら, $e_{penalty}(v) = 1$ になるようなペナルティにすればよい.

### 例 : dist(v, 3) が求めたい

先程の図に少し書き加えます.

![lines-03]({{ "img/penalize-speedup-lines-03.png" | absolute_url }})

具体的に, $e_{-5}(v) = 3, e_{-15}(v) = 3$ であったとする. $penalty = -5$ を考える.

$d_{-5}(v) = 130$ だったとします. そしたら, $dist^\prime_{-5}(v, 3) = 130$ なわけですが, 3本の辺でペナルティを課されたわけですから, 元のグラフでの距離は $3 \cdot penalty$ を引いた数になります. つまり, $dist(v, 3) = dist^\prime_{-5}(v, 3) - 3 \cdot (-5) = 130 + 15 = 145$ となります.

同様に, $penalty = -15$ としたならば, $d_{-15}(v) = 100$ が得られ, 計算すると同じ値が求まります.



---

一方で, $dist(v, 2)$ は $d_{penalty}(v)$ から求めることは, どのようにペナルティを調整しても, できない.

このアルゴリズムは, ペナルティを固定して, 得られた経路長 $d_{penalty}(v)$ が, $f_k(x) = dist(v, k) + kx$ という直線上に乗っていると捉えて, $dist(v, k)$ を求めるからだ. つまり, 以下のような命題が成り立つ.

> PenalizeSpeedup を適用して $dist(v, k)$ を求めるには以下が成り立つ必要がある.
>
> 直線 $f_k(x) = dist(v, k) + kx$ が $d_{x}(v)$ と一致する瞬間 (ペナルティ $x$) がある.

(直線であることがわかりやすいように, 変数に $x$ を用いた)

直感的に言い換えるなら, 目的とする直線が, 下側にむき出しになっている必要があるということだ.

以下, 上記の条件を満たすことを, $f_k$ が有効である, と呼ぶことにする.

# 条件のさらなる言い換え

上記の条件を更に言い換える. 言い換えには, CHT (TODO) で用いられるような方法を用いる.

引き続き, 頂点 $v$ を固定して考える.

v-t 経路につかう辺の数としてあり得る値を $0, 1, 2, \cdots, n$ とします.

(実際には飛び飛びになってしまっても大丈夫かもしれません.
しかし, 次項でも触れますが, 常にこのように連続した値を取りえることを前提としてしまいましょう.
ただし, 上の方のいくつかが存在しない場合, $dist$ は十分大きな有限値になるとしてしまっても問題ありません.
これについても, 後の項で触れます. こうすることで, $n = N - 1$ とできますね.
)

また, 先程のグラフのように $f_0(x) = dist(v, 0) + 0 \cdot x, f_1(x) = dist(v, 1) + 1 \cdot x, \cdots, f_n(x) = dist(v, n) + nx$ といった直線を考えます.

$f_0$ と $f_n$ はそれぞれ, 十分大きい$x$, 十分小さい$x$ で最小値となるので, 有効です.

---

復習 : 直線 $y = a_1x + b_1$ と $y = a_2x + b_2$ の交点は $-\frac{b_2-b_1}{a_2-a_1}$.

---

$0 \lt i \lt n$ について, $f_i$ が有効である条件とは, $$f_i, f_{i+1}$$ の交点のx座標, $$f_{i-1}, f_i$$ の交点のx座標がこの順番に登場する (か等しい) 場合です.

つまり, $-\frac{dist(v, i) - dist(v, i + 1)}{i - (i + 1)} \leq -\frac{dist(v, i - 1) - dist(v, i)}{(i - 1) - i}$ です. 整理すると,

$$dist(v, i) - dist(v, i - 1) \geq dist(v, i + 1) - dist(v, i)$$

となります.

---

すべての $0 \lt i \lt n$ において上記が成り立つ条件を考えてみます.

これは, $dist(v, i)$ を $i$ の関数としてみると, この関数に, **凸性を要求している**事がわかります. (上に凸)

(上に凸とは, いいかえれば, "増え方" が増えていく, ということです.)

これが, "AlienDPが凸性を要求する" という言葉の真意です.

---

一つ注意事項. 凸というと, 図で示した直線の最小値も凸なので, そっちのことを言っているのかな? となるかもしれません. \\
しかし, 上記で言っている凸性というのは, あくまでも式変形をして出てきた不等式が凸性を言っている, というだけの話であることには注意してください.


# PenalizeSpeedupが適用可能な条件のまとめ

任意の $v \in G$, $0 \lt k \lt n$ について, $dist(v, k)$ を $k$ の関数とみたとき, 凸である.

すなわち, $dist(v, i) - dist(v, i - 1) \geq dist(v, i + 1) - dist(v, i)$ であること.


以上が十分条件である.

# 任意のv,kに対して条件を課す必要があるか

前項の条件は任意の $v, k$ に対して条件を要求している. 実際には求めたいところだけ満たせばいい.

しかし, 現実的には, この $v, k$ はグラフの形に関係なく与えられることが多いはずだ.

つまり, $dist(v, k)$ は求められる条件を満たすが, それ以外の $dist(v^\prime, k^\prime)$ は求められる条件を満たさない, といったような都合のいいケースは考えにくい.


なので, 前項のような十分条件を PenalizeSpeedup の前提と考えることが多い.


# 目的のpenaltyを求める

$e_x(v) = k$ となるような $x$ を求められなくてはならない.

ところで, $e_x(v)$ は, $x$ の関数とみると, 単調減少である. (図を見てもらえれば明らかだ)

$e_x(v)$ が一意でない場合は次項で議論する.

よって, これは $penalty$ に対して二分探索を行えばよい.
具体的なアルゴリズムや，探索する範囲, 繰り返しの回数, 整数か小数どっちを使うべきか, といったことについては後で議論する.

# あるペナルティにおいて, 最小長を取れる辺数が複数ある場合

これはいつも存在する. なぜなら, 複数の直線が一点で, 最小値として交わる点がそのような点であり, ２つの直線が交わる点が必ず存在するからだ.















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

# 練習問題

* [#56 Or Problem - CSAcademy](https://csacademy.com/contest/round-56/task/or-problem/){:target="_blank"}<!--_-->
* [#351 C - Levels and Regions - codeforces](https://codeforces.com/contest/674/problem/C){:target="_blank"}<!--_-->
* [#381 div1 E - Gosha is hunting - codeforces](https://codeforces.com/contest/739/problem/E){:target="_blank"}<!--_-->
  * 下の参考にも書いたが，この問題がAlienDPを適用できる条件を満たしていることの証明がない

# 参考

* [Round #56 (Div. 1 + Div. 2) with prizes - codeforces](https://codeforces.com/blog/entry/55638){:target="_blank"}<!--_-->
* [Computing a Minimum Weight k-Link Path in Graphs with the Concave Monge Property](http://www.cs.ust.hk/mjg_lib/bibs/DPSu/DPSu.Files/sdarticle_204.pdf){:target="_blank"}<!--_-->
  * 完全DAG上での話だが，内容はAlienDPと捉えて問題ない
* [Incredibly beautiful DP optimization from N^3 to N log^2 N - codeforces](https://codeforces.com/blog/entry/49691){:target="_blank"}<!--_-->
  * やっていることはAlienDPだが，誰も $f(b) \coloneqq dp[i][a][b]$ が上に凸である事を証明できていない
  * 証明については，直感的に，得する順にソートするといったことを考えると良さそうだが，使えるbが増えたときに，他の組合せを変えて得することがあり，それも含めた証明は，そんなに自明なことではない
  * (コメントを見る限り) 誰も証明できていないが，おそらく上に凸だと思われる
* [競技プログラミングにおける動的計画法更新最適化まとめ - はまやんはまやんはまやん](https://www.hamayanhamayan.com/entry/2017/03/20/234711){:target="_blank"}<!--_-->

a



グラフを考える．  
橋(bridge)とはそれを除くとグラフが連結でなくなる辺．  
関節点(articulation point)とはそれとそれにつながる辺を除くとグラフが連結でなくなる頂点．

DFS TreeとはDFSして訪れるときに使う辺で作られる有向木．(このときの根や辺の決め方はどうでもいい)  
後退辺(back edge)とはDFS Treeに含まれない辺，ただし深い方から浅い方への有向辺．  

ordとはDFSして訪れた順番に頂点につけられた番号（オイラーツアーでのid的な）  
lowとはDFSTreeの有向辺を任意本，退行辺をたかだか1本つかって到達可能な頂点のordの最小値．

それぞれの定義を覚えておけば実装できる．

// @ Lowlink Library

# 参考

lowlinkでggって．

# 検証 

* 橋 - [D - 旅行会社高橋君](https://beta.atcoder.jp/contests/arc039/submissions/2136670){:target="_blank"}
* 関節点 - [AOJの](http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2723146#1){:target="_blank"}


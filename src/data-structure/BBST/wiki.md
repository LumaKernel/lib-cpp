平衡二分探索木には二種類あるという結論に至った

その道筋を記したブログを，今書いている

いつ書き終わるか知らない．とりあえず結論

# Sequenceタイプ

遅延セグ木でできることに加えて，条件付きで区間reverseができる．連続している区間を扱う

名前は適当に決めた．Segmentだとセグ木のイメージが強かったりでこの名前で呼んでいる

keyはindex (つまりindexの順序を保っているといえる)

## 共通の関数と使い方

`操作(obj, ...)` の順序

* `merge(lnode, rnode)`
* `split(node, k)`
* `split(node, l, r)`
* `push_back(node, v)`
* `pop_back(node, v)`
* `insert(node, v)`
* `insert(node, k, node2)`
* `erase(node, k)`
* `erase(node, l, r)`
* `mset(node, k, v)`
* `mget(node, k)`
* `getValue(node)`
* `act(node, l, r, m)`
* `query(node)`
* `query(node, l, r)`
* `vector<X> getAll(node, l, r)`
* `reverse(node)`
* `reverse(node, l, r)`
* `size(node)`

実装が間に合っていないものもある

1引数のものは基本的にそのノードに対して問い合わせるもの

# Multisetタイプ

multisetにできることができる（インターフェースはちょっと違く実装したけど）

keyは保持する値そのもので，比較が定義されていることが前提となる．比較による順序が保たれている

k-thをとったりすることができる

あとは通常のmultisetに対する利点といえば，merge, splitだろうか

---

それぞれのタイプについて各種のBBSTに共通部分は多いが，それぞれのBBSTで構造に合わせて独自に書いている

# BBST共通の用語

僕が個人的に呼んでいるというだけのものです．セグ木でも呼んでます

## propagate

略 : prop

子どもの値から，サイズや自分の蓄積された値を計算する

ボトムアップ

propする際は子どもはevaledでなければならない

propされた後のノードをpropedと呼ぶ

## evaluate

略 : eval

遅延を処理 (評価) して子どもへ伝える

トップダウン

子どもノードを使う前に呼ぶ必要がある

evalされた後のノードをevaledと呼ぶ

---

上記はそれぞれupdate, pushや他の名前でよばれているのを見ることもある

# 参考

* [Self-balancing binary search tree - Wikipedia (en)](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree){:target="_blank"}<!--_-->


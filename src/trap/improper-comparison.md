---
title: 不適切な評価関数をsortなどに使っている
---

`sort` や `lower_bound` などは評価関数 `comp` を渡すことができるが，  
これは `operator<` 相当でなければいけない．  
`operator>` の否定は `operator<=` 相当になるため注意が必要．

つまり，比較関数において同値であるものに対し， `1` を返してはいけないということです．

そのため以下のような常に `1` を返す比較関数でも危険です．

```cpp
// bad
int a[] = {1, 3, 2};
sort(a, a + n, [&](int a, int b) {
  return 1;
})
```

このような比較関数はREになる可能性があります．

逆に常に `0` を返す場合は大丈夫です．

```cpp
// no problem
int a[] = {1, 3, 2};
sort(a, a + n, [&](int a, int b) {
  return 0;
})
```

ほかにも，複雑な独自の評価関数を使い，かつその評価関数において同値となる値がある可能性がある場合は気をつけたほうがいいでしょう．

特にこういったものはローカルとジャッジで挙動が変わり，ローカルでは大丈夫でもREを喰らったりします．

以下に，[Moのアルゴリズムの高速化]({{ "algorithm/Mo#Moの高速化" | absolute_url }}) として，評価関数を変更するときの危うい例を示します．

```cpp
// bad
bool comp(int a, int b) {
  int aBlock = a / width, bBlock = b / width;
  if(aBlock != bBlock) return aBlock < bBlock;
  return (right[a] < right[b]) ^ (aBlock & 1); // この行
}
```

上に示した行は， `aBlock` が奇数のときに否定になるようにしたものですが，  
上記したように， `operator<` の否定は `operator>=` になるため，危険です．

```cpp
// good
bool comp(int a, int b) {
  int aBlock = a / width, bBlock = b / width;
  if(aBlock != bBlock) return aBlock < bBlock;
  return (aBlock & 1) ? right[a] < right[b] : right[a] > right[b]; // この行
}
```

このように書き換えれば安全です．


---
title: C++における左辺と右辺の評価順序
---

参考: [右辺と左辺の計算順序 - Qiita](https://qiita.com/Nabetani/items/e0bcfd6a99bf417f419d){:target="_blank"}<!--_-->

C++の演算子は評価の順が不定の演算子が結構ある．

以下のコードは代入演算子の左辺と右辺の評価順序が不定なため，危険なコードになっている．

```cpp
// bad
vector<int> v(1);
v[0] = (v.push_back(3), 5);
```

`push_back` はメモリの再確保が行われる可能性があり，  
もし仮に左辺が先に評価され，右辺が評価されたときにメモリが再確保されると  
先に評価された左辺の値（これは参照，イテレータ）が右辺の評価後には使われていない参照となっている．（本来の `v[0]` を参照していない）

これを避けるためには，左辺と右辺の依存関係に気をつけることだ．

以下に危うい例をいくつか示す．

## 1

```cpp
// bad
vector<int> v(1);
int make() {
  int newIndex = v.size();
  v.push_back(0);
  return newIndex;
}
int main() {
  v[0] = make();
}
```

これはmake()でとった内容を一旦変数に入れればいい．

```cpp
// good
void main() {
  int index = make();
  v[0] = index;
}
```

## 2

```cpp
// bad
int sum = 0;
vector<int> ans(100);
int next() {
  sum++;
  return 0;
}
int main() {
  ans[next()] = sum;
}
```

これはメモリの再確保は行われていないが，  
ansの内容が異なってくる可能性があり，結果が不定である．  
これも一時変数に一旦いれることで避けれる．

```cpp
// good
int sum = 0;
vector<int> ans(100);
int next() {
  sum++;
  return 0;
}
int main() {
  int index = next();
  ans[index] = sum;
}
```


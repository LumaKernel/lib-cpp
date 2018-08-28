---
title: BigInteger
---

多倍長整数．  
基本的に不必要だが，必要になることがたまにある．  
いくつか解決方法を示す．

# long double, \_\_int128\_tを使う

C++の`long double`は仮数部64bitらしいので`long long`とかわらないのかな  
うーんよくわからん

`__int128_t`は入出力ができないので，入出力ができるようにする必要があります．  
（[128bit整数の入出力 \| Luzhiled's Page](https://luzhiled.github.io/CLibrary/Other/IO_int128.html){:target="_blank"}）

# boost

AtCoderならそれで良かろうですが，AtCoderはやさしいのでまずこの問題は発生しない．

[多倍長整数 \| Boost逆引きリファレンス](https://boostjp.github.io/tips/multiprec-int.html){:target="_blank"}

# bigintライブラリ

* [BigInt for C++ (Arpaさん) \| Codeforcesの記事](https://codeforces.com/blog/entry/22566){:target="_blank"}
  * [ArpaさんのBigInt.cpp](https://gist.github.com/ar-pa/957297fb3f88996ead11){:target="_blank"}

おｋ．


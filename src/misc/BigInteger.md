---
title: 多倍長整数, 任意精度演算
---

多倍長整数．  
基本的に不必要だが，64bitの2倍の精度が必要になることがたまにある．  

真に無限の精度が欲しい場合，その解法は間違っているかもしれない (TLEなど)  
modを取れないか，などを検討すべき

いくつか解決方法を示す

# long double, \_\_int128\_tを使う

C++の`long double`は仮数部64bitらしいので`long long`とかわらないのかな  
うーんよくわからん (本質的な改善にはなっていなさそう)

`__int128_t`は入出力ができないので，必要なら入出力ができるようにする必要があります  
（[128bit整数の入出力 - Luzhiled's Page](https://luzhiled.github.io/CLibrary/Other/IO_int128.html){:target="_blank"}）
<!--_-->

# boost

AtCoderならそれで良かろうですが，AtCoderはやさしいのでまずこの問題は発生しない  
(とは言いましたが，結構あります)

[多倍長整数 - Boost逆引きリファレンス](https://boostjp.github.io/tips/multiprec-int.html){:target="_blank"}<!--_-->

こんな感じ

// @ boost-bigint

# bigintライブラリ

* [BigInt for C++ (Arpaさん) - Codeforcesの記事](https://codeforces.com/blog/entry/22566){:target="_blank"}<!--_-->
  * [ArpaさんのBigInt.cpp](https://gist.github.com/ar-pa/957297fb3f88996ead11){:target="_blank"}<!--_-->

無限精度です

## forked

少し整理して，正・負の無限大を実装しています

// @ bigint

* 小数の代入
  * 小数が渡された場合はそれなりに正しい値を入れる
  * 1未満の正の小数なら0
* 無限大
  * 不定形でない四則演算関係のものは実装しています (累乗はない)
  * 0割りは対応なし (0に符号がない)
  * 不定形に対しては完全に無視するので，事前に防ぐようにする
* `numerlic_limits<bigint>`
  * そもそもprimitiveじゃないので他のライブラリと整合するため，程度
  * 今のところ全部は書いていない

DCHTやrational，他大体のライブラリに使えると思います


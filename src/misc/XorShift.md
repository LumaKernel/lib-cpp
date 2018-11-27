---
title: XorShift
---

mt19937などより速い ([僕の記事](http://tomorinao.blogspot.com/2018/08/xorshift128.html){:target="_blank"}<!--_-->)

[Treap]({{ "data-structure/BBST/Treap" | absolute_url }}) などでつかったけど  
マラソンで使ったりすることが多いのかな

## XorShift128

要件 [UniformRandomBitGenerator](https://ja.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator){:target="_blank"}<!--_--> を満たします (例えば，[shuffle](https://cpprefjp.github.io/reference/algorithm/shuffle.html){:target="_blank"}<!--_-->で使えるなどの嬉しさがあります)

// @ XorShift128

# 参考

* [Xorshift - Wikipedia](https://ja.wikipedia.org/wiki/Xorshift){:target="_blank"}<!--_-->
* [http://hexadrive.sblo.jp/article/63660775.html](http://hexadrive.sblo.jp/article/63660775.html){:target="_blank"}<!--_-->


---
title: 巨大な累乗・階乗計算の誤差をlogで抑える
---

式変形して $p^N \times N!$ とか出てきたときに，mod上であれば二分累乗とかすればいいんですが，小数で求める場合は $p = 10^{-5}, N = 10^5$ とかだと，桁が小さくなりすぎてしまいます

`double` の指数部は11bitなので，約 $2^{1000} \approx 10^{300}$ ぐらいまでのオーダーでしか値を保持できません

式が複雑な場合はboostの高精度の浮動小数点数などを使うのもあるかと思いますが時間がかかります

なので，足し算とかするだけになるまで，$\log$をとった値で保持します

階乗や組み合わせの事前計算もできます

$\log(N!) = \log(N \times (N-1)!) = \log N + \log(N-1)!$ より `dp[0] = 1, dp[i] = dp[i-1] + log(i)` で求まる


# 練習問題

* [D - Sushi Restaurant (700) - AtCoder](https://beta.atcoder.jp/contests/code-festival-2018-qualb/tasks/code_festival_2018_qualb_d){:target="_blank"}<!--_-->
  * この手の問題によくあることですが，考察によってはこのテクが不必要かもしれません
* [CODEFES2018 Final B - Theme Color - AtCoder](https://beta.atcoder.jp/contests/code-festival-2018-final-open/tasks/code_festival_2018_final_b){:target="_blank"}<!--_-->


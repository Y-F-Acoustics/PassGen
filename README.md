# PassGen
Random Password Generator written in C/C++.

# Version Log
## v1
- 8文字以上256文字以下のパスワード生成に対応
- 乱数生成にC言語標準ではないメルセンヌ・ツイスタ([mt19937-64](http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/mt64.html))を採用
- パスワードは表示後すぐにNull文字で上書き
- 配列のポインタも不要になったら即座にNull文字で上書き
- 整数は全て符号無し8bitで定義した省メモリ設計
- エンターキーで終了


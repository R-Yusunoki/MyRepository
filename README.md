# MyRepository

1/6にいただいた課題（C++によるゲーム・行列クラス）についてのコードです。


# DEMO

"hoge"の魅力が直感的に伝えわるデモ動画や図解を載せる


# Features

【ゲーム】
Windowsコンソールアプリです。
【行列クラス】
行列の積についてのクラスです。
積を定義できる２つの行列を２次元配列で指定します。


# Requirement

Windows10での動作確認済み。


# Usage

【ゲーム】
十字キー・Tab・Space・0キー を使用します。
操作方法は別途「操作方法.txt」に記載しています。

【行列クラス multimat】
２つの行列に対応する２次元配列 A[..][..], B[..][..] に対して、
コンストラクタ「multimat<decltype(A), decltype(B)>(A, B)」により、A×B についてのインスタンスをつくります。　
publicメンバ関数は以下の通り。

(bool)get_within_sd():
(int)get_rows():
(int)get_columns():
(Aの要素の型)get_entry(unsigned int i, unsigned int j): 積の(i, j)成分を、Aの要素の型として返す。
　※A×B が定義できない場合、1×1行列{0} をAの要素の型として返します。

# Note

フォルダーごとに、コンパイルに必要なファイルを一式まとめています。

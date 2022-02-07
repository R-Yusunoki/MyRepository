# MyRepository

1/6にいただいた課題（C++によるゲーム・行列クラス）についてのコードです。


# DEMO

"hoge"の魅力が直感的に伝えわるデモ動画や図解を載せる


# Features

【ゲーム】
Windowsコンソールアプリです。<br>
【行列クラス】
行列の積についてのクラスです。
積を定義できる２つの行列を２次元配列で指定します。


# Requirement

Windows10での動作確認済み。


# Usage

【ゲーム】<br>
十字キー・Tab・Space・0キー を使用します。
操作方法は別途「操作方法.txt」に記載しています。<br><br>
【行列クラス multimat】<br>
２つの行列に対応する２次元配列 A[..][..], B[..][..] に対して、<br>
コンストラクタ「multimat<decltype(A), decltype(B)>(A, B)」により、A×B についてのインスタンスをつくります。<br><br>
（publicメンバ関数は以下の通り。）<br>
(bool) get_within_std(): A×B を定義できるとき true を返す。<br>
(int) get_rows(): 積の行数を返す。<br>
(int) get_columns(): 積の列数を返す。<br>
(Aの要素の型) get_entry(unsigned int i, unsigned int j): 積の(i, j)成分を、Aの要素の型として返す。<br>
　※A×B が定義できない場合、1×1行列{0} をAの要素の型として返します。<br>
display_mat(): 積を、最大10行、10列まで表示する。

# Note

フォルダーごとに、コンパイルに必要なファイルを一式まとめています。

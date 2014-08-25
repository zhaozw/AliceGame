#ifndef STATIC_CONPILEMODE
#define STATIC_COMPILEMODE

// 暗号化設定など、コンパイルごとに変更する定数を定義する。

// 現在のバージョン。
// バージョン違いを検出する時などに用いる。
#define MYGAME_CURRENT_VERSION		20140812

// 暗号化したデータを使うか否か。
// (DXArchiveで作成した素材アーカイブを用いる)
#define MYGAME_USE_ENCODED_DATA

// 暗号化したデータを使うか否か。
// 元々Csvデータであるものを独自関数により暗号化したものを用いる。
#define MYGAME_USE_ENCODED_CSV

// データの暗号化のみを行って終了する場合。
// Csvデータを独自関数を用いて暗号化する。
// #define MYGAME_PERFORM_ENCODING

#endif

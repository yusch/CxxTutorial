#define WIN32_LEAN_AND_MEAN		// Windows ヘッダーから使用されていない部分を除外します。
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// 入力対象のプログラムをアクティブにするまでの待ち時間（ミリ秒単位）
DWORD dwSleepTime = 5000;
// キーの取りこぼしを防ぐための、各入力間の待機時間（ミリ秒単位）
DWORD dwWaitTime = 10;
// ※1ミリ秒＝0.001秒のこと

// ********************************************************************
// * checkKey                                                         *
// *   キーボードシミュレート対象文字列かどうかを調べる。             *
// *   引数cが対象ならばtrueを返し、そうでなければfalseを返す。       *
// ********************************************************************
bool checkKey(unsigned char c)
{
	if ( '0' <= c && c <= '9' ) { // 数字ならＯＫ
		return true;
	}
	else if ( 'A' <= c && c <= 'Z' ) { // 英大文字ならＯＫ
		// 余談：処理系によっては、A～Zは連続していないかもしれないが、
		// 　　　少なくとも動作対象の日本語Winodwsで用いられているShift-JIS
		// 　　　は連続しているので、この記述を使う。
		return true;
	}
	else if ( c == ' ' ) { // スペースならＯＫ
		return true;
	}
	else if ( c == '\t' ) { // タブならＯＫ
		return true;
	}

	// それら以外の場合はＮＧ
	return false;
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		// 引数が指定されていない場合、使用方法を表示
		puts("キーボード入力をシミュレートしたい文字列を引数に指定してください。");
		puts("");
		puts("keysimcpp <文字列> [<待機時間> [<文字間ウェイト>]]");
		puts("");
		puts("文字列に指定可能な文字は、英大文字・数字・スペース・タブです。");
		puts("（英小文字は無視されますのでご注意下さい）");
		puts("スペース・タブを指定する場合は、文字列全体をダブルコーテーションで囲います。");
		puts("待機時間は、入力開始までの待ち時間をミリ秒単位で指定します(1以上)。");
		puts("文字間ウェイトは、入力文字間のウェイト時間をミリ秒単位で指定します(1以上)。");
		return 1;
	}

	// 待機時間取得
	if ( argc > 2 ) {
		dwSleepTime = atoi(argv[2]);
		if (dwSleepTime == 0) {
			puts("待機時間の指定が不正です。ミリ秒単位で1以上の数を指定してください。");
			return 1;
		}
	}

	// 文字間ウェイト取得
	if ( argc > 3 ) {
		dwWaitTime = atoi(argv[3]);
		if (dwWaitTime == 0) {
			puts("文字間ウェイトの指定が不正です。ミリ秒単位で1以上の数を指定してください。");
			return 1;
		}
	}

	// 入力対象のプログラムをアクティブにするまでの待ち
	puts("入力対象のプログラムをアクティブにしてください。");
	printf("%uミリ秒間待機します...", dwSleepTime);
	Sleep(dwSleepTime);
	puts("\n入力中...");

	// コマンドラインの文字列を取得する
	const unsigned char *p = (const unsigned char *)(argv[1]);

	// 取得された文字列を１文字ずつ検査し、
	// シミュレート可能文字列であればkeybd_event() APIに
	// 渡す。
	for(; *p ; ++p) {
		// 入力対象の文字列かどうかを調べる
		if ( checkKey(*p) ) {
			// キーの押し下げをシミュレートする。
			keybd_event( *p, 0, 0, 0);
			// キーの解放をシミュレートする。
			keybd_event( *p, 0, KEYEVENTF_KEYUP, 0);

			// dwWaitTimeミリ秒間待機する
			// (キーの取りこぼしを防ぐため)
			Sleep(dwWaitTime);
		}
	}

	puts("キーボードシミュレートが終了しました。");

	return 0;
}

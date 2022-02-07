#ifndef _PLAYER_H_
#define _PLAYER_H_

class Cplayer{
private:
	int posi_x;//画面上の位置
	int posi_y;//上に同じ
	int direct_x;
	int direct_y;

	int coef;//1 or -1
	int stop_count;//1以上のときは何もしない。

public:
	Cplayer(int n);
	void decide_direct(int key);//keyから(direct_x, direct_y)を決定する。
	void player_move();//(posi_x, posi_y)を決定する。

	bool match(int* px, int* py);//(*px, *py)に一致しているとき true

	//ゲッター
	int* get_px(void);
	int* get_py(void);
	int get_nextx(void);//posi_x + direct_x を取得。
	int get_nexty(void);//上に同様
	int get_stopcount(void);
	//セッター
	void stopcount_add(void);
	void stopcount_down(void);
	void stopcount_exchange(void);//stop_countを、0以上と-1とで切り替える。
	void change_x(int x);//posi_xを変更する。
};

int key_get(void);//キー番号を返す。
void key_reset(void);//未取得のキー操作を無効化する。
int title_key_set(void);//タイトル画面でのキー番号を返す。
int random(int n);//0～n-1の整数をランダムに返す。

#endif // _PLAYER_H_

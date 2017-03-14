

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include <conio.h>

#define POS_TX 1					//現在地表示のX位置
#define POS_TY 1					//現在地表示のY位置
#define POS_MX 120					//map表示のX位置
#define POS_MY 2					//map表示のY位置
#define POS_CX 0					//現在の内容のX位置 
#define POS_CY 5					//現在の内容のY位置
#define POS_IX 120					//アイテム表示のX位置
#define POS_IY 8					//アイテム表示のY位置
#define POS_SX 0					//選択肢の表示のX位置
#define POS_SY 28					//選択肢の表示のY位置
#define SEL_S 0						//選択の結果
#define O_s 100						//delayの時間

int memoid = 0;						//難易度の変数
 int check_place=0;					//エナミーの存在の確認
 int m;								//移動マス数
 int item_cor;						//現在のインベントリの位置
 int em_att;						//monsterの属性
 int i;								//現在地の情報
 int j;								//ゲーム終了用変数
 int mass;							//制限マス数
 int mat1, mat2, mat3, mat4;		//keyitem

 int game = 1;						//リスタートの変数
 int s1=0;							//スコアボードの検索用変数
 int s2 = 0;						//スコアボードの表示用変数
 int esc;							//脱出状態を表現０：脱出している1：脱出してない
 int esc1;							//ゲームの結果の表示用変数０：表示する1：表示ない
 int enter_x;						//enter関数用変数１
 int enter_y;						//enter関数用変数２
 int enter_c;						//enter関数用変数３
 int boat_esc=0;					//脱出の方法用変数
 int same=0;						//引き分けの判断用変数
 int pp = 0;						//メモ帳の検索用変数最初状態は0
 int mr = 0;						//メモ帳の表示用変数１
 int mp;							//メモ帳の表示用変数２
 char sl;							//選択のときのenter用変数
 int sl1 = 0;						//選択用変数
 int fight_re;						//戦闘結果用変数
 int score_gameover;				//スコア用変数
 int sear_cor;						//探索済みを確認用変数
 int escape_num;					//脱出番号用変数
 int escape_item;					//脱出item用変数
 int escape_person;					//脱出person用変数
 int game_num;						//gameover判定用変数
 int move_search;					//訪問or探索or戦闘用変数
 int act_sel;						//選択肢入力用変数
 int wp1;							//武器の選択用変数
 int at1;							//戦闘選択用変数
 int lose_point;					//敗北回数用変数
 int re;							//戦闘結果用変数
 int boss_1 = 1;					//boss 条件アイテム１用変数
int boss_2;							//boss 条件アイテム２用変数
 int key, key1;						//鍵のアイテムを探すための番号
 char d;

struct memochou {		//Hintであるメモ帳の情報
	 int id;			//HintのID
	 char name[40];		//Hintの名前
	 char explan[40];	//Hintの内容		

 }save[100];

struct map {				//マップの情報
	int id;					//マップのID
	char name[40];			//マップの名前
	char item[40];			//マップ上のアイテム
	char monster[40];		//マップ上のエナミーの名前
	char person[40];		//マップ上のキーパーソン
	char escape[40];		//マップ上の脱出方法

}data[100];

struct player {				//プレイヤーの情報
	int item_id;			//プレイヤーのアイテムのID
	char item_name[40];		//プレイヤーのアイテムの名前
	char item_explan[80];	//プレイヤーのアイテムの説明
}stock[100];

struct score {				//スコアの情報
	int item_point;			//アイテムの情報
	int mass_point;			//残りのマスの情報
	int escape_point;		//脱出方法の情報
}score[10];

struct monster {			//プレイヤーの情報
	int monster_id;			//エナミーのID
	char monster_name[40];	//エナミーの名前
	char monster_att[40];	//エナミーの情報
	int monster_att_id;		//エナミーのアイテムのID

}enermy[100];

struct combination {		//組み合わせアイテム（キーアイテム）の情報
	int combination_id;		//組み合わせアイテム（キーアイテム）のID
	char material1[40];		//材料になるアイテム１の名前
	char material2[40];		//材料になるアイテム２の名前
	char combination[40];	//組み合わせアイテム（キーアイテム）の名前

}item[100];

struct score_save {			//点数の一時保存情報
	int score;				//点数
	char name[30];			//名前
	int id;					//ID
};

struct cor_info{		//現在の情報
	char cor[100];
}info[100];

struct score score[10] = {	//スコア構造体の初期化
	0, 30, 0				
	//アイテムは最初持っていないので0
	//残りのマスの制限が30マスなので30
	//脱出方法は最初脱出してないので0

};

struct score_save scoreboard[100] = {  //スコアボード構造体の初期化
	0,"",1,								//1～9順位の点数と名前がないので０と””
	0,"",2,
	0,"",3,
	0,"",4,
	0,"",5,
	0,"",6,
	0,"",7,
	0,"",8,
	0,"",9,
};

struct map data[100] = {	//マップ構造体の現在情報を保存
	00, "旧研究棟", "0", "アラクネ", "0", "0"
	, 01, "旧研究棟", "研究資料1", "ゾンビコロニー", "0", "0"
	, 02, "隔離研究棟", "0", "ゾンビプラント", "0", "0"
	, 03, "隔離研究棟*第二シェルター", "0", "0", "同僚", "0"

	, 10, "森林", "軽飛行機の鍵", "ゾンビ植物", "0", "0"
	, 11, "森林", "スマホ", "0", "0", "0"
	, 12, "森林", "スケジュール長", "ゾンビ植物", "0", "0"
	, 13, "森林", "枝", "0", "0", "0"

	, 20, "川", "0", "0", "0", "0"
	, 21, "本研究棟", "注射器", "0", "0", "0"
	, 22, "本研究棟", "研究資料２", "ゾンビコロニー", "0", "0"
	, 23, "本研究棟", "修理キット", "0", "0", "0"

	, 30, "川", "日記", "蟲ゾンビ", "0", "0"
	, 31, "滑走路", "0", "0", "0", "軽飛行機"
	, 32, "本研究棟", "USB", "ゾンビコロニー", "0", "0"
	, 33, "本研究棟", "0", "0", "0", "0"

	, 40, "社員寮*シェルター", "空のライター", "0", "社長", "0"
	, 41, "磯", "ライターオイル", "0", "0", "ボート"
	, 42, "砂浜", "0", "蟲ゾンビ", "0", "0"
	, 43, "船付き場", "0", "0", "0", "クルーザ" 
	//x座標とy座標の情報を00～43で表現
	//現在のマスの名前を表示
	//現在のマスにあるアイテムを表示
	//現在のマスにあるエナミーを表示
	//現在のマスにある人を表示
	//現在のマスにある脱出方法を表示
};

struct monster enermy[100] = {	//エナミー構造体の初期化
	0, "ゾンビコロニー", "打", 0
	, 1, "ゾンビ植物", "遠", 1
	, 2, "蟲ゾンビ", "切", 2
	, 3, "ゾンビプラント", "遠", 1
	, 4, "アラクネ", "切", 2
	//エナミーのIDを表示
	//エナミーの名前を表示
	//エナミーの属性を表示
	//エナミーの属性IDを表示
};

struct combination item[100] = {	//キーアイテム構造体：このルールに合わせて組み合わせが起こる。
	0, "空のライター", "ライターオイル", "中身があるライター"
	, 1, "毒針", "枝", "毒枝"
	, 2, "注射器", "抗体", "ワクチン"

	//キーアイテムのID
	//キーアイテムを作るために必要なアイテム１
	//キーアイテムを作るために必要なアイテム１
	//キーアイテムの名前
};

struct player stock[100] = {		//プレイヤーインベントリの現在情報を保存
	0, "ハンマー", ""
	, 1, "サブマシンガン", ""
	, 2, "コンバットナイフ", "" 
	//プレイヤーのアイテムのID
	//プレイヤーのアイテムの名前
	//プレイヤーのアイテムの説明
};

const struct map reset_m[100] = {	//マップ構造体の初期状態
	00, "旧研究棟", "0", "アラクネ", "0", "0"
	, 01, "旧研究棟", "研究資料1", "ゾンビコロニー", "0", "0"
	, 02, "隔離研究棟", "0", "ゾンビプラント", "0", "0"
	, 03, "隔離研究棟*第二シェルター", "0", "0", "同僚", "0"

	, 10, "森林", "軽飛行機の鍵", "ゾンビ植物", "0", "0"
	, 11, "森林", "スマホ", "0", "0", "0"
	, 12, "森林", "スケジュール長", "ゾンビ植物", "0", "0"
	, 13, "森林", "枝", "0", "0", "0"

	, 20, "川", "0", "0", "0", "0"
	, 21, "本研究棟", "注射器", "0", "0", "0"
	, 22, "本研究棟", "研究資料２", "ゾンビコロニー", "0", "0"
	, 23, "本研究棟", "修理キット", "0", "0", "0"

	, 30, "川", "日記", "蟲ゾンビ", "0", "0"
	, 31, "滑走路", "0", "0", "0", "軽飛行機"
	, 32, "本研究棟", "USB", "ゾンビコロニー", "0", "0"
	, 33, "本研究棟", "0", "0", "0", "0"

	, 40, "社員寮*シェルター", "空のライター", "0", "社長", "0"
	, 41, "磯", "ライターオイル", "0", "0", "ボート"
	, 42, "砂浜", "0", "蟲ゾンビ", "0", "0"
	, 43, "船付き場", "0", "0", "0", "クルーザ" };

const struct player reset_p[100] = {		//プレイヤー構造体の初期状態
	0, "ハンマー", ""
	, 1, "サブマシンガン", ""
	, 2, "コンバットナイフ", "" 
};

struct memochou save[100] = {		//メモ帳（Hint)の現在情報を保存
	0,"1","1",
	1,"1","1",
	2,"1","1",
	3,"1","1",
	4,"1","1",
	5,"1","1",
	6,"1","1",
	7,"1","1",
	8,"1","1",
	//IDはHintを探した順番
	//Hintの名前は難易度をEasyにしたときだけに表示
	//Hintの説明は難易度をNormalとEasyにしたときに表示
};

const struct memochou reset_me[100] = { //メモ帳（Hint)構造体の初期状態
	0,"1","1",
	1,"1","1",
	2,"1","1",
	3,"1","1",
	4,"1","1",
	5,"1","1",
	6,"1","1",
	7,"1","1",
	8,"1","1",
};

//関数の宣言

void posxy(int x, int y);
void condition();
int score_re();
void title_dis();
void prologue_dis();
void script(int em_id, int wp1, int lose_point, int move_search, int re);
void cor_dis();
int act_select();
int gameover_wl(int game_num, int score_gameover);
int gameover();
void map_dis();
int player_move();
int fight(int em_id, int re);
void display();
int player_research();
int escape();
void item_dis();
char c;
int play = 1;
void explan();
void enter(int enter_x, int enter_y);
void memo();
void inprint();
void monster_dis();

int main(void) {
	while (game) {									//consoleが始まったとき
		memcpy(&data, &reset_m, sizeof(reset_m));	//マップの初期化
		memcpy(&stock, &reset_p, sizeof(reset_p));	//プレイヤーインベントリの初期化
		pp = 0;										//メモ帳の検索用変数最初状態は0
		memcpy(&save, &reset_me, sizeof(reset_me));	//メモ帳の初期化
		esc1 = 1;									//ゲームの結果の表示用変数０：表示する1：表示ない最初状態は１
		same = 0;									//戦闘の引き分けの結果用変数０：引き分けじゃない1：引き分け最初状態は0
		
		while (play) {								//ゲームのプレイが始まったとき
			system("mode con:cols=140 lines=35");	//consoleの大きさを決める。
			system("title HAZARD ISLAND");			//consoleの名前を決める。
		
			struct cor_info info[100];				//今の状態を宣言
			
			esc = 1;								//脱出状態を表現０：脱出している1：脱出してない最初状態は１
													
			

			item_cor = 3;							//現在のインベントリの位置最初に武器を3つ持っているので3から始まる。
		
			mat1 = 0;								//キーアイテムの材料になるアイテムの検索用変数１最初状態は0
			mat2 = 0;								//キーアイテムの材料になるアイテムの検索用変数２最初状態は0
			mat3 = 0;								//キーアイテムの検索用変数最初状態は0
			m = 0;									//移動マス数最初状態は0

			i = 16;									//始まる位置 マップ上の17番目一番左下から始まる。（ｘ、ｙ）＝（4、0）
			escape_item = 0;						//脱出用アイテムの検索用変数最初状態は0
			score_gameover = 0;						//終わったときのスコアの情報最初状態は0



			mass = 0;								//マス変数で移動したマスを表す。最初状態は0

			act_sel = 0;							//動作選択を表して、最初状態は0


			title_dis();							//タイトルの表示
			prologue_dis();							//プロログの表示
			
			explan();								//ゲーム説明の表示

			for (j = 0; j < 100; j++) {				//ゲーム終了用変数100を超えるとプレイが終わる。
				if (mass < 31) {					//マス変数		  30を超えるとプレイが終わる。30回移動するとプレイが終わる。
					c = getchar();					//enterの入力
					system("cls");					//画面の初期化
					sear_cor = i;					//探索済みを確認
					map_dis(); 						//マップの表示
					cor_dis();						//現在地の表示
					item_dis(); memo();				//アイテムの表示
					act_sel = act_select();			//動作選択の表示
					check_place = 0;				//エナミーの存在の確認最初状態は0

					if (act_sel == 1) {					//１を選んだとき、探索
						item_cor = player_research();	//探索結果の表示

					
						//材料アイテムが2つあるときキーアイテムに組み合わせする。
						for (mat1 = 0; mat1 < 50; mat1++) {			//材料アイテム1をインベントリの中で50まで検索
							for (mat2 = 0; mat2 < 50; mat2++) {		//材料アイテム2をインベントリの中で50まで検索
								for (mat3 = 0; mat3 < 3; mat3++) {	//キーアイテムを構造体の中で３まで検索
									if (!strcmp(stock[mat1].item_name, item[mat3].material1)) {		//材料アイテム1がインベントリの中で存在するとき
										if (!strcmp(stock[mat2].item_name, item[mat3].material2)) {	//材料アイテム2がインベントリの中で存在するとき
											printf("\n%sと%sを組み合わせて%sを獲得した。", stock[mat1].item_name, stock[mat2].item_name, item[mat3].combination);;
											//組み合わせを表示

											if (mat1<mat2) {		 //材料アイテム1の位置が材料アイテム2より前のとき
												strcpy_s(stock[mat1].item_name, sizeof(stock[mat1].item_name), item[mat3].combination);
												//組み合わせたキーアイテムを材料アイテム1の位置に追加
												strcpy_s(stock[mat2].item_name, sizeof(stock[mat2].item_name), "0");
												//材料アイテム2の情報を初期化
												item_cor = mat2;
												//現在インベントリの位置を材料アイテム2の位置にする。
											}
											else if (mat1>mat2) {//材料アイテム2の位置が材料アイテム1より前のとき
												strcpy_s(stock[mat2].item_name, sizeof(stock[mat2].item_name), item[mat3].combination);
												//組み合わせたキーアイテムを材料アイテム2の位置に追加
												strcpy_s(stock[mat1].item_name, sizeof(stock[mat1].item_name), "0");
												//材料アイテム1の情報を初期化
												item_cor = mat1;
												//現在インベントリの位置を材料アイテム1の位置にする。
											}
										}
									}
								}
							}
						}		
					}
					else if (act_sel == 2) {  //2を選んだとき、移動

						i = player_move();	//移動の表示

						if (i > 99 && i < 120) {	//動けない所に向かったとき100を足したので100～119の範囲になる。
							i = i - 100;				//足した100を引いて既存の位置を表示
						}



					}
				
					posxy(117, 27); printf("▼");	//scriptの最後を"▼"で表示
				}
				else {
					gameover_wl(0, 0);	//敗北のとき０、点数０の結果表示
					j = j + 150;		//150を足して
					play = 0;			//プレイを終わらせる。
				}

			}

		
			play = 0;					//プレイを終わらせる。

		}

		scoreboard[6].score = score_gameover;							//点数をスコアボードに入れる。

	
		system("cls");													//画面の初期化

		
		if (scoreboard[6].score != 0) {									//スコアボードの点数が0じゃないとき、
			if (score_gameover != 0) {									//点数が0じゃないとき、
				posxy(68, 5); printf("score:%d\n", score_gameover);		//点数の表示
				posxy(63, 6); printf("名前を書いてください。\n");			//名前を書いてください。の表示
				posxy(70, 7); scanf_s("%s", &scoreboard[6].name,sizeof(scoreboard[6].name));	//名前の入力
				c = getchar();

				for (s1 = 5; s1 > -1; s1--) {			//スコアボードの順位を探索
					s2 = s1 + 1;
					if (scoreboard[s1].score < scoreboard[s2].score) {	//点数が高いほうを上に入れる。
						scoreboard[8] = scoreboard[s1];
						scoreboard[s1] = scoreboard[s2];
						scoreboard[s2] = scoreboard[8];
					}


				}

			}
		}

		posxy(68, 9); printf("scoreboard\n");		//スコアボードを表示

		posxy(52, 13); printf("------------------------------------------\n");
		posxy(52, 14); printf("| 1位：%s", scoreboard[0].name);
		posxy(52, 15); printf("| 2位：%s", scoreboard[1].name);
		posxy(52, 16); printf("| 3位：%s", scoreboard[2].name);
		posxy(52, 17); printf("| 4位：%s", scoreboard[3].name);
		posxy(52, 18); printf("| 5位：%s", scoreboard[4].name);
		posxy(77, 14); printf("スコア：%d \n",  scoreboard[0].score);
		posxy(77, 15); printf("スコア：%d \n",  scoreboard[1].score);
		posxy(77, 16); printf("スコア：%d \n",  scoreboard[2].score);
		posxy(77, 17); printf("スコア：%d \n",  scoreboard[3].score);
		posxy(77, 18); printf("スコア：%d \n",  scoreboard[4].score);

		posxy(93, 14); printf("|");
		posxy(93, 15); printf("|");
		posxy(93, 16); printf("|");
		posxy(93, 17); printf("|");
		posxy(93, 18); printf("|");
		posxy(52, 19); printf("------------------------------------------\n");
		c = getchar();

		posxy(60, 25);	printf("リスタートしますか？\n");			//リスタート選択の表示
		posxy(60, 26); printf("1.はい２．いいえ\n");

		posxy(60, 27);
		sl = getchar();
		sl1 = atoi(&sl);				//リスタート選択の入力
		while (sl == '\n') {			//enterを入れるまで、リスタート選択の入力
			posxy(60, 27);
			sl = getchar();
			sl1 = atoi(&sl);
		}
		game = sl1;				//リスタート選択の内容によってゲームをリスタート１：リスタート２：終わり


		c = getchar();
		if (game == 1) {		//１：リスタート
			game = 1;
			play = 1;


		}
		else if (game == 2) {	//２：終わり
			game = 0;
		}
		else {					//その他の入力は"この作動はいけません。"を表示
			printf("この作動はいけません。\n");

		}
	}
}
		
void condition() {								//アラクネの登場を判断
	
	if (!strcmp(data[17].item, "1")) {			//材料アイテムであるライターオイルを拾ったとき
			if (!strcmp(data[16].item, "1")) {	//材料アイテムである空のライターを拾ったとき
		//材料アイテム2つをそろってキーアイテムを持っているのでアラクネが登場
				boss_1 = 0;
			}
			else {

		//そのほかはアラクネが登場しない
				boss_1 = 1;
			}
		}


}

int score_re() {	//スコアの計算

	score_gameover = 0;										//スコアの初期化
	score_gameover = score_gameover + ((30 - mass) * 100);		//残りのマスのスコア
	score_gameover = score_gameover + (item_cor * 200);		//アイテムのスコア
	score_gameover = score_gameover + (game_num * 10000);	//脱出方法のスコア

															//printf("あなたの点数は%d", score_gameover);			//スコアの表示

	return score_gameover;

}

void title_dis() {			//タイトルの表示

	posxy(40, 2 + 3); printf("   ■    ■    ■    ■■■■    ■    ■■■   ■■■    \n");
	posxy(40, 3 + 3); printf("   ■    ■   ■■        ■    ■■   ■   ■  ■   ■   \n");
	posxy(40, 4 + 3); printf("   ■■■■  ■  ■      ■    ■  ■  ■■■   ■   ■   \n");
	posxy(40, 5 + 3); printf("   ■    ■  ■■■    ■      ■■■  ■  ■   ■   ■   \n");
	posxy(40, 6 + 3); printf("   ■    ■ ■    ■  ■      ■    ■ ■   ■  ■   ■   \n");
	posxy(40, 7 + 3); printf("   ■    ■ ■    ■ ■■■■ ■    ■ ■    ■ ■■■    \n");

	posxy(41, 9 + 3); printf("      ■  ■■■  ■        ■    ■     ■ ■■■        \n");
	posxy(41, 10 + 3); printf("      ■ ■       ■       ■■   ■■   ■ ■   ■       \n");
	posxy(41, 11 + 3); printf("      ■  ■■■  ■      ■  ■  ■ ■  ■ ■   ■       \n");
	posxy(41, 12 + 3); printf("      ■       ■ ■      ■■■  ■  ■ ■ ■   ■       \n");
	posxy(41, 13 + 3); printf("      ■ ■    ■ ■     ■    ■ ■   ■■ ■   ■       \n");
	posxy(41, 14 + 3); printf("      ■  ■■■  ■■■ ■    ■ ■     ■ ■■■        \n");

	c=getchar();
	
	posxy(45, 18 + 3); printf("場所は日本列島から遥か南に位置する孤島。");
	posxy(45, 19 + 3); printf("その島にて、生物が異形と化し暴走し始めた。");
	posxy(45, 20 + 3); printf("「ここから脱出して生き残る」と決意を胸に抱いた。");
	posxy(45, 21 + 3); printf("異形の者達から生き残れるか。");

	posxy(55, 25 + 3); printf("PRESS THE ANY BUTTON"); 
	
	enter(75, 28);



}

void prologue_dis() {		//プロログの表示
	system("cls");

	posxy(65, 3); printf("バイオハザード。"); c = getchar();
	posxy(22, 4); printf("ゲームなどでその単語を耳にした事はあった。しかし、自分がその状況に置かれるなど考えもしなかった。"); c = getchar();
	posxy(22, 5); printf("場所は日本列島から遥か南。大手製薬会社、カルミアの所有する小さな島。"); c = getchar();
	posxy(22, 6); printf("そこでは、秘密裏に生物兵器の研究が行われていた。"); c = getchar();
	posxy(22, 7); printf("僕一一柳原一志は、そこで研究を任されてその主導をしていたのだが……。"); c = getchar();
	posxy(65, 8); printf("「……………」"); c = getchar();
	posxy(22, 9); printf("コンクリートの部屋を、蛍光灯の無機質な光が照らしている。"); c = getchar();
	posxy(22, 10); printf("僕と、カルミアの社長一一筒地昌は、生物兵器の暴走を逃れシェルターに立て籠もっていた。"); c = getchar();
	posxy(22, 11); printf("どうやら部下である他の研究員が、機材の操作を誤ってこのような状況になってしまったらしい。"); c = getchar();
	posxy(22, 12); printf("数時間が経過したが、他の人間は未だに誰も訪ねて来ない。時おり、扉の外を呻き声がよぎるだけだ。"); c = getchar();
	posxy(22, 13); printf("社長「チッ」"); c = getchar();
	posxy(22, 14); printf("社長が舌打ちする。煙草に火をつけようとしたが、オイル切れていたようだ。"); c = getchar();
	posxy(22, 15); printf("社長「おい、柳原」"); c = getchar();
	posxy(22, 16); printf("社長が僕の名を呼んだ。"); c = getchar();
	posxy(22, 17); printf("「はい」"); c = getchar();
	posxy(22, 18); printf("社長「外に出てここから出る方法を探して来い」"); c = getchar();
	posxy(22, 19); printf("「……わかりました」"); c = getchar();
	posxy(22, 20); printf("僕はシェルターから外に出た。"); c = getchar();
	posxy(22, 21); printf("社員寮の廊下。窓の外から呻くような声が聞こえ、僕は外の景色を見る。"); c = getchar();
	posxy(22, 22); printf("霧に遮られ、遠くまで見通す事ができない。"); c = getchar();
	posxy(22, 23); printf("生物の遺伝子を書き換え暴走させる酵素を撒き散らす『ゾンビプラント』の発生させた物だろう。"); c = getchar();
	posxy(22, 24); printf("島の空気をあと半日も吸えば、この霧の奥にいるゾンビ達の仲間入りをする事になるだろう。"); c = getchar();
	posxy(22, 25); printf("それまでに、この島から出る方法を見つけて逃れねばならない。"); c = getchar();
	posxy(65, 26); printf("「……………」"); c = getchar();
	posxy(22, 27); printf("自分の身を案じるべき状況なのであろうが、僕はとある大切な人が無事か気掛かりだった。"); c = getchar();
	posxy(22, 28); printf("一体何処にいるのだろうか……。"); c = getchar();



	system("cls");
}

void cor_dis() {		//現在位置の情報の表示
	posxy(0, 1);
	printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
	posxy(POS_TX, POS_TY);
	printf("\n現在位置:%s\n", data[i].name);		//現在位置の表示
	posxy(0, 3);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
}

int act_select() {					//選択肢（何をやるか）の入力  1:探索 2:移動
	
									//system("cls");
	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("何をやりますか？\n");
	printf("1:探索 2:移動\n");
	posxy(POS_SX, POS_SY+3);

	sl = getchar();
	sl1 = atoi(&sl);		//選択肢（何をやるか）の入力
	while(sl=='\n'){		//enterを押すまで入力
			posxy(POS_SX, POS_SY + 3);
			sl = getchar();
			sl1 = atoi(&sl);
	}
	act_sel = sl1;			//入力結果を入れる。

	return act_sel;

};

void posxy(int x, int y) {		 //UIの位置の設定
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_gameover() {			//敗北したとき、結果表示
	esc1 =0;
	score_gameover = 0;
	system("cls");
	posxy(22, 7); printf("              ■■■■■                                                                       \n");
	posxy(22, 8); printf("           ■■■   ■■■                                                                     \n");
	posxy(22, 9); printf("          ■■           ■                      ■■■■■ ■■■        ■■■■             \n");
	posxy(22, 10); printf("         ■■                     ■■■         ■■■■■■ ■■      ■■    ■■           \n");
	posxy(22, 11); printf("         ■■      ■■■■           ■■     ■■     ■■    ■■   ■■■■■■■          \n");
	posxy(22, 12); printf("         ■■            ■■    ■■■■■    ■■     ■■    ■■   ■■                    \n");
	posxy(22, 13); printf("           ■■         ■■     ■■    ■■  ■■     ■■    ■■    ■■                   \n");
	posxy(22, 14); printf("             ■■■■■■        ■■■■■    ■■     ■■    ■■     ■■■■■            \n");
	posxy(19, 19); printf("                        ■■■■■                                                             \n");
	posxy(19, 20); printf("                     ■■        ■■                                                          \n");
	posxy(19, 21); printf("                    ■■          ■■   ■■       ■■    ■■■■       ■■■■            \n");
	posxy(19, 22); printf("                    ■■          ■■   ■■      ■■   ■■    ■■     ■■■              \n");
	posxy(19, 23); printf("                    ■■          ■■    ■■    ■■   ■■■■■■■    ■■                \n");
	posxy(19, 24); printf("                    ■■          ■■     ■■  ■■     ■■             ■■                \n");
	posxy(19, 25); printf("                      ■■      ■■         ■■■        ■■            ■■                \n");
	posxy(19, 26); printf("                         ■■■■             ■■           ■■■■      ■■                \n");


	


}

void print_win() {					//勝利したとき、結果表示
	esc1 = 0;
	system("cls");
	posxy(40, 4); printf("          ■■■   ■ ■         ■     ■     ■        ");
	posxy(40, 5); printf("          ■  ■  ■■■■       ■     ■     ■          ");
	posxy(40, 6); printf("          ■■■  ■    ■       ■     ■     ■          ");
	posxy(40, 7); printf("          ■  ■  ■    ■       ■■■■■■■■          ");
	posxy(40, 8); printf("          ■■■  ■■■■              ■             ");
	posxy(40, 9); printf("          ■  ■   ■ ■  ■   ■       ■       ■       ");
	posxy(40, 10); printf("          ■  ■   ■ ■  ■   ■       ■       ■       ");
	posxy(40, 11); printf("         ■   ■  ■  ■  ■   ■       ■       ■      ");
	posxy(40, 12); printf("        ■    ■ ■   ■■■   ■■■■■■■■■■      ");
	posxy(40, 16); printf("                 ■   ■                          ■           ");
	posxy(40, 17); printf("           ■■■■■■■■   ■■■■■■        ■         ");
	posxy(40, 18); printf("          ■      ■               ■      ■■■■■■■   ");
	posxy(40, 19); printf("          ■       ■              ■           ■     ■   ");
	posxy(40, 20); printf("          ■■■    ■             ■          ■      ■   ");
	posxy(40, 21); printf("          ■   ■    ■   ■       ■         ■       ■    ");
	posxy(40, 22); printf("         ■     ■    ■ ■   ■■■■■■   ■        ■     ");
	posxy(40, 23); printf("        ■    ■■     ■                  ■        ■      ");
	posxy(40, 24); printf("       ■            ■ ■               ■       ■■        ");





}

int gameover_wl(int game_num, int score_gameover) { //勝利結果と敗北結果の表示
	system("cls");

	if (game_num == 0) {		//敗北scriptの表示
		
		system("cls");
		map_dis();			//マップの表示
		cor_dis();			//現在地の表示
		item_dis(); 		//アイテムの表示
		memo();				//Hintの表示
		posxy(POS_SX, POS_SY);
		printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
		posxy(POS_CX, POS_CY);

		printf("「うっ……」\n"); c =getchar();
		printf("唐突に平衡感覚が崩れ、その場に膝をついてしまう。\n"); c =getchar();
		printf("異常なくらいに身体が熱い。ふと自分の腕を見ると、血管が不気味なくらいにくっきりと浮き上がっていた。\n"); c =getchar();
		printf("新陳代謝が異常なくらい加速している。\n"); c = getchar();
		printf("霧に含まれるゾンビプラントの酵素が、身体の遺伝子を組み替えて始めた影響だ。\n"); c =getchar();
		printf("間に合わなかった。もう少しこの島から速く脱出していれば、こんな事にはならなかった。\n"); c =getchar();
		printf("「が、あああああっ」\n"); c =getchar();
		printf("僕の意識は、背中が裂けるような激痛と共に途絶えた。\n"); c =getchar();


		system("cls");
		print_gameover();		//敗北結果の表示	
		
			play = 0;			//プレイの終了

	}
	else if (game_num == 1) {	 //軽飛行機で脱出したときの勝利結果の表示、点数の表示
		print_win();
		posxy(62, 27);	printf("軽飛行機で脱出しました。\n");
		posxy(65, 28);	printf("CONGRATULATIONS\n");
		posxy(62, 29);	printf("あなたの点数は%d", score_gameover);
		play = 0;				//プレイの終了
	}
	else if (game_num == 2) {	 //ボートで脱出したときの勝利結果の表示、点数の表示
		print_win();
		posxy(62, 27);	printf("ボートで脱出しました。\n");
		posxy(65, 28);	printf("CONGRATULATIONS\n");
		posxy(62, 29);	printf("あなたの点数は%d", score_gameover);
		play = 0;				//プレイの終了	
	}
	else if (game_num == 3) { //クルーザで脱出したときの勝利結果の表示、点数の表示
		print_win();
		posxy(62, 27);		printf("クルーザで脱出しました。\n");
		posxy(65, 28);		printf("CONGRATULATIONS\n");
		posxy(62, 29);		printf("あなたの点数は%d", score_gameover);
		play = 0;			//プレイの終了
	}
	else if (game_num == 4) { //クルーザで脱出+シオンしたときの勝利結果の表示、点数の表示
		print_win();
		posxy(62, 27);	printf("クルーザで脱出しました。\n");
		posxy(63, 28);	printf("シオンを助かりました。\n");
		posxy(65, 29);	printf("CONGRATULATIONS\n");
		posxy(62, 30);	printf("あなたの点数は%d", score_gameover);
		play = 0;			//プレイの終了
	}
	play = 0;				//プレイの終了
	c=getchar();
	
}

int gameover() {					//ゲームオバの判定
	mass = mass + 50;				//マス変数にを50を足してゲームを終わらせる。
	return mass;
	play = 0;						//プレイの終了
}

void map_dis() {		//マップの表示

	int map1;			//現在地の変数
	char map[30];		//マップ全体の構造体

	for (map1 = 0; map1 < 20; map1++) {		 //現在地を'.'であらわす。
		if (map1 == i) {
			map[map1] = '.';
		}
		else if (map1 != i) {				//現在地以外は' 'であらわす。
			map[map1] = ' ';
		}
	}
	posxy(POS_MX, POS_MY);		 //マップの形を書く
	printf("| ┌%c┬%c┬%c┬%c┐   \n", map[0], map[1], map[2], map[3]);
	posxy(POS_MX, POS_MY + 1);
	printf("| ├%c┼%c┼%c┼%c┤   \n", map[4], map[5], map[6], map[7]);
	posxy(POS_MX, POS_MY + 2);
	printf("| ├%c┼%c┼%c┼%c┤   \n", map[8], map[9], map[10], map[11]);
	posxy(POS_MX, POS_MY + 3);
	printf("| ├%c┼%c┼%c┼%c┤   \n", map[12], map[13], map[14], map[15]);
	posxy(POS_MX, POS_MY + 4);
	printf("| ├%c┼%c┼%c┼%c┤   \n", map[16], map[17], map[18], map[19]);
	posxy(POS_MX, POS_MY + 5);
	printf("| └ ┴ ┴ ┴ ┘\n");

	posxy(POS_MX, POS_MY + 6);
	printf("| 残りの動き：%d", 30 - mass);		//残りの動きを表示
}

int player_move() {	//選択肢（どこに移動するか）の入力
	mass++;
	int dir = 0;			//移動向き
	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("どこに移動しますか？\n");
	printf("1:北 2:南  3.西  4.東\n");
	posxy(POS_SX, POS_SY+3);
	printf("位置方向:");

	sl = getchar();
	sl1 = atoi(&sl);		//移動向きの入力1:北 2:南  3.西  4.東
	while (sl == '\n') {	//enterを入れるまで、移動向き選択の入力
		posxy(POS_SX+10, POS_SY + 3);
		sl = getchar();
		sl1 = atoi(&sl);
	}
	dir = sl1;				//向きを入れる。


	posxy(POS_CX, POS_CY);

	if (dir == 1) {			//上を入力したとき
		if (i == 0 || i == 1 || i == 2 || i == 3) {		//一番上のときは、"この方向にはいけません。\n"を表示
			printf("この方向にはいけません。\n");
		
			i = i + 100;								//iに100を足して現在地の移動を止める。
			c = getchar();
			mass--;										//実際に移動してないのでマスの数を減らす。
		}
		else {

			printf("北に移動した。\n");					//その以外の場合は、"上に移動した。\n"を表示して、現在地から－4して上に行く
			i = i - 4;
		};

	}
	else if (dir == 2) {									//下を入力したとき
		if (i == 16 || i == 17 || i == 18 || i == 19) {		//一番下のときは、"この方向にはいけません。\n"を表示
			printf("この方向にはいけません。\n");
			i = i + 100;									//iに100を足して現在地の移動を止める。
			c = getchar();
			mass--;											//実際に移動してないのでマスの数を減らす。
		}
		else {

			printf("南に移動した。\n");						//その以外の場合は、"下に移動した。\n"を表示して、現在地から+4して下に行く
			i = i + 4;
		};

	}
	else if (dir == 3) {										//左を入力したとき

		if (i == 0 || i == 4 || i == 8 || i == 12 || i == 16) {	//一番左のときは、"この方向にはいけません。\n"を表示
			printf("この方向にはいけません。\n");
			i = i + 100;										//iに100を足して現在地の移動を止める。
			c = getchar();
			mass--;												//実際に移動してないのでマスの数を減らす。
		}
		else {

			printf("西に移動した。\n");					//その以外の場合は、"左に移動した。\n"を表示して、現在地から－1して左に行く
			i = i - 1;
		};



	}
	else if (dir == 4) {											//右を入力したとき
		if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19) {	//一番右のときは、"この方向にはいけません。\n"を表示
			printf("この方向にはいけません。\n");
			i = i + 100;											//iに100を足して現在地の移動を止める。
			c = getchar();
			mass--;													//実際に移動してないのでマスの数を減らす。
		}
		else {
			printf("東に移動した。\n");								//その以外の場合は、"右に移動した。\n"を表示して、現在地から+1して右に行く
			i = i + 1;
		};
	}
	else {															//それ以外を入力したとき
		printf("この作動はいけません。\n");
		i + 100;													//iに100を足して現在地の移動を止める。
		c = getchar();
		mass--;														//実際に移動してないのでマスの数を減らす。
	};
	move_search= 2;									//移動後、来訪のフェーズに
	script(10, 10, 0, move_search, re);				//来訪のscriptの表示
	return i;
};

void display() {								//UIの表示
	system("cls");								//画面の初期化
	map_dis();								 	//マップの表示
	cor_dis();									//現在地の表示
	item_dis();									 //アイテムの表示
	memo();										//Hintの表示
	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("<Press the enter>\n");
	posxy(POS_CX, POS_CY);

};

void script(int em_id, int wp1, int lose_point, int move_search, int re) {	//scriptdの関数
	// 0, "ゾンビコロニー", "打", 0
	// 1, "ゾンビ植物", "遠", 1
	// 2, "蟲ゾンビ", "切", 2
	// 3, "ゾンビ", "遠", 1
	// 4, "アラクネ", "切", 2
	// 0 ,"ハンマー" ""
	// 1, "サブマシンガン", ""
	// 2, "コンバットナイフ", ""
	//move_search, re =1  戦闘
	//move_search, re =２  来訪
	//move_search, re =３  探索
	condition();
	
		if (move_search == 1) {//戦闘
			if (em_id == 2) {
				if (re == 0) {

					printf("鎧のような甲殻を身に纏い、鋏のような大きな顎を広げて威嚇している。あんなものに挟まれたら一溜りもない。\n");
					c = getchar();
					printf("武器は三種類だ。この中からどれを選ぶべきか。\n");
					c = getchar();
				}
				else if (re == 1) {

					printf("飛び掛かって来た拍子に、ハンマーを相手の頭に振り下ろした。\n");
					c = getchar();
					printf("金属の塊が昆虫の頭殻を陥没させた。相手は一瞬悶えるように腕を広げ、そのまま動かなくなった。\n");
					c = getchar();
					printf("戦闘に勝利した。\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("飛び掛かって来る昆虫にナイフで対抗した。\n");
					c = getchar();
					printf("こちらを目掛けて突っ込んでくる相手の身体をナイフで弾き返す。\n");
					c = getchar();
					printf("鋏はこちらにまで届かなかったが、相手も無傷のようだ。\n");
					c = getchar();
					printf("どうやら他のものを使ったほうが良さそうだ\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {

						printf("機関銃の引き金を引き、銃弾を相手に向けてばらまいた。\n");
						c = getchar();
						printf("しかし、あろうことか相手の鎧は難なく受け流し、こちらに飛び掛かって来た。\n");
						c = getchar();
						printf("すんでの所で回避を試みるも、鋏の切っ先が太腿を切り裂いた。\n");
						c = getchar();
						printf("辛うじて致命傷は避けたが、恐らく次は回避できない。改めて武器を選ばなければ。\n");
						c = getchar();
				
					}
					else if (lose_point == 2) {

						printf("機関銃の引き金を引き、銃弾を相手に向けてばらまいた。\n");
						c = getchar();
						printf("しかし、あろうことか相手の鎧は難なく受け流し、こちらに飛び掛かって来た。\n");
						c = getchar();
						printf("鋏が僕の足を捉え、そのまま切断した。\n");
						c = getchar();
						printf("太腿の断面から血が止めどなく流れ出る。だが、もう逃げる術はなかった。\n");
						c = getchar();
						printf("最期に見たのは、巨大な昆虫が自分の身体を貪り食う姿だった。\n");
						c = getchar();

					}
				}
			}
			else if (em_id == 0) {
				if (re == 0) {

					printf("一体一体なら動きが鈍く対処がしやすいが、数が多い。囲まれる事だけは避けなければ。\n");
					c = getchar();
					printf("武器は三種類だ。この中からどれを選ぶべきか。\n");
					c = getchar();
				}
				else if (re == 1) {
					printf("機関銃の引き金を引き、薙ぎ払うように弾丸をばら撒いた。\n");
					c = getchar();
					printf("ゾンビの集団は身体を撃たれると動きを鈍くし、それ以降の対処は容易だった。\n");
					c = getchar();
					printf("戦闘に勝利した。\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("ハンマーを両手に、ゾンビの集団に突撃した。\n");
					c = getchar();
					printf("相手の頭蓋に叩き付けようとするが、その隙に背後からゾンビが襲い掛かった。\n");
					c = getchar();
					printf("即座に攻撃を中断し、背後のゾンビに柄を叩き付け、その場から抜け出す。\n");
					c = getchar();
					printf("どうやら他のものを使ったほうが良さそうだ\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {
						printf("ナイフを片手に、ゾンビの集団に突撃した。\n");
						c = getchar();
						printf("相手の喉元を切り裂こうとナイフを構えるが、その隙に背後からゾンビが襲い掛かり、僕を羽交い絞めにした。\n");
						c = getchar();
						printf("その隙に数体のゾンビに囲まれ、至る個所に噛み付かれた。\n");
						c = getchar();
						printf("何とか抜け出したが、次も同じように逃れられるとは到底思えない。\n");
						c = getchar();
						printf("改めて武器を選ばなければ。\n");
						c = getchar();
					}
					else if (lose_point == 2) {
						printf("ナイフを片手に、ゾンビの集団に突撃した。\n");
						c = getchar();
						printf("相手の喉元を切り裂こうとナイフを構えるが、その隙に背後からゾンビが襲い掛かり、僕を羽交い絞めにした。\n");
						c = getchar();
						printf("その隙に数体のゾンビに囲まれ、全身に噛み付かれた。\n");
						c = getchar();
						printf("抜け出そうとするも、周囲からがっちりと拘束され逃げ出す事は出来なかった。\n");
						c = getchar();
						printf("最期に見たのは、ゾンビ達が寄って集って僕の身体から肉を噛み千切る姿だった。\n");
						c = getchar();
					}

				}
			}
			else if (em_id == 1) {
				if (re == 0) {

					printf("巨大なハエトリグサが根を足に自立して動いている。元が植物だから身体は茎であり細身だ。\n");
					c = getchar();
					printf("しかし、動物の口を思わせる、複数の巨大な補虫葉から地面に垂れ落ちた消化液が白い煙を上げた。\n");
					c = getchar();
					printf("恐らく強力な酸だろう。あれを浴びたらどうなるか解らない。\n");
					c = getchar();
					printf("武器は三種類だ。この中からどれを選ぶべきか。\n");
					c = getchar();
				}
				else if (re == 1) {

					printf("コンバットナイフを片手に、相手に突撃した。\n");
					c = getchar();
					printf("補虫葉の真下を掻い潜り、茎を鷲掴みにして力強く切り裂いた。\n");
					c = getchar();
					printf("真っ二つにされたハエトリグサは身体を震えさせ、そのまま動かなくなった。\n");
					c = getchar();
					printf("戦闘に勝利した。\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("僕は機関銃の引き金を引いて、相手に向けてばらまいた。\n");
					c = getchar();
					printf("しかし、身体が細いせいか掠めるだけで致命打にはならない。このままでは弾が減るだけでジリ貧だ。\n");
					c = getchar();
					printf("どうやら他のものを使ったほうが良さそうだ。\n");
					c = getchar();
				
				}
				else if (re == 3) {
					if (lose_point == 1) {

						printf("ハンマーを両手に、相手に向けて突撃した。\n");
						c = getchar();
						printf("巨大な補虫葉に向けて大振りで叩き付ける。しかし、植物しなやかな身体にこちらの攻撃は受け流された。\n");
						c = getchar();
						printf("その隙に、二の腕を他の補虫葉に噛まれる。消化液が肌を焼いた。\n");
						c = getchar();
						printf("何とか抜け出すことはできたものの、次に同じ目に遭ったら逃れるのは難しいだろう。\n");
						c = getchar();
						printf("身体が弱り動きが鈍くなるのを感じる。次は回避できそうにない。改めて武器を選ばなければ。\n");
						c = getchar();
					}
					else if (lose_point == 2) {

						printf("巨大な補虫葉に向けて大振りで叩き付ける。しかし、植物のしなやかな身体にこちらの攻撃は受け流された。\n");
						c = getchar();
						printf("その隙に、他の葉から吐き掛けられた消化液をかぶってしまい、全身に激痛をもたらした。\n");
						c = getchar();
						printf("致命傷を負い、僕はその場から動けなくなってしまった。補虫用の一つが、僕の身体を丸呑みにする。\n");
						c = getchar();
						printf("最期に見たのは、補虫葉の真っ赤な内側だった。\n");
						c = getchar();
					}
				}
			}
			else if (em_id == 4) {
				if (re == 0) {
					printf("僕は蜘蛛の巣をライターで焼き払った。\n");
					c = getchar();
					printf("室内が炎に包まれる。その奥で、巨大な蜘蛛が天井から落ち、火に巻かれて悶え苦しんでいた。\n");
					c = getchar();
					printf("もしそのまま入っていたら勝てない相手だったが、今なら弱っている。攻撃のチャンスだ。\n");
					c = getchar();
					printf("どの武器を使うべきか。\n");
					c = getchar();
				
				}
				else if (re == 1) {


					printf("ハンマーを振りかぶり、相手の頭に叩き付けた。一撃では倒せず、何度も殴打する。\n");
					c = getchar();
					printf("頑丈な甲殻が徐々に陥没していき、十数回叩き付けた所でようやく動きを止めた。\n");
					c = getchar();
					printf("戦闘に勝利した。\n");
					c = getchar();
				}
				else if (re == 2) {
					printf("ナイフを持ち相手に飛び掛かる。\n");
					c = getchar();
					printf("しかし、頑丈な甲殻に遮られ刃は通らない。相手も噛み付こうとしてきたが、即座にナイフで防御して距離を取る。\n");
					c = getchar();
					printf("どうやら他のものを使ったほうが良さそうだ。\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {
						printf("機関銃の引き金を引き、鉄のあられを浴びせる。\n");
						c = getchar();
						printf("しかし、こちらの攻撃は頑丈な甲殻に弾き返された。\n");
						c = getchar();
						printf("反撃して相手がこちらへ飛び掛かる。すんでの所で回避して噛みつかれずに済むも、身体を蜘蛛の巨体に打ち付けられる。\n");
						c = getchar();
						printf("身体がふらふらする。次は回避できそうにない。\n");
						c = getchar();
					}
					else if (lose_point == 2) {

						printf("機関銃の引き金を引き、鉄のあられを浴びせる。\n");
						c = getchar();
						printf("しかし、こちらの攻撃は頑丈な甲殻に弾き返された。\n");
						c = getchar();
						printf("反撃して相手がこちらへ飛び掛かる。平衡感覚を崩していた僕に、それを回避する術はなかった。\n");
						c = getchar();
						printf("脇腹に噛み付かれ、毒液が流し込まれる。\n");
						c = getchar();
						printf("「があああああっっっ!!」\n");
						c = getchar();
						printf("激痛で視界が明滅する。散々床をのた打ち回った後、やがて何も感じなくなり、何も見えなくなった。\n");
						c = getchar();
						printf("最期に見たのは、視界を潰され何も見えなくなった暗闇だった。\n");
						c = getchar();
					}
				}
			}
			else if (em_id == 3) {
				if (re == 0) {

					printf("僕は扉を開いた。\n");
					c = getchar();
					printf("熱のある白い蒸気をかぶる。その深い霧の奥は、まるで臓物の内側だった。\n");
					c = getchar();
					printf("巨大な部屋の中心で、血管や臓器の管が大樹を形作るように纏まって水槽を突き破り、\n");
					c = getchar();
						printf("天井から壁を伝い床にかけて深紅のツタを張り巡らせている。\n");
					c = getchar();
					printf("床からツルが僕の足に巻き付く。その蔦に、アラクネの毒針で作った槍を突き刺した。\n");
					c = getchar();
					printf("化け物が呻いているような野太い轟音がフロアを揺らす。臓物の大樹が赤から紫に変色する。\n");
					c = getchar();
					printf("今なら弱っている、攻撃のチャンスだ。\n");
					c = getchar();
					printf("どの武器を使うべきか。\n");
					c = getchar();
				
				}
				else if (re == 1) {
					printf("僕はコンバットナイフを構えて突撃した。\n");
					c = getchar();
					printf("ツルが足に絡み付こうとしてくる。その度に僕はそれを切り払い、強引に突き進む。\n");
					c = getchar();
					printf("大樹の幹から伸ばされた触腕が薙ぎ払おうとしてくる。それを体勢を低くして回避。\n");
					c = getchar();
					printf("「！？」\n");
					c = getchar();
					printf("それを狙ってか、僕の身体を複数のツルが一気に捉えようとしてくる。腕、背中、脚に絡み付いた。\n");
					c = getchar();
					printf("続いて、真上から触腕が叩き付けようと迫ってくる。\n");
					c = getchar();
					printf("僕は、腕からツタを強引に引き剥がし、触腕にナイフの切っ先を突き付けた。\n");
					c = getchar();
					printf("酸を分泌しているのか、触腕から垂れ落ちた液体が手の甲を焼いた。\n");
					c = getchar();

					printf("しかし、身体に巻き付いていたツタが緩んだ。その拍子に立ち上がり、一気に距離を詰める。\n");
					c = getchar();
					display();
					printf("臓物の大樹に、ナイフを持たないもう一方の手で杭を打つように突き刺す。そのまま横一線に切り裂いた。\n");
					c = getchar();
					printf("血液の濁流が僕の白衣を染める。それに耐えつつ同じ要領で縦に切り裂き、最後にその中心に刃を突き付けた。\n");
					c = getchar();
				

					printf("震撼する臓物の大樹。僕の身体は濁流に押され、背後に転倒する。\n");
					c = getchar();
					printf("「……………」\n");
					c = getchar();
					printf("空間が静かになる。ゾンビプラントは、活動を停止した。\n");
					c = getchar();
					printf("戦闘に勝利した。\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("ゾンビプラントに向けてサブマシンガンの鉛玉をばら撒く。しかし、穿たれた銃創はすぐに再生してしまう。\n");
					c = getchar();
					printf("効果はいまひとつ。どうやら他のものを使ったほうが良さそうだ\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {

						printf("ハンマーを両手に、相手に突撃した。\n");
						c = getchar();
						printf("足元からツルが巻き付いてくる。引き抜こうとするが、幾重にも巻き付いて離れない。\n");
						c = getchar();
						printf("その隙を狙い、触腕が僕の身体を撫でた。\n");
						c = getchar();
						printf("「ぐうっ……!!」\n");
						c = getchar();
						printf("酸を分泌していたのか、衣服の一部を溶かして身体を焼く。\n");
						c = getchar();
						printf("触腕をハンマーで殴り付け足元のツタが緩み、何とか抜け出す。\n");
						c = getchar();
						printf("体力を削がれて身体がふらふらする。次の攻撃は回避できそうにない。\n");
						c = getchar();

					}
					else if (lose_point == 2) {
						printf("ハンマーを両手に、相手に突撃した。\n");
						c = getchar();
						printf("足元からツルが巻き付いてくる。引き抜こうとするが、幾重にも巻き付いて離れない。\n");
						c = getchar();
						printf("その隙を狙い、触腕が僕の身体を撫でた。\n");
						c = getchar();
						printf("「ぐうっ……!!」\n");
						c = getchar();
						printf("酸を分泌していたのか、衣服の一部を溶かして身体を焼く。\n");
						c = getchar();
						printf("体力を失った僕に、それから逃れる術は無かった。\n");
						c = getchar();
						printf("身体が酸で溶かされ、赤い血管のようなツタが幾重にも群がる。\n");
						c = getchar();
						printf("自分の身体がゾンビプラントの栄養として吸収されていく。\n");
						c = getchar();
						printf("「…………………」\n");
						c = getchar();
						printf("最期に見たのは、僕が探していた、かつて笑顔でわらっていたあの子の幻だった。\n");
						c = getchar();
					}
				}
			}
		}
		else if (move_search == 2) {//来訪
									//○旧研究棟(0)＠北＆西、移動不可
			

			if (i == 0) {
				if (boss_1== 0) {

					//◇来訪時(アラクネ撃破前＆中身のあるライター所持)
					printf("本研究棟が建設される以前からある旧研究棟の一角。\n");
					c = getchar();
					printf("扉を開くと、そこには巨大な蜘蛛の巣が至る所に張り巡らされていた。このまま入ると手足を取られかねない。\n");
					c = getchar();
					printf("ゾンビプラントの酵素で哺乳類の遺伝子を昆虫の遺伝子で書き換える実験が行われていた筈だが、その副産物だろうか。\n");
					c = getchar();
					printf("以前に蜘蛛の遺伝子を組み込んだ哺乳類の出した糸は『引火しやすい弱点』があった筈だ。\n");
					c = getchar();
					printf("今、『火種』となる『中身のあるライター』は持っている。この蜘蛛の巣を焼き払って探索を行う事もできる。\n");
					c = getchar();
					printf("この施設から出て北は切り立った崖があり、西は傾斜になっており移動できない。\n");
					c = getchar();
					printf("探索と移動、どちらを行うべきか。\n");
					c = getchar();
				}
				else if (boss_1 = 1) {
					//◇来訪時(アラクネ撃破前＆中身のあるライター無所持)

					printf("本研究棟が建設される以前からある旧研究棟の一角。\n");
					c = getchar();
					printf("扉を開くと、そこには巨大な蜘蛛の巣が至る所に張り巡らされていた。このまま入ると手足を取られかねない。\n");
					c = getchar();
					printf("ゾンビプラントの酵素で哺乳類の遺伝子を昆虫の遺伝子で書き換える実験が行われていた筈だが、その副産物だろうか。\n");
					c = getchar();
					printf("以前に蜘蛛の遺伝子を組み込んだ哺乳類の出した糸は『引火しやすい弱点』があった筈だ。\n");
					c = getchar();
					printf("『火種』となるものがあれば解決策があるかもしれないが、今のところそのようなものは所持していない。\n");
					c = getchar();
					printf("現時点では別の場所を探索することが適切だと僕は考えた。\n");
					c = getchar();
					printf("この施設から出て北は切り立った崖があり、西は傾斜になっており移動できない。\n");
					c = getchar();
					printf("これから何処に移動するべきか。\n");
					c = getchar();

					inprint("アラクネ", "『引火しやすい弱点』");
				}
				
			}
			else if (i == 1) {

				printf("本研究棟が建設される以前からある旧研究棟の一角。\n");
				c = getchar();
				printf("本棟に比べて年期があるせいか、壁が変色し小さな蜘蛛の巣が張っているのが見受けられる。\n");
				c = getchar();
				printf("この施設から出て北は切り立った崖があり移動できない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 2) {
				if (strcmp(data[0].monster, "0")) {
					printf("危険度の高い実験を行うため、本研究棟から隔離されて配置された研究棟。\n");
					c = getchar();
					printf("ハザードマークが書かれた扉の前で、僕は足を止めた。\n");
					c = getchar();
					printf("この辺りは霧が非常に深い。恐らくこの奥に今回の騒動の現況となっているゾンビプラントがいる筈だ。\n");
					c = getchar();
					printf("しかし、『鍵』を所持していないため開く事ができない。この島の何処かにはある筈だが……。\n");
					c = getchar();
					printf("現時点では別の場所を探索することが適切だと僕は考えた。\n");
					c = getchar();
					printf("この施設から出て北は切り立った崖があり移動できない。\n");
					c = getchar();
					printf("これから何処に移動するべきか。\n");
					c = getchar();

					inprint("隔離研究棟", "『鍵』");
				}
			

				else if ((!strcmp(data[0].monster, "0")) && (!strcmp(data[7].item, "枝"))) {
						printf("僕は鍵で扉を開けようとして、途中で手を止めた。\n");
						c = getchar();
						printf("ゾンビプラント自体も高い戦闘能力を持っている。このまま入ったらどうなるか解らない。\n");
						c = getchar();
						printf("何か『相手を弱らせるための手段』が必要だ。僕は他の場所を探索する事にした。\n");
						c = getchar();
						printf("この施設から出て北は切り立った崖があり移動できない。\n");
						c = getchar();
						printf("これから何処に移動するべきか。\n");
						c = getchar();
						inprint("毒に弱いゾンビプラント", "『相手を弱らせるための手段』");
				}
				else if (!strcmp(data[0].monster, "0")) {

					printf("危険度の高い実験を行うため、本研究棟から隔離されて配置された研究棟。\n");
					c = getchar();
					printf("ハザードマークが書かれた扉の前で、僕は足を止めた。\n");
					c = getchar();
					printf("この辺りは霧が非常に深い。恐らくこの奥に今回の騒動の現況となっているゾンビプラントがいる筈だ。\n");
					c = getchar();
					printf("この施設から出て北は切り立った崖があり移動できない。\n");
					c = getchar();
					printf("鍵は持っている。開いて探索を行うべきか。それとも移動するべきか。\n");
					c = getchar();


				}
			
			}
			else if (i == 3) {
				if (strcmp(data[2].monster, "0")) {
					printf("隔離研究棟内に設けられたシェルター。行う実験の危険性が大きい都合を考え設けられたものだ。\n");
					c = getchar();
					printf("もしかすると誰かが立て籠もっている可能性がある。しかし、『開けるための鍵』を所持していないため開くことができない。\n");
					c = getchar();
					printf("現時点では別の場所を探索することが適切だと僕は考えた。\n");
					c = getchar();
					printf("この施設から出て北は切り立った崖があり、東は断崖絶壁でその先は海となっており移動できそうにない。\n");
					c = getchar();
					printf("これから何処に移動するべきか。\n");
					c = getchar();
					inprint("シェルター", "『開けるための鍵』");
				}
			}
			else if (i == 4) {

				printf("森林地帯。霧に加えて木々が生い茂り、非常に視界が悪い。\n");
				c = getchar();
				printf("西は傾斜となっており移動できそうにない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 5) {

				printf("森林地帯。木々の影と霧の深さで周囲をよく見通せない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 6) {

				printf("森林地帯。藪だらけで少し歩きにくい。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 7) {
				printf("森林地帯。丈夫そうな木々が連なっている。\n");
				c = getchar();
				printf("東は断崖絶壁でその先は海となっており移動できない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 8) {
				printf("ここから北にある森林を縫って流れている川だ。幅はあまり広くない。\n");
				c = getchar();
				printf("探索と移動、\n");
				c = getchar();
				printf("西は傾斜となっており移動できそうにない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 9) {
				printf("本研究棟の一角。薬剤の調合や酵素の培養を行う区画であり、薬品棚などが見受けられる。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 10) {
				printf("本研究棟の一角である資料室。様々な書類や書籍が棚に整理されている。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 11) {
				printf("本研究棟に設けられた倉庫。工具や掃除用具など、研究とはあまり関わりのない雑多な物が保管されている。\n");
				c = getchar();
				printf("この外の東側は断崖絶壁でその先は海となっており移動できない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 12) {
				printf("社員寮から北に行くと流れている川だ。砂利が広がっているが歩くことに難はない。\n");
				c = getchar();
				printf("西は傾斜となっており移動できそうにない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 13) {
				printf("高台に設けられた滑走路。以前までは見晴らしの良い場所だったが、空は霧で隠されている。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか\n");
				c = getchar();
			}
			else if (i == 14) {
				printf("本研究棟の一角。主に情報処理を担当するエリアであり、PCやサーバの置かれた部屋が連なっている。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 15) {
				printf("本研究棟のエントランス。割れて動かなくなったガラス製の自動ドアから霧が吹きこんでいる。\n");
				c = getchar();
				printf("この外の東側は断崖絶壁でその先は海となっており移動できない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか\n");
				c = getchar();
			}
			else if (i == 16) {
				printf("島の南西に位置する社員寮。このエリアには僕が最初にいたシェルターも一緒にある。\n");
				c = getchar();
				printf("屋内は特に異常はないが、窓外の景色は霧に包まれて遠くまで見通す事ができない。\n");
				c = getchar();
				printf("南には海が広がり、西は傾斜になっており移動できそうにない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 17) {
				printf("社員寮に隣接する岩礁地帯。\n");
				c = getchar();
				printf("漂着物が至る所に転がり、適当な場所に寄せられているだけであまり片付けられていない。\n");
				c = getchar();
				printf("南には海が広がっており移動できない。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 18) {
				printf("島の南に位置する砂浜。清掃が行き届きゴミも片付けられているのだが、その美しい景観は霧に遮られ見通す事が出来ない。\n");
				c = getchar();
				printf("南には海が広がっており移動できない\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
			else if (i == 19) {
				printf("島の南東に設けられた船着き場。暫く日本に帰っていないが、僕はここから島に降りた。\n");
				c = getchar();
				printf("南は海が広がり、東は断崖絶壁でその先は海が広がり移動できない。\n");
				c = getchar();
				printf("南と東には海が広がっている。\n");
				c = getchar();
				printf("探索と移動、どちらを行うべきか。\n");
				c = getchar();
			}
		}
		else if (move_search == 3) {
			if (i == 1) {
				printf("廊下を歩いていたら、ゾンビの集団が奥から追いかけて来た。\n");
				c = getchar();
				//『戦闘時』の項目より'ゾンビコロニー'\n");
			
			}
			else if (i == 4) {
				printf("探索をしていると、植物型のゾンビが道を塞いだ。\n");
				c = getchar();
				//『戦闘時』の項目より'ゾンビ植物'\n");
		
			}
			else if (i == 5) {
				printf("ハエトリグサの補虫葉から、消化しきれなかったと思われる鞄が滑り落ちてきた。\n");
				c = getchar();
				printf("その中を調べるとスマートフォンがあり、データに研究内容に関わる写真が保管されていた。\n");
				c = getchar();
				printf("スマホを手に入れた。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			else if (i == 6) {
				printf("探索をしていると、植物型のゾンビが姿を現した。\n");
				c = getchar();
				//『戦闘時』の項目より'ゾンビ植物'\n");
		
			}
			else if (i == 7) {
				printf("頑丈そうな木の枝を見つけ、ナイフで加工して棒状にした。\n");
				c = getchar();
				printf("何かに使えそうなので回収する事にした。\n");
				c = getchar();
				printf("枝を手に入れた。\n");
				c = getchar();
				printf("東は断崖絶壁でその先は海となっており移動できない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			else if (i == 8) {
				printf("探索をしていると大きな羽音が聞こえた。振り向くと、昆虫型のゾンビが突撃して来ていた。\n");
				c = getchar();
				//『戦闘時』の項目より'蟲ゾンビ'\n");
	
			}
			else if (i == 9) {
				display();
				printf("薬品器具棚から未使用の注射器を見つける事ができた。使い時があるかもしれないので持っていく。\n");
				c = getchar();
				printf("注射器を手に入れた。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			else if (i == 10) {
				printf("本棚を縫って、複数のゾンビがこちらに向かってきた。\n");
				c = getchar();
				//『戦闘時』の項目より'ゾンビコロニー'\n");
	
			}
			else if (i == 11) {
				printf("周囲を探していると、何かの補修や修理に使えそうな材料や工具を見つけた。\n");
				c = getchar();
				printf("修理キットを手に入れた。\n");
				c = getchar();
				printf("この外の東側は断崖絶壁でその先は海となっており移動できない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			else if (i == 12) {
				printf("周囲を探索していると、川の中から昆虫型のゾンビが飛び出して来た。\n");
				c = getchar();
			}
			else if (i == 13) {
				if (!strcmp(data[16].person, "社長")) {
					if (strcmp(data[4].monster, "0")) {//鍵を持ってない状態
						printf("滑走路に隣接する倉庫を調べたら、軽飛行機が置かれてあった。社長が趣味で所有しているものだ。\n");
						c = getchar();
						printf("『エンジンの鍵』が無いため今は動かせないが、脱出の候補となる筈だ。\n");
						c = getchar();
						printf("もしこれで脱出するならば、鍵を見つけた後に『社長』を連れていく必要がある。\n");
						c = getchar();
						printf("これから何処に移動するべきか。\n");
						c = getchar();
						inprint("滑走路", "『エンジンの鍵』");
					}
					else if (!strcmp(data[4].monster, "0")) {//鍵を持ってる状態
						printf("滑走路に隣接する倉庫を調べたら、軽飛行機が置かれてあった。社長が趣味で所有しているものだ。\n");
						c = getchar();
						printf("『エンジンを動かすための鍵』は持っている。『社長』に声を掛ければ脱出する事はできるが……？\n");
						c = getchar();
						printf("これから何処に移動するべきか。\n");
						c = getchar();
						inprint("軽飛行機の運転ができる人", "『社長』");
					}
				}
			}
			else if (i == 14) {
				printf("サーバールームを探索していると、周囲からうめき声が聞こえた。どうやらゾンビの集団に囲まれたようだ。\n");
				c = getchar();
				//『戦闘時』の項目より'ゾンビコロニー'\n");
	
			}
			else if (i == 15) {
				printf("持ち主を失った靴ばかりで、特に何かに使えそうなものは見つける事はできなかった。\n");
				c = getchar();
				printf("この外の東側は断崖絶壁でその先は海となっており移動できない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			else if (i == 16) {
				printf("社長が空のライターを捨てていた事を思い出し、僕は一度シェルターに戻りそれを回収した。\n");
				c = getchar();
				printf("横で社長は僕の事を怪訝そうに見つめていた。\n");
				c = getchar();
				printf("ライターを手に入れた。\n");
				c = getchar();
				printf("この外の南側には海が広がり、西は断崖絶壁でその先は海となっており移動できない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			else if (i == 17) {
				printf("瓦礫の中にボートを見つける事ができ、それを引き摺りだした。\n");
				c = getchar();
				printf("一人乗りの小さなボート。脱出手段の候補となりそうだが、破損している個所があり今は使えそうにない。\n");
				c = getchar();
				printf("『本研究棟の何処か』に修理するための物があるかもしれない。これで脱出するならば探してみる必要がある。\n");
				c = getchar();
				printf("だが、ボートの中からライターオイルの入った缶を見つける事ができた。\n");
				c = getchar();
				printf("ライターオイルを手に入れた。\n");
				c = getchar();
				printf("南には海が広がっており移動できない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
				inprint("ボートの修理", "『本研究棟の何処か』");
			}
			else if (i == 18) {
				printf("周辺を歩いていたら、霧の奥から昆虫型のゾンビが襲い掛かって来た。\n");
				c = getchar();
				//『戦闘時』の項目より'蟲ゾンビ'\n");
		
			}
			else if (i == 19) {
				
				printf("奥にクルーザーが停泊していた。運転できる人間が今はいないが、脱出の候補となり得る筈だ。\n");
				c = getchar();
				printf("確か、島の北西にある『隔離研究棟』で働いている『同僚』のひとりが船舶免許を持っていると聞いた覚えがある。\n");
				c = getchar();
				printf("また、近くに銀色に光るものがあり、それを拾った。\n");
				c = getchar();
				printf("それは、僕が探していた人のペンダントだった。周囲を探したが、彼女の影は見当たらない。彼女は何処に行ったのだろうか。\n");
				c = getchar();
				printf("南と東には海が広がっている。\n");
				c = getchar();
				printf("これから何処に移動するべきか\n");
			
				c = getchar();

				inprint("クルーザー", "『同僚』");
			}

		}

		else if (move_search == 4) {
			if (i == 1) {//戦闘で勝ったとき
				printf("その後、探索を続けていると、事務机に研究に密接に関わっている資料の一つが置かれているのが目に留まった。\n");
				c = getchar();
				printf("研究資料1を手に入れた。\n");
				c = getchar();
				printf("この施設から出て北は切り立った崖があり移動できない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}

			else if (i == 4) {//戦闘で勝ったとき
				printf("その後、探索を続けていると、土の中に光ってるものがが置かれているのが目に留まった。\n");
				c = getchar();
				printf("軽飛行機の鍵を手に入れた\n");
				c = getchar();
				printf("西は傾斜となっており移動できそうにない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			
			else if (i == 6) {//戦闘で勝ったとき
				printf("その後も探索を続けていると一人の男性の遺体を見つけ、持ち物を調べると研究のスケジュールが書かれたノートを見つけた。\n");
				c = getchar();
				printf("スケジュール張を手に入れた。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}

			else if (i == 10) {//戦闘で勝ったとき
				printf("その後も資料を探索していたら、研究内容に密接に関わる研究資料の一つを見つけた。\n");
				c = getchar();
				printf("研究資料2を手に入れた。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			else if (i == 12) {//戦闘で勝ったとき
				printf("ゾンビ達の中に白衣を着た個体がいた。変わり果ててはいるが、恐らく僕の部下だった研究員だろう。\n");
				c = getchar();
				printf("白衣のポケットから研究日誌を見つける事ができた。\n");
				c = getchar();
				printf("日記を手に入れた。\n");
				c = getchar();
				printf("西は傾斜となっており移動できそうにない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}
			
			else if (i == 14) {//戦闘で勝ったとき
				printf("このゾンビ達はどうやらここの区画を任していた僕の部下達のようだ。\n");
				c = getchar();
				printf("僕の研究が彼らをこんな姿に変えてしまったと思うと背筋が凍り、自責に苛まれた。\n");
				c = getchar();
				printf("彼らの持ち物から、研究データのUSBを回収した。\n");
				c = getchar();
				printf("USBを手に入れた\n");
				c = getchar();
				printf("これから何処に移動するべきか？\n");
				c = getchar();
			}
			else if (i == 18) {//戦闘で勝ったとき
				printf("その後、周囲を探索したが特に何かを見つける事はできなかった。\n");
				c = getchar();
				printf("南には海が広がっており移動できない。\n");
				c = getchar();
				printf("これから何処に移動するべきか。\n");
				c = getchar();
			}

		}

}

void item_dis() {							//プレイヤーのアイテムの表示
	int r = 0;								//アイテム確認用検索変数
	int ip;									//アイテム確認用検索変数2
	for (r = 0; r < 50; r++) {				//プレイヤーのアイテムを確認するためにプレイヤー構造体を検索して表示
		if (strcmp(stock[r].item_name, "0") && strcmp(stock[r].item_name, "1")) {
			if (strcmp(stock[r].item_name, "\0")) {
				ip = r + 1;
				posxy(POS_IX, POS_IY + ip);
				printf("| %s\n", stock[r].item_name);		//インベントリの表示
			}
		};
	};
};

int fight(int em_id, int re) {			//戦闘の関数

	
	wp1 = 0;							//武器の選択用変数１：ハンマー２：サブマシンガン３：コンバットナイフ
	at1 = 0;							//戦闘と逃走の選択用変数1.逃走 2.戦闘
	move_search = 1;					//戦闘の状態

	system("cls");
	map_dis(); 	//マップの表示
	cor_dis();	//現在地の表示
	item_dis(); memo();	//アイテムの表示

	posxy(POS_TX + 50, POS_TY + 1);
	printf("%sとの戦闘\n", data[i].monster);			//エナミーとの戦闘の表示
	
	
	if (re <2 || re >2) {
		posxy(POS_CX, POS_CY);
		printf("%sが現れた。\n", data[i].monster);		//エナミーの登場
		monster_dis();									//エナミーのimageの表示
		
		posxy(POS_SX, POS_SY);
		printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("何をしますか。\n");
		printf("1.逃走 2.戦闘\n");
		posxy(POS_SX, POS_SY + 3);

		sl = getchar();
		sl1 = atoi(&sl);						//戦闘と逃走の選択の入力1.逃走 2.戦闘
		while (sl == '\n') {					//enterを押すまで戦闘と逃走の選択
			posxy(POS_SX, POS_SY + 3);
			sl = getchar();
			sl1 = atoi(&sl);					//戦闘と逃走の選択の入力1.逃走 2.戦闘	
		}
		at1 = sl1;								//選択結果を入れる。



		system("cls");
		map_dis(); 	//マップの表示
		cor_dis();	//現在地の表示
		item_dis(); memo();	//アイテムの表示
		posxy(POS_SX, POS_SY);
		printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("何をしますか。\n");
		printf("1.逃走 2.戦闘\n");

		same = 0;
		re = 0;
	}
	else {					//戦闘の途中に引きわけったとき、選択なしで戦闘に入る。
		at1 = 2;			
		re = 2;
	}

		if (at1 == 2) {		//戦闘の初め
		
			if (re == 0) {
				posxy(POS_CX, POS_CY);
			script(em_id, 5, lose_point, move_search, re);
				c = getchar();
			}
		
			posxy(POS_SX, POS_SY);
			printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("何をつかいますか。\n");
			printf("1.%s 2.%s 3.%s \n", stock[0].item_name, stock[1].item_name, stock[2].item_name);
			posxy(POS_SX, POS_SY + 3);

			sl = getchar();
			sl1 = atoi(&sl);			//武器の選択１：ハンマー２：サブマシンガン３：コンバットナイフ
			while (sl == '\n') {		//enterを押すまでに武器の選択
				posxy(POS_SX, POS_SY + 3);
				sl = getchar();
				sl1 = atoi(&sl);		//武器の選択１：ハンマー２：サブマシンガン３：コンバットナイフ
			}
			wp1 = sl1;					//武器の選択を入れる。

			posxy(POS_CX, POS_CY);
			display();
			// 0, "ゾンビコロニー", "打", 0
			// 1, "ゾンビ植物", "遠", 1
			// 2, "蟲ゾンビ", "切", 2
			// 3, "ゾンビプラント", "遠", 1
			// 4, "アラクネ", "切", 2
			// 0 ,"ハンマー" ""
			// 1, "サブマシンガン", ""
			// 2, "コンバットナイフ", ""
			//引き分けのとき、また戦闘に入る。
			//1回負けたとき、もう一回武器を選んで戦う。
			//2回負けたとき、ゲームオバ
			//勝ったとき、勝利の表示
			posxy(POS_CX, POS_CY);
			if (em_id == 0) {

				if (wp1 == 1) {				//引き分け
					re = 2; same = 1;
					script(em_id, 0, lose_point, move_search, re);		//引き分けのときのscriptが表示
					printf("%sで攻撃した。\n", stock[0].item_name);
					printf("%sの攻撃を防御した。\n", data[i].monster);



				}
				else if (wp1 == 3) {			//lose
					same = 0; re = 3; lose_point = 1;


					script(em_id, 2, lose_point, move_search, re);		//1回負けたときのscriptが表示
					printf("%sで攻撃した。\n", stock[2].item_name);
					printf("%sに攻撃された。\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%sとの戦闘\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();

					posxy(POS_SX, POS_SY);
					printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("何をつかいますか。\n");
					printf("1.%s 2.%s 3.%s \n", stock[0].item_name, stock[1].item_name, stock[2].item_name);
					posxy(POS_SX, POS_SY + 3);

					sl = getchar();
					sl1 = atoi(&sl);			
					while (sl == '\n') {		
						posxy(POS_SX, POS_SY + 3);
						sl = getchar();
						sl1 = atoi(&sl);		
					}
					wp1 = sl1;					


					posxy(POS_CX, POS_CY);

					if (wp1 == 1) {//引き分け
						re = 2; same = 1;
						script(em_id, wp1 - 1, lose_point, move_search, re);		//引き分けたときのscriptが表示
						printf("%sで攻撃した。\n", stock[0].item_name);
						printf("%sの攻撃を防御した。\n", data[i].monster);

					}
					else if (wp1 == 3) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 2, lose_point, move_search, re);				//２回負けたときのscriptが表示
						printf("%sで攻撃した。\n", stock[2].item_name);
						printf("%sに攻撃された。\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);											//ゲームオバ判定
						j = j + 100;												//プレイ終了
					}
					else if (wp1 == 2) {//win
						same = 0; re = 1;
						script(em_id, 1, lose_point, move_search, re);				//勝ったときのscriptが表示
						printf("%sで攻撃した。\n", stock[1].item_name);
						printf("%sを倒した。\n", data[i].monster);



					}

				}
				else if (wp1 == 2) {//win

					same = 0; re = 1;
				
					script(em_id, 1, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[1].item_name);
					printf("%sを倒した。\n", data[i].monster);


				}
			}
			else if (em_id == 1) {

				if (wp1 == 2) {//引き分け
					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[1].item_name);
					printf("%sの攻撃を防御した。\n", data[i].monster);


				}
				else if (wp1 == 1) {//lose
					same = 0; re = 3; lose_point = 1;
					script(em_id, 0, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[0].item_name);
					printf("%sに攻撃された。\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%sとの戦闘\n", data[i].monster);
					map_dis(); 
					cor_dis();
					item_dis();
					memo();

					posxy(POS_SX, POS_SY);
					printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("何をつかいますか。\n");
					printf("1.%s 2.%s 3.%s \n", stock[0].item_name, stock[1].item_name, stock[2].item_name);
					posxy(POS_SX, POS_SY + 3);


					sl = getchar();
					sl1 = atoi(&sl);
					while (sl == '\n') {
						posxy(POS_SX, POS_SY + 3);
						sl = getchar();
						sl1 = atoi(&sl);
					}
					wp1 = sl1;

					posxy(POS_CX, POS_CY);

					if (wp1 == 2) {//引き分け

						re = 2; same = 1;
						printf("%sで攻撃した。\n", stock[1].item_name);
						printf("%sの攻撃を防御した。\n", data[i].monster);

					}
					else if (wp1 == 1) {//lose
						same = 0; re = 3; lose_point = 2;

						script(em_id, 0, lose_point, move_search, re);

						printf("%sで攻撃した。\n", stock[0].item_name);
						printf("%sに攻撃された。\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 3) {//win

						same = 0; re = 1;

						script(em_id, 2, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[2].item_name);
						printf("%sを倒した。\n", data[i].monster);



					}

				}
				else if (wp1 == 3) {//win


					same = 0; re = 1;
					script(em_id, 2, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[2].item_name);
					printf("%sを倒した。\n", data[i].monster);


				}
			}
			else if (em_id == 2) {



				if (wp1 == 3) {//引き分け
					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[2].item_name);
					printf("%sの攻撃を防御した。\n", data[i].monster);


				}
				else if (wp1 == 2) {//lose
					same = 0; re = 3; lose_point = 1;
					script(em_id, 1, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[1].item_name);
					printf("%sに攻撃された。\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%sとの戦闘\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();

					posxy(POS_SX, POS_SY);
					printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("何をつかいますか。\n");
					printf("1.%s 2.%s 3.%s \n", stock[0].item_name, stock[1].item_name, stock[2].item_name);
					posxy(POS_SX, POS_SY + 3);
					sl = getchar();
					sl1 = atoi(&sl);
					while (sl == '\n') {
						posxy(POS_SX, POS_SY + 3);
						sl = getchar();
						sl1 = atoi(&sl);
					}
					wp1 = sl1;

					posxy(POS_CX, POS_CY);

					if (wp1 == 3) {//引き分け

						re = 2; same = 1;
						script(em_id, wp1 - 1, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[2].item_name);
						printf("%sの攻撃を防御した。\n", data[i].monster);

					}
					else if (wp1 == 2) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 1, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[1].item_name);
						printf("%sに攻撃された。\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 1) {//win


						same = 0; re = 1;
						script(em_id, 0, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[0].item_name);
						printf("%sを倒した。\n", data[i].monster);


					}

				}
				else if (wp1 == 1) {//win
					same = 0; re = 1;
					script(em_id, 0, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[0].item_name);
					printf("%sを倒した。\n", data[i].monster);


				}
			}
			else if (em_id == 3) {

				if (wp1 == 2) {//引き分け

					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[1].item_name);
					printf("%sの攻撃を防御した。\n", data[i].monster);


				}
				else if (wp1 == 1) {//lose
					same = 0; re = 3; lose_point = 1;

					script(em_id, 0, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[0].item_name);
					printf("%sに攻撃された。\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%sとの戦闘\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();	

					posxy(POS_SX, POS_SY);
					printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("何をつかいますか。\n");
					printf("1.%s 2.%s 3.%s \n", stock[0].item_name, stock[1].item_name, stock[2].item_name);

					posxy(POS_SX, POS_SY + 3);
					sl = getchar();
					sl1 = atoi(&sl);
					while (sl == '\n') {
						posxy(POS_SX, POS_SY + 3);
						sl = getchar();
						sl1 = atoi(&sl);
					}
					wp1 = sl1;

					posxy(POS_CX, POS_CY);

					if (wp1 == 2) {//引き分け
						re = 2; same = 1;
						script(em_id, wp1 - 1, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[1].item_name);
						printf("%sの攻撃を防御した。\n", data[i].monster);


					}
					else if (wp1 == 1) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 0, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[0].item_name);
						printf("%sに攻撃された。\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 3) {//win

						same = 0; re = 1;
						script(em_id, 2, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[2].item_name);
						printf("%sを倒した。\n", data[i].monster);


					}

				}
				else if (wp1 == 3) {//win

					same = 0; re = 1;
					script(em_id, 2, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[2].item_name);
					printf("%sを倒した。\n", data[i].monster);


				}
			}
			else if (em_id == 4) {

				if (wp1 == 3) {//引き分け
					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[2].item_name);
					printf("%sの攻撃を防御した。\n", data[i].monster);


				}
				else if (wp1 == 2) {//lose
					same = 0; re = 3; lose_point = 1;
					script(em_id, 1, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[1].item_name);
					printf("%sに攻撃された。\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%sとの戦闘\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();

					posxy(POS_SX, POS_SY);
					printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("何をつかいますか。\n");
					printf("1.%s 2.%s 3.%s \n", stock[0].item_name, stock[1].item_name, stock[2].item_name);
					posxy(POS_SX, POS_SY + 3);
					sl = getchar();
					sl1 = atoi(&sl);
					while (sl == '\n') {
						posxy(POS_SX, POS_SY + 3);
						sl = getchar();
						sl1 = atoi(&sl);
					}
					wp1 = sl1;

					posxy(POS_CX, POS_CY);

					if (wp1 == 3) {//引き分け


						script(em_id, wp1 - 1, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[2].item_name);
						printf("%sの攻撃を防御した。\n", data[i].monster);
						re = 2; same = 1;
					}
					else if (wp1 == 2) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 1, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[1].item_name);
						printf("%sに攻撃された。\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 1) {//win

						same = 0; re = 1;
						script(em_id, 0, lose_point, move_search, re);
						printf("%sで攻撃した。\n", stock[0].item_name);
						printf("%sを倒した。\n", data[i].monster);

					}

				}
				else if (wp1 == 1) {//win

					same = 0; re = 1;
					script(em_id, 0, lose_point, move_search, re);
					printf("%sで攻撃した。\n", stock[0].item_name);
					printf("%sを倒した。\n", data[i].monster);

				}
			}
		}
	

	else if (at1 == 1) {	//逃走を選んだとき、最初の選択に戻る
			system("cls");
			map_dis(); 
			cor_dis();
			item_dis();
			memo();	

		posxy(POS_CX, POS_CY);
		printf("逃走に成功した。\n");
		posxy(POS_SX, POS_SY);
		printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("何をやりますか？\n");
		printf("1:探索 2:移動\n");
		c = getchar();
		re = 0;
	}
	else {
		posxy(POS_CX, POS_CY);
		printf("この作動はいけません。\n");

	}


	return re;


};

void print_item() {	//アイテムの関数アイテムが最初に拾えたときにscriptを表示して、Hintを与える説明を見れる。
	if (!strcmp(stock[item_cor].item_name, "研究資料1")) {
		printf("研究資料1 : 遺伝子組み換えを行う酵素『ヌクレアーゼ』による癌の治療に関する資料だ。");
	}
	else if (!strcmp(stock[item_cor].item_name, "軽飛行機の鍵")) {
		printf("軽飛行機の鍵 : 社長が趣味で所有している軽飛行機の鍵。");
		c = getchar();
		printf("軽飛行機を見つけたら社長を呼ぶ必要がある。");
	}
	else if (!strcmp(stock[item_cor].item_name, "スマホ")) {
		printf("スマホ : 遺伝子組み換えを行ったモルモットの写真が内部に残されている。");
	}
	else if (!strcmp(stock[item_cor].item_name, "スケジュール張")) {
		printf("スケジュール張 : 研究に関するスケジュールが書き込まれている。");
	}
	else if (!strcmp(stock[item_cor].item_name, "枝")) {
		printf("枝 : 頑丈な加工した木の枝。何かと組み合わせれば武器が作れるかもしれない。");
	}
	else if (!strcmp(stock[item_cor].item_name, "注射器")) {
		printf("注射器 : 未使用の中身が入っていない注射器だ。");
	}
	else if (!strcmp(stock[item_cor].item_name, "研究資料2")) {
		printf("研究資料2 : 元もと行っていた医療研究の兵器転用に関する資料だ。");
	}
	else if (!strcmp(stock[item_cor].item_name, "修理キット")) {
		printf("修理キット : 主にボートなどを修理するための");
		c = getchar();
		printf("資材やそれを加工するための工具を纏めたもの。");
	}
	else if (!strcmp(stock[item_cor].item_name, "日記")) {
		printf("日記 : 研究に関する記録や仕事の愚痴が書きなぐられている。");
	}
	else if (!strcmp(stock[item_cor].item_name, "USB")) {
		printf("USB : 研究の計画書やその記録などが保存されている。");
	}
	else if (!strcmp(stock[item_cor].item_name, "空のライター")) {
		printf("空のライター : 社長の持っていたライター。");
		c = getchar();
		printf("しかし中身のライターオイルが無ければ使い物にならない。");
	}
	else if (!strcmp(stock[item_cor].item_name, "ライターオイル")) {
		printf("ライターオイル : ライターの燃料となるオイル。漂流物のようだ。");
	}
	else if (!strcmp(stock[item_cor].item_name, "探し人のペンダント")) {
		printf("探し人のペンダント : あの子の誕生日に買ってあげたアゲハ蝶のペンダントだ。");
	}
	else if (!strcmp(stock[item_cor].item_name, "中身のあるライター")) {
		printf("中身のあるライター : 拝借した社長のライターにオイルを新たに注入したもの。");
		c = getchar();
		printf("邪魔なものを燃やす事ができる。");
	}
	else if (!strcmp(stock[item_cor].item_name, "毒槍")) {
		printf("毒槍 : アラクネの毒針を木の枝に括り付けた簡素な槍。");
		c = getchar();
		printf("大型の異形に効果がある筈だ。");
	}
	else if (!strcmp(stock[item_cor].item_name, "ワクチン")) {
		printf("ワクチン : 遺伝子組み換え酵素の抗体が入った注射器。");
	}
}

int player_research() {			//探索結果の関数
	
	int em_id;					//エナミーのid
	int key, key1;				//鍵のアイテムを探すための番号
	em_id = 6;					//エナミーのidは5まであるので6にして初期化
	int fight_re = 5;			//戦闘の結果を初期化
	int fight_num;				
	move_search= 3;				//探索のフェーズ

	boss_2 = 0;					//boss 条件アイテム２

	posxy(POS_CX, POS_CY);
	printf("探索を行った。\n");

	
		if (i == 0 || i == 2 || i == 3) {	//鍵がしまっているマスの判定

			if (i == 0) {
				if (strcmp(data[i].monster, "0")) {				//アラクネが倒されなかった場合は、
					script(10, 10, lose_point, move_search, re);
					for (key = 0; key < 50; key++) {		//アラクネをあらわせるための条件
						if (!strcmp(stock[key].item_name, "中身があるライター")) {	//"中身があるライター"あって、

							printf("僕は蜘蛛の巣をライターで焼き払った。\n");
							c = getchar();
							printf("室内が炎に包まれる。その奥で、巨大な蜘蛛が天井から落ち、火に巻かれて悶え苦しんでいた。\n");
							c = getchar();
							printf("もしそのまま入っていたら勝てない相手だったが、今なら弱っている。攻撃のチャンスだ。\n");
							c = getchar();
							printf("どの武器を使うべきか。\n");
							c = getchar();
							map_dis();
							cor_dis();	
							item_dis(); memo();
							posxy(POS_CX, POS_CY);
							printf("%sが現れた。\n", data[i].monster);
							monster_dis();
							for (fight_num = 0; fight_num < 40; fight_num++) {	//アラクネと戦う。
								if (fight_re == 5) {					//初めてのアラクネと戦闘するとき
									
									system("cls");
									map_dis(); 	
									cor_dis();	
									item_dis();
									memo();	

									fight_re = fight(4, 5);				//アラクネと戦闘

								}
								else if (fight == 2) {					//引き分けってからアラクネと戦闘するとき
									system("cls");
									map_dis(); 	
									cor_dis();	
									item_dis(); 
									memo();	

									fight_re = fight(4, 2);				//アラクネと戦闘
									c = getchar();
								}
							}
							if (fight_re == 1) {											//アラクネと戦闘に勝ったとき
								strcpy_s(data[i].monster, sizeof(data[i].monster), "0");	//構造体の中のアラクネの情報を消す

								strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), "隔離研究棟の鍵");		//アラクネのアイテムを拾う。
								strcpy_s(stock[item_cor + 1].item_name, sizeof(stock[item_cor + 1].item_name), "毒針");			
								item_cor = item_cor + 2;

								//アラクネと戦闘に勝ったときのscript
								printf("その後、蜘蛛のいた部屋を抜けて探索をしていると、社長の秘書と思しき遺体を見つける事ができた。\n");
								c = getchar();
								printf("彼の持ち物を調べると、隔離研究棟の鍵を手に入れる事が出来た。\n");
								c = getchar();
								printf("また、去り際に蜘蛛の顎から毒針を取り出した。恐らく何かに使えるかもしれない。\n");
								c = getchar();
								printf("隔離研究棟の鍵を手に入れた。\n");
								c = getchar();
								printf("隔離研究棟の鍵 : 北西にある隔離された実験施設の鍵。");

								c = getchar();
								display();
								printf("アラクネの毒針を手に入れた。\n");
								c = getchar();
								printf("アラクネの毒針 : このままでは使えない。棒のようなものが欲しい。");
								c = getchar();
								
								printf("この施設から出て北は切り立った崖があり移動できない。\n");
								c = getchar();
								printf("これから何処に移動するべきか。\n");
								c = getchar();
								
							

							

								check_place = 1;
								strcpy_s(data[i].item, sizeof(data[i].item), "1");		//構造体の中のアラクネのアイテム情報を消す
							}
						}

					}

				}
				else {
					if (!strcmp(data[i].item, "1")) {  //来訪時(アラクネ撃破後)\n");

						printf("本研究棟が建設される以前からある旧研究棟の一角。");
						c = getchar();

						printf("先ほど撃破したアラクネの死骸が転がっている。\n");
						c = getchar();
						printf("この施設から出て北は切り立った崖があり、");
						c = getchar();

						printf("西は傾斜となっており移動できそうにない。\n");
						c = getchar();
						printf("探索と移動、どちらを行うべきか。\n");
						c = getchar();

					}

				}
			}
			else if (i == 2) {			//ゾンビプラントをあらわせるための条件		
				if (strcmp(data[i].monster, "0")) {		//ゾンビプラントが倒されなかった場合は、

					script(10, 10, lose_point, move_search, re);
					for (key = 0; key < 50; key++) {
						if (!strcmp(stock[key].item_name, "隔離研究棟の鍵")) {		//"隔離研究棟の鍵"があって、
							script(10, 10, lose_point, move_search, re);
							for (key1 = 0; key1 < 50; key1++) {
								if (!strcmp(stock[key1].item_name, "毒枝")) {	//"毒枝"があって、
									printf("僕は扉を開いた。\n");
									c = getchar();
									printf("熱のある白い蒸気をかぶる。その深い霧の奥は、まるで臓物の内側だった。\n");
									c = getchar();
									printf("巨大な部屋の中心で、血管や臓器の管が大樹を形作るように纏まって水槽を突き破り、\n");
									c = getchar();
									printf("天井から壁を伝い床にかけて深紅のツタを張り巡らせている。\n");
									c = getchar();
									printf("床からツルが僕の足に巻き付く。その蔦に、アラクネの毒針で作った槍を突き刺した。\n");
									c = getchar();
									printf("化け物が呻いているような野太い轟音がフロアを揺らす。臓物の大樹が赤から紫に変色する。\n");
									c = getchar();
									printf("今なら弱っている、攻撃のチャンスだ。\n");
									c = getchar();
									printf("どの武器を使うべきか。\n");
								
									//◇探索時(鍵所持、毒槍所持)\n");
									map_dis(); 	
									cor_dis();	
									item_dis(); memo();	
									posxy(POS_CX, POS_CY);

									printf("%sが現れた。\n", data[i].monster);	//ジェネレータと戦う。

									monster_dis();

									for (fight_num = 0; fight_num < 40; fight_num++) {
										if (fight_re == 5) {			//初めてのゾンビプラントと戦闘するとき
											
											system("cls");
											map_dis(); 	
											cor_dis();	
											item_dis(); memo();	
											fight_re = fight(3, 5);		//ゾンビプラントと戦闘

										}
										else if (fight_re == 2) {		//引き分けってからゾンビプラントと戦闘するとき
											system("cls");
											map_dis(); 	
											cor_dis();	
											item_dis(); memo();	
											fight_re = fight(3, 2);		//ゾンビプラントと戦闘
											c = getchar();
										}
									}
									if (fight_re == 1) {//◇戦闘勝利時\n");

										strcpy_s(data[i].monster, sizeof(data[i].monster), "0");		//構造体の中のゾンビプラントの情報を消す
										strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), "クールザの鍵");	//ゾンビプラントのアイテムを拾う。
										strcpy_s(stock[item_cor + 1].item_name, sizeof(stock[item_cor + 1].item_name), "第二シェルターの鍵");
										strcpy_s(stock[item_cor + 2].item_name, sizeof(stock[item_cor + 2].item_name), "抗体");
										item_cor = item_cor + 3;

										printf("その後、室内を探索していると、未完成だがゾンビプラントの酵素の抗体が入ったフラスコを見つける事ができた。\n");
										c = getchar();
										printf("また、鍵の束が床に落ちており、それを回収した。\n");
										c = getchar();
										printf("鍵の束には第二シェルターの鍵とクールザの鍵が入ってあった。\n");
										display();
										c = getchar();
										printf("抗体の入ったフラスコを手に入れた。\n");
										c = getchar();
										printf("抗体 : ジェネレーターの発生させていた酵素の抗体。");
										c = getchar();
										printf("第二シェルターの鍵を手に入れた。\n");
										c = getchar();
									
										printf("クールザの鍵を手に入れた。\n");
										c = getchar();
										printf("この施設から出て北は切り立った崖があり移動できない。\n");
										c = getchar();
										printf("これから何処に移動するべきか。\n");
									

										strcpy_s(data[i].item, sizeof(data[i].item), "1");			//構造体の中のゾンビプラントのアイテム情報を消す
										check_place = 1;
									}
								}
							}
						}
					
					}
				}
				else {
					if (!strcmp(data[i].item, "1")) {//◇来訪時(ゾンビプラント撃破後)\n");
						printf("危険度の高い実験を行うため、本研究棟から隔離されて配置された研究棟。活動を停止したゾンビプラントがある。\n");
						c = getchar();
						printf("この施設から出て北は切り立った崖があり移動できない。\n");
						c = getchar();
						printf("探索と移動、どちらを行うべきか。\n");
						c = getchar();

					}


				}
			}
			else if (i == 3) {
				for (key = 0; key < 50; key++) {			//第二シェルターを開くための条件
					if (!strcmp(stock[key].item_name, "第二シェルターの鍵")) {	//"第二シェルターの鍵"がある場合は、
						if (strcmp(data[3].person, "0")) {
							printf("僕は扉のロックを解除してシェルターに入った。\n");
							c = getchar();
							printf("そこには、クルーザーの運転を社長に任されている、同僚の明石弘樹がいた。\n");
							c = getchar();
							printf("明石「研究長」\n");
							c = getchar();
							printf("「無事ですか？」\n");
							c = getchar();
							printf("明石は活動を止めたゾンビプラントに目配せする。\n");
							c = getchar();
							printf("明石「あいつを止めれたんですか？」\n");
							c = getchar();
							printf("「はい。これから社長と共に脱出します。あまり時間は残っていません」\n");
							c = getchar();
							printf("明石「わ、わかりました。行きましょう」\n");
							c = getchar();


							printf("%sが仲間になった。\n", data[3].person);			//第二シェルターにはいて同僚と仲間になる。
							strcpy_s(data[3].person, sizeof(data[3].person), "0");
						}
					}
				}

			}

		}
		else
		{
			if (strcmp(data[i].monster, "0")) {	//エナミーが存在するとき
				for (em_id = 5; em_id > -1; em_id--) {
					if (!strcmp(data[i].monster, enermy[em_id].monster_name)) {		//エナミーの名前を確認する。
						printf("%sを発見した。\n", data[i].monster);			//エナミーと戦う。

						for (fight_num = 0; fight_num < 40; fight_num++) {
							if (fight_re == 5) {					//初めてのエナミーと戦闘するとき
							
								system("cls");
								map_dis(); 	
								cor_dis();	
								item_dis(); memo();	
								fight_re = fight(em_id, 5);			//エナミーと戦闘

							}
							else if (fight_re == 2) {				//引き分けってからエナミーと戦闘するとき
								system("cls");
								map_dis(); 	
								cor_dis();	
								item_dis(); memo();	
								fight_re = fight(em_id, 2);			//エナミーと戦闘
								c = getchar();
							}


						}
						if (fight_re == 1) {						//勝ったときの処理
							strcpy_s(data[i].monster, sizeof(data[i].monster), "0");	//構造体の中のエナミーの情報を消す
							if (strcmp(data[i].item, "0") && strcmp(data[i].item, "1")) {

								script(10, 10, lose_point, 4, re);						//勝利のときのscriptを表示


								printf("%sを落とした。\n", data[i].item);			//落としたアイテムを拾う。
								strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), data[i].item);
								print_item();
								strcpy_s(data[i].item, sizeof(data[i].item), "1");	//構造体の中のエナミーのアイテムの情報を消す		
								item_cor++;
								check_place = 1;

							}
						}
					}
				}
			}

			else
			{
				if (esc1 == 1) {
					//エナミーが存在しないとき
					if (strcmp(data[i].item, "0") && strcmp(data[i].item, "1")) {								//マップ上にアイテムがある場合は、アイテムを発見して拾う。

						script(10, 10, lose_point, move_search, re);											//探索のときのscriptを表示
						strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), data[i].item);//アイテムを拾う。
						print_item();																			//アイテムを表示	
						strcpy_s(data[i].item, sizeof(data[i].item), "1");										//構造体の中のアイテムの情報を消す	
						item_cor++;

						check_place = 1;


					}
					else {			//マスに何もないとき

						if (!strcmp(data[i].item, "1")) {
							if (esc == 1) {
								printf("念のため改めて探索を行ったが、特に何かを見つける事も遭遇する事もなかった。\n");
								c = getchar();
							}
						}
						else {
						if (i == 13) {
								script(em_id, wp1, lose_point, 3,re);
						

							}
						else {
								printf("何もありません。\n");
								c = getchar();

						}
							
						}

					}
				}
				if (i == 16) {		//社長が仲間になるための条件
					//
					if (!strcmp(data[16].item, "1")) {
						if (!strcmp(data[4].item, "1")) {		//"軽飛行機の鍵"を拾って
							if (strcmp(data[16].person, "0")) {	//マップ上に社長があるとき、社長が仲間になる。
								display();
								printf("僕は社長に軽飛行機の鍵を見せた。\n");
								c = getchar();
								printf("「社長、軽飛行機の鍵を見つけました」\n");
								c = getchar();
								printf("社長「本当か」\n");
								c = getchar();
								printf("「運転はできましたよね」\n");
								c = getchar();
								printf("社長「ああ、さっさとここから出るぞ」\n");
								c = getchar();
								printf("%sが仲間になった。\n", data[16].person);
								strcpy_s(data[16].person, sizeof(data[16].person), "0");	//構造体の中の人の情報を消す	
							}
						}
					}
				}
				if (i == 13 || i == 17 || i == 19) {
					score_gameover = score_re();	//スコアの情報
					game_num = escape();	//勝利の結果表示
					

				}
			
			}
		}
	
	return item_cor;


};


void enter(enter_x, enter_y) {	//"∇"と"▼"を振り替えす関数


	for (enter_c = 0; enter_c < 4; enter_c++) {

	posxy(enter_x, enter_y);
	printf("∇");
	Sleep(O_s);

	posxy(enter_x, enter_y);
	printf("▼");
	Sleep(O_s);
		}
	c = getchar();


}

void explan() {						//ゲームの説明ページの関数
	system("cls");


	posxy(POS_MX, POS_MY);
	printf("|①");					//マップの表示
	posxy(POS_MX, POS_MY + 1);		
	printf("| ┌ ┬ ┬ ┬ ┐   \n");
	posxy(POS_MX, POS_MY + 2);
	printf("| ├ ┼ ┼ ┼ ┤   \n");
	posxy(POS_MX, POS_MY + 3);
	printf("| ├ ┼ ┼ ┼ ┤   \n");
	posxy(POS_MX, POS_MY + 4);
	printf("| ├ ┼.┼ ┼ ┤   \n");
	posxy(POS_MX, POS_MY + 5);
	printf("| ├ ┼ ┼ ┼ ┤   \n");
	posxy(POS_MX, POS_MY + 6);
	printf("| └ ┴ ┴ ┴ ┘\n");
	posxy(POS_MX, POS_MY + 7);
	printf("|②");					//残りの動きの表示
	posxy(POS_MX, POS_MY + 8);
	printf("| 残りの動き：30");

	posxy(POS_MX, POS_MY + 9);
	printf("|③");					//インベントリの表示


	posxy(0, 1);
	//system("cls");
	printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
	posxy(POS_TX, POS_TY);
	printf("\n現在位置:④\n");		//現在位置の表示
	posxy(0, 3);
	printf("----------------------------------------------------------------------------------------------------------------------\n");



	//アイテムの表示

	posxy(POS_IX, POS_IY + 4);
	printf("|ハンマー\n");
	posxy(POS_IX, POS_IY + 5);
	printf("|サブマシンガン\n");
	posxy(POS_IX, POS_IY + 6);
	printf("|コンバットナイフ\n");


	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("⑤\n");	//選択の表示

	posxy(95, POS_SY + 1);
	printf("|⑥");	//Hintの表示
	posxy(95, POS_SY + 2);
	printf("|");
	posxy(95, POS_SY + 3);
	printf("|");
	posxy(95, POS_SY + 4);
	printf("|");
	posxy(95, POS_SY + 5);
	printf("|");


	posxy(115, 27); printf("⑦▼");

	posxy(POS_CX, POS_CY);
	printf("① マップ：シェルターで手に入れたこの島の地図。プレイヤーの位置を.で表す。\n\n");
	printf("② 制限時間：プレイヤーの行動可能回数が表示される。\n\n");
	printf("③ インベントリ：プレイヤーが所持しているアイテムが表示される。\n");
	printf("               初期所持アイテムとして3種の武器が存在する。\n\n");
	printf("④ 現在位置：プレイヤーの現在位置が表示される。\n\n");
	printf("⑤ 選択肢：行動を選択し、脱出への糸口を見つける。\n\n");
	printf("⑥ メモ：研究員であるプレイヤーは普段からメモを取る癖がついていた。\n");
	printf("       難易度に合わせてヒントとなるメモを見ることができる。\n\n");
	printf("⑦ ▼：テキストの終了を意味する。エンターを押すと選択肢が表示される。\n\n");

	printf("※入力のとき、一気に入力を何個か入れたら、重複入力されるので、一個ずつ入力してください。\n\n");
	c = getchar();

	printf("プレイヤーは研究員である柳原一志を操り、無事に島を脱出することが目標となる。\n");
	printf("脱出には条件がありアイテムや人物の助けが必要になる。\n");


	posxy(POS_SX, POS_SY + 2);
	printf("難易度を選んでください。\n");
	printf("1:EASY 2:NORMAL 3:HARD\n");

	posxy(POS_SX, POS_SY + 4);
	sl = getchar();
	sl1 = atoi(&sl);				//選択肢（難易度）の入力
	while (sl == '\n') {			//enterを押すまで入力
		posxy(POS_SX, POS_SY + 4);
		sl = getchar();
		sl1 = atoi(&sl);			//選択肢（難易度）の入力
	}
	memoid = sl1;					//難易度を入れる。

}

int escape() {
	//勝利条件
	if (i == 13 || i == 17 || i == 19) {
		if (i == 13) {					//軽飛行機で脱出する条件
			for (escape_item = 0; escape_item < 50; escape_item++) {
				if (strcmp(stock[4].item_name, "1")) {
					if (!strcmp(data[16].person, "0")) {
						if (mass < 31) {
							//"軽飛行機の鍵"を拾って、社長と仲間になって、滑走路についたら、脱出
							printf("社長「鍵は持ってるな」\n");
							c = getchar();
							printf("「はい、大丈夫です」\n");
							c = getchar();
							printf("社長「さっさと出るぞ、いつまでもこんな所に居たら命がいくつあっても足りん」\n");
							c = getchar();
							printf("「……………」\n");
							c = getchar();
							printf("僕と社長は軽飛行機で島から脱出した。およそ一日半が経過したが、何とか日本に戻る事ができた。\n");
							c = getchar();
							printf("僕は新たに社長が買い取った別の島で、生物兵器の研究を再開させられた。\n");
							c = getchar();
							printf("この技術が多くの人間を殺すだろう。今回とは比べ物にならないくらい大勢の人間を。\n");
							c = getchar();
							printf("でも、もう僕には全てがどうでもよかった。\n");
							c = getchar();
							printf("自分にとって大切な人は、この世界にはもういない。\n");
							c = getchar();
							printf("僕には人を殺せても、人を生かす事なんて出来やしない。\n");
							c = getchar();


							game_num = 2;
							score_gameover = score_re();		//点数を入れる。
							gameover_wl(1, score_gameover);		//脱出の方法による成功の判断
							mass = gameover();					//残りのマスを消す
							j = j + 150;						//プレイの終了
							play = 0;							
							esc = 0;							
								

						}
					}
				}
			}
		}
		else if (i == 17) {	//ボートで脱出する条件
			for (escape_item = 0; escape_item < 50; escape_item++) {
				if (!strcmp(stock[escape_item].item_name, "修理キット")) {
					//修理キットがあって、磯についたら、脱出
					display();
					posxy(POS_CX, POS_CY);
					printf("ボートを修理してボートで脱出できるようだ。\n");
					posxy(POS_SX, POS_SY);
					printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("ボートで脱出しますか。\n");
					printf("1.する。 2.しない。\n");

					posxy(POS_SX, POS_SY + 4);
					sl = getchar();
					sl1 = atoi(&sl);
					while (sl == '\n') {
						posxy(POS_SX, POS_SY + 4);
						sl = getchar();
						sl1 = atoi(&sl);
					}
					boat_esc = sl1;

					if (boat_esc == 2) {
						posxy(POS_CX, POS_CY);
						printf("ボートで脱出するよりいい方法を探すべきである。");
						c = getchar();

					}
						else if (boat_esc == 1) {
					posxy(POS_CX, POS_CY);
					printf("僕は島にいた人々を残し、ボートで脱出した。\n");
					c = getchar();
					printf("途中で何度も陽が海に落ちたが、何とか陸地に辿り着く事ができ、そこから日本に戻る事ができた。\n");
					c = getchar();
					printf("しかし僕は、島に残したとある人の事が気掛かりだった。\n");
					c = getchar();
					printf("僕は一生、彼女を見捨てた事を後悔する事になるだろう。\n");
					c = getchar();


					game_num = 1;
					score_gameover = score_re();			//点数を入れる。
					gameover_wl(2, score_gameover);			//脱出の方法による成功の判断
					mass = gameover();						//残りのマスを消す
					j = j + 150;							//プレイの終了
					play = 0;
					esc = 0;

					}
				}
			}
		}
		else if (i == 19) {		//クールザで脱出する条件
			for (escape_item = 0; escape_item < 50; escape_item++) {
				if (!strcmp(stock[escape_item].item_name, "クールザの鍵")) {
					if (!strcmp(data[3].person, "0")) {
						int sion = 0;
						//"クールザの鍵"があって、同僚と仲間になって、船付き場についたら、脱出+シオン
						for (escape_item = 0; escape_item < 50; escape_item++) {
							if (!strcmp(stock[escape_item].item_name, "ワクチン")) {
								printf("同僚「ここです？」\n");
								c = getchar();
								printf("「はい。操縦は任せます」\n");
								c = getchar();
								printf("社長「おい、待て」\n");
								c = getchar();
								printf("「………！？」\n");
								c = getchar();
								printf("そこにいたのは、身体の半分が異形となった僕の妹――柳原紫苑だった。\n");
								c = getchar();
								printf("紫苑。\n");
								c = getchar();
								printf("僕は実の妹を助けるために、この研究を始めた。\n");
								c = getchar();
								printf("柳原の家系には女系に遺伝癌があり、女として生まれると20代半ばで全身に癌が多発して死ぬ。\n");
								c = getchar();
								printf("その治療するため、遺伝子を組み換える酵素――ヌクレアーゼの研究をするため僕はこの会社に入った。\n");
								c = getchar();
								printf("しかし、研究の過程でこの技術が生物兵器として使える事が解ってしまった。\n");
								c = getchar();
								display();			//ディスプレイクリア
								printf("その事を知った社長は紫苑を人質に取り、僕に兵器開発をするよう指示した。\n");
								c = getchar();
								printf("僕は、妹を生かす所か、妹を化け物に変えた。\n");
								c = getchar();
								printf("だが、\n");
								c = getchar();
								printf("「社長、明石さん、先に船に乗っていてください」\n");
								c = getchar();
								printf("社長「わ、解った。おい、いくぞ」\n");
								c = getchar();
								printf("明石「は、はい」\n");
								c = getchar();
								printf("社長と明石さんがクルーザーに乗り込む。\n");
								c = getchar();
								printf("今、僕の手には未完成だがワクチンがある。\n");
								c = getchar();
								printf("助けるとはいかないまでも、彼女の容態の悪化を止め、動きを抑える事くらいは出来る筈だ。\n");
								c = getchar();
								printf("「紫苑」\n");
								c = getchar();
								display();			//ディスプレイクリア
								printf("ワクチンの入った注射器を握り締める。\n");
								c = getchar();
								printf("「今度こそ……必ず助けるから」\n");
								c = getchar();
								printf("…………………。\n");
								c = getchar();
								printf("僕達は助かった。\n");
								c = getchar();
								printf("あの後、僕は紫苑を取り押さえ、その隙にワクチンを紫苑に注射する事が出来た。\n");
								c = getchar();
								printf("抗体を打ち込まれた彼女は動きを止め、そのまま気絶した。\n");
								c = getchar();
								printf("それからクルーザーに乗って数日が経過し、僕達は日本に辿り着いた。\n");
								c = getchar();
								printf("その後はどうなったか。\n");
								display();			//ディスプレイクリア
								c = getchar();
								printf("僕はクルーザーにひそかに乗せた紫苑と共に、隙を見て社長の元から逃げ出した。\n");
								c = getchar();
								printf("彼は僕が故意にネットに流した研究内容のせいで、今は警察に追われているらしい。\n");
								c = getchar();
								printf("追われているのは自分もでありお互い様だが、まだ捕まる訳にはいかない。\n");
								c = getchar();
								printf("妹は気絶したまま未だに目を覚ましていない。自首するのは彼女を助けた後だ。\n");
								c = getchar();
								printf("以前のワクチンを改良していけば、紫苑を元の姿に戻し、癌を治療する事ができる筈だ。まだ希望はある。\n");
								c = getchar();
								printf("次こそは、紫苑を必ず助ける。");
								c = getchar();

								game_num = 4;
								score_gameover = score_re();				//点数を入れる。
								gameover_wl(4, score_gameover);				//脱出の方法による成功の判断
								mass = gameover();							//残りのマスを消す
								sion = 10;									//プレイの終了
								j = j + 150;
								play = 0;
								esc = 0;
							}
						}

						//"クールザの鍵"があって、同僚と仲間になって、船付き場についたら、脱出
						if (sion == 0) {
							printf("明石「ここです？」\n");
							c = getchar();
							printf("「はい。操縦は任せます」\n");
							c = getchar();
							printf("社長「おい、待て」\n");
							c = getchar();
							printf("「………！？」\n");
							c = getchar();
							printf("そこにいたのは、身体の半分が異形となった僕の妹??柳原紫苑だった。\n");
							c = getchar();
							printf("紫苑。\n");
							c = getchar();
							printf("僕は実の妹を助けるために、この研究を始めた。\n");
							c = getchar();
							printf("柳原の家系には女系に遺伝癌があり、女として生まれると20代半ばで全身に癌が多発して死ぬ。\n");
							c = getchar();
							printf("その治療するため、遺伝子を組み換える酵素??ヌクレアーゼの研究をするため僕はこの会社に入った。\n");
							c = getchar();
							printf("しかし、研究の過程でこの技術が生物兵器として使える事が解ってしまった。\n");
							c = getchar();
							display();
							printf("その事を知った社長は紫苑を人質に取り、僕に兵器開発をするよう指示した。\n");
							c = getchar();//ディスプレイクリア
							printf("だが、今回の事件で、僕の妹は変わり果てた姿になってしまった。\n");
							c = getchar();
							printf("僕は、妹を生かす所か、妹を化け物に変えた。\n");
							c = getchar();
							printf("…………………。\n");

							c = getchar();
							printf("結論から言うと、僕達は助かった。\n");
							c = getchar();
							printf("社長と同僚に、先にクルーザーに乗るよう告げ、僕は銃で彼女の片足を撃って動きを止め、後から乗り込んだ。\n");
							c = getchar();
							printf("島から去っていく僕達を、紫苑は船着き場に佇んで眺めていた。\n");
							c = getchar();
							printf("…………………。\n");
							c = getchar();
							printf("辿り着くまで数日が経過したが、何とか日本に辿り着く事ができた。\n");
							c = getchar();
							printf("だけど、あの時の引き金の感触と紫苑の姿が、ずっと頭から離れない。\n");
							c = getchar();
							printf("紫苑は、何処か悲しそうな表情をしていた。\n");
							c = getchar();
							display();			//ディスプレイクリア
							printf("僕は新たに社長が買い取った別の島で、生物兵器の研究を再開させられた。\n");
							c = getchar();
							printf("この技術が多くの人間を殺すだろう。今回とは比べ物にならないくらい大勢の人間を。\n");
							c = getchar();
							printf("でも、もう僕には全てがどうでもよかった。\n");
							c = getchar();
							printf("自分にとって大切な人は、この世界にはもういない。\n");
							c = getchar();
							printf("僕には人を殺せても、人を生かす事なんて出来やしない。\n");
							c = getchar();

							game_num = 3;
							score_gameover = score_re();		//点数を入れる。
							gameover_wl(3, score_gameover);		//脱出の方法による成功の判断
							mass = gameover();					//残りのマスを消す
							j = j + 150;						//プレイの終了
							play = 0;							
							esc = 0;
						}
					}
				}
			}
		}
	}
	return	game_num;
}

void memo() {

	
	if (memoid == 1) {

	
	for (mr = 0; mr < 9; mr++) {												//難易度をEasyにしたときのメモ帳のUI

	
			mp = mr % 5 ;
			
		
				posxy(70, POS_SY+1 + mp);
				printf("|");
					if (strcmp(save[mr].name, "1")) {
					posxy(75+mr*7-mp*7, POS_SY + 1 + mp);
					printf("%s:%s", save[mr].name, save[mr].explan);			//Hintの名前と説明を出力

			}
		}
	}
	else if (memoid == 2) {


		for (mr = 0; mr < 9; mr++) {											//難易度をNormalにしたときのメモ帳のUI
			mp = mr % 5;				


			posxy(90, POS_SY + 1 + mp);
			printf("|");
			if (strcmp(save[mr].name, "1")) {
				posxy(95 + mr * 5 - mp * 5, POS_SY + 1 + mp);
				printf("%s", save[mr].explan);									//Hintの説明を出力


			}
		}
	}
}

void inprint(char name[10], char explan[10]) {								//Hintの出力の関数
	int ii;																	//検索用変数
	int mip=0;
	for (ii = pp; ii>-1; ii--) {											//Hintの名前がもう出力できているときは出力しない
		if (!strcmp(save[ii].name, name)) {
			mip = 1;														
		}
	}
	if(mip==0){
	strcpy_s(save[pp].name, sizeof(save[pp].name), name);					//Hintの名前を出力
	strcpy_s(save[pp].explan, sizeof(save[pp].explan), explan);				//Hintの説明を出力
	pp++;
	}
	mip = 0;



}
void monster_dis() {									//エナミーのimageの出力関数

//	0, "ゾンビコロニー", "打", 0
//		, 1, "ゾンビ植物", "遠", 1
//		, 2, "蟲ゾンビ", "切", 2
//		, 3, "ゾンビプラント", "遠", 1
//		, 4, "アラクネ", "切", 2




	if (!strcmp(data[i].monster, "ゾンビコロニー")) {	//敵がゾンビコロニーのとき

		posxy(POS_CX + 20, POS_CY + 1);		printf("	     ,r      :r        7      r:     ;r     :;,       	 \n");
		posxy(POS_CX + 20, POS_CY + 2); 	printf("	       r      :7      ,r.      .r.     i;     ,7      r:       	 \n");
		posxy(POS_CX + 20, POS_CY + 3); 	printf("	    ,i;ii:   ,:i:.  :;ii;;i  ,;ii;;  iiii;;  .,i:.    ;i,,     	 \n");
		posxy(POS_CX + 20, POS_CY + 4); 	printf("	    riiiirX;;i:::;i X7i:::;  7X7i:i.:iiii;;i;iii,;X;;i:,:;;    	 \n");
		posxy(POS_CX + 20, POS_CY + 5);		printf("	   @Mr.:,;XX.:ZBr::iXXi,,7@2 iXX:.7MMr,:rX7: 7MMr,XS;.iSS;;    	 \n");
		posxy(POS_CX + 20, POS_CY + 6);		printf("	   8Mr :;r7rirB0; .;77i, 7MB::r7;:iWMi  :Xr. :@@;,r7;.XMMX:    	 \n");
		posxy(POS_CX + 20, POS_CY + 7);		printf("	   7WX;7rrr;;rBW7,i;r7r;:rWS;r;;;;rZ0Sr;;;r7r78B7r;;;i;@Z...   	 \n");
		posxy(POS_CX + 20, POS_CY + 8);		printf("	 XMWBBW@X;;;8WB0W@Brii7@@W0WWB7irBWB0BW@X:7@WBB0BWSi7X0BBXXi   	 \n");
		posxy(POS_CX + 20, POS_CY + 9);		printf("	 M@B00BBW;iXW00000WW;iXZa8B0BWZ:SWB000BBBiSWB0000BZrWBB0BWMa   	 \n");
		posxy(POS_CX + 20, POS_CY + 10);	printf("	rZ7B0008Wr:aB000000W7:aB2XXZ0W8iZB00080ZB;ZB00000002B00000WM   	 \n");
		posxy(POS_CX + 20, POS_CY + 11);	printf("	XSiB000aBri0B00000BW7:ZWB0aXXS07BB00000Z020000000008000000WM   	 \n");
		posxy(POS_CX + 20, POS_CY + 12);	printf("	 SWB0000@;iBB000000Wri8B00BB8S7rBBB0888BBZB00000000B080008WM   	 \n");
		posxy(POS_CX + 20, POS_CY + 13);	printf("	 .MB000BXi;BSZB000BX,i8W0000W@7XX2a0B00BX70B00000BBZB00000@Z   	 \n");
		posxy(POS_CX + 20, POS_CY + 14);	printf("	  WW00BB;;;S7XWB0B0r  XW0BBBW;;M7XaXa8WW;i:2B0080WX,aB800BM.   	 \n");
		posxy(POS_CX + 20, POS_CY + 15);	printf("	  8@8ZWBr:iX .MZBWW7  78WSr@7 X;,X@BrXZX;;.XW000BSi ;BBXa@a    	 \n");
		posxy(POS_CX + 20, POS_CY + 16);	printf("	  SM7r@a;irS  M;r@S7  7X@7rM  2 .S@B,8@r,i 7W00BWr. ;2WrXM7    	 \n");
		posxy(POS_CX + 20, POS_CY + 17);	printf("	  SM::Ma;XXX  M,,MXX  rXM;XM  2iiX@B.ZM. rir@ZiWM7;.ra@ZZMX    	 \n");
		posxy(POS_CX + 20, POS_CY + 18);	printf("	  rM. MX.,Z;  M7XMX2  X2M.2M  S7 SMBBM:  Si XS,MrirrXZ@;7M     	 \n");
		posxy(POS_CX + 20, POS_CY + 19);	printf("	  7MX M   rr  MMMX..  :Z@ Mr  Xr  S@M7   ;  7MSW,  , XM;07     	 \n");
		posxy(POS_CX + 20, POS_CY + 20);	printf("	   @S M:      8MM      .i7M,      7M8.      a7SM:    rMiW7     	 \n");
		posxy(POS_CX + 20, POS_CY + 21);	printf("	   2W 7,      XM.        8M       :Mr         8@      MXi;   	 \n");





	}else if (!strcmp(data[i].monster, "ゾンビ植物")) {		//敵がゾンビ植物のとき

		posxy(POS_CX + 24, POS_CY + 1);	printf("	         ,,:::       r       rB                   	 \n");
		posxy(POS_CX + 24, POS_CY + 2); 	printf("	      :issssssHsrrr  B9,i9SsXB,                   	 \n");
		posxy(POS_CX + 24, POS_CY + 3); 	printf("	     ,rSsss2s2sH29B@irMs,:r9B@                    	 \n");
		posxy(POS_CX + 24, POS_CY + 4); 	printf("	  ,sr, ,:ir:;r22rsSXssSXGGGX@                     	 \n");
		posxy(POS_CX + 24, POS_CY + 5);	printf("	  ,2XGs:,  ,,  ,     :,rM@BG:,                    	 \n");
		posxy(POS_CX + 24, POS_CY + 6);	printf("	     ,9sG92BGii9S sriir 2B@Msr    292,            	 \n");
		posxy(POS_CX + 24, POS_CY + 7);	printf("	      :BG@Bi,;rssSB@29Mi S9XX@MGr@5               	 \n");
		posxy(POS_CX + 24, POS_CY + 8);	printf("	       sXGi ;rsrsir,s2B,       M@:                	 \n");
		posxy(POS_CX + 24, POS_CY + 9);	printf("	       r2r ,:i,::S, sS  ,r      B@                	 \n");
		posxy(POS_CX + 24, POS_CY + 10);	printf("	       ,i,,,,,rsMMi ,  r@:   ,s:MM                	 \n");
		posxy(POS_CX + 24, POS_CY + 11);	printf("	       rr2s2222X, i, rG@2  ,,  9Mi                	 \n");
		posxy(POS_CX + 24, POS_CY + 12);	printf("	        ,iGM@; ,  :rSr:       MB,                 	 \n");
		posxy(POS_CX + 24, POS_CY + 13);	printf("	          iMs, :rri         s@s                   	 \n");
		posxy(POS_CX + 24, POS_CY + 14);	printf("	                        r@Br                      	 \n");
		posxy(POS_CX + 24, POS_CY + 15);	printf("	                   ,r2ir@s                        	 \n");
		posxy(POS_CX + 24, POS_CY + 16);	printf("	            ,iririr:, ,G@,      r2MBMri           	 \n");
		posxy(POS_CX + 24, POS_CY + 17);	printf("	     ,   rXGr,,GGBM@B@22B@B@B2XG29GBi             	 \n");
		posxy(POS_CX + 24, POS_CY + 18);	printf("	     ,:G@2      :s@BMG@BMM@9rrr;9G9M@M@M@r        	 \n");
		posxy(POS_CX + 24, POS_CY + 19);	printf("	             :s@B@B    i:is9sSM@Gr      B@B@MG52i 	 \n");
		posxy(POS_CX + 24, POS_CY + 20);	printf("	          iG@M2i5B   i, sG@   si@M,      :s       	 \n");
		posxy(POS_CX + 24, POS_CY + 21);	printf("	                     ,,2X,       i:               	 \n");


	}else if (!strcmp(data[i].monster, "蟲ゾンビ")) {		//敵が蟲ゾンビのとき

		posxy(POS_CX + 24, POS_CY + 1);	printf("	@@@@@@@@@@@@@@7@@@@. @@  .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 2); 	printf("	@@@@@@@@@@@@@@@@@@@  7@ .@:0@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 3); 	printf("	@@@@@@@@@@@@@@@@@@@      2@X2M@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 4); 	printf("	@@@@@@@@@@@@@@@@@@      .    .::::iii:..       :.:::2@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 5);	printf("	@@@@@@@@@@@@@@@@@@i    i:                               r@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 6);	printf("	@@@@@@@@@:    @@@@@r .:7  i.    ir:..            i7@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 7);	printf("	@@@@@@@@   :.  @@@@@. ::.  ..   .:.i7777rii:i:72228@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 8);	printf("	@@@@@@@i ..r@   @       :...7   ...     .. .             @@@	 \n");
		posxy(POS_CX + 24, POS_CY + 9);	printf("	@@@@@@@. ..@@@     ..@Z@@777::    ...:.    . 7@@7i:  ..:@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 10);	printf("	@@@@@@@X  :@@@@i .@@@@@@  :27S  i..7r.:i       .@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 11);	printf("	@@@@@@@@i  @@@@@@@@@@@    .i7r  .:: :ri::r :.     @@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 12);	printf("	@@@@@@@@@@  2@@@@@@@@  .iir2  ::.@@i  :;i.  r7.   @@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 13);	printf("	@@@@@@@@@@@  @@@@@@@@  :..r2   . .a@r:::...   :.   @@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 14);	printf("	@@@@@@@@@@@@@@@@@@@@@@@@2:  @@7i:  @@@@@: .:.  .   :@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 15);	printf("	@@@@@@@@@@@@@@@@@@@@@@@@@@@  :@@@.  @@@@@@2i:i::.  2@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 16);	printf("	@@@@@@@@@@@@@@@@@@@@@@@@@@7   .@@@   .@@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 17);	printf("	@@@@@@@@@@@@@@@@@@@@@@@@    :@@@@@;   .@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 18);	printf("	@@@@@@@@@@@@@@@@@@@@@@.   .:@@@@@@@.  i@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 19);	printf("	@@@@@@@@@@@@@@: .:::.  . :@@@@@@@@:    @@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 20);	printf("	@@@@@@@@@@@@@7@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 24, POS_CY + 21);	printf("	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@. @@@@@@@@@@@@@@@@@@@@@@	 \n");





	}else if (!strcmp(data[i].monster, "ゾンビプラント")) {			//敵がゾンビプラントのとき

		posxy(POS_CX + 20, POS_CY + 1);	printf("	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 2); 	printf("	@@@@@@@@@@@@@@@@@@@@@@2.::::i2027777i277Z@@@@@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 3); 	printf("	@@@@@@@@@@@@@@@M@@2777::::.....:...::.   ..:2@@@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 4); 	printf("	@@@@@@@@@@@@@S :.:riir77. ...  ....         .:i@@@@@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 5);	printf("	@@@@@@@@@@@7::727:... .r:      :.. .i::r:   :.  ..:@@@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 6);	printf("	@@@@@@. .7::::.:7: .:  .r7::ii..:: i. ;7..rr...  . .:@@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 7);	printf("	@@@@@@:irr:      ..   :i:i:ri..i:7727X82aa7::ii:i:.:i:8@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 8);	printf("	@@@@@X:i7;:    :r::..   rr8@22M@M0@@@8X7ri: .     :i: i   @@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 9);	printf("	@@@@@ r07. .: .@. @r .iM  @8r@i:@@SB@B27i:.      .   .77a: .@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 10);	printf("	@@@@8 ;7:  .ir0@  @7r@@@ .@2@. 7@@rM2S7::.. ....:::.   .7@@ 22@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 11);	printf("	@@@S .7ri:i7W:2@7.@airB@:S@@@2X722i:rii7i.  :::i.:72; 7:  @@: .@@	 \n");
		posxy(POS_CX + 20, POS_CY + 12);	printf("	@M...:rriii@r.iZ7.. ::rX8@@Xi22@Mi.     .:  .  r2i:7B.7@r  @@M@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 13);	printf("	@7..ii.ir::..7X22.:2@@@@772i:ri;i..        i .   .:. W0@@; @MXB@@	 \n");
		posxy(POS_CX + 20, POS_CY + 14);	printf("	@8@@.7r::8@77@@@@@@@@@@::7ir:      .       : 7:  .@.  7XX77  2@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 15);	printf("	@@@@2@@8@@@@@@@@@@@@@@..27 .i.  :  ..  .:.   7@7 i@@7  a2. .M@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 16);	printf("	@@@@@@@@@@@@@@@@@@@@@. 07i ...        iii:  :.7Mi:.r@2rSr;@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 17);	printf("	@@@@@@@@@@@@@@@@@@@@@ .@2i: : .:. .    :i: 27  @2X;. :r  :@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 18);	printf("	@@@@@@@@@@@@@@@@@@@@@ .@077:ri.:. :::i.::7iM@.  XrZX7:.::@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 19);	printf("	@@@@@@@@@@@@@@@@@@@@@2 .:r727ir::.;i::7i .7 @2ii7 Bi.B@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 20);	printf("	@@@@@@@@@@@@@@@@@@@@@@@Z77:i;r7;00ii:7r.722 ..ii  :@28@@@@@@@@@@@	 \n");
		posxy(POS_CX + 20, POS_CY + 21);	printf("	@@@@@@@@@@@@@@@@@@@@@@@@@@@X7i7X0ZZ@@@@7@@7M@:....X0MB@@@@@@@@@@@	 \n");


		}else if(!strcmp(data[i].monster, "アラクネ")){			//敵がアラクネのとき
		posxy(POS_CX + 24, POS_CY + 1);		printf("		         irEBBBOENEOMBGviivriii                      	 \n");
		posxy(POS_CX + 24, POS_CY + 2); 	printf("		       iBBBBVrrrrJFNGEBBBBBBBBB   ii                 	 \n");
		posxy(POS_CX + 24, POS_CY + 3); 	printf("		     iBBBNviii  iiirUivSMEEBBBBE rBBO                	 \n");
		posxy(POS_CX + 24, POS_CY + 4); 	printf("		     BBZJiiiiiiiiiiiiivLjoFXZBBB iMBi  ii            	 \n");
		posxy(POS_CX + 24, POS_CY + 5);		printf("		    kBBNriiiiriiiiiriLrFXSNMBBBBN BBi vBBBi i        	 \n");
		posxy(POS_CX + 24, POS_CY + 6);		printf("		    XBBBBGUYvvrYJrivLUSOMBBBBBBBBMBBBOBBBBXBBBBi     	 \n");
		posxy(POS_CX + 24, POS_CY + 7);		printf("		    iBBBBBBBOGMvioNPOMOBBBBFrivoNIIMBBBUvBBMuiBBBi   	 \n");
		posxy(POS_CX + 24, POS_CY + 8);		printf("		     iBBBBZMi uGiOBBBGMBBMriivBBV  PMBBBBkBBBi  BBBv 	 \n");
		posxy(POS_CX + 24, POS_CY + 9);		printf("		      iuiFBBBBBBBBBBBBBSBOuviiYBBBBBBBBBB   iBBi EBB 	 \n");
		posxy(POS_CX + 24, POS_CY + 10);	printf("		      iBriiEBBBBBBMBBBMBFUBBBXJvFMBBBBGJBBjI  iB  BB 	 \n");
		posxy(POS_CX + 24, POS_CY + 11);	printf("		   iBBBi        YOuYBOrEMIviBBBBBBBViNXIoi        BBY	 \n");
		posxy(POS_CX + 24, POS_CY + 12);	printf("		  iBBBr        riMBBNi       oBvLEBqrOUiBBBGFi    BB 	 \n");
		posxy(POS_CX + 24, POS_CY + 13);	printf("		 iJri       ivNBi              iFoNMGBBLirBBvBi   vi 	 \n");
		posxy(POS_CX + 24, POS_CY + 14);	printf("		           iBBv                   iIPUBi    rOL      	 \n");
		posxy(POS_CX + 24, POS_CY + 15);	printf("		          ivB                       iiBi     EEB     	 \n");
		posxy(POS_CX + 24, POS_CY + 16);	printf("		          iBN                       iLBP     NBB     	 \n");
		posxy(POS_CX + 24, POS_CY + 17);	printf("		           MB                        BBB     iBr     	 \n");
		posxy(POS_CX + 24, POS_CY + 18);	printf("		          iY                         iBi    rBBi     	 \n");
		posxy(POS_CX + 24, POS_CY + 19);	printf("		                                     rB     BB       	 \n");
		posxy(POS_CX + 24, POS_CY + 20);	printf("		                                     uB    iB        	 \n");
		posxy(POS_CX + 24, POS_CY + 21);	printf("		                                      r              	 \n");

	}


}
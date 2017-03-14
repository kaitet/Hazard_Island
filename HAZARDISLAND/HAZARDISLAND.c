

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include <conio.h>

#define POS_TX 1					//���ݒn�\����X�ʒu
#define POS_TY 1					//���ݒn�\����Y�ʒu
#define POS_MX 120					//map�\����X�ʒu
#define POS_MY 2					//map�\����Y�ʒu
#define POS_CX 0					//���݂̓��e��X�ʒu 
#define POS_CY 5					//���݂̓��e��Y�ʒu
#define POS_IX 120					//�A�C�e���\����X�ʒu
#define POS_IY 8					//�A�C�e���\����Y�ʒu
#define POS_SX 0					//�I�����̕\����X�ʒu
#define POS_SY 28					//�I�����̕\����Y�ʒu
#define SEL_S 0						//�I���̌���
#define O_s 100						//delay�̎���

int memoid = 0;						//��Փx�̕ϐ�
 int check_place=0;					//�G�i�~�[�̑��݂̊m�F
 int m;								//�ړ��}�X��
 int item_cor;						//���݂̃C���x���g���̈ʒu
 int em_att;						//monster�̑���
 int i;								//���ݒn�̏��
 int j;								//�Q�[���I���p�ϐ�
 int mass;							//�����}�X��
 int mat1, mat2, mat3, mat4;		//keyitem

 int game = 1;						//���X�^�[�g�̕ϐ�
 int s1=0;							//�X�R�A�{�[�h�̌����p�ϐ�
 int s2 = 0;						//�X�R�A�{�[�h�̕\���p�ϐ�
 int esc;							//�E�o��Ԃ�\���O�F�E�o���Ă���1�F�E�o���ĂȂ�
 int esc1;							//�Q�[���̌��ʂ̕\���p�ϐ��O�F�\������1�F�\���Ȃ�
 int enter_x;						//enter�֐��p�ϐ��P
 int enter_y;						//enter�֐��p�ϐ��Q
 int enter_c;						//enter�֐��p�ϐ��R
 int boat_esc=0;					//�E�o�̕��@�p�ϐ�
 int same=0;						//���������̔��f�p�ϐ�
 int pp = 0;						//�������̌����p�ϐ��ŏ���Ԃ�0
 int mr = 0;						//�������̕\���p�ϐ��P
 int mp;							//�������̕\���p�ϐ��Q
 char sl;							//�I���̂Ƃ���enter�p�ϐ�
 int sl1 = 0;						//�I��p�ϐ�
 int fight_re;						//�퓬���ʗp�ϐ�
 int score_gameover;				//�X�R�A�p�ϐ�
 int sear_cor;						//�T���ς݂��m�F�p�ϐ�
 int escape_num;					//�E�o�ԍ��p�ϐ�
 int escape_item;					//�E�oitem�p�ϐ�
 int escape_person;					//�E�operson�p�ϐ�
 int game_num;						//gameover����p�ϐ�
 int move_search;					//�K��or�T��or�퓬�p�ϐ�
 int act_sel;						//�I�������͗p�ϐ�
 int wp1;							//����̑I��p�ϐ�
 int at1;							//�퓬�I��p�ϐ�
 int lose_point;					//�s�k�񐔗p�ϐ�
 int re;							//�퓬���ʗp�ϐ�
 int boss_1 = 1;					//boss �����A�C�e���P�p�ϐ�
int boss_2;							//boss �����A�C�e���Q�p�ϐ�
 int key, key1;						//���̃A�C�e����T�����߂̔ԍ�
 char d;

struct memochou {		//Hint�ł��郁�����̏��
	 int id;			//Hint��ID
	 char name[40];		//Hint�̖��O
	 char explan[40];	//Hint�̓��e		

 }save[100];

struct map {				//�}�b�v�̏��
	int id;					//�}�b�v��ID
	char name[40];			//�}�b�v�̖��O
	char item[40];			//�}�b�v��̃A�C�e��
	char monster[40];		//�}�b�v��̃G�i�~�[�̖��O
	char person[40];		//�}�b�v��̃L�[�p�[�\��
	char escape[40];		//�}�b�v��̒E�o���@

}data[100];

struct player {				//�v���C���[�̏��
	int item_id;			//�v���C���[�̃A�C�e����ID
	char item_name[40];		//�v���C���[�̃A�C�e���̖��O
	char item_explan[80];	//�v���C���[�̃A�C�e���̐���
}stock[100];

struct score {				//�X�R�A�̏��
	int item_point;			//�A�C�e���̏��
	int mass_point;			//�c��̃}�X�̏��
	int escape_point;		//�E�o���@�̏��
}score[10];

struct monster {			//�v���C���[�̏��
	int monster_id;			//�G�i�~�[��ID
	char monster_name[40];	//�G�i�~�[�̖��O
	char monster_att[40];	//�G�i�~�[�̏��
	int monster_att_id;		//�G�i�~�[�̃A�C�e����ID

}enermy[100];

struct combination {		//�g�ݍ��킹�A�C�e���i�L�[�A�C�e���j�̏��
	int combination_id;		//�g�ݍ��킹�A�C�e���i�L�[�A�C�e���j��ID
	char material1[40];		//�ޗ��ɂȂ�A�C�e���P�̖��O
	char material2[40];		//�ޗ��ɂȂ�A�C�e���Q�̖��O
	char combination[40];	//�g�ݍ��킹�A�C�e���i�L�[�A�C�e���j�̖��O

}item[100];

struct score_save {			//�_���̈ꎞ�ۑ����
	int score;				//�_��
	char name[30];			//���O
	int id;					//ID
};

struct cor_info{		//���݂̏��
	char cor[100];
}info[100];

struct score score[10] = {	//�X�R�A�\���̂̏�����
	0, 30, 0				
	//�A�C�e���͍ŏ������Ă��Ȃ��̂�0
	//�c��̃}�X�̐�����30�}�X�Ȃ̂�30
	//�E�o���@�͍ŏ��E�o���ĂȂ��̂�0

};

struct score_save scoreboard[100] = {  //�X�R�A�{�[�h�\���̂̏�����
	0,"",1,								//1�`9���ʂ̓_���Ɩ��O���Ȃ��̂łO�Ɓh�h
	0,"",2,
	0,"",3,
	0,"",4,
	0,"",5,
	0,"",6,
	0,"",7,
	0,"",8,
	0,"",9,
};

struct map data[100] = {	//�}�b�v�\���̂̌��ݏ���ۑ�
	00, "��������", "0", "�A���N�l", "0", "0"
	, 01, "��������", "��������1", "�]���r�R���j�[", "0", "0"
	, 02, "�u��������", "0", "�]���r�v�����g", "0", "0"
	, 03, "�u��������*���V�F���^�[", "0", "0", "����", "0"

	, 10, "�X��", "�y��s�@�̌�", "�]���r�A��", "0", "0"
	, 11, "�X��", "�X�}�z", "0", "0", "0"
	, 12, "�X��", "�X�P�W���[����", "�]���r�A��", "0", "0"
	, 13, "�X��", "�}", "0", "0", "0"

	, 20, "��", "0", "0", "0", "0"
	, 21, "�{������", "���ˊ�", "0", "0", "0"
	, 22, "�{������", "���������Q", "�]���r�R���j�[", "0", "0"
	, 23, "�{������", "�C���L�b�g", "0", "0", "0"

	, 30, "��", "���L", "峃]���r", "0", "0"
	, 31, "�����H", "0", "0", "0", "�y��s�@"
	, 32, "�{������", "USB", "�]���r�R���j�[", "0", "0"
	, 33, "�{������", "0", "0", "0", "0"

	, 40, "�Ј���*�V�F���^�[", "��̃��C�^�[", "0", "�В�", "0"
	, 41, "��", "���C�^�[�I�C��", "0", "0", "�{�[�g"
	, 42, "���l", "0", "峃]���r", "0", "0"
	, 43, "�D�t����", "0", "0", "0", "�N���[�U" 
	//x���W��y���W�̏���00�`43�ŕ\��
	//���݂̃}�X�̖��O��\��
	//���݂̃}�X�ɂ���A�C�e����\��
	//���݂̃}�X�ɂ���G�i�~�[��\��
	//���݂̃}�X�ɂ���l��\��
	//���݂̃}�X�ɂ���E�o���@��\��
};

struct monster enermy[100] = {	//�G�i�~�[�\���̂̏�����
	0, "�]���r�R���j�[", "��", 0
	, 1, "�]���r�A��", "��", 1
	, 2, "峃]���r", "��", 2
	, 3, "�]���r�v�����g", "��", 1
	, 4, "�A���N�l", "��", 2
	//�G�i�~�[��ID��\��
	//�G�i�~�[�̖��O��\��
	//�G�i�~�[�̑�����\��
	//�G�i�~�[�̑���ID��\��
};

struct combination item[100] = {	//�L�[�A�C�e���\���́F���̃��[���ɍ��킹�đg�ݍ��킹���N����B
	0, "��̃��C�^�[", "���C�^�[�I�C��", "���g�����郉�C�^�["
	, 1, "�Őj", "�}", "�Ŏ}"
	, 2, "���ˊ�", "�R��", "���N�`��"

	//�L�[�A�C�e����ID
	//�L�[�A�C�e������邽�߂ɕK�v�ȃA�C�e���P
	//�L�[�A�C�e������邽�߂ɕK�v�ȃA�C�e���P
	//�L�[�A�C�e���̖��O
};

struct player stock[100] = {		//�v���C���[�C���x���g���̌��ݏ���ۑ�
	0, "�n���}�[", ""
	, 1, "�T�u�}�V���K��", ""
	, 2, "�R���o�b�g�i�C�t", "" 
	//�v���C���[�̃A�C�e����ID
	//�v���C���[�̃A�C�e���̖��O
	//�v���C���[�̃A�C�e���̐���
};

const struct map reset_m[100] = {	//�}�b�v�\���̂̏������
	00, "��������", "0", "�A���N�l", "0", "0"
	, 01, "��������", "��������1", "�]���r�R���j�[", "0", "0"
	, 02, "�u��������", "0", "�]���r�v�����g", "0", "0"
	, 03, "�u��������*���V�F���^�[", "0", "0", "����", "0"

	, 10, "�X��", "�y��s�@�̌�", "�]���r�A��", "0", "0"
	, 11, "�X��", "�X�}�z", "0", "0", "0"
	, 12, "�X��", "�X�P�W���[����", "�]���r�A��", "0", "0"
	, 13, "�X��", "�}", "0", "0", "0"

	, 20, "��", "0", "0", "0", "0"
	, 21, "�{������", "���ˊ�", "0", "0", "0"
	, 22, "�{������", "���������Q", "�]���r�R���j�[", "0", "0"
	, 23, "�{������", "�C���L�b�g", "0", "0", "0"

	, 30, "��", "���L", "峃]���r", "0", "0"
	, 31, "�����H", "0", "0", "0", "�y��s�@"
	, 32, "�{������", "USB", "�]���r�R���j�[", "0", "0"
	, 33, "�{������", "0", "0", "0", "0"

	, 40, "�Ј���*�V�F���^�[", "��̃��C�^�[", "0", "�В�", "0"
	, 41, "��", "���C�^�[�I�C��", "0", "0", "�{�[�g"
	, 42, "���l", "0", "峃]���r", "0", "0"
	, 43, "�D�t����", "0", "0", "0", "�N���[�U" };

const struct player reset_p[100] = {		//�v���C���[�\���̂̏������
	0, "�n���}�[", ""
	, 1, "�T�u�}�V���K��", ""
	, 2, "�R���o�b�g�i�C�t", "" 
};

struct memochou save[100] = {		//�������iHint)�̌��ݏ���ۑ�
	0,"1","1",
	1,"1","1",
	2,"1","1",
	3,"1","1",
	4,"1","1",
	5,"1","1",
	6,"1","1",
	7,"1","1",
	8,"1","1",
	//ID��Hint��T��������
	//Hint�̖��O�͓�Փx��Easy�ɂ����Ƃ������ɕ\��
	//Hint�̐����͓�Փx��Normal��Easy�ɂ����Ƃ��ɕ\��
};

const struct memochou reset_me[100] = { //�������iHint)�\���̂̏������
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

//�֐��̐錾

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
	while (game) {									//console���n�܂����Ƃ�
		memcpy(&data, &reset_m, sizeof(reset_m));	//�}�b�v�̏�����
		memcpy(&stock, &reset_p, sizeof(reset_p));	//�v���C���[�C���x���g���̏�����
		pp = 0;										//�������̌����p�ϐ��ŏ���Ԃ�0
		memcpy(&save, &reset_me, sizeof(reset_me));	//�������̏�����
		esc1 = 1;									//�Q�[���̌��ʂ̕\���p�ϐ��O�F�\������1�F�\���Ȃ��ŏ���Ԃ͂P
		same = 0;									//�퓬�̈��������̌��ʗp�ϐ��O�F������������Ȃ�1�F���������ŏ���Ԃ�0
		
		while (play) {								//�Q�[���̃v���C���n�܂����Ƃ�
			system("mode con:cols=140 lines=35");	//console�̑傫�������߂�B
			system("title HAZARD ISLAND");			//console�̖��O�����߂�B
		
			struct cor_info info[100];				//���̏�Ԃ�錾
			
			esc = 1;								//�E�o��Ԃ�\���O�F�E�o���Ă���1�F�E�o���ĂȂ��ŏ���Ԃ͂P
													
			

			item_cor = 3;							//���݂̃C���x���g���̈ʒu�ŏ��ɕ����3�����Ă���̂�3����n�܂�B
		
			mat1 = 0;								//�L�[�A�C�e���̍ޗ��ɂȂ�A�C�e���̌����p�ϐ��P�ŏ���Ԃ�0
			mat2 = 0;								//�L�[�A�C�e���̍ޗ��ɂȂ�A�C�e���̌����p�ϐ��Q�ŏ���Ԃ�0
			mat3 = 0;								//�L�[�A�C�e���̌����p�ϐ��ŏ���Ԃ�0
			m = 0;									//�ړ��}�X���ŏ���Ԃ�0

			i = 16;									//�n�܂�ʒu �}�b�v���17�Ԗڈ�ԍ�������n�܂�B�i���A���j���i4�A0�j
			escape_item = 0;						//�E�o�p�A�C�e���̌����p�ϐ��ŏ���Ԃ�0
			score_gameover = 0;						//�I������Ƃ��̃X�R�A�̏��ŏ���Ԃ�0



			mass = 0;								//�}�X�ϐ��ňړ������}�X��\���B�ŏ���Ԃ�0

			act_sel = 0;							//����I����\���āA�ŏ���Ԃ�0


			title_dis();							//�^�C�g���̕\��
			prologue_dis();							//�v�����O�̕\��
			
			explan();								//�Q�[�������̕\��

			for (j = 0; j < 100; j++) {				//�Q�[���I���p�ϐ�100�𒴂���ƃv���C���I���B
				if (mass < 31) {					//�}�X�ϐ�		  30�𒴂���ƃv���C���I���B30��ړ�����ƃv���C���I���B
					c = getchar();					//enter�̓���
					system("cls");					//��ʂ̏�����
					sear_cor = i;					//�T���ς݂��m�F
					map_dis(); 						//�}�b�v�̕\��
					cor_dis();						//���ݒn�̕\��
					item_dis(); memo();				//�A�C�e���̕\��
					act_sel = act_select();			//����I���̕\��
					check_place = 0;				//�G�i�~�[�̑��݂̊m�F�ŏ���Ԃ�0

					if (act_sel == 1) {					//�P��I�񂾂Ƃ��A�T��
						item_cor = player_research();	//�T�����ʂ̕\��

					
						//�ޗ��A�C�e����2����Ƃ��L�[�A�C�e���ɑg�ݍ��킹����B
						for (mat1 = 0; mat1 < 50; mat1++) {			//�ޗ��A�C�e��1���C���x���g���̒���50�܂Ō���
							for (mat2 = 0; mat2 < 50; mat2++) {		//�ޗ��A�C�e��2���C���x���g���̒���50�܂Ō���
								for (mat3 = 0; mat3 < 3; mat3++) {	//�L�[�A�C�e�����\���̂̒��łR�܂Ō���
									if (!strcmp(stock[mat1].item_name, item[mat3].material1)) {		//�ޗ��A�C�e��1���C���x���g���̒��ő��݂���Ƃ�
										if (!strcmp(stock[mat2].item_name, item[mat3].material2)) {	//�ޗ��A�C�e��2���C���x���g���̒��ő��݂���Ƃ�
											printf("\n%s��%s��g�ݍ��킹��%s���l�������B", stock[mat1].item_name, stock[mat2].item_name, item[mat3].combination);;
											//�g�ݍ��킹��\��

											if (mat1<mat2) {		 //�ޗ��A�C�e��1�̈ʒu���ޗ��A�C�e��2���O�̂Ƃ�
												strcpy_s(stock[mat1].item_name, sizeof(stock[mat1].item_name), item[mat3].combination);
												//�g�ݍ��킹���L�[�A�C�e�����ޗ��A�C�e��1�̈ʒu�ɒǉ�
												strcpy_s(stock[mat2].item_name, sizeof(stock[mat2].item_name), "0");
												//�ޗ��A�C�e��2�̏���������
												item_cor = mat2;
												//���݃C���x���g���̈ʒu���ޗ��A�C�e��2�̈ʒu�ɂ���B
											}
											else if (mat1>mat2) {//�ޗ��A�C�e��2�̈ʒu���ޗ��A�C�e��1���O�̂Ƃ�
												strcpy_s(stock[mat2].item_name, sizeof(stock[mat2].item_name), item[mat3].combination);
												//�g�ݍ��킹���L�[�A�C�e�����ޗ��A�C�e��2�̈ʒu�ɒǉ�
												strcpy_s(stock[mat1].item_name, sizeof(stock[mat1].item_name), "0");
												//�ޗ��A�C�e��1�̏���������
												item_cor = mat1;
												//���݃C���x���g���̈ʒu���ޗ��A�C�e��1�̈ʒu�ɂ���B
											}
										}
									}
								}
							}
						}		
					}
					else if (act_sel == 2) {  //2��I�񂾂Ƃ��A�ړ�

						i = player_move();	//�ړ��̕\��

						if (i > 99 && i < 120) {	//�����Ȃ����Ɍ��������Ƃ�100�𑫂����̂�100�`119�͈̔͂ɂȂ�B
							i = i - 100;				//������100�������Ċ����̈ʒu��\��
						}



					}
				
					posxy(117, 27); printf("��");	//script�̍Ō��"��"�ŕ\��
				}
				else {
					gameover_wl(0, 0);	//�s�k�̂Ƃ��O�A�_���O�̌��ʕ\��
					j = j + 150;		//150�𑫂���
					play = 0;			//�v���C���I��点��B
				}

			}

		
			play = 0;					//�v���C���I��点��B

		}

		scoreboard[6].score = score_gameover;							//�_�����X�R�A�{�[�h�ɓ����B

	
		system("cls");													//��ʂ̏�����

		
		if (scoreboard[6].score != 0) {									//�X�R�A�{�[�h�̓_����0����Ȃ��Ƃ��A
			if (score_gameover != 0) {									//�_����0����Ȃ��Ƃ��A
				posxy(68, 5); printf("score:%d\n", score_gameover);		//�_���̕\��
				posxy(63, 6); printf("���O�������Ă��������B\n");			//���O�������Ă��������B�̕\��
				posxy(70, 7); scanf_s("%s", &scoreboard[6].name,sizeof(scoreboard[6].name));	//���O�̓���
				c = getchar();

				for (s1 = 5; s1 > -1; s1--) {			//�X�R�A�{�[�h�̏��ʂ�T��
					s2 = s1 + 1;
					if (scoreboard[s1].score < scoreboard[s2].score) {	//�_���������ق�����ɓ����B
						scoreboard[8] = scoreboard[s1];
						scoreboard[s1] = scoreboard[s2];
						scoreboard[s2] = scoreboard[8];
					}


				}

			}
		}

		posxy(68, 9); printf("scoreboard\n");		//�X�R�A�{�[�h��\��

		posxy(52, 13); printf("------------------------------------------\n");
		posxy(52, 14); printf("| 1�ʁF%s", scoreboard[0].name);
		posxy(52, 15); printf("| 2�ʁF%s", scoreboard[1].name);
		posxy(52, 16); printf("| 3�ʁF%s", scoreboard[2].name);
		posxy(52, 17); printf("| 4�ʁF%s", scoreboard[3].name);
		posxy(52, 18); printf("| 5�ʁF%s", scoreboard[4].name);
		posxy(77, 14); printf("�X�R�A�F%d \n",  scoreboard[0].score);
		posxy(77, 15); printf("�X�R�A�F%d \n",  scoreboard[1].score);
		posxy(77, 16); printf("�X�R�A�F%d \n",  scoreboard[2].score);
		posxy(77, 17); printf("�X�R�A�F%d \n",  scoreboard[3].score);
		posxy(77, 18); printf("�X�R�A�F%d \n",  scoreboard[4].score);

		posxy(93, 14); printf("|");
		posxy(93, 15); printf("|");
		posxy(93, 16); printf("|");
		posxy(93, 17); printf("|");
		posxy(93, 18); printf("|");
		posxy(52, 19); printf("------------------------------------------\n");
		c = getchar();

		posxy(60, 25);	printf("���X�^�[�g���܂����H\n");			//���X�^�[�g�I���̕\��
		posxy(60, 26); printf("1.�͂��Q�D������\n");

		posxy(60, 27);
		sl = getchar();
		sl1 = atoi(&sl);				//���X�^�[�g�I���̓���
		while (sl == '\n') {			//enter������܂ŁA���X�^�[�g�I���̓���
			posxy(60, 27);
			sl = getchar();
			sl1 = atoi(&sl);
		}
		game = sl1;				//���X�^�[�g�I���̓��e�ɂ���ăQ�[�������X�^�[�g�P�F���X�^�[�g�Q�F�I���


		c = getchar();
		if (game == 1) {		//�P�F���X�^�[�g
			game = 1;
			play = 1;


		}
		else if (game == 2) {	//�Q�F�I���
			game = 0;
		}
		else {					//���̑��̓��͂�"���̍쓮�͂����܂���B"��\��
			printf("���̍쓮�͂����܂���B\n");

		}
	}
}
		
void condition() {								//�A���N�l�̓o��𔻒f
	
	if (!strcmp(data[17].item, "1")) {			//�ޗ��A�C�e���ł��郉�C�^�[�I�C�����E�����Ƃ�
			if (!strcmp(data[16].item, "1")) {	//�ޗ��A�C�e���ł����̃��C�^�[���E�����Ƃ�
		//�ޗ��A�C�e��2��������ăL�[�A�C�e���������Ă���̂ŃA���N�l���o��
				boss_1 = 0;
			}
			else {

		//���̂ق��̓A���N�l���o�ꂵ�Ȃ�
				boss_1 = 1;
			}
		}


}

int score_re() {	//�X�R�A�̌v�Z

	score_gameover = 0;										//�X�R�A�̏�����
	score_gameover = score_gameover + ((30 - mass) * 100);		//�c��̃}�X�̃X�R�A
	score_gameover = score_gameover + (item_cor * 200);		//�A�C�e���̃X�R�A
	score_gameover = score_gameover + (game_num * 10000);	//�E�o���@�̃X�R�A

															//printf("���Ȃ��̓_����%d", score_gameover);			//�X�R�A�̕\��

	return score_gameover;

}

void title_dis() {			//�^�C�g���̕\��

	posxy(40, 2 + 3); printf("   ��    ��    ��    ��������    ��    ������   ������    \n");
	posxy(40, 3 + 3); printf("   ��    ��   ����        ��    ����   ��   ��  ��   ��   \n");
	posxy(40, 4 + 3); printf("   ��������  ��  ��      ��    ��  ��  ������   ��   ��   \n");
	posxy(40, 5 + 3); printf("   ��    ��  ������    ��      ������  ��  ��   ��   ��   \n");
	posxy(40, 6 + 3); printf("   ��    �� ��    ��  ��      ��    �� ��   ��  ��   ��   \n");
	posxy(40, 7 + 3); printf("   ��    �� ��    �� �������� ��    �� ��    �� ������    \n");

	posxy(41, 9 + 3); printf("      ��  ������  ��        ��    ��     �� ������        \n");
	posxy(41, 10 + 3); printf("      �� ��       ��       ����   ����   �� ��   ��       \n");
	posxy(41, 11 + 3); printf("      ��  ������  ��      ��  ��  �� ��  �� ��   ��       \n");
	posxy(41, 12 + 3); printf("      ��       �� ��      ������  ��  �� �� ��   ��       \n");
	posxy(41, 13 + 3); printf("      �� ��    �� ��     ��    �� ��   ���� ��   ��       \n");
	posxy(41, 14 + 3); printf("      ��  ������  ������ ��    �� ��     �� ������        \n");

	c=getchar();
	
	posxy(45, 18 + 3); printf("�ꏊ�͓��{�񓇂���y����Ɉʒu����Ǔ��B");
	posxy(45, 19 + 3); printf("���̓��ɂāA�������ٌ`�Ɖ����\�����n�߂��B");
	posxy(45, 20 + 3); printf("�u��������E�o���Đ����c��v�ƌ��ӂ����ɕ������B");
	posxy(45, 21 + 3); printf("�ٌ`�̎ҒB���琶���c��邩�B");

	posxy(55, 25 + 3); printf("PRESS THE ANY BUTTON"); 
	
	enter(75, 28);



}

void prologue_dis() {		//�v�����O�̕\��
	system("cls");

	posxy(65, 3); printf("�o�C�I�n�U�[�h�B"); c = getchar();
	posxy(22, 4); printf("�Q�[���Ȃǂł��̒P������ɂ������͂������B�������A���������̏󋵂ɒu�����ȂǍl�������Ȃ������B"); c = getchar();
	posxy(22, 5); printf("�ꏊ�͓��{�񓇂���y����B��萻���ЁA�J���~�A�̏��L���鏬���ȓ��B"); c = getchar();
	posxy(22, 6); printf("�����ł́A�閧���ɐ�������̌������s���Ă����B"); c = getchar();
	posxy(22, 7); printf("�l��������u�́A�����Ō�����C����Ă��̎哱�����Ă����̂����c�c�B"); c = getchar();
	posxy(65, 8); printf("�u�c�c�c�c�c�v"); c = getchar();
	posxy(22, 9); printf("�R���N���[�g�̕������A�u�����̖��@���Ȍ����Ƃ炵�Ă���B"); c = getchar();
	posxy(22, 10); printf("�l�ƁA�J���~�A�̎В���ꓛ�n���́A��������̖\���𓦂�V�F���^�[�ɗ����Ă����Ă����B"); c = getchar();
	posxy(22, 11); printf("�ǂ���畔���ł��鑼�̌��������A�@�ނ̑��������Ă��̂悤�ȏ󋵂ɂȂ��Ă��܂����炵���B"); c = getchar();
	posxy(22, 12); printf("�����Ԃ��o�߂������A���̐l�Ԃ͖����ɒN���K�˂ė��Ȃ��B������A���̊O�������悬�邾�����B"); c = getchar();
	posxy(22, 13); printf("�В��u�`�b�v"); c = getchar();
	posxy(22, 14); printf("�В�����ł�����B�����ɉ΂����悤�Ƃ������A�I�C���؂�Ă����悤���B"); c = getchar();
	posxy(22, 15); printf("�В��u�����A�����v"); c = getchar();
	posxy(22, 16); printf("�В����l�̖����Ă񂾁B"); c = getchar();
	posxy(22, 17); printf("�u�͂��v"); c = getchar();
	posxy(22, 18); printf("�В��u�O�ɏo�Ă�������o����@��T���ė����v"); c = getchar();
	posxy(22, 19); printf("�u�c�c�킩��܂����v"); c = getchar();
	posxy(22, 20); printf("�l�̓V�F���^�[����O�ɏo���B"); c = getchar();
	posxy(22, 21); printf("�Ј����̘L���B���̊O�����悤�Ȑ����������A�l�͊O�̌i�F������B"); c = getchar();
	posxy(22, 22); printf("���ɎՂ��A�����܂Ō��ʂ������ł��Ȃ��B"); c = getchar();
	posxy(22, 23); printf("�����̈�`�q�����������\��������y�f���T���U�炷�w�]���r�v�����g�x�̔��������������낤�B"); c = getchar();
	posxy(22, 24); printf("���̋�C�����Ɣ������z���΁A���̖��̉��ɂ���]���r�B�̒��ԓ�������鎖�ɂȂ邾�낤�B"); c = getchar();
	posxy(22, 25); printf("����܂łɁA���̓�����o����@�������ē���˂΂Ȃ�Ȃ��B"); c = getchar();
	posxy(65, 26); printf("�u�c�c�c�c�c�v"); c = getchar();
	posxy(22, 27); printf("�����̐g���Ă���ׂ��󋵂Ȃ̂ł��낤���A�l�͂Ƃ����؂Ȑl���������C�|���肾�����B"); c = getchar();
	posxy(22, 28); printf("��̉����ɂ���̂��낤���c�c�B"); c = getchar();



	system("cls");
}

void cor_dis() {		//���݈ʒu�̏��̕\��
	posxy(0, 1);
	printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
	posxy(POS_TX, POS_TY);
	printf("\n���݈ʒu:%s\n", data[i].name);		//���݈ʒu�̕\��
	posxy(0, 3);
	printf("----------------------------------------------------------------------------------------------------------------------\n");
}

int act_select() {					//�I�����i������邩�j�̓���  1:�T�� 2:�ړ�
	
									//system("cls");
	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("�������܂����H\n");
	printf("1:�T�� 2:�ړ�\n");
	posxy(POS_SX, POS_SY+3);

	sl = getchar();
	sl1 = atoi(&sl);		//�I�����i������邩�j�̓���
	while(sl=='\n'){		//enter�������܂œ���
			posxy(POS_SX, POS_SY + 3);
			sl = getchar();
			sl1 = atoi(&sl);
	}
	act_sel = sl1;			//���͌��ʂ�����B

	return act_sel;

};

void posxy(int x, int y) {		 //UI�̈ʒu�̐ݒ�
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_gameover() {			//�s�k�����Ƃ��A���ʕ\��
	esc1 =0;
	score_gameover = 0;
	system("cls");
	posxy(22, 7); printf("              ����������                                                                       \n");
	posxy(22, 8); printf("           ������   ������                                                                     \n");
	posxy(22, 9); printf("          ����           ��                      ���������� ������        ��������             \n");
	posxy(22, 10); printf("         ����                     ������         ������������ ����      ����    ����           \n");
	posxy(22, 11); printf("         ����      ��������           ����     ����     ����    ����   ��������������          \n");
	posxy(22, 12); printf("         ����            ����    ����������    ����     ����    ����   ����                    \n");
	posxy(22, 13); printf("           ����         ����     ����    ����  ����     ����    ����    ����                   \n");
	posxy(22, 14); printf("             ������������        ����������    ����     ����    ����     ����������            \n");
	posxy(19, 19); printf("                        ����������                                                             \n");
	posxy(19, 20); printf("                     ����        ����                                                          \n");
	posxy(19, 21); printf("                    ����          ����   ����       ����    ��������       ��������            \n");
	posxy(19, 22); printf("                    ����          ����   ����      ����   ����    ����     ������              \n");
	posxy(19, 23); printf("                    ����          ����    ����    ����   ��������������    ����                \n");
	posxy(19, 24); printf("                    ����          ����     ����  ����     ����             ����                \n");
	posxy(19, 25); printf("                      ����      ����         ������        ����            ����                \n");
	posxy(19, 26); printf("                         ��������             ����           ��������      ����                \n");


	


}

void print_win() {					//���������Ƃ��A���ʕ\��
	esc1 = 0;
	system("cls");
	posxy(40, 4); printf("          ������   �� ��         ��     ��     ��        ");
	posxy(40, 5); printf("          ��  ��  ��������       ��     ��     ��          ");
	posxy(40, 6); printf("          ������  ��    ��       ��     ��     ��          ");
	posxy(40, 7); printf("          ��  ��  ��    ��       ����������������          ");
	posxy(40, 8); printf("          ������  ��������              ��             ");
	posxy(40, 9); printf("          ��  ��   �� ��  ��   ��       ��       ��       ");
	posxy(40, 10); printf("          ��  ��   �� ��  ��   ��       ��       ��       ");
	posxy(40, 11); printf("         ��   ��  ��  ��  ��   ��       ��       ��      ");
	posxy(40, 12); printf("        ��    �� ��   ������   ��������������������      ");
	posxy(40, 16); printf("                 ��   ��                          ��           ");
	posxy(40, 17); printf("           ����������������   ������������        ��         ");
	posxy(40, 18); printf("          ��      ��               ��      ��������������   ");
	posxy(40, 19); printf("          ��       ��              ��           ��     ��   ");
	posxy(40, 20); printf("          ������    ��             ��          ��      ��   ");
	posxy(40, 21); printf("          ��   ��    ��   ��       ��         ��       ��    ");
	posxy(40, 22); printf("         ��     ��    �� ��   ������������   ��        ��     ");
	posxy(40, 23); printf("        ��    ����     ��                  ��        ��      ");
	posxy(40, 24); printf("       ��            �� ��               ��       ����        ");





}

int gameover_wl(int game_num, int score_gameover) { //�������ʂƔs�k���ʂ̕\��
	system("cls");

	if (game_num == 0) {		//�s�kscript�̕\��
		
		system("cls");
		map_dis();			//�}�b�v�̕\��
		cor_dis();			//���ݒn�̕\��
		item_dis(); 		//�A�C�e���̕\��
		memo();				//Hint�̕\��
		posxy(POS_SX, POS_SY);
		printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
		posxy(POS_CX, POS_CY);

		printf("�u�����c�c�v\n"); c =getchar();
		printf("���˂ɕ��t���o������A���̏�ɕG�����Ă��܂��B\n"); c =getchar();
		printf("�ُ�Ȃ��炢�ɐg�̂��M���B�ӂƎ����̘r������ƁA���ǂ��s�C���Ȃ��炢�ɂ�������ƕ����オ���Ă����B\n"); c =getchar();
		printf("�V��ӂ��ُ�Ȃ��炢�������Ă���B\n"); c = getchar();
		printf("���Ɋ܂܂��]���r�v�����g�̍y�f���A�g�̂̈�`�q��g�ݑւ��Ďn�߂��e�����B\n"); c =getchar();
		printf("�Ԃɍ���Ȃ������B�����������̓����瑬���E�o���Ă���΁A����Ȏ��ɂ͂Ȃ�Ȃ������B\n"); c =getchar();
		printf("�u���A�������������v\n"); c =getchar();
		printf("�l�̈ӎ��́A�w�����􂯂�悤�Ȍ��ɂƋ��ɓr�₦���B\n"); c =getchar();


		system("cls");
		print_gameover();		//�s�k���ʂ̕\��	
		
			play = 0;			//�v���C�̏I��

	}
	else if (game_num == 1) {	 //�y��s�@�ŒE�o�����Ƃ��̏������ʂ̕\���A�_���̕\��
		print_win();
		posxy(62, 27);	printf("�y��s�@�ŒE�o���܂����B\n");
		posxy(65, 28);	printf("CONGRATULATIONS\n");
		posxy(62, 29);	printf("���Ȃ��̓_����%d", score_gameover);
		play = 0;				//�v���C�̏I��
	}
	else if (game_num == 2) {	 //�{�[�g�ŒE�o�����Ƃ��̏������ʂ̕\���A�_���̕\��
		print_win();
		posxy(62, 27);	printf("�{�[�g�ŒE�o���܂����B\n");
		posxy(65, 28);	printf("CONGRATULATIONS\n");
		posxy(62, 29);	printf("���Ȃ��̓_����%d", score_gameover);
		play = 0;				//�v���C�̏I��	
	}
	else if (game_num == 3) { //�N���[�U�ŒE�o�����Ƃ��̏������ʂ̕\���A�_���̕\��
		print_win();
		posxy(62, 27);		printf("�N���[�U�ŒE�o���܂����B\n");
		posxy(65, 28);		printf("CONGRATULATIONS\n");
		posxy(62, 29);		printf("���Ȃ��̓_����%d", score_gameover);
		play = 0;			//�v���C�̏I��
	}
	else if (game_num == 4) { //�N���[�U�ŒE�o+�V�I�������Ƃ��̏������ʂ̕\���A�_���̕\��
		print_win();
		posxy(62, 27);	printf("�N���[�U�ŒE�o���܂����B\n");
		posxy(63, 28);	printf("�V�I����������܂����B\n");
		posxy(65, 29);	printf("CONGRATULATIONS\n");
		posxy(62, 30);	printf("���Ȃ��̓_����%d", score_gameover);
		play = 0;			//�v���C�̏I��
	}
	play = 0;				//�v���C�̏I��
	c=getchar();
	
}

int gameover() {					//�Q�[���I�o�̔���
	mass = mass + 50;				//�}�X�ϐ��ɂ�50�𑫂��ăQ�[�����I��点��B
	return mass;
	play = 0;						//�v���C�̏I��
}

void map_dis() {		//�}�b�v�̕\��

	int map1;			//���ݒn�̕ϐ�
	char map[30];		//�}�b�v�S�̂̍\����

	for (map1 = 0; map1 < 20; map1++) {		 //���ݒn��'.'�ł���킷�B
		if (map1 == i) {
			map[map1] = '.';
		}
		else if (map1 != i) {				//���ݒn�ȊO��' '�ł���킷�B
			map[map1] = ' ';
		}
	}
	posxy(POS_MX, POS_MY);		 //�}�b�v�̌`������
	printf("| ��%c��%c��%c��%c��   \n", map[0], map[1], map[2], map[3]);
	posxy(POS_MX, POS_MY + 1);
	printf("| ��%c��%c��%c��%c��   \n", map[4], map[5], map[6], map[7]);
	posxy(POS_MX, POS_MY + 2);
	printf("| ��%c��%c��%c��%c��   \n", map[8], map[9], map[10], map[11]);
	posxy(POS_MX, POS_MY + 3);
	printf("| ��%c��%c��%c��%c��   \n", map[12], map[13], map[14], map[15]);
	posxy(POS_MX, POS_MY + 4);
	printf("| ��%c��%c��%c��%c��   \n", map[16], map[17], map[18], map[19]);
	posxy(POS_MX, POS_MY + 5);
	printf("| �� �� �� �� ��\n");

	posxy(POS_MX, POS_MY + 6);
	printf("| �c��̓����F%d", 30 - mass);		//�c��̓�����\��
}

int player_move() {	//�I�����i�ǂ��Ɉړ����邩�j�̓���
	mass++;
	int dir = 0;			//�ړ�����
	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("�ǂ��Ɉړ����܂����H\n");
	printf("1:�k 2:��  3.��  4.��\n");
	posxy(POS_SX, POS_SY+3);
	printf("�ʒu����:");

	sl = getchar();
	sl1 = atoi(&sl);		//�ړ������̓���1:�k 2:��  3.��  4.��
	while (sl == '\n') {	//enter������܂ŁA�ړ������I���̓���
		posxy(POS_SX+10, POS_SY + 3);
		sl = getchar();
		sl1 = atoi(&sl);
	}
	dir = sl1;				//����������B


	posxy(POS_CX, POS_CY);

	if (dir == 1) {			//�����͂����Ƃ�
		if (i == 0 || i == 1 || i == 2 || i == 3) {		//��ԏ�̂Ƃ��́A"���̕����ɂ͂����܂���B\n"��\��
			printf("���̕����ɂ͂����܂���B\n");
		
			i = i + 100;								//i��100�𑫂��Č��ݒn�̈ړ����~�߂�B
			c = getchar();
			mass--;										//���ۂɈړ����ĂȂ��̂Ń}�X�̐������炷�B
		}
		else {

			printf("�k�Ɉړ������B\n");					//���̈ȊO�̏ꍇ�́A"��Ɉړ������B\n"��\�����āA���ݒn����|4���ď�ɍs��
			i = i - 4;
		};

	}
	else if (dir == 2) {									//������͂����Ƃ�
		if (i == 16 || i == 17 || i == 18 || i == 19) {		//��ԉ��̂Ƃ��́A"���̕����ɂ͂����܂���B\n"��\��
			printf("���̕����ɂ͂����܂���B\n");
			i = i + 100;									//i��100�𑫂��Č��ݒn�̈ړ����~�߂�B
			c = getchar();
			mass--;											//���ۂɈړ����ĂȂ��̂Ń}�X�̐������炷�B
		}
		else {

			printf("��Ɉړ������B\n");						//���̈ȊO�̏ꍇ�́A"���Ɉړ������B\n"��\�����āA���ݒn����+4���ĉ��ɍs��
			i = i + 4;
		};

	}
	else if (dir == 3) {										//������͂����Ƃ�

		if (i == 0 || i == 4 || i == 8 || i == 12 || i == 16) {	//��ԍ��̂Ƃ��́A"���̕����ɂ͂����܂���B\n"��\��
			printf("���̕����ɂ͂����܂���B\n");
			i = i + 100;										//i��100�𑫂��Č��ݒn�̈ړ����~�߂�B
			c = getchar();
			mass--;												//���ۂɈړ����ĂȂ��̂Ń}�X�̐������炷�B
		}
		else {

			printf("���Ɉړ������B\n");					//���̈ȊO�̏ꍇ�́A"���Ɉړ������B\n"��\�����āA���ݒn����|1���č��ɍs��
			i = i - 1;
		};



	}
	else if (dir == 4) {											//�E����͂����Ƃ�
		if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19) {	//��ԉE�̂Ƃ��́A"���̕����ɂ͂����܂���B\n"��\��
			printf("���̕����ɂ͂����܂���B\n");
			i = i + 100;											//i��100�𑫂��Č��ݒn�̈ړ����~�߂�B
			c = getchar();
			mass--;													//���ۂɈړ����ĂȂ��̂Ń}�X�̐������炷�B
		}
		else {
			printf("���Ɉړ������B\n");								//���̈ȊO�̏ꍇ�́A"�E�Ɉړ������B\n"��\�����āA���ݒn����+1���ĉE�ɍs��
			i = i + 1;
		};
	}
	else {															//����ȊO����͂����Ƃ�
		printf("���̍쓮�͂����܂���B\n");
		i + 100;													//i��100�𑫂��Č��ݒn�̈ړ����~�߂�B
		c = getchar();
		mass--;														//���ۂɈړ����ĂȂ��̂Ń}�X�̐������炷�B
	};
	move_search= 2;									//�ړ���A���K�̃t�F�[�Y��
	script(10, 10, 0, move_search, re);				//���K��script�̕\��
	return i;
};

void display() {								//UI�̕\��
	system("cls");								//��ʂ̏�����
	map_dis();								 	//�}�b�v�̕\��
	cor_dis();									//���ݒn�̕\��
	item_dis();									 //�A�C�e���̕\��
	memo();										//Hint�̕\��
	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("<Press the enter>\n");
	posxy(POS_CX, POS_CY);

};

void script(int em_id, int wp1, int lose_point, int move_search, int re) {	//scriptd�̊֐�
	// 0, "�]���r�R���j�[", "��", 0
	// 1, "�]���r�A��", "��", 1
	// 2, "峃]���r", "��", 2
	// 3, "�]���r", "��", 1
	// 4, "�A���N�l", "��", 2
	// 0 ,"�n���}�[" ""
	// 1, "�T�u�}�V���K��", ""
	// 2, "�R���o�b�g�i�C�t", ""
	//move_search, re =1  �퓬
	//move_search, re =�Q  ���K
	//move_search, re =�R  �T��
	condition();
	
		if (move_search == 1) {//�퓬
			if (em_id == 2) {
				if (re == 0) {

					printf("�Z�̂悤�ȍb�k��g�ɓZ���A���̂悤�ȑ傫�Ȋ{���L���ĈЊd���Ă���B����Ȃ��̂ɋ��܂ꂽ��ꗭ����Ȃ��B\n");
					c = getchar();
					printf("����͎O��ނ��B���̒�����ǂ��I�Ԃׂ����B\n");
					c = getchar();
				}
				else if (re == 1) {

					printf("��ъ|�����ė������q�ɁA�n���}�[�𑊎�̓��ɐU�艺�낵���B\n");
					c = getchar();
					printf("�����̉򂪍����̓��k���זv�������B����͈�u�ウ��悤�ɘr���L���A���̂܂ܓ����Ȃ��Ȃ����B\n");
					c = getchar();
					printf("�퓬�ɏ��������B\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("��ъ|�����ė��鍩���Ƀi�C�t�ő΍R�����B\n");
					c = getchar();
					printf("�������ڊ|���ē˂�����ł��鑊��̐g�̂��i�C�t�Œe���Ԃ��B\n");
					c = getchar();
					printf("���͂�����ɂ܂œ͂��Ȃ��������A����������̂悤���B\n");
					c = getchar();
					printf("�ǂ���瑼�̂��̂��g�����ق����ǂ�������\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {

						printf("�@�֏e�̈������������A�e�e�𑊎�Ɍ����Ă΂�܂����B\n");
						c = getchar();
						printf("�������A���낤���Ƃ�����̊Z�͓�Ȃ��󂯗����A������ɔ�ъ|�����ė����B\n");
						c = getchar();
						printf("����ł̏��ŉ�������݂���A���̐؂��悪���ڂ�؂�􂢂��B\n");
						c = getchar();
						printf("�h�����Ēv�����͔��������A���炭���͉���ł��Ȃ��B���߂ĕ����I�΂Ȃ���΁B\n");
						c = getchar();
				
					}
					else if (lose_point == 2) {

						printf("�@�֏e�̈������������A�e�e�𑊎�Ɍ����Ă΂�܂����B\n");
						c = getchar();
						printf("�������A���낤���Ƃ�����̊Z�͓�Ȃ��󂯗����A������ɔ�ъ|�����ė����B\n");
						c = getchar();
						printf("�����l�̑��𑨂��A���̂܂ܐؒf�����B\n");
						c = getchar();
						printf("���ڂ̒f�ʂ��猌���~�߂ǂȂ�����o��B�����A����������p�͂Ȃ������B\n");
						c = getchar();
						printf("�Ŋ��Ɍ����̂́A����ȍ����������̐g�̂��Â�H���p�������B\n");
						c = getchar();

					}
				}
			}
			else if (em_id == 0) {
				if (re == 0) {

					printf("��̈�̂Ȃ瓮�����݂��Ώ������₷�����A���������B�͂܂�鎖�����͔����Ȃ���΁B\n");
					c = getchar();
					printf("����͎O��ނ��B���̒�����ǂ��I�Ԃׂ����B\n");
					c = getchar();
				}
				else if (re == 1) {
					printf("�@�֏e�̈������������A�ガ�����悤�ɒe�ۂ��΂�T�����B\n");
					c = getchar();
					printf("�]���r�̏W�c�͐g�̂��������Ɠ�����݂����A����ȍ~�̑Ώ��͗e�Ղ������B\n");
					c = getchar();
					printf("�퓬�ɏ��������B\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("�n���}�[�𗼎�ɁA�]���r�̏W�c�ɓˌ������B\n");
					c = getchar();
					printf("����̓��W�ɒ@���t���悤�Ƃ��邪�A���̌��ɔw�ォ��]���r���P���|�������B\n");
					c = getchar();
					printf("�����ɍU���𒆒f���A�w��̃]���r�ɕ���@���t���A���̏ꂩ�甲���o���B\n");
					c = getchar();
					printf("�ǂ���瑼�̂��̂��g�����ق����ǂ�������\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {
						printf("�i�C�t��Ў�ɁA�]���r�̏W�c�ɓˌ������B\n");
						c = getchar();
						printf("����̍A����؂�􂱂��ƃi�C�t���\���邪�A���̌��ɔw�ォ��]���r���P���|����A�l���H�����i�߂ɂ����B\n");
						c = getchar();
						printf("���̌��ɐ��̂̃]���r�Ɉ͂܂�A������Ɋ��ݕt���ꂽ�B\n");
						c = getchar();
						printf("���Ƃ������o�������A���������悤�ɓ������Ƃ͓���v���Ȃ��B\n");
						c = getchar();
						printf("���߂ĕ����I�΂Ȃ���΁B\n");
						c = getchar();
					}
					else if (lose_point == 2) {
						printf("�i�C�t��Ў�ɁA�]���r�̏W�c�ɓˌ������B\n");
						c = getchar();
						printf("����̍A����؂�􂱂��ƃi�C�t���\���邪�A���̌��ɔw�ォ��]���r���P���|����A�l���H�����i�߂ɂ����B\n");
						c = getchar();
						printf("���̌��ɐ��̂̃]���r�Ɉ͂܂�A�S�g�Ɋ��ݕt���ꂽ�B\n");
						c = getchar();
						printf("�����o�����Ƃ�����A���͂��炪������ƍS�����ꓦ���o�����͏o���Ȃ������B\n");
						c = getchar();
						printf("�Ŋ��Ɍ����̂́A�]���r�B������ďW���Ėl�̐g�̂���������ݐ�؂�p�������B\n");
						c = getchar();
					}

				}
			}
			else if (em_id == 1) {
				if (re == 0) {

					printf("����ȃn�G�g���O�T�����𑫂Ɏ������ē����Ă���B�����A��������g�̂͌s�ł���אg���B\n");
					c = getchar();
					printf("�������A�����̌����v�킹��A�����̋���ȕ⒎�t����n�ʂɐ��ꗎ���������t�����������グ���B\n");
					c = getchar();
					printf("���炭���͂Ȏ_���낤�B����𗁂т���ǂ��Ȃ邩����Ȃ��B\n");
					c = getchar();
					printf("����͎O��ނ��B���̒�����ǂ��I�Ԃׂ����B\n");
					c = getchar();
				}
				else if (re == 1) {

					printf("�R���o�b�g�i�C�t��Ў�ɁA����ɓˌ������B\n");
					c = getchar();
					printf("�⒎�t�̐^����~������A�s��h�݂͂ɂ��ė͋����؂�􂢂��B\n");
					c = getchar();
					printf("�^����ɂ��ꂽ�n�G�g���O�T�͐g�̂�k�������A���̂܂ܓ����Ȃ��Ȃ����B\n");
					c = getchar();
					printf("�퓬�ɏ��������B\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("�l�͋@�֏e�̈������������āA����Ɍ����Ă΂�܂����B\n");
					c = getchar();
					printf("�������A�g�̂��ׂ����������߂邾���Œv���łɂ͂Ȃ�Ȃ��B���̂܂܂ł͒e�����邾���ŃW���n���B\n");
					c = getchar();
					printf("�ǂ���瑼�̂��̂��g�����ق����ǂ��������B\n");
					c = getchar();
				
				}
				else if (re == 3) {
					if (lose_point == 1) {

						printf("�n���}�[�𗼎�ɁA����Ɍ����ēˌ������B\n");
						c = getchar();
						printf("����ȕ⒎�t�Ɍ����đ�U��Œ@���t����B�������A�A�����Ȃ₩�Ȑg�̂ɂ�����̍U���͎󂯗����ꂽ�B\n");
						c = getchar();
						printf("���̌��ɁA��̘r�𑼂̕⒎�t�Ɋ��܂��B�����t�������Ă����B\n");
						c = getchar();
						printf("���Ƃ������o�����Ƃ͂ł������̂́A���ɓ����ڂɑ������瓦���͓̂�����낤�B\n");
						c = getchar();
						printf("�g�̂���蓮�����݂��Ȃ�̂�������B���͉���ł������ɂȂ��B���߂ĕ����I�΂Ȃ���΁B\n");
						c = getchar();
					}
					else if (lose_point == 2) {

						printf("����ȕ⒎�t�Ɍ����đ�U��Œ@���t����B�������A�A���̂��Ȃ₩�Ȑg�̂ɂ�����̍U���͎󂯗����ꂽ�B\n");
						c = getchar();
						printf("���̌��ɁA���̗t����f���|����ꂽ�����t�����Ԃ��Ă��܂��A�S�g�Ɍ��ɂ������炵���B\n");
						c = getchar();
						printf("�v�����𕉂��A�l�͂��̏ꂩ�瓮���Ȃ��Ȃ��Ă��܂����B�⒎�p�̈���A�l�̐g�̂��ۓۂ݂ɂ���B\n");
						c = getchar();
						printf("�Ŋ��Ɍ����̂́A�⒎�t�̐^���Ԃȓ����������B\n");
						c = getchar();
					}
				}
			}
			else if (em_id == 4) {
				if (re == 0) {
					printf("�l�͒w偂̑������C�^�[�ŏĂ��������B\n");
					c = getchar();
					printf("���������ɕ�܂��B���̉��ŁA����Ȓw偂��V�䂩�痎���A�΂Ɋ�����Ėウ�ꂵ��ł����B\n");
					c = getchar();
					printf("�������̂܂ܓ����Ă����珟�ĂȂ����肾�������A���Ȃ����Ă���B�U���̃`�����X���B\n");
					c = getchar();
					printf("�ǂ̕�����g���ׂ����B\n");
					c = getchar();
				
				}
				else if (re == 1) {


					printf("�n���}�[��U�肩�Ԃ�A����̓��ɒ@���t�����B�ꌂ�ł͓|�����A���x�����ł���B\n");
					c = getchar();
					printf("���ȍb�k�����X�Ɋזv���Ă����A�\����@���t�������ł悤�₭�������~�߂��B\n");
					c = getchar();
					printf("�퓬�ɏ��������B\n");
					c = getchar();
				}
				else if (re == 2) {
					printf("�i�C�t����������ɔ�ъ|����B\n");
					c = getchar();
					printf("�������A���ȍb�k�ɎՂ��n�͒ʂ�Ȃ��B��������ݕt�����Ƃ��Ă������A�����Ƀi�C�t�Ŗh�䂵�ċ��������B\n");
					c = getchar();
					printf("�ǂ���瑼�̂��̂��g�����ق����ǂ��������B\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {
						printf("�@�֏e�̈������������A�S�̂����𗁂т���B\n");
						c = getchar();
						printf("�������A������̍U���͊��ȍb�k�ɒe���Ԃ��ꂽ�B\n");
						c = getchar();
						printf("�������đ��肪������֔�ъ|����B����ł̏��ŉ�����Ċ��݂��ꂸ�ɍςނ��A�g�̂�w偂̋��̂ɑł��t������B\n");
						c = getchar();
						printf("�g�̂��ӂ�ӂ炷��B���͉���ł������ɂȂ��B\n");
						c = getchar();
					}
					else if (lose_point == 2) {

						printf("�@�֏e�̈������������A�S�̂����𗁂т���B\n");
						c = getchar();
						printf("�������A������̍U���͊��ȍb�k�ɒe���Ԃ��ꂽ�B\n");
						c = getchar();
						printf("�������đ��肪������֔�ъ|����B���t���o������Ă����l�ɁA������������p�͂Ȃ������B\n");
						c = getchar();
						printf("�e���Ɋ��ݕt����A�ŉt���������܂��B\n");
						c = getchar();
						printf("�u������������������!!�v\n");
						c = getchar();
						printf("���ɂŎ��E�����ł���B�U�X�����̂��ł��������A�₪�ĉ��������Ȃ��Ȃ�A���������Ȃ��Ȃ����B\n");
						c = getchar();
						printf("�Ŋ��Ɍ����̂́A���E��ׂ��ꉽ�������Ȃ��Ȃ����Èł������B\n");
						c = getchar();
					}
				}
			}
			else if (em_id == 3) {
				if (re == 0) {

					printf("�l�͔����J�����B\n");
					c = getchar();
					printf("�M�̂��锒�����C�����Ԃ�B���̐[�����̉��́A�܂�ő����̓����������B\n");
					c = getchar();
					printf("����ȕ����̒��S�ŁA���ǂ⑟��̊ǂ�������`���悤�ɓZ�܂��Đ�����˂��j��A\n");
					c = getchar();
						printf("�V�䂩��ǂ�`�����ɂ����Đ[�g�̃c�^�𒣂菄�点�Ă���B\n");
					c = getchar();
					printf("������c�����l�̑��Ɋ����t���B���̒ӂɁA�A���N�l�̓Őj�ō��������˂��h�����B\n");
					c = getchar();
					printf("����������Ă���悤�Ȗ쑾���������t���A��h�炷�B�����̑�����Ԃ��率�ɕϐF����B\n");
					c = getchar();
					printf("���Ȃ����Ă���A�U���̃`�����X���B\n");
					c = getchar();
					printf("�ǂ̕�����g���ׂ����B\n");
					c = getchar();
				
				}
				else if (re == 1) {
					printf("�l�̓R���o�b�g�i�C�t���\���ēˌ������B\n");
					c = getchar();
					printf("�c�������ɗ��ݕt�����Ƃ��Ă���B���̓x�ɖl�͂����؂蕥���A�����ɓ˂��i�ށB\n");
					c = getchar();
					printf("����̊�����L�΂��ꂽ�G�r���ガ�������Ƃ��Ă���B�����̐���Ⴍ���ĉ���B\n");
					c = getchar();
					printf("�u�I�H�v\n");
					c = getchar();
					printf("�����_���Ă��A�l�̐g�̂𕡐��̃c������C�ɑ����悤�Ƃ��Ă���B�r�A�w���A�r�ɗ��ݕt�����B\n");
					c = getchar();
					printf("�����āA�^�ォ��G�r���@���t���悤�Ɣ����Ă���B\n");
					c = getchar();
					printf("�l�́A�r����c�^�������Ɉ����������A�G�r�Ƀi�C�t�̐؂����˂��t�����B\n");
					c = getchar();
					printf("�_�𕪔債�Ă���̂��A�G�r���琂�ꗎ�����t�̂���̍b���Ă����B\n");
					c = getchar();

					printf("�������A�g�̂Ɋ����t���Ă����c�^���ɂ񂾁B���̔��q�ɗ����オ��A��C�ɋ������l�߂�B\n");
					c = getchar();
					display();
					printf("�����̑���ɁA�i�C�t�������Ȃ���������̎�ōY��ł悤�ɓ˂��h���B���̂܂܉�����ɐ؂�􂢂��B\n");
					c = getchar();
					printf("���t�̑������l�̔��߂���߂�B����ɑς������v�̂ŏc�ɐ؂�􂫁A�Ō�ɂ��̒��S�ɐn��˂��t�����B\n");
					c = getchar();
				

					printf("�k�����鑟���̑���B�l�̐g�̂͑����ɉ�����A�w��ɓ]�|����B\n");
					c = getchar();
					printf("�u�c�c�c�c�c�v\n");
					c = getchar();
					printf("��Ԃ��Â��ɂȂ�B�]���r�v�����g�́A�������~�����B\n");
					c = getchar();
					printf("�퓬�ɏ��������B\n");
					c = getchar();
				}
				else if (re == 2) {

					printf("�]���r�v�����g�Ɍ����ăT�u�}�V���K���̉��ʂ��΂�T���B�������A�����ꂽ�e�n�͂����ɍĐ����Ă��܂��B\n");
					c = getchar();
					printf("���ʂ͂��܂ЂƂB�ǂ���瑼�̂��̂��g�����ق����ǂ�������\n");
					c = getchar();
				}
				else if (re == 3) {
					if (lose_point == 1) {

						printf("�n���}�[�𗼎�ɁA����ɓˌ������B\n");
						c = getchar();
						printf("��������c���������t���Ă���B�����������Ƃ��邪�A��d�ɂ������t���ė���Ȃ��B\n");
						c = getchar();
						printf("���̌���_���A�G�r���l�̐g�̂𕏂ł��B\n");
						c = getchar();
						printf("�u�������c�c!!�v\n");
						c = getchar();
						printf("�_�𕪔債�Ă����̂��A�ߕ��̈ꕔ��n�����Đg�̂��Ă��B\n");
						c = getchar();
						printf("�G�r���n���}�[�ŉ���t�������̃c�^���ɂ݁A���Ƃ������o���B\n");
						c = getchar();
						printf("�̗͂��킪��Đg�̂��ӂ�ӂ炷��B���̍U���͉���ł������ɂȂ��B\n");
						c = getchar();

					}
					else if (lose_point == 2) {
						printf("�n���}�[�𗼎�ɁA����ɓˌ������B\n");
						c = getchar();
						printf("��������c���������t���Ă���B�����������Ƃ��邪�A��d�ɂ������t���ė���Ȃ��B\n");
						c = getchar();
						printf("���̌���_���A�G�r���l�̐g�̂𕏂ł��B\n");
						c = getchar();
						printf("�u�������c�c!!�v\n");
						c = getchar();
						printf("�_�𕪔債�Ă����̂��A�ߕ��̈ꕔ��n�����Đg�̂��Ă��B\n");
						c = getchar();
						printf("�̗͂��������l�ɁA���ꂩ�瓦���p�͖��������B\n");
						c = getchar();
						printf("�g�̂��_�ŗn������A�Ԃ����ǂ̂悤�ȃc�^����d�ɂ��Q����B\n");
						c = getchar();
						printf("�����̐g�̂��]���r�v�����g�̉h�{�Ƃ��ċz������Ă����B\n");
						c = getchar();
						printf("�u�c�c�c�c�c�c�c�v\n");
						c = getchar();
						printf("�Ŋ��Ɍ����̂́A�l���T���Ă����A���ďΊ�ł����Ă������̎q�̌��������B\n");
						c = getchar();
					}
				}
			}
		}
		else if (move_search == 2) {//���K
									//����������(0)���k�����A�ړ��s��
			

			if (i == 0) {
				if (boss_1== 0) {

					//�����K��(�A���N�l���j�O�����g�̂��郉�C�^�[����)
					printf("�{�����������݂����ȑO���炠�鋌�������̈�p�B\n");
					c = getchar();
					printf("�����J���ƁA�����ɂ͋���Ȓw偂̑������鏊�ɒ��菄�炳��Ă����B���̂܂ܓ���Ǝ葫�����ꂩ�˂Ȃ��B\n");
					c = getchar();
					printf("�]���r�v�����g�̍y�f�ŚM���ނ̈�`�q�������̈�`�q�ŏ���������������s���Ă����������A���̕��Y�����낤���B\n");
					c = getchar();
					printf("�ȑO�ɒw偂̈�`�q��g�ݍ��񂾚M���ނ̏o�������́w���΂��₷����_�x�������������B\n");
					c = getchar();
					printf("���A�w�Ύ�x�ƂȂ�w���g�̂��郉�C�^�[�x�͎����Ă���B���̒w偂̑����Ă������ĒT�����s�������ł���B\n");
					c = getchar();
					printf("���̎{�݂���o�Ėk�͐؂藧�����R������A���͌X�΂ɂȂ��Ă���ړ��ł��Ȃ��B\n");
					c = getchar();
					printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
					c = getchar();
				}
				else if (boss_1 = 1) {
					//�����K��(�A���N�l���j�O�����g�̂��郉�C�^�[������)

					printf("�{�����������݂����ȑO���炠�鋌�������̈�p�B\n");
					c = getchar();
					printf("�����J���ƁA�����ɂ͋���Ȓw偂̑������鏊�ɒ��菄�炳��Ă����B���̂܂ܓ���Ǝ葫�����ꂩ�˂Ȃ��B\n");
					c = getchar();
					printf("�]���r�v�����g�̍y�f�ŚM���ނ̈�`�q�������̈�`�q�ŏ���������������s���Ă����������A���̕��Y�����낤���B\n");
					c = getchar();
					printf("�ȑO�ɒw偂̈�`�q��g�ݍ��񂾚M���ނ̏o�������́w���΂��₷����_�x�������������B\n");
					c = getchar();
					printf("�w�Ύ�x�ƂȂ���̂�����Ή����􂪂��邩������Ȃ����A���̂Ƃ��낻�̂悤�Ȃ��̂͏������Ă��Ȃ��B\n");
					c = getchar();
					printf("�����_�ł͕ʂ̏ꏊ��T�����邱�Ƃ��K�؂��Ɩl�͍l�����B\n");
					c = getchar();
					printf("���̎{�݂���o�Ėk�͐؂藧�����R������A���͌X�΂ɂȂ��Ă���ړ��ł��Ȃ��B\n");
					c = getchar();
					printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
					c = getchar();

					inprint("�A���N�l", "�w���΂��₷����_�x");
				}
				
			}
			else if (i == 1) {

				printf("�{�����������݂����ȑO���炠�鋌�������̈�p�B\n");
				c = getchar();
				printf("�{���ɔ�ׂĔN�������邹�����A�ǂ��ϐF�������Ȓw偂̑��������Ă���̂����󂯂���B\n");
				c = getchar();
				printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 2) {
				if (strcmp(data[0].monster, "0")) {
					printf("�댯�x�̍����������s�����߁A�{����������u������Ĕz�u���ꂽ�������B\n");
					c = getchar();
					printf("�n�U�[�h�}�[�N�������ꂽ���̑O�ŁA�l�͑����~�߂��B\n");
					c = getchar();
					printf("���̕ӂ�͖������ɐ[���B���炭���̉��ɍ���̑����̌����ƂȂ��Ă���]���r�v�����g�����锤���B\n");
					c = getchar();
					printf("�������A�w���x���������Ă��Ȃ����ߊJ�������ł��Ȃ��B���̓��̉������ɂ͂��锤�����c�c�B\n");
					c = getchar();
					printf("�����_�ł͕ʂ̏ꏊ��T�����邱�Ƃ��K�؂��Ɩl�͍l�����B\n");
					c = getchar();
					printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
					c = getchar();
					printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
					c = getchar();

					inprint("�u��������", "�w���x");
				}
			

				else if ((!strcmp(data[0].monster, "0")) && (!strcmp(data[7].item, "�}"))) {
						printf("�l�͌��Ŕ����J���悤�Ƃ��āA�r���Ŏ���~�߂��B\n");
						c = getchar();
						printf("�]���r�v�����g���̂������퓬�\�͂������Ă���B���̂܂ܓ�������ǂ��Ȃ邩����Ȃ��B\n");
						c = getchar();
						printf("�����w�������点�邽�߂̎�i�x���K�v���B�l�͑��̏ꏊ��T�����鎖�ɂ����B\n");
						c = getchar();
						printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
						c = getchar();
						printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
						c = getchar();
						inprint("�łɎア�]���r�v�����g", "�w�������点�邽�߂̎�i�x");
				}
				else if (!strcmp(data[0].monster, "0")) {

					printf("�댯�x�̍����������s�����߁A�{����������u������Ĕz�u���ꂽ�������B\n");
					c = getchar();
					printf("�n�U�[�h�}�[�N�������ꂽ���̑O�ŁA�l�͑����~�߂��B\n");
					c = getchar();
					printf("���̕ӂ�͖������ɐ[���B���炭���̉��ɍ���̑����̌����ƂȂ��Ă���]���r�v�����g�����锤���B\n");
					c = getchar();
					printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
					c = getchar();
					printf("���͎����Ă���B�J���ĒT�����s���ׂ����B����Ƃ��ړ�����ׂ����B\n");
					c = getchar();


				}
			
			}
			else if (i == 3) {
				if (strcmp(data[2].monster, "0")) {
					printf("�u�����������ɐ݂���ꂽ�V�F���^�[�B�s�������̊댯�����傫���s�����l���݂���ꂽ���̂��B\n");
					c = getchar();
					printf("����������ƒN���������Ă����Ă���\��������B�������A�w�J���邽�߂̌��x���������Ă��Ȃ����ߊJ�����Ƃ��ł��Ȃ��B\n");
					c = getchar();
					printf("�����_�ł͕ʂ̏ꏊ��T�����邱�Ƃ��K�؂��Ɩl�͍l�����B\n");
					c = getchar();
					printf("���̎{�݂���o�Ėk�͐؂藧�����R������A���͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł������ɂȂ��B\n");
					c = getchar();
					printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
					c = getchar();
					inprint("�V�F���^�[", "�w�J���邽�߂̌��x");
				}
			}
			else if (i == 4) {

				printf("�X�ђn�сB���ɉ����Ė؁X�������΂�A���Ɏ��E�������B\n");
				c = getchar();
				printf("���͌X�΂ƂȂ��Ă���ړ��ł������ɂȂ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 5) {

				printf("�X�ђn�сB�؁X�̉e�Ɩ��̐[���Ŏ��͂��悭���ʂ��Ȃ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 6) {

				printf("�X�ђn�сB�M���炯�ŏ��������ɂ����B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 7) {
				printf("�X�ђn�сB��v�����Ȗ؁X���A�Ȃ��Ă���B\n");
				c = getchar();
				printf("���͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 8) {
				printf("��������k�ɂ���X�т�D���ė���Ă���삾�B���͂��܂�L���Ȃ��B\n");
				c = getchar();
				printf("�T���ƈړ��A\n");
				c = getchar();
				printf("���͌X�΂ƂȂ��Ă���ړ��ł������ɂȂ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 9) {
				printf("�{�������̈�p�B��܂̒�����y�f�̔|�{���s�����ł���A��i�I�Ȃǂ����󂯂���B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 10) {
				printf("�{�������̈�p�ł��鎑�����B�l�X�ȏ��ނ⏑�Ђ��I�ɐ�������Ă���B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 11) {
				printf("�{�������ɐ݂���ꂽ�q�ɁB�H���|���p��ȂǁA�����Ƃ͂��܂�ւ��̂Ȃ��G���ȕ����ۊǂ���Ă���B\n");
				c = getchar();
				printf("���̊O�̓����͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 12) {
				printf("�Ј�������k�ɍs���Ɨ���Ă���삾�B�������L�����Ă��邪�������Ƃɓ�͂Ȃ��B\n");
				c = getchar();
				printf("���͌X�΂ƂȂ��Ă���ړ��ł������ɂȂ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 13) {
				printf("����ɐ݂���ꂽ�����H�B�ȑO�܂ł͌����炵�̗ǂ��ꏊ���������A��͖��ŉB����Ă���B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ���\n");
				c = getchar();
			}
			else if (i == 14) {
				printf("�{�������̈�p�B��ɏ�񏈗���S������G���A�ł���APC��T�[�o�̒u���ꂽ�������A�Ȃ��Ă���B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 15) {
				printf("�{�������̃G���g�����X�B����ē����Ȃ��Ȃ����K���X���̎����h�A���疶����������ł���B\n");
				c = getchar();
				printf("���̊O�̓����͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ���\n");
				c = getchar();
			}
			else if (i == 16) {
				printf("���̓쐼�Ɉʒu����Ј����B���̃G���A�ɂ͖l���ŏ��ɂ����V�F���^�[���ꏏ�ɂ���B\n");
				c = getchar();
				printf("�����͓��Ɉُ�͂Ȃ����A���O�̌i�F�͖��ɕ�܂�ĉ����܂Ō��ʂ������ł��Ȃ��B\n");
				c = getchar();
				printf("��ɂ͊C���L����A���͌X�΂ɂȂ��Ă���ړ��ł������ɂȂ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 17) {
				printf("�Ј����ɗאڂ����ʒn�сB\n");
				c = getchar();
				printf("�Y���������鏊�ɓ]����A�K���ȏꏊ�Ɋ񂹂��Ă��邾���ł��܂�Еt�����Ă��Ȃ��B\n");
				c = getchar();
				printf("��ɂ͊C���L�����Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 18) {
				printf("���̓�Ɉʒu���鍻�l�B���|���s���͂��S�~���Еt�����Ă���̂����A���̔������i�ς͖��ɎՂ�ꌩ�ʂ������o���Ȃ��B\n");
				c = getchar();
				printf("��ɂ͊C���L�����Ă���ړ��ł��Ȃ�\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
			else if (i == 19) {
				printf("���̓쓌�ɐ݂���ꂽ�D������B�b�����{�ɋA���Ă��Ȃ����A�l�͂������瓇�ɍ~�肽�B\n");
				c = getchar();
				printf("��͊C���L����A���͒f�R��ǂł��̐�͊C���L����ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("��Ɠ��ɂ͊C���L�����Ă���B\n");
				c = getchar();
				printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
				c = getchar();
			}
		}
		else if (move_search == 3) {
			if (i == 1) {
				printf("�L��������Ă�����A�]���r�̏W�c��������ǂ������ė����B\n");
				c = getchar();
				//�w�퓬���x�̍��ڂ��'�]���r�R���j�['\n");
			
			}
			else if (i == 4) {
				printf("�T�������Ă���ƁA�A���^�̃]���r�������ǂ����B\n");
				c = getchar();
				//�w�퓬���x�̍��ڂ��'�]���r�A��'\n");
		
			}
			else if (i == 5) {
				printf("�n�G�g���O�T�̕⒎�t����A����������Ȃ������Ǝv���銓�����藎���Ă����B\n");
				c = getchar();
				printf("���̒��𒲂ׂ�ƃX�}�[�g�t�H��������A�f�[�^�Ɍ������e�Ɋւ��ʐ^���ۊǂ���Ă����B\n");
				c = getchar();
				printf("�X�}�z����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			else if (i == 6) {
				printf("�T�������Ă���ƁA�A���^�̃]���r���p���������B\n");
				c = getchar();
				//�w�퓬���x�̍��ڂ��'�]���r�A��'\n");
		
			}
			else if (i == 7) {
				printf("��䂻���Ȗ؂̎}�������A�i�C�t�ŉ��H���Ė_��ɂ����B\n");
				c = getchar();
				printf("�����Ɏg�������Ȃ̂ŉ�����鎖�ɂ����B\n");
				c = getchar();
				printf("�}����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			else if (i == 8) {
				printf("�T�������Ă���Ƒ傫�ȉH�������������B�U������ƁA�����^�̃]���r���ˌ����ė��Ă����B\n");
				c = getchar();
				//�w�퓬���x�̍��ڂ��'峃]���r'\n");
	
			}
			else if (i == 9) {
				display();
				printf("��i���I���疢�g�p�̒��ˊ�������鎖���ł����B�g���������邩������Ȃ��̂Ŏ����Ă����B\n");
				c = getchar();
				printf("���ˊ����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			else if (i == 10) {
				printf("�{�I��D���āA�����̃]���r��������Ɍ������Ă����B\n");
				c = getchar();
				//�w�퓬���x�̍��ڂ��'�]���r�R���j�['\n");
	
			}
			else if (i == 11) {
				printf("���͂�T���Ă���ƁA�����̕�C��C���Ɏg�������ȍޗ���H����������B\n");
				c = getchar();
				printf("�C���L�b�g����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���̊O�̓����͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			else if (i == 12) {
				printf("���͂�T�����Ă���ƁA��̒����獩���^�̃]���r����яo���ė����B\n");
				c = getchar();
			}
			else if (i == 13) {
				if (!strcmp(data[16].person, "�В�")) {
					if (strcmp(data[4].monster, "0")) {//���������ĂȂ����
						printf("�����H�ɗאڂ���q�ɂ𒲂ׂ���A�y��s�@���u����Ă������B�В�����ŏ��L���Ă�����̂��B\n");
						c = getchar();
						printf("�w�G���W���̌��x���������ߍ��͓������Ȃ����A�E�o�̌��ƂȂ锤���B\n");
						c = getchar();
						printf("��������ŒE�o����Ȃ�΁A������������Ɂw�В��x��A��Ă����K�v������B\n");
						c = getchar();
						printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
						c = getchar();
						inprint("�����H", "�w�G���W���̌��x");
					}
					else if (!strcmp(data[4].monster, "0")) {//���������Ă���
						printf("�����H�ɗאڂ���q�ɂ𒲂ׂ���A�y��s�@���u����Ă������B�В�����ŏ��L���Ă�����̂��B\n");
						c = getchar();
						printf("�w�G���W���𓮂������߂̌��x�͎����Ă���B�w�В��x�ɐ����|����ΒE�o���鎖�͂ł��邪�c�c�H\n");
						c = getchar();
						printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
						c = getchar();
						inprint("�y��s�@�̉^�]���ł���l", "�w�В��x");
					}
				}
			}
			else if (i == 14) {
				printf("�T�[�o�[���[����T�����Ă���ƁA���͂��炤�߂��������������B�ǂ����]���r�̏W�c�Ɉ͂܂ꂽ�悤���B\n");
				c = getchar();
				//�w�퓬���x�̍��ڂ��'�]���r�R���j�['\n");
	
			}
			else if (i == 15) {
				printf("��������������C�΂���ŁA���ɉ����Ɏg�������Ȃ��̂͌����鎖�͂ł��Ȃ������B\n");
				c = getchar();
				printf("���̊O�̓����͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			else if (i == 16) {
				printf("�В�����̃��C�^�[���̂ĂĂ��������v���o���A�l�͈�x�V�F���^�[�ɖ߂肻�����������B\n");
				c = getchar();
				printf("���ŎВ��͖l�̎������b�����Ɍ��߂Ă����B\n");
				c = getchar();
				printf("���C�^�[����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���̊O�̓쑤�ɂ͊C���L����A���͒f�R��ǂł��̐�͊C�ƂȂ��Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			else if (i == 17) {
				printf("���I�̒��Ƀ{�[�g�������鎖���ł��A������������肾�����B\n");
				c = getchar();
				printf("��l���̏����ȃ{�[�g�B�E�o��i�̌��ƂȂ肻�������A�j�����Ă���������荡�͎g�������ɂȂ��B\n");
				c = getchar();
				printf("�w�{�������̉������x�ɏC�����邽�߂̕������邩������Ȃ��B����ŒE�o����Ȃ�ΒT���Ă݂�K�v������B\n");
				c = getchar();
				printf("�����A�{�[�g�̒����烉�C�^�[�I�C���̓������ʂ������鎖���ł����B\n");
				c = getchar();
				printf("���C�^�[�I�C������ɓ��ꂽ�B\n");
				c = getchar();
				printf("��ɂ͊C���L�����Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
				inprint("�{�[�g�̏C��", "�w�{�������̉������x");
			}
			else if (i == 18) {
				printf("���ӂ�����Ă�����A���̉����獩���^�̃]���r���P���|�����ė����B\n");
				c = getchar();
				//�w�퓬���x�̍��ڂ��'峃]���r'\n");
		
			}
			else if (i == 19) {
				
				printf("���ɃN���[�U�[���┑���Ă����B�^�]�ł���l�Ԃ����͂��Ȃ����A�E�o�̌��ƂȂ蓾�锤���B\n");
				c = getchar();
				printf("�m���A���̖k���ɂ���w�u���������x�œ����Ă���w�����x�̂ЂƂ肪�D���Ƌ��������Ă���ƕ������o��������B\n");
				c = getchar();
				printf("�܂��A�߂��ɋ�F�Ɍ�����̂�����A������E�����B\n");
				c = getchar();
				printf("����́A�l���T���Ă����l�̃y���_���g�������B���͂�T�������A�ޏ��̉e�͌�������Ȃ��B�ޏ��͉����ɍs�����̂��낤���B\n");
				c = getchar();
				printf("��Ɠ��ɂ͊C���L�����Ă���B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ���\n");
			
				c = getchar();

				inprint("�N���[�U�[", "�w�����x");
			}

		}

		else if (move_search == 4) {
			if (i == 1) {//�퓬�ŏ������Ƃ�
				printf("���̌�A�T���𑱂��Ă���ƁA�������Ɍ����ɖ��ڂɊւ���Ă��鎑���̈���u����Ă���̂��ڂɗ��܂����B\n");
				c = getchar();
				printf("��������1����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}

			else if (i == 4) {//�퓬�ŏ������Ƃ�
				printf("���̌�A�T���𑱂��Ă���ƁA�y�̒��Ɍ����Ă���̂����u����Ă���̂��ڂɗ��܂����B\n");
				c = getchar();
				printf("�y��s�@�̌�����ɓ��ꂽ\n");
				c = getchar();
				printf("���͌X�΂ƂȂ��Ă���ړ��ł������ɂȂ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			
			else if (i == 6) {//�퓬�ŏ������Ƃ�
				printf("���̌���T���𑱂��Ă���ƈ�l�̒j���̈�̂������A�������𒲂ׂ�ƌ����̃X�P�W���[���������ꂽ�m�[�g���������B\n");
				c = getchar();
				printf("�X�P�W���[��������ɓ��ꂽ�B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}

			else if (i == 10) {//�퓬�ŏ������Ƃ�
				printf("���̌��������T�����Ă�����A�������e�ɖ��ڂɊւ�錤�������̈���������B\n");
				c = getchar();
				printf("��������2����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			else if (i == 12) {//�퓬�ŏ������Ƃ�
				printf("�]���r�B�̒��ɔ��߂𒅂��̂������B�ς��ʂĂĂ͂��邪�A���炭�l�̕������������������낤�B\n");
				c = getchar();
				printf("���߂̃|�P�b�g���猤�������������鎖���ł����B\n");
				c = getchar();
				printf("���L����ɓ��ꂽ�B\n");
				c = getchar();
				printf("���͌X�΂ƂȂ��Ă���ړ��ł������ɂȂ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}
			
			else if (i == 14) {//�퓬�ŏ������Ƃ�
				printf("���̃]���r�B�͂ǂ���炱���̋���C���Ă����l�̕����B�̂悤���B\n");
				c = getchar();
				printf("�l�̌������ނ������Ȏp�ɕς��Ă��܂����Ǝv���Ɣw�؂�����A���ӂɉՂ܂ꂽ�B\n");
				c = getchar();
				printf("�ނ�̎���������A�����f�[�^��USB����������B\n");
				c = getchar();
				printf("USB����ɓ��ꂽ\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����H\n");
				c = getchar();
			}
			else if (i == 18) {//�퓬�ŏ������Ƃ�
				printf("���̌�A���͂�T�����������ɉ����������鎖�͂ł��Ȃ������B\n");
				c = getchar();
				printf("��ɂ͊C���L�����Ă���ړ��ł��Ȃ��B\n");
				c = getchar();
				printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
				c = getchar();
			}

		}

}

void item_dis() {							//�v���C���[�̃A�C�e���̕\��
	int r = 0;								//�A�C�e���m�F�p�����ϐ�
	int ip;									//�A�C�e���m�F�p�����ϐ�2
	for (r = 0; r < 50; r++) {				//�v���C���[�̃A�C�e�����m�F���邽�߂Ƀv���C���[�\���̂��������ĕ\��
		if (strcmp(stock[r].item_name, "0") && strcmp(stock[r].item_name, "1")) {
			if (strcmp(stock[r].item_name, "\0")) {
				ip = r + 1;
				posxy(POS_IX, POS_IY + ip);
				printf("| %s\n", stock[r].item_name);		//�C���x���g���̕\��
			}
		};
	};
};

int fight(int em_id, int re) {			//�퓬�̊֐�

	
	wp1 = 0;							//����̑I��p�ϐ��P�F�n���}�[�Q�F�T�u�}�V���K���R�F�R���o�b�g�i�C�t
	at1 = 0;							//�퓬�Ɠ����̑I��p�ϐ�1.���� 2.�퓬
	move_search = 1;					//�퓬�̏��

	system("cls");
	map_dis(); 	//�}�b�v�̕\��
	cor_dis();	//���ݒn�̕\��
	item_dis(); memo();	//�A�C�e���̕\��

	posxy(POS_TX + 50, POS_TY + 1);
	printf("%s�Ƃ̐퓬\n", data[i].monster);			//�G�i�~�[�Ƃ̐퓬�̕\��
	
	
	if (re <2 || re >2) {
		posxy(POS_CX, POS_CY);
		printf("%s�����ꂽ�B\n", data[i].monster);		//�G�i�~�[�̓o��
		monster_dis();									//�G�i�~�[��image�̕\��
		
		posxy(POS_SX, POS_SY);
		printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("�������܂����B\n");
		printf("1.���� 2.�퓬\n");
		posxy(POS_SX, POS_SY + 3);

		sl = getchar();
		sl1 = atoi(&sl);						//�퓬�Ɠ����̑I���̓���1.���� 2.�퓬
		while (sl == '\n') {					//enter�������܂Ő퓬�Ɠ����̑I��
			posxy(POS_SX, POS_SY + 3);
			sl = getchar();
			sl1 = atoi(&sl);					//�퓬�Ɠ����̑I���̓���1.���� 2.�퓬	
		}
		at1 = sl1;								//�I�����ʂ�����B



		system("cls");
		map_dis(); 	//�}�b�v�̕\��
		cor_dis();	//���ݒn�̕\��
		item_dis(); memo();	//�A�C�e���̕\��
		posxy(POS_SX, POS_SY);
		printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("�������܂����B\n");
		printf("1.���� 2.�퓬\n");

		same = 0;
		re = 0;
	}
	else {					//�퓬�̓r���Ɉ����킯�����Ƃ��A�I���Ȃ��Ő퓬�ɓ���B
		at1 = 2;			
		re = 2;
	}

		if (at1 == 2) {		//�퓬�̏���
		
			if (re == 0) {
				posxy(POS_CX, POS_CY);
			script(em_id, 5, lose_point, move_search, re);
				c = getchar();
			}
		
			posxy(POS_SX, POS_SY);
			printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("���������܂����B\n");
			printf("1.%s 2.%s 3.%s \n", stock[0].item_name, stock[1].item_name, stock[2].item_name);
			posxy(POS_SX, POS_SY + 3);

			sl = getchar();
			sl1 = atoi(&sl);			//����̑I���P�F�n���}�[�Q�F�T�u�}�V���K���R�F�R���o�b�g�i�C�t
			while (sl == '\n') {		//enter�������܂łɕ���̑I��
				posxy(POS_SX, POS_SY + 3);
				sl = getchar();
				sl1 = atoi(&sl);		//����̑I���P�F�n���}�[�Q�F�T�u�}�V���K���R�F�R���o�b�g�i�C�t
			}
			wp1 = sl1;					//����̑I��������B

			posxy(POS_CX, POS_CY);
			display();
			// 0, "�]���r�R���j�[", "��", 0
			// 1, "�]���r�A��", "��", 1
			// 2, "峃]���r", "��", 2
			// 3, "�]���r�v�����g", "��", 1
			// 4, "�A���N�l", "��", 2
			// 0 ,"�n���}�[" ""
			// 1, "�T�u�}�V���K��", ""
			// 2, "�R���o�b�g�i�C�t", ""
			//���������̂Ƃ��A�܂��퓬�ɓ���B
			//1�񕉂����Ƃ��A������񕐊��I��Ő키�B
			//2�񕉂����Ƃ��A�Q�[���I�o
			//�������Ƃ��A�����̕\��
			posxy(POS_CX, POS_CY);
			if (em_id == 0) {

				if (wp1 == 1) {				//��������
					re = 2; same = 1;
					script(em_id, 0, lose_point, move_search, re);		//���������̂Ƃ���script���\��
					printf("%s�ōU�������B\n", stock[0].item_name);
					printf("%s�̍U����h�䂵���B\n", data[i].monster);



				}
				else if (wp1 == 3) {			//lose
					same = 0; re = 3; lose_point = 1;


					script(em_id, 2, lose_point, move_search, re);		//1�񕉂����Ƃ���script���\��
					printf("%s�ōU�������B\n", stock[2].item_name);
					printf("%s�ɍU�����ꂽ�B\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%s�Ƃ̐퓬\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();

					posxy(POS_SX, POS_SY);
					printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("���������܂����B\n");
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

					if (wp1 == 1) {//��������
						re = 2; same = 1;
						script(em_id, wp1 - 1, lose_point, move_search, re);		//�����������Ƃ���script���\��
						printf("%s�ōU�������B\n", stock[0].item_name);
						printf("%s�̍U����h�䂵���B\n", data[i].monster);

					}
					else if (wp1 == 3) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 2, lose_point, move_search, re);				//�Q�񕉂����Ƃ���script���\��
						printf("%s�ōU�������B\n", stock[2].item_name);
						printf("%s�ɍU�����ꂽ�B\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);											//�Q�[���I�o����
						j = j + 100;												//�v���C�I��
					}
					else if (wp1 == 2) {//win
						same = 0; re = 1;
						script(em_id, 1, lose_point, move_search, re);				//�������Ƃ���script���\��
						printf("%s�ōU�������B\n", stock[1].item_name);
						printf("%s��|�����B\n", data[i].monster);



					}

				}
				else if (wp1 == 2) {//win

					same = 0; re = 1;
				
					script(em_id, 1, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[1].item_name);
					printf("%s��|�����B\n", data[i].monster);


				}
			}
			else if (em_id == 1) {

				if (wp1 == 2) {//��������
					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[1].item_name);
					printf("%s�̍U����h�䂵���B\n", data[i].monster);


				}
				else if (wp1 == 1) {//lose
					same = 0; re = 3; lose_point = 1;
					script(em_id, 0, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[0].item_name);
					printf("%s�ɍU�����ꂽ�B\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%s�Ƃ̐퓬\n", data[i].monster);
					map_dis(); 
					cor_dis();
					item_dis();
					memo();

					posxy(POS_SX, POS_SY);
					printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("���������܂����B\n");
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

					if (wp1 == 2) {//��������

						re = 2; same = 1;
						printf("%s�ōU�������B\n", stock[1].item_name);
						printf("%s�̍U����h�䂵���B\n", data[i].monster);

					}
					else if (wp1 == 1) {//lose
						same = 0; re = 3; lose_point = 2;

						script(em_id, 0, lose_point, move_search, re);

						printf("%s�ōU�������B\n", stock[0].item_name);
						printf("%s�ɍU�����ꂽ�B\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 3) {//win

						same = 0; re = 1;

						script(em_id, 2, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[2].item_name);
						printf("%s��|�����B\n", data[i].monster);



					}

				}
				else if (wp1 == 3) {//win


					same = 0; re = 1;
					script(em_id, 2, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[2].item_name);
					printf("%s��|�����B\n", data[i].monster);


				}
			}
			else if (em_id == 2) {



				if (wp1 == 3) {//��������
					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[2].item_name);
					printf("%s�̍U����h�䂵���B\n", data[i].monster);


				}
				else if (wp1 == 2) {//lose
					same = 0; re = 3; lose_point = 1;
					script(em_id, 1, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[1].item_name);
					printf("%s�ɍU�����ꂽ�B\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%s�Ƃ̐퓬\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();

					posxy(POS_SX, POS_SY);
					printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("���������܂����B\n");
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

					if (wp1 == 3) {//��������

						re = 2; same = 1;
						script(em_id, wp1 - 1, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[2].item_name);
						printf("%s�̍U����h�䂵���B\n", data[i].monster);

					}
					else if (wp1 == 2) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 1, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[1].item_name);
						printf("%s�ɍU�����ꂽ�B\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 1) {//win


						same = 0; re = 1;
						script(em_id, 0, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[0].item_name);
						printf("%s��|�����B\n", data[i].monster);


					}

				}
				else if (wp1 == 1) {//win
					same = 0; re = 1;
					script(em_id, 0, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[0].item_name);
					printf("%s��|�����B\n", data[i].monster);


				}
			}
			else if (em_id == 3) {

				if (wp1 == 2) {//��������

					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[1].item_name);
					printf("%s�̍U����h�䂵���B\n", data[i].monster);


				}
				else if (wp1 == 1) {//lose
					same = 0; re = 3; lose_point = 1;

					script(em_id, 0, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[0].item_name);
					printf("%s�ɍU�����ꂽ�B\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%s�Ƃ̐퓬\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();	

					posxy(POS_SX, POS_SY);
					printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("���������܂����B\n");
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

					if (wp1 == 2) {//��������
						re = 2; same = 1;
						script(em_id, wp1 - 1, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[1].item_name);
						printf("%s�̍U����h�䂵���B\n", data[i].monster);


					}
					else if (wp1 == 1) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 0, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[0].item_name);
						printf("%s�ɍU�����ꂽ�B\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 3) {//win

						same = 0; re = 1;
						script(em_id, 2, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[2].item_name);
						printf("%s��|�����B\n", data[i].monster);


					}

				}
				else if (wp1 == 3) {//win

					same = 0; re = 1;
					script(em_id, 2, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[2].item_name);
					printf("%s��|�����B\n", data[i].monster);


				}
			}
			else if (em_id == 4) {

				if (wp1 == 3) {//��������
					re = 2; same = 1;
					script(em_id, wp1 - 1, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[2].item_name);
					printf("%s�̍U����h�䂵���B\n", data[i].monster);


				}
				else if (wp1 == 2) {//lose
					same = 0; re = 3; lose_point = 1;
					script(em_id, 1, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[1].item_name);
					printf("%s�ɍU�����ꂽ�B\n", data[i].monster);

					c = getchar();
					system("cls");
					posxy(POS_TX + 50, POS_TY + 1);
					printf("%s�Ƃ̐퓬\n", data[i].monster);
					map_dis(); 	
					cor_dis();	
					item_dis(); 
					memo();

					posxy(POS_SX, POS_SY);
					printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("���������܂����B\n");
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

					if (wp1 == 3) {//��������


						script(em_id, wp1 - 1, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[2].item_name);
						printf("%s�̍U����h�䂵���B\n", data[i].monster);
						re = 2; same = 1;
					}
					else if (wp1 == 2) {//lose
						same = 0; re = 3; lose_point = 2;
						script(em_id, 1, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[1].item_name);
						printf("%s�ɍU�����ꂽ�B\n", data[i].monster);
						c = getchar();
						gameover_wl(0, 0);
						j = j + 100;
					}
					else if (wp1 == 1) {//win

						same = 0; re = 1;
						script(em_id, 0, lose_point, move_search, re);
						printf("%s�ōU�������B\n", stock[0].item_name);
						printf("%s��|�����B\n", data[i].monster);

					}

				}
				else if (wp1 == 1) {//win

					same = 0; re = 1;
					script(em_id, 0, lose_point, move_search, re);
					printf("%s�ōU�������B\n", stock[0].item_name);
					printf("%s��|�����B\n", data[i].monster);

				}
			}
		}
	

	else if (at1 == 1) {	//������I�񂾂Ƃ��A�ŏ��̑I���ɖ߂�
			system("cls");
			map_dis(); 
			cor_dis();
			item_dis();
			memo();	

		posxy(POS_CX, POS_CY);
		printf("�����ɐ��������B\n");
		posxy(POS_SX, POS_SY);
		printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("�������܂����H\n");
		printf("1:�T�� 2:�ړ�\n");
		c = getchar();
		re = 0;
	}
	else {
		posxy(POS_CX, POS_CY);
		printf("���̍쓮�͂����܂���B\n");

	}


	return re;


};

void print_item() {	//�A�C�e���̊֐��A�C�e�����ŏ��ɏE�����Ƃ���script��\�����āAHint��^��������������B
	if (!strcmp(stock[item_cor].item_name, "��������1")) {
		printf("��������1 : ��`�q�g�݊������s���y�f�w�k�N���A�[�[�x�ɂ����̎��ÂɊւ��鎑�����B");
	}
	else if (!strcmp(stock[item_cor].item_name, "�y��s�@�̌�")) {
		printf("�y��s�@�̌� : �В�����ŏ��L���Ă���y��s�@�̌��B");
		c = getchar();
		printf("�y��s�@����������В����ĂԕK�v������B");
	}
	else if (!strcmp(stock[item_cor].item_name, "�X�}�z")) {
		printf("�X�}�z : ��`�q�g�݊������s�����������b�g�̎ʐ^�������Ɏc����Ă���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "�X�P�W���[����")) {
		printf("�X�P�W���[���� : �����Ɋւ���X�P�W���[�����������܂�Ă���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "�}")) {
		printf("�} : ���ȉ��H�����؂̎}�B�����Ƒg�ݍ��킹��Ε��킪���邩������Ȃ��B");
	}
	else if (!strcmp(stock[item_cor].item_name, "���ˊ�")) {
		printf("���ˊ� : ���g�p�̒��g�������Ă��Ȃ����ˊ킾�B");
	}
	else if (!strcmp(stock[item_cor].item_name, "��������2")) {
		printf("��������2 : �����ƍs���Ă�����Ì����̕���]�p�Ɋւ��鎑�����B");
	}
	else if (!strcmp(stock[item_cor].item_name, "�C���L�b�g")) {
		printf("�C���L�b�g : ��Ƀ{�[�g�Ȃǂ��C�����邽�߂�");
		c = getchar();
		printf("���ނ₻������H���邽�߂̍H���Z�߂����́B");
	}
	else if (!strcmp(stock[item_cor].item_name, "���L")) {
		printf("���L : �����Ɋւ���L�^��d���̋�s�������Ȃ����Ă���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "USB")) {
		printf("USB : �����̌v�揑�₻�̋L�^�Ȃǂ��ۑ�����Ă���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "��̃��C�^�[")) {
		printf("��̃��C�^�[ : �В��̎����Ă������C�^�[�B");
		c = getchar();
		printf("���������g�̃��C�^�[�I�C����������Ύg�����ɂȂ�Ȃ��B");
	}
	else if (!strcmp(stock[item_cor].item_name, "���C�^�[�I�C��")) {
		printf("���C�^�[�I�C�� : ���C�^�[�̔R���ƂȂ�I�C���B�Y�����̂悤���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "�T���l�̃y���_���g")) {
		printf("�T���l�̃y���_���g : ���̎q�̒a�����ɔ����Ă������A�Q�n���̃y���_���g���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "���g�̂��郉�C�^�[")) {
		printf("���g�̂��郉�C�^�[ : �q�؂����В��̃��C�^�[�ɃI�C����V���ɒ����������́B");
		c = getchar();
		printf("�ז��Ȃ��̂�R�₷�����ł���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "�ő�")) {
		printf("�ő� : �A���N�l�̓Őj��؂̎}�Ɋ���t�����ȑf�ȑ��B");
		c = getchar();
		printf("��^�ٌ̈`�Ɍ��ʂ����锤���B");
	}
	else if (!strcmp(stock[item_cor].item_name, "���N�`��")) {
		printf("���N�`�� : ��`�q�g�݊����y�f�̍R�̂����������ˊ�B");
	}
}

int player_research() {			//�T�����ʂ̊֐�
	
	int em_id;					//�G�i�~�[��id
	int key, key1;				//���̃A�C�e����T�����߂̔ԍ�
	em_id = 6;					//�G�i�~�[��id��5�܂ł���̂�6�ɂ��ď�����
	int fight_re = 5;			//�퓬�̌��ʂ�������
	int fight_num;				
	move_search= 3;				//�T���̃t�F�[�Y

	boss_2 = 0;					//boss �����A�C�e���Q

	posxy(POS_CX, POS_CY);
	printf("�T�����s�����B\n");

	
		if (i == 0 || i == 2 || i == 3) {	//�������܂��Ă���}�X�̔���

			if (i == 0) {
				if (strcmp(data[i].monster, "0")) {				//�A���N�l���|����Ȃ������ꍇ�́A
					script(10, 10, lose_point, move_search, re);
					for (key = 0; key < 50; key++) {		//�A���N�l������킹�邽�߂̏���
						if (!strcmp(stock[key].item_name, "���g�����郉�C�^�[")) {	//"���g�����郉�C�^�["�����āA

							printf("�l�͒w偂̑������C�^�[�ŏĂ��������B\n");
							c = getchar();
							printf("���������ɕ�܂��B���̉��ŁA����Ȓw偂��V�䂩�痎���A�΂Ɋ�����Ėウ�ꂵ��ł����B\n");
							c = getchar();
							printf("�������̂܂ܓ����Ă����珟�ĂȂ����肾�������A���Ȃ����Ă���B�U���̃`�����X���B\n");
							c = getchar();
							printf("�ǂ̕�����g���ׂ����B\n");
							c = getchar();
							map_dis();
							cor_dis();	
							item_dis(); memo();
							posxy(POS_CX, POS_CY);
							printf("%s�����ꂽ�B\n", data[i].monster);
							monster_dis();
							for (fight_num = 0; fight_num < 40; fight_num++) {	//�A���N�l�Ɛ키�B
								if (fight_re == 5) {					//���߂ẴA���N�l�Ɛ퓬����Ƃ�
									
									system("cls");
									map_dis(); 	
									cor_dis();	
									item_dis();
									memo();	

									fight_re = fight(4, 5);				//�A���N�l�Ɛ퓬

								}
								else if (fight == 2) {					//�����������Ă���A���N�l�Ɛ퓬����Ƃ�
									system("cls");
									map_dis(); 	
									cor_dis();	
									item_dis(); 
									memo();	

									fight_re = fight(4, 2);				//�A���N�l�Ɛ퓬
									c = getchar();
								}
							}
							if (fight_re == 1) {											//�A���N�l�Ɛ퓬�ɏ������Ƃ�
								strcpy_s(data[i].monster, sizeof(data[i].monster), "0");	//�\���̂̒��̃A���N�l�̏�������

								strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), "�u���������̌�");		//�A���N�l�̃A�C�e�����E���B
								strcpy_s(stock[item_cor + 1].item_name, sizeof(stock[item_cor + 1].item_name), "�Őj");			
								item_cor = item_cor + 2;

								//�A���N�l�Ɛ퓬�ɏ������Ƃ���script
								printf("���̌�A�w偂̂��������𔲂��ĒT�������Ă���ƁA�В��̔鏑�Ǝv������̂������鎖���ł����B\n");
								c = getchar();
								printf("�ނ̎������𒲂ׂ�ƁA�u���������̌�����ɓ���鎖���o�����B\n");
								c = getchar();
								printf("�܂��A����ۂɒw偂̊{����Őj�����o�����B���炭�����Ɏg���邩������Ȃ��B\n");
								c = getchar();
								printf("�u���������̌�����ɓ��ꂽ�B\n");
								c = getchar();
								printf("�u���������̌� : �k���ɂ���u�����ꂽ�����{�݂̌��B");

								c = getchar();
								display();
								printf("�A���N�l�̓Őj����ɓ��ꂽ�B\n");
								c = getchar();
								printf("�A���N�l�̓Őj : ���̂܂܂ł͎g���Ȃ��B�_�̂悤�Ȃ��̂��~�����B");
								c = getchar();
								
								printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
								c = getchar();
								printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
								c = getchar();
								
							

							

								check_place = 1;
								strcpy_s(data[i].item, sizeof(data[i].item), "1");		//�\���̂̒��̃A���N�l�̃A�C�e����������
							}
						}

					}

				}
				else {
					if (!strcmp(data[i].item, "1")) {  //���K��(�A���N�l���j��)\n");

						printf("�{�����������݂����ȑO���炠�鋌�������̈�p�B");
						c = getchar();

						printf("��قǌ��j�����A���N�l�̎��[���]�����Ă���B\n");
						c = getchar();
						printf("���̎{�݂���o�Ėk�͐؂藧�����R������A");
						c = getchar();

						printf("���͌X�΂ƂȂ��Ă���ړ��ł������ɂȂ��B\n");
						c = getchar();
						printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
						c = getchar();

					}

				}
			}
			else if (i == 2) {			//�]���r�v�����g������킹�邽�߂̏���		
				if (strcmp(data[i].monster, "0")) {		//�]���r�v�����g���|����Ȃ������ꍇ�́A

					script(10, 10, lose_point, move_search, re);
					for (key = 0; key < 50; key++) {
						if (!strcmp(stock[key].item_name, "�u���������̌�")) {		//"�u���������̌�"�������āA
							script(10, 10, lose_point, move_search, re);
							for (key1 = 0; key1 < 50; key1++) {
								if (!strcmp(stock[key1].item_name, "�Ŏ}")) {	//"�Ŏ}"�������āA
									printf("�l�͔����J�����B\n");
									c = getchar();
									printf("�M�̂��锒�����C�����Ԃ�B���̐[�����̉��́A�܂�ő����̓����������B\n");
									c = getchar();
									printf("����ȕ����̒��S�ŁA���ǂ⑟��̊ǂ�������`���悤�ɓZ�܂��Đ�����˂��j��A\n");
									c = getchar();
									printf("�V�䂩��ǂ�`�����ɂ����Đ[�g�̃c�^�𒣂菄�点�Ă���B\n");
									c = getchar();
									printf("������c�����l�̑��Ɋ����t���B���̒ӂɁA�A���N�l�̓Őj�ō��������˂��h�����B\n");
									c = getchar();
									printf("����������Ă���悤�Ȗ쑾���������t���A��h�炷�B�����̑�����Ԃ��率�ɕϐF����B\n");
									c = getchar();
									printf("���Ȃ����Ă���A�U���̃`�����X���B\n");
									c = getchar();
									printf("�ǂ̕�����g���ׂ����B\n");
								
									//���T����(�������A�ő�����)\n");
									map_dis(); 	
									cor_dis();	
									item_dis(); memo();	
									posxy(POS_CX, POS_CY);

									printf("%s�����ꂽ�B\n", data[i].monster);	//�W�F�l���[�^�Ɛ키�B

									monster_dis();

									for (fight_num = 0; fight_num < 40; fight_num++) {
										if (fight_re == 5) {			//���߂Ẵ]���r�v�����g�Ɛ퓬����Ƃ�
											
											system("cls");
											map_dis(); 	
											cor_dis();	
											item_dis(); memo();	
											fight_re = fight(3, 5);		//�]���r�v�����g�Ɛ퓬

										}
										else if (fight_re == 2) {		//�����������Ă���]���r�v�����g�Ɛ퓬����Ƃ�
											system("cls");
											map_dis(); 	
											cor_dis();	
											item_dis(); memo();	
											fight_re = fight(3, 2);		//�]���r�v�����g�Ɛ퓬
											c = getchar();
										}
									}
									if (fight_re == 1) {//���퓬������\n");

										strcpy_s(data[i].monster, sizeof(data[i].monster), "0");		//�\���̂̒��̃]���r�v�����g�̏�������
										strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), "�N�[���U�̌�");	//�]���r�v�����g�̃A�C�e�����E���B
										strcpy_s(stock[item_cor + 1].item_name, sizeof(stock[item_cor + 1].item_name), "���V�F���^�[�̌�");
										strcpy_s(stock[item_cor + 2].item_name, sizeof(stock[item_cor + 2].item_name), "�R��");
										item_cor = item_cor + 3;

										printf("���̌�A������T�����Ă���ƁA�����������]���r�v�����g�̍y�f�̍R�̂��������t���X�R�������鎖���ł����B\n");
										c = getchar();
										printf("�܂��A���̑������ɗ����Ă���A�������������B\n");
										c = getchar();
										printf("���̑��ɂ͑��V�F���^�[�̌��ƃN�[���U�̌��������Ă������B\n");
										display();
										c = getchar();
										printf("�R�̂̓������t���X�R����ɓ��ꂽ�B\n");
										c = getchar();
										printf("�R�� : �W�F�l���[�^�[�̔��������Ă����y�f�̍R�́B");
										c = getchar();
										printf("���V�F���^�[�̌�����ɓ��ꂽ�B\n");
										c = getchar();
									
										printf("�N�[���U�̌�����ɓ��ꂽ�B\n");
										c = getchar();
										printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
										c = getchar();
										printf("���ꂩ�牽���Ɉړ�����ׂ����B\n");
									

										strcpy_s(data[i].item, sizeof(data[i].item), "1");			//�\���̂̒��̃]���r�v�����g�̃A�C�e����������
										check_place = 1;
									}
								}
							}
						}
					
					}
				}
				else {
					if (!strcmp(data[i].item, "1")) {//�����K��(�]���r�v�����g���j��)\n");
						printf("�댯�x�̍����������s�����߁A�{����������u������Ĕz�u���ꂽ�������B�������~�����]���r�v�����g������B\n");
						c = getchar();
						printf("���̎{�݂���o�Ėk�͐؂藧�����R������ړ��ł��Ȃ��B\n");
						c = getchar();
						printf("�T���ƈړ��A�ǂ�����s���ׂ����B\n");
						c = getchar();

					}


				}
			}
			else if (i == 3) {
				for (key = 0; key < 50; key++) {			//���V�F���^�[���J�����߂̏���
					if (!strcmp(stock[key].item_name, "���V�F���^�[�̌�")) {	//"���V�F���^�[�̌�"������ꍇ�́A
						if (strcmp(data[3].person, "0")) {
							printf("�l�͔��̃��b�N���������ăV�F���^�[�ɓ������B\n");
							c = getchar();
							printf("�����ɂ́A�N���[�U�[�̉^�]���В��ɔC����Ă���A�����̖��΍O���������B\n");
							c = getchar();
							printf("���΁u�������v\n");
							c = getchar();
							printf("�u�����ł����H�v\n");
							c = getchar();
							printf("���΂͊������~�߂��]���r�v�����g�ɖڔz������B\n");
							c = getchar();
							printf("���΁u�������~�߂ꂽ��ł����H�v\n");
							c = getchar();
							printf("�u�͂��B���ꂩ��В��Ƌ��ɒE�o���܂��B���܂莞�Ԃ͎c���Ă��܂���v\n");
							c = getchar();
							printf("���΁u��A�킩��܂����B�s���܂��傤�v\n");
							c = getchar();


							printf("%s�����ԂɂȂ����B\n", data[3].person);			//���V�F���^�[�ɂ͂��ē����ƒ��ԂɂȂ�B
							strcpy_s(data[3].person, sizeof(data[3].person), "0");
						}
					}
				}

			}

		}
		else
		{
			if (strcmp(data[i].monster, "0")) {	//�G�i�~�[�����݂���Ƃ�
				for (em_id = 5; em_id > -1; em_id--) {
					if (!strcmp(data[i].monster, enermy[em_id].monster_name)) {		//�G�i�~�[�̖��O���m�F����B
						printf("%s�𔭌������B\n", data[i].monster);			//�G�i�~�[�Ɛ키�B

						for (fight_num = 0; fight_num < 40; fight_num++) {
							if (fight_re == 5) {					//���߂ẴG�i�~�[�Ɛ퓬����Ƃ�
							
								system("cls");
								map_dis(); 	
								cor_dis();	
								item_dis(); memo();	
								fight_re = fight(em_id, 5);			//�G�i�~�[�Ɛ퓬

							}
							else if (fight_re == 2) {				//�����������Ă���G�i�~�[�Ɛ퓬����Ƃ�
								system("cls");
								map_dis(); 	
								cor_dis();	
								item_dis(); memo();	
								fight_re = fight(em_id, 2);			//�G�i�~�[�Ɛ퓬
								c = getchar();
							}


						}
						if (fight_re == 1) {						//�������Ƃ��̏���
							strcpy_s(data[i].monster, sizeof(data[i].monster), "0");	//�\���̂̒��̃G�i�~�[�̏�������
							if (strcmp(data[i].item, "0") && strcmp(data[i].item, "1")) {

								script(10, 10, lose_point, 4, re);						//�����̂Ƃ���script��\��


								printf("%s�𗎂Ƃ����B\n", data[i].item);			//���Ƃ����A�C�e�����E���B
								strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), data[i].item);
								print_item();
								strcpy_s(data[i].item, sizeof(data[i].item), "1");	//�\���̂̒��̃G�i�~�[�̃A�C�e���̏�������		
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
					//�G�i�~�[�����݂��Ȃ��Ƃ�
					if (strcmp(data[i].item, "0") && strcmp(data[i].item, "1")) {								//�}�b�v��ɃA�C�e��������ꍇ�́A�A�C�e���𔭌����ďE���B

						script(10, 10, lose_point, move_search, re);											//�T���̂Ƃ���script��\��
						strcpy_s(stock[item_cor].item_name, sizeof(stock[item_cor].item_name), data[i].item);//�A�C�e�����E���B
						print_item();																			//�A�C�e����\��	
						strcpy_s(data[i].item, sizeof(data[i].item), "1");										//�\���̂̒��̃A�C�e���̏�������	
						item_cor++;

						check_place = 1;


					}
					else {			//�}�X�ɉ����Ȃ��Ƃ�

						if (!strcmp(data[i].item, "1")) {
							if (esc == 1) {
								printf("�O�̂��߉��߂ĒT�����s�������A���ɉ����������鎖���������鎖���Ȃ������B\n");
								c = getchar();
							}
						}
						else {
						if (i == 13) {
								script(em_id, wp1, lose_point, 3,re);
						

							}
						else {
								printf("��������܂���B\n");
								c = getchar();

						}
							
						}

					}
				}
				if (i == 16) {		//�В������ԂɂȂ邽�߂̏���
					//
					if (!strcmp(data[16].item, "1")) {
						if (!strcmp(data[4].item, "1")) {		//"�y��s�@�̌�"���E����
							if (strcmp(data[16].person, "0")) {	//�}�b�v��ɎВ�������Ƃ��A�В������ԂɂȂ�B
								display();
								printf("�l�͎В��Ɍy��s�@�̌����������B\n");
								c = getchar();
								printf("�u�В��A�y��s�@�̌��������܂����v\n");
								c = getchar();
								printf("�В��u�{�����v\n");
								c = getchar();
								printf("�u�^�]�͂ł��܂�����ˁv\n");
								c = getchar();
								printf("�В��u�����A�������Ƃ�������o�邼�v\n");
								c = getchar();
								printf("%s�����ԂɂȂ����B\n", data[16].person);
								strcpy_s(data[16].person, sizeof(data[16].person), "0");	//�\���̂̒��̐l�̏�������	
							}
						}
					}
				}
				if (i == 13 || i == 17 || i == 19) {
					score_gameover = score_re();	//�X�R�A�̏��
					game_num = escape();	//�����̌��ʕ\��
					

				}
			
			}
		}
	
	return item_cor;


};


void enter(enter_x, enter_y) {	//"��"��"��"��U��ւ����֐�


	for (enter_c = 0; enter_c < 4; enter_c++) {

	posxy(enter_x, enter_y);
	printf("��");
	Sleep(O_s);

	posxy(enter_x, enter_y);
	printf("��");
	Sleep(O_s);
		}
	c = getchar();


}

void explan() {						//�Q�[���̐����y�[�W�̊֐�
	system("cls");


	posxy(POS_MX, POS_MY);
	printf("|�@");					//�}�b�v�̕\��
	posxy(POS_MX, POS_MY + 1);		
	printf("| �� �� �� �� ��   \n");
	posxy(POS_MX, POS_MY + 2);
	printf("| �� �� �� �� ��   \n");
	posxy(POS_MX, POS_MY + 3);
	printf("| �� �� �� �� ��   \n");
	posxy(POS_MX, POS_MY + 4);
	printf("| �� ��.�� �� ��   \n");
	posxy(POS_MX, POS_MY + 5);
	printf("| �� �� �� �� ��   \n");
	posxy(POS_MX, POS_MY + 6);
	printf("| �� �� �� �� ��\n");
	posxy(POS_MX, POS_MY + 7);
	printf("|�A");					//�c��̓����̕\��
	posxy(POS_MX, POS_MY + 8);
	printf("| �c��̓����F30");

	posxy(POS_MX, POS_MY + 9);
	printf("|�B");					//�C���x���g���̕\��


	posxy(0, 1);
	//system("cls");
	printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
	posxy(POS_TX, POS_TY);
	printf("\n���݈ʒu:�C\n");		//���݈ʒu�̕\��
	posxy(0, 3);
	printf("----------------------------------------------------------------------------------------------------------------------\n");



	//�A�C�e���̕\��

	posxy(POS_IX, POS_IY + 4);
	printf("|�n���}�[\n");
	posxy(POS_IX, POS_IY + 5);
	printf("|�T�u�}�V���K��\n");
	posxy(POS_IX, POS_IY + 6);
	printf("|�R���o�b�g�i�C�t\n");


	posxy(POS_SX, POS_SY);
	printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("�D\n");	//�I���̕\��

	posxy(95, POS_SY + 1);
	printf("|�E");	//Hint�̕\��
	posxy(95, POS_SY + 2);
	printf("|");
	posxy(95, POS_SY + 3);
	printf("|");
	posxy(95, POS_SY + 4);
	printf("|");
	posxy(95, POS_SY + 5);
	printf("|");


	posxy(115, 27); printf("�F��");

	posxy(POS_CX, POS_CY);
	printf("�@ �}�b�v�F�V�F���^�[�Ŏ�ɓ��ꂽ���̓��̒n�}�B�v���C���[�̈ʒu��.�ŕ\���B\n\n");
	printf("�A �������ԁF�v���C���[�̍s���\�񐔂��\�������B\n\n");
	printf("�B �C���x���g���F�v���C���[���������Ă���A�C�e�����\�������B\n");
	printf("               ���������A�C�e���Ƃ���3��̕��킪���݂���B\n\n");
	printf("�C ���݈ʒu�F�v���C���[�̌��݈ʒu���\�������B\n\n");
	printf("�D �I�����F�s����I�����A�E�o�ւ̎�����������B\n\n");
	printf("�E �����F�������ł���v���C���[�͕��i���烁�������Ȃ����Ă����B\n");
	printf("       ��Փx�ɍ��킹�ăq���g�ƂȂ郁�������邱�Ƃ��ł���B\n\n");
	printf("�F ���F�e�L�X�g�̏I�����Ӗ�����B�G���^�[�������ƑI�������\�������B\n\n");

	printf("�����͂̂Ƃ��A��C�ɓ��͂��������ꂽ��A�d�����͂����̂ŁA������͂��Ă��������B\n\n");
	c = getchar();

	printf("�v���C���[�͌������ł��������u�𑀂�A�����ɓ���E�o���邱�Ƃ��ڕW�ƂȂ�B\n");
	printf("�E�o�ɂ͏���������A�C�e����l���̏������K�v�ɂȂ�B\n");


	posxy(POS_SX, POS_SY + 2);
	printf("��Փx��I��ł��������B\n");
	printf("1:EASY 2:NORMAL 3:HARD\n");

	posxy(POS_SX, POS_SY + 4);
	sl = getchar();
	sl1 = atoi(&sl);				//�I�����i��Փx�j�̓���
	while (sl == '\n') {			//enter�������܂œ���
		posxy(POS_SX, POS_SY + 4);
		sl = getchar();
		sl1 = atoi(&sl);			//�I�����i��Փx�j�̓���
	}
	memoid = sl1;					//��Փx������B

}

int escape() {
	//��������
	if (i == 13 || i == 17 || i == 19) {
		if (i == 13) {					//�y��s�@�ŒE�o�������
			for (escape_item = 0; escape_item < 50; escape_item++) {
				if (strcmp(stock[4].item_name, "1")) {
					if (!strcmp(data[16].person, "0")) {
						if (mass < 31) {
							//"�y��s�@�̌�"���E���āA�В��ƒ��ԂɂȂ��āA�����H�ɂ�����A�E�o
							printf("�В��u���͎����Ă�ȁv\n");
							c = getchar();
							printf("�u�͂��A���v�ł��v\n");
							c = getchar();
							printf("�В��u�������Əo�邼�A���܂ł�����ȏ��ɋ����疽�����������Ă������v\n");
							c = getchar();
							printf("�u�c�c�c�c�c�v\n");
							c = getchar();
							printf("�l�ƎВ��͌y��s�@�œ�����E�o�����B���悻��������o�߂������A���Ƃ����{�ɖ߂鎖���ł����B\n");
							c = getchar();
							printf("�l�͐V���ɎВ�������������ʂ̓��ŁA��������̌������ĊJ������ꂽ�B\n");
							c = getchar();
							printf("���̋Z�p�������̐l�Ԃ��E�����낤�B����Ƃ͔�ו��ɂȂ�Ȃ����炢�吨�̐l�Ԃ��B\n");
							c = getchar();
							printf("�ł��A�����l�ɂ͑S�Ă��ǂ��ł��悩�����B\n");
							c = getchar();
							printf("�����ɂƂ��đ�؂Ȑl�́A���̐��E�ɂ͂������Ȃ��B\n");
							c = getchar();
							printf("�l�ɂ͐l���E���Ă��A�l�𐶂������Ȃ�ďo���₵�Ȃ��B\n");
							c = getchar();


							game_num = 2;
							score_gameover = score_re();		//�_��������B
							gameover_wl(1, score_gameover);		//�E�o�̕��@�ɂ�鐬���̔��f
							mass = gameover();					//�c��̃}�X������
							j = j + 150;						//�v���C�̏I��
							play = 0;							
							esc = 0;							
								

						}
					}
				}
			}
		}
		else if (i == 17) {	//�{�[�g�ŒE�o�������
			for (escape_item = 0; escape_item < 50; escape_item++) {
				if (!strcmp(stock[escape_item].item_name, "�C���L�b�g")) {
					//�C���L�b�g�������āA��ɂ�����A�E�o
					display();
					posxy(POS_CX, POS_CY);
					printf("�{�[�g���C�����ă{�[�g�ŒE�o�ł���悤���B\n");
					posxy(POS_SX, POS_SY);
					printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("�{�[�g�ŒE�o���܂����B\n");
					printf("1.����B 2.���Ȃ��B\n");

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
						printf("�{�[�g�ŒE�o�����肢�����@��T���ׂ��ł���B");
						c = getchar();

					}
						else if (boat_esc == 1) {
					posxy(POS_CX, POS_CY);
					printf("�l�͓��ɂ����l�X���c���A�{�[�g�ŒE�o�����B\n");
					c = getchar();
					printf("�r���ŉ��x���z���C�ɗ��������A���Ƃ����n�ɒH�蒅�������ł��A����������{�ɖ߂鎖���ł����B\n");
					c = getchar();
					printf("�������l�́A���Ɏc�����Ƃ���l�̎����C�|���肾�����B\n");
					c = getchar();
					printf("�l�͈ꐶ�A�ޏ������̂Ă�����������鎖�ɂȂ邾�낤�B\n");
					c = getchar();


					game_num = 1;
					score_gameover = score_re();			//�_��������B
					gameover_wl(2, score_gameover);			//�E�o�̕��@�ɂ�鐬���̔��f
					mass = gameover();						//�c��̃}�X������
					j = j + 150;							//�v���C�̏I��
					play = 0;
					esc = 0;

					}
				}
			}
		}
		else if (i == 19) {		//�N�[���U�ŒE�o�������
			for (escape_item = 0; escape_item < 50; escape_item++) {
				if (!strcmp(stock[escape_item].item_name, "�N�[���U�̌�")) {
					if (!strcmp(data[3].person, "0")) {
						int sion = 0;
						//"�N�[���U�̌�"�������āA�����ƒ��ԂɂȂ��āA�D�t����ɂ�����A�E�o+�V�I��
						for (escape_item = 0; escape_item < 50; escape_item++) {
							if (!strcmp(stock[escape_item].item_name, "���N�`��")) {
								printf("�����u�����ł��H�v\n");
								c = getchar();
								printf("�u�͂��B���c�͔C���܂��v\n");
								c = getchar();
								printf("�В��u�����A�҂āv\n");
								c = getchar();
								printf("�u�c�c�c�I�H�v\n");
								c = getchar();
								printf("�����ɂ����̂́A�g�̂̔������ٌ`�ƂȂ����l�̖��\�\���������������B\n");
								c = getchar();
								printf("�����B\n");
								c = getchar();
								printf("�l�͎��̖��������邽�߂ɁA���̌������n�߂��B\n");
								c = getchar();
								printf("�����̉ƌn�ɂ͏��n�Ɉ�`��������A���Ƃ��Đ��܂���20�㔼�΂őS�g�Ɋ����������Ď��ʁB\n");
								c = getchar();
								printf("���̎��Â��邽�߁A��`�q��g�݊�����y�f�\�\�k�N���A�[�[�̌��������邽�ߖl�͂��̉�Ђɓ������B\n");
								c = getchar();
								printf("�������A�����̉ߒ��ł��̋Z�p����������Ƃ��Ďg���鎖�������Ă��܂����B\n");
								c = getchar();
								display();			//�f�B�X�v���C�N���A
								printf("���̎���m�����В��͎�����l���Ɏ��A�l�ɕ���J��������悤�w�������B\n");
								c = getchar();
								printf("�l�́A���𐶂��������A�����������ɕς����B\n");
								c = getchar();
								printf("�����A\n");
								c = getchar();
								printf("�u�В��A���΂���A��ɑD�ɏ���Ă��Ă��������v\n");
								c = getchar();
								printf("�В��u��A�������B�����A�������v\n");
								c = getchar();
								printf("���΁u�́A�͂��v\n");
								c = getchar();
								printf("�В��Ɩ��΂��񂪃N���[�U�[�ɏ�荞�ށB\n");
								c = getchar();
								printf("���A�l�̎�ɂ͖������������N�`��������B\n");
								c = getchar();
								printf("������Ƃ͂����Ȃ��܂ł��A�ޏ��̗e�Ԃ̈������~�߁A������}���鎖���炢�͏o���锤���B\n");
								c = getchar();
								printf("�u�����v\n");
								c = getchar();
								display();			//�f�B�X�v���C�N���A
								printf("���N�`���̓��������ˊ��������߂�B\n");
								c = getchar();
								printf("�u���x�����c�c�K�������邩��v\n");
								c = getchar();
								printf("�c�c�c�c�c�c�c�B\n");
								c = getchar();
								printf("�l�B�͏��������B\n");
								c = getchar();
								printf("���̌�A�l�͎�������艟�����A���̌��Ƀ��N�`���������ɒ��˂��鎖���o�����B\n");
								c = getchar();
								printf("�R�̂�ł����܂ꂽ�ޏ��͓������~�߁A���̂܂܋C�₵���B\n");
								c = getchar();
								printf("���ꂩ��N���[�U�[�ɏ���Đ������o�߂��A�l�B�͓��{�ɒH�蒅�����B\n");
								c = getchar();
								printf("���̌�͂ǂ��Ȃ������B\n");
								display();			//�f�B�X�v���C�N���A
								c = getchar();
								printf("�l�̓N���[�U�[�ɂЂ����ɏ悹�������Ƌ��ɁA�������ĎВ��̌����瓦���o�����B\n");
								c = getchar();
								printf("�ނ͖l���̈ӂɃl�b�g�ɗ������������e�̂����ŁA���͌x�@�ɒǂ��Ă���炵���B\n");
								c = getchar();
								printf("�ǂ��Ă���͎̂������ł��肨�݂��l�����A�܂��߂܂��ɂ͂����Ȃ��B\n");
								c = getchar();
								printf("���͋C�₵���܂ܖ����ɖڂ��o�܂��Ă��Ȃ��B���񂷂�͔̂ޏ����������ゾ�B\n");
								c = getchar();
								printf("�ȑO�̃��N�`�������ǂ��Ă����΁A���������̎p�ɖ߂��A�������Â��鎖���ł��锤���B�܂���]�͂���B\n");
								c = getchar();
								printf("�������́A������K��������B");
								c = getchar();

								game_num = 4;
								score_gameover = score_re();				//�_��������B
								gameover_wl(4, score_gameover);				//�E�o�̕��@�ɂ�鐬���̔��f
								mass = gameover();							//�c��̃}�X������
								sion = 10;									//�v���C�̏I��
								j = j + 150;
								play = 0;
								esc = 0;
							}
						}

						//"�N�[���U�̌�"�������āA�����ƒ��ԂɂȂ��āA�D�t����ɂ�����A�E�o
						if (sion == 0) {
							printf("���΁u�����ł��H�v\n");
							c = getchar();
							printf("�u�͂��B���c�͔C���܂��v\n");
							c = getchar();
							printf("�В��u�����A�҂āv\n");
							c = getchar();
							printf("�u�c�c�c�I�H�v\n");
							c = getchar();
							printf("�����ɂ����̂́A�g�̂̔������ٌ`�ƂȂ����l�̖�??���������������B\n");
							c = getchar();
							printf("�����B\n");
							c = getchar();
							printf("�l�͎��̖��������邽�߂ɁA���̌������n�߂��B\n");
							c = getchar();
							printf("�����̉ƌn�ɂ͏��n�Ɉ�`��������A���Ƃ��Đ��܂���20�㔼�΂őS�g�Ɋ����������Ď��ʁB\n");
							c = getchar();
							printf("���̎��Â��邽�߁A��`�q��g�݊�����y�f??�k�N���A�[�[�̌��������邽�ߖl�͂��̉�Ђɓ������B\n");
							c = getchar();
							printf("�������A�����̉ߒ��ł��̋Z�p����������Ƃ��Ďg���鎖�������Ă��܂����B\n");
							c = getchar();
							display();
							printf("���̎���m�����В��͎�����l���Ɏ��A�l�ɕ���J��������悤�w�������B\n");
							c = getchar();//�f�B�X�v���C�N���A
							printf("�����A����̎����ŁA�l�̖��͕ς��ʂĂ��p�ɂȂ��Ă��܂����B\n");
							c = getchar();
							printf("�l�́A���𐶂��������A�����������ɕς����B\n");
							c = getchar();
							printf("�c�c�c�c�c�c�c�B\n");

							c = getchar();
							printf("���_���猾���ƁA�l�B�͏��������B\n");
							c = getchar();
							printf("�В��Ɠ����ɁA��ɃN���[�U�[�ɏ��悤�����A�l�͏e�Ŕޏ��̕Б��������ē������~�߁A�ォ���荞�񂾁B\n");
							c = getchar();
							printf("�����狎���Ă����l�B���A�����͑D������ɘȂ�Œ��߂Ă����B\n");
							c = getchar();
							printf("�c�c�c�c�c�c�c�B\n");
							c = getchar();
							printf("�H�蒅���܂Ő������o�߂������A���Ƃ����{�ɒH�蒅�������ł����B\n");
							c = getchar();
							printf("�����ǁA���̎��̈������̊��G�Ǝ����̎p���A�����Ɠ����痣��Ȃ��B\n");
							c = getchar();
							printf("�����́A�������߂������ȕ\������Ă����B\n");
							c = getchar();
							display();			//�f�B�X�v���C�N���A
							printf("�l�͐V���ɎВ�������������ʂ̓��ŁA��������̌������ĊJ������ꂽ�B\n");
							c = getchar();
							printf("���̋Z�p�������̐l�Ԃ��E�����낤�B����Ƃ͔�ו��ɂȂ�Ȃ����炢�吨�̐l�Ԃ��B\n");
							c = getchar();
							printf("�ł��A�����l�ɂ͑S�Ă��ǂ��ł��悩�����B\n");
							c = getchar();
							printf("�����ɂƂ��đ�؂Ȑl�́A���̐��E�ɂ͂������Ȃ��B\n");
							c = getchar();
							printf("�l�ɂ͐l���E���Ă��A�l�𐶂������Ȃ�ďo���₵�Ȃ��B\n");
							c = getchar();

							game_num = 3;
							score_gameover = score_re();		//�_��������B
							gameover_wl(3, score_gameover);		//�E�o�̕��@�ɂ�鐬���̔��f
							mass = gameover();					//�c��̃}�X������
							j = j + 150;						//�v���C�̏I��
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

	
	for (mr = 0; mr < 9; mr++) {												//��Փx��Easy�ɂ����Ƃ��̃�������UI

	
			mp = mr % 5 ;
			
		
				posxy(70, POS_SY+1 + mp);
				printf("|");
					if (strcmp(save[mr].name, "1")) {
					posxy(75+mr*7-mp*7, POS_SY + 1 + mp);
					printf("%s:%s", save[mr].name, save[mr].explan);			//Hint�̖��O�Ɛ������o��

			}
		}
	}
	else if (memoid == 2) {


		for (mr = 0; mr < 9; mr++) {											//��Փx��Normal�ɂ����Ƃ��̃�������UI
			mp = mr % 5;				


			posxy(90, POS_SY + 1 + mp);
			printf("|");
			if (strcmp(save[mr].name, "1")) {
				posxy(95 + mr * 5 - mp * 5, POS_SY + 1 + mp);
				printf("%s", save[mr].explan);									//Hint�̐������o��


			}
		}
	}
}

void inprint(char name[10], char explan[10]) {								//Hint�̏o�͂̊֐�
	int ii;																	//�����p�ϐ�
	int mip=0;
	for (ii = pp; ii>-1; ii--) {											//Hint�̖��O�������o�͂ł��Ă���Ƃ��͏o�͂��Ȃ�
		if (!strcmp(save[ii].name, name)) {
			mip = 1;														
		}
	}
	if(mip==0){
	strcpy_s(save[pp].name, sizeof(save[pp].name), name);					//Hint�̖��O���o��
	strcpy_s(save[pp].explan, sizeof(save[pp].explan), explan);				//Hint�̐������o��
	pp++;
	}
	mip = 0;



}
void monster_dis() {									//�G�i�~�[��image�̏o�͊֐�

//	0, "�]���r�R���j�[", "��", 0
//		, 1, "�]���r�A��", "��", 1
//		, 2, "峃]���r", "��", 2
//		, 3, "�]���r�v�����g", "��", 1
//		, 4, "�A���N�l", "��", 2




	if (!strcmp(data[i].monster, "�]���r�R���j�[")) {	//�G���]���r�R���j�[�̂Ƃ�

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





	}else if (!strcmp(data[i].monster, "�]���r�A��")) {		//�G���]���r�A���̂Ƃ�

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


	}else if (!strcmp(data[i].monster, "峃]���r")) {		//�G��峃]���r�̂Ƃ�

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





	}else if (!strcmp(data[i].monster, "�]���r�v�����g")) {			//�G���]���r�v�����g�̂Ƃ�

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


		}else if(!strcmp(data[i].monster, "�A���N�l")){			//�G���A���N�l�̂Ƃ�
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
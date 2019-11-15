#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"


//
//	多倍長変数の値をゼロクリアし, 符号をプラスにセット
//
void clearByZero(struct NUMBER* a)
{
	int i;

	for (i = 0; i < KETA; i++) {
		a->n[i] = 0;
	}

	a->sign = 1;	//	符号をプラス側にセット
}

//
//	aを表示
//
void dispNumber(struct NUMBER* a)
{
	int i;

	if (a->sign == 1) {
		putchar('+');
	}
	else {
		putchar('-');
	}

	for (i = 0; i < KETA; i++) {
		printf("%d ", a->n[i]);
	}
}

//
//	aの下位k桁に乱数値をセット
//
void setRnd(struct NUMBER *a, int k)
{
	int i;

	for (i = 0; i < k; i++) {
		a->n[(KETA-1) - i] = random() % 10;
	}

	a->sign = random() % 2;	//	符号をどちらかにセット
}

//
//	aをbにコピー
//
void copyNumber(struct NUMBER *a, struct NUMBER *b)
{
	//	aのメンバー変数をすべてbにコピー
	int i;

	for (i = 0; i < KETA; i++) {
		b->n[i] = a->n[i];
	}

	b->sign = a->sign;
}

//
//	aの絶対値をbに返す
//
void getAbs(struct NUMBER *a, struct NUMBER *b)
{
	//int i;

	copyNumber(a, b);

	b->sign = 1;
}

//	戻り値
//	0  ... a == 0
//	-1 ... a != 0
//
int isZero(struct NUMBER *a)
{
	int i;

	for (i = 0; i < KETA; i++) {
		if (a->n[i] != 0) {
			return -1;
		}
	}

	return 0;
}

//
//	aを10倍してbに返す
//
//	戻り値
//	0  ... 正常終了
//	-1 ... オーバーフロー
//
int mulBy10(struct NUMBER *a, struct NUMBER *b)
{
	int i;

	if (a->n[0] != 0) {
		return -1;	//	オーバーフロー
	}

	for (i = 0; i < KETA - 1; i++) {
		b->n[i] = a->n[i+1];
	}

	b->n[KETA-1] = 0;

	b->sign = a->sign;

	return 0;
}

//
//	aを1/10倍してbに返す
//
//	戻り値
//		aを10で割った余り
//
int divBy10(struct NUMBER *a, struct NUMBER *b)
{
	int i;
	int n = 0;

	n = a->n[KETA-1];

	for (i = 0; i < KETA - 2; i++) {
		b->n[(KETA-1) - i] = a->n[(KETA-2) - i];
	}

	b->n[0] = 0;

	b->sign = a->sign;

	return n;
}
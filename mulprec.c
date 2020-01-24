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
		a->n[i] = 0;	//	各桁ごとの値を0に設定
	}

	a->sign = 1;	//	符号をプラス側にセット
}

//
//	aを表示
//
void dispNumber(struct NUMBER* a)
{
	int i;

	//	符号の表示
	//	signが1のときに+を, それ以外のときに-を表示
	if (a->sign == 1) {
		putchar('+');
	}
	else {
		putchar('-');
	}

	//	各桁ごとの値を順番に表示
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
	//	copyNumber関数を用いて, 符号を+に設定することによって絶対値を代入
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

	//	上位桁からその桁の値が0かどうかを比較
	for (i = 0; i < KETA; i++) {
		if (a->n[i] != 0) {	//	0でなかった場合に-1を返す
			return -1;
		}
	}

	return 0;	//	すべての桁の値が0の場合に0を返す
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

	if (a->n[0] != 0) {	//	aの最上位桁が0でなければ10倍したときにオーバーフローしてしまう
		return -1;	//	オーバーフロー
	}

	//	bのi桁にaのi+1桁（iの右の桁）を代入
	for (i = 0; i < KETA - 1; i++) {
		b->n[i] = a->n[i+1];
	}

	b->n[KETA-1] = 0;	//	bの最下位桁に0を代入

	b->sign = a->sign;	//	符号の情報をコピー

	return 0;
}

//
//	aを1/10倍してbに返す
//
//	戻り値
//	n ... aを10で割った余り
//
int divBy10(struct NUMBER *a, struct NUMBER *b)
{
	int i;
	int n = 0;

	n = a->n[KETA-1];	//	aを10で割った余りをnに代入

	//	bの最下位桁から順番にaの最下位+1+i桁目の値を代入
	for (i = 0; i < KETA - 2; i++) {
		b->n[(KETA-1) - i] = a->n[(KETA-2) - i];
	}

	b->n[0] = 0;	//	bの最上位桁に0を代入

	b->sign = a->sign;	//	符号の情報をコピー

	return n;	//	戻り値にnを返す
}

//
//  多倍長変数のaにint型変数xの値を設定
//
//  戻り値
//      0 ... 正常終了
//     -1 ... xの値がaに設定しきれなかった
//
int setInt(struct NUMBER *a, int x)
{
	int surplus = 0;
	int i;

	clearByZero(a);

	if (x < 0) {
		a->sign = 0;

		x = ~x + 1;
	}

    for (i = 0; x > 0; i++)
	{
		surplus = x % 10;
		if (i >= KETA) {
			return -1;
		}
		a->n[(KETA-1) - i] = surplus;
		x -= surplus;
		x /= 10;
	}

	return 0;
}

//
//	多倍長変数aの符号を
//	s = 1なら正に, s = -1 なら負に設定して0を返す
//	それ以外はエラーとして-1を返す
//
int setSign(struct NUMBER *a, int s)
{
	switch (s)
	{
	case 1:
		a->sign = 1;
		break;

	case -1:
		a->sign = 0;
		break;
	
	default:
		return -1;
		break;
	}

	return 0;
}

//
//	aの符号が正なら+1を, 負なら-1を返す
//
int getSign(struct NUMBER *a)
{
	if (a->sign == 1) {
		return 1;
	}
	else if (a->sign == 0) {
		return -1;
	}

	return 0;
}

//
//  2つの多倍長変数a, bの大小を比較
//
//  戻り値
//      0 ... a == b
//      1 ... a > b
//     -1 ... a < b
//
int numComp(struct NUMBER *a, struct NUMBER *b)
{
    int i;
    
    if (getSign(a) > getSign(b)) {
        return 1;
    }
    else if (getSign(a) < getSign(b)) {
        return -1;
    }
    else {
        if (getSign(a) == 1) {
            for (i = 0; i < KETA; i++) {
                if (a->n[i] > b->n[i]) {
                    return 1;
                    break;
                }
                else if (a->n[i] < b->n[i]) {
                    return -1;
                    break;
                }
            }
            return 0;
        }
        else if (getSign(a) == -1) {
            for (i = 0; i < KETA; i++) {
                if (a->n[i] > b->n[i]) {
                    return -1;
                    break;
                }
                else if (a->n[i] < b->n[i]) {
                    return 1;
                    break;
                }
            }
            return 0;
        }
        else {
            return -1;
        }
    }
}

//
//  aとbを交換
//
void swap(struct NUMBER *a, struct NUMBER *b)
{
    int i, c = 0;

	for (i = 0; i < KETA; i++) {
        c = b->n[i];
		b->n[i] = a->n[i];
        a->n[i] = c;
	}

    c = getSign(b);
	setSign(b, getSign(a));
    setSign(a, c);
}

//
//  c <= a + b
//
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	int i, x = 0, e = 0;

	clearByZero(c);

	if (getSign(a) == -1) {
		if (getSign(b) == -1) {
			struct NUMBER d, e;
			getAbs(a, &d);
			getAbs(b, &e);
			add(&d, &e, c);
			setSign(c, -1);

			return 0;
		}
		struct NUMBER f;
		getAbs(a, &f);
		sub(&f, b, c);
		
		if (numComp(&f, b) == 1) {
			setSign(c, -1);
		}
		else {
			setSign(c, 1);
		}
		
		return 0;
	}
	else if (getSign(b) == -1) {
		struct NUMBER g;
		getAbs(b, &g);
		sub(a, &g, c);

		if (numComp(a, &g) >= 0) {
			setSign(c, 1);
		}
		else {
			setSign(c, -1);
		}

		return 0;
	}

	for (i = 0; i < KETA; i++) {
		x = a->n[KETA-1 - i] + b->n[KETA-1 - i] + e;
		c->n[KETA-1 - i] = x % 10;
		e = x / 10;
	}

	if (e != 0) {
		return -1;
	}

	return 0;
}

//
//	c <= a - b
//
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	int h = 0, i;

	clearByZero(c);

	if (getSign(a) == -1) {
		if (getSign(b) == -1) {
			struct NUMBER d, e;
			getAbs(a, &d);
			getAbs(b, &e);

			sub(&d, &e, c);

			if (numComp(a, b) >= 0) {
				setSign(c, 1);	
			}
			else {
				setSign(c, -1);
			}
			
			return 0;
		}
		struct NUMBER f;
		getAbs(a, &f);
		add(&f, b, c);
		setSign(c, -1);
			
		return 0;
	}
	else if (getSign(b) == -1) {
		struct NUMBER g;
		getAbs(b, &g);
		add(a, &g, c);
			
		return 0;
	}

	if (numComp(a, b) == 1) {
		for (i = 0; i < KETA; i++) {
			if ((a->n[KETA-1 - i] - h) >= b->n[KETA-1 - i]) {
				c->n[KETA-1 - i] = (a->n[KETA-1 - i] - h) - b->n[KETA-1 - i];
				h = 0;
			}
			else {
				c->n[KETA-1 - i] = 10 + (a->n[KETA-1 - i] - h) - b->n[KETA-1 - i];
				h = 1;
			}
		}

		if (h == 1) {
			return -1;
		}
	}
	else if (numComp(a,b) == -1) {
		for (i = 0; i < KETA; i++) {
			if ((b->n[KETA-1 - i] - h) >= a->n[KETA-1 - i]) {
				c->n[KETA-1 - i] = (b->n[KETA-1 - i] - h) - a->n[KETA-1 - i];
				h = 0;
			}
			else {
				c->n[KETA-1 - i] = 10 + (b->n[KETA-1 - i] - h) - a->n[KETA-1 - i];
				h = 1;
			}
		}

		if (h == 1) {
			return -1;
		}
		setSign(c, -1);
	}
	else {
		clearByZero(c);
	}

	return 0;
	
}
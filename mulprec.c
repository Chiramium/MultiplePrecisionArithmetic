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
	if (0) {
	//	aのメンバー変数をすべてbにコピー
	int i;

	for (i = 0; i < KETA; i++) {
		b->n[i] = a->n[i];
	}

	b->sign = a->sign;
	}

	if (1) {
		*b = *a;

		b->sign = a->sign;
	}
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
//	戻り値
//		0 ... a == 1
//	   -1 ... a != 1
//
int isOne(struct NUMBER *a)
{
	int i;

	for (i = 0; i < KETA-1; i++) {
		if (a->n[i] != 0) {
			return -1;
		}
	}

	if (a->n[KETA-1] != 1) {
		return -1;
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
	struct NUMBER x;
	int i;

	clearByZero(&x);

	if (a->n[0] != 0) {	//	aの最上位桁が0でなければ10倍したときにオーバーフローしてしまう
		return -1;	//	オーバーフロー
	}

	//	bのi桁にaのi+1桁（iの右の桁）を代入
	for (i = 0; i < KETA - 1; i++) {
		x.n[i] = a->n[i+1];
	}

	x.n[KETA-1] = 0;	//	bの最下位桁に0を代入

	x.sign = a->sign;	//	符号の情報をコピー

	copyNumber(&x,b);

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
	struct NUMBER x;
	int i;
	int n = 0;

	clearByZero(&x);

	n = a->n[KETA-1];	//	aを10で割った余りをnに代入

	//	bの最下位桁から順番にaの最下位+1+i桁目の値を代入
	for (i = 0; i < KETA - 1; i++) {
		x.n[(KETA-1) - i] = a->n[(KETA-2) - i];
	}

	x.n[0] = 0;	//	bの最上位桁に0を代入

	x.sign = a->sign;	//	符号の情報をコピー

	copyNumber(&x, b);

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
	struct NUMBER n;
	int i, x = 0, e = 0;

	clearByZero(&n);

	if (getSign(a) == -1) {
		if (getSign(b) == -1) {
			struct NUMBER d, e;
			getAbs(a, &d);
			getAbs(b, &e);
			add(&d, &e, &n);
			setSign(&n, -1);

			copyNumber(&n, c);

			return 0;
		}
		struct NUMBER f;
		getAbs(a, &f);
		sub(&f, b, &n);
		
		if (numComp(&f, b) == 1) {
			setSign(&n, -1);
		}
		else {
			setSign(&n, 1);
		}

		copyNumber(&n, c);
		
		return 0;
	}
	else if (getSign(b) == -1) {
		struct NUMBER g;
		getAbs(b, &g);
		sub(a, &g, &n);

		if (numComp(a, &g) >= 0) {
			setSign(&n, 1);
		}
		else {
			setSign(&n, -1);
		}

		copyNumber(&n, c);

		return 0;
	}

	for (i = 0; i < KETA; i++) {
		x = a->n[KETA-1 - i] + b->n[KETA-1 - i] + e;
		n.n[KETA-1 - i] = x % 10;
		e = x / 10;
	}

	if (e != 0) {
		return -1;
	}

	copyNumber(&n, c);

	return 0;
}

//
//	c <= a - b
//
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	struct NUMBER n;
	int h = 0, i;

	clearByZero(&n);

	if (getSign(a) == -1) {
		if (getSign(b) == -1) {
			struct NUMBER d, e;
			getAbs(a, &d);
			getAbs(b, &e);

			sub(&d, &e, &n);

			if (numComp(a, b) >= 0) {
				setSign(&n, 1);	
			}
			else {
				setSign(&n, -1);
			}

			copyNumber(&n, c);
			
			return 0;
		}
		struct NUMBER f;
		getAbs(a, &f);
		add(&f, b, &n);
		setSign(&n, -1);

		copyNumber(&n, c);
			
		return 0;
	}
	else if (getSign(b) == -1) {
		struct NUMBER g;
		getAbs(b, &g);
		add(a, &g, &n);

		copyNumber(&n, c);
			
		return 0;
	}

	if (numComp(a, b) == 1) {
		for (i = 0; i < KETA; i++) {
			if ((a->n[KETA-1 - i] - h) >= b->n[KETA-1 - i]) {
				n.n[KETA-1 - i] = (a->n[KETA-1 - i] - h) - b->n[KETA-1 - i];
				h = 0;
			}
			else {
				n.n[KETA-1 - i] = 10 + (a->n[KETA-1 - i] - h) - b->n[KETA-1 - i];
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
				n.n[KETA-1 - i] = (b->n[KETA-1 - i] - h) - a->n[KETA-1 - i];
				h = 0;
			}
			else {
				n.n[KETA-1 - i] = 10 + (b->n[KETA-1 - i] - h) - a->n[KETA-1 - i];
				h = 1;
			}
		}

		if (h == 1) {
			return -1;
		}
		setSign(&n, -1);
	}
	else {
		clearByZero(&n);
	}

	copyNumber(&n, c);

	return 0;
	
}

//
//	c <= a * b
//
//	##### REFERENCECODE #####
//	--------NORMAL--------
//	100 ... n * 0 (n = 0, 1, 2, ...)
//	101 ... n * 1 (n = 1, 2, 3, ...)
//	--------ERROR---------
//	-1 ... overflow
//
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	struct NUMBER x;
	struct NUMBER y;
	//struct NUMBER k;

	clearByZero(&x);
	clearByZero(&y);
	//clearByZero(&k);

	if (isZero(a) == 0 || isZero(b) == 0) {
		clearByZero(c);

		return 100;
	}

	if (isOne(a) == 0) {
		copyNumber(b, c);

		return 101;
	}
	else if (isOne(b) == 0) {
		copyNumber(a, c);

		return 101;
	}
	else {}

	getAbs(a, &x);
	getAbs(b, &y);

	/*printf("---------------------------\n");
	dispNumber(&x);
	putchar('\n');
	dispNumber(&x);
	putchar('\n');*/

	int i = 0, j = 0;
	int h = 0, e = 0;
	struct NUMBER d;
	clearByZero(&d);

	clearByZero(c);

	while (1)
	{
		if (i >= KETA) {
			break;
		}

		//printf("%d回目\n", i);
		
		h = 0;
		clearByZero(&d);

		j = 0;

		while (1)
		{
			if (j >= KETA) {
				break;
			}
			e = x.n[KETA-1 - j] * y.n[KETA-1 - i] + h;
			//printf("[%d]\n", KETA-1 - (j + i));
			if ((j + i) < KETA){
			d.n[KETA-1 - (j + i)] = e % 10;
			h = e / 10;
			}
			else {
				if (e > 0)
					return -1;
			}

			if (j == KETA-1) {
				if (h > 0) {
					return -1;
				}
			}

			j++;
		}

		//dispNumber(&d);
		//putchar('\n');

		if (add(&d, c, c) == -1) {
			return -1;
		}

		/*dispNumber(c);
		putchar('\n');
		printf("---------------------------\n");*/

		i++;
	}

	if (getSign(a) == -1) {
		if (getSign(b) == 1) {
			setSign(c, -1);
		}
	}
	else if (getSign(b) == -1) {
		setSign(c, -1);
	}

	return 0;
}

//
//	c <= a / b の商
//	d <= a / b の剰余
//
int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d)
{
	struct NUMBER m, n, x, y;

	//int i = 0;

	clearByZero(c);
	clearByZero(d);
	clearByZero(&m);
	clearByZero(&n);
	clearByZero(&x);
	clearByZero(&y);

	if (isZero(b) == 0) {
		return  -1;
	}

	if (getSign(a) == -1) {
		if (getSign(b) == -1) {
			getAbs(a, &m);
			getAbs(b, &n);
			divide(&m, &n, c, d);
			setSign(d, -1);
			
			return 0;
		}
		else {
			getAbs(a, &m);
			copyNumber(b, &n);
			divide(&m, &n, c, d);
			setSign(c, -1);
			setSign(d, -1);

			return 0;
		}
	}
	else if (getSign(b) == -1) {
		copyNumber(a, &m);
		getAbs(b, &n);
		divide(&m, &n, c, d);
		setSign(c, -1);

		return 0;
	}

	copyNumber(a, &m);

	while (1) {
		if (numComp(&m, b) == -1) {
			copyNumber(&m, d);
			break;
		}
		increment(c, &n);
		copyNumber(&n, c);

		//dispNumber(b);
		//putchar('\n');
		sub(&m, b, &n);
		copyNumber(&n, &m);
		//dispNumber(&n);
		//putchar('\n');
	}

	return 0;
}

//
//	b <= a++
//
int increment(struct NUMBER *a, struct NUMBER *b)
{
	struct NUMBER one, x, y;
	int r;

	clearByZero(&one);
	clearByZero(&x);
	clearByZero(&y);

	copyNumber(a, &x);

	one.n[KETA-1] = 1;
	
	r = add(&x, &one, &y);

	copyNumber(&y, b);

	return r;
}

//
//	b <= a--
//
int decrement(struct NUMBER *a, struct NUMBER *b)
{
	struct NUMBER one, x, y;
	int r;

	clearByZero(&one);
	clearByZero(&x);
	clearByZero(&y);

	copyNumber(a, &x);

	one.n[KETA-1] = 1;

	r = sub(&x, &one, &y);

	copyNumber(&y, b);

	return r;
}

//
//	c <= a ^ b
//	再帰を使用した累乗関数
//
int fastPower(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	struct NUMBER x, y, z, m, n, two;

	clearByZero(&x);
	clearByZero(&y);
	clearByZero(&z);
	clearByZero(&m);
	clearByZero(&n);
	clearByZero(&two);

	two.n[KETA-1] = 2;

	if (isZero(b) == 0) {
		clearByZero(c);
		c->n[KETA-1] = 1;
		return 0;
	}

	if (isOne(b) == 0)
	{
		copyNumber(a, c);
		return 0;
	}

	divide(b, &two, &m, &n);
	if (isZero(&n) == 0) {
		if (multiple(a, a, &x) == -1)
			return -1;
		fastPower(&x, &m, &z);
	}

	decrement(b, &y);
	fastPower(a, &y, &z);
	if (multiple(a, &z, c) == -1)
		return -1;

	return 0;
}

//
//	c <= a * 10 ^ n
//
int exponential_N(struct NUMBER *a, struct NUMBER *n, struct NUMBER *c)
{
	struct NUMBER x, y, i;

	clearByZero(&x);
	clearByZero(&y);
	clearByZero(&i);

	copyNumber(n, &i);
	copyNumber(a, c);
	copyNumber(a, &y);

	while (isZero(&i) == -1) {
		mulBy10(&y, &x);
		copyNumber(&x, &y);

		decrement(&i, &i);
	}

	x.sign = a->sign;	//	符号の情報をコピー

	copyNumber(&x,c);

	return 0;
}

//
//	c <= a / b の商
//	d <= a / b の剰余
//	最適化された除算関数
//
int fastDivide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d)
{
	struct NUMBER m, n, e, y;

	int i, k;
	//int j = 0;

	clearByZero(c);
	clearByZero(d);
	clearByZero(&m);
	clearByZero(&n);
	clearByZero(&e);
	clearByZero(&y);

	if (isZero(b) == 0) {
		return  -1;
	}

	if (getSign(a) == -1) {
		if (getSign(b) == -1) {
			getAbs(a, &m);
			getAbs(b, &n);
			fastDivide(&m, &n, c, d);
			setSign(d, -1);
			
			return 0;
		}
		else {
			getAbs(a, &m);
			copyNumber(b, &n);
			fastDivide(&m, &n, c, d);
			setSign(c, -1);
			setSign(d, -1);

			return 0;
		}
	}
	else if (getSign(b) == -1) {
		copyNumber(a, &m);
		getAbs(b, &n);
		fastDivide(&m, &n, c, d);
		setSign(c, -1);

		return 0;
	}
	setSign(c, 1);

	copyNumber(a, &m);

	while (1) {
		if (numComp(&m, b) == -1) {
			copyNumber(&m, d);
			break;
		}
		i = 1;

		copyNumber(b, d);
		clearByZero(&e);
		e.n[KETA-1] = 1;

		while (1) {
			if (numComp(&m, d) == -1) {
				divBy10(d, d);
				i--;
				break;
			}
			else if (numComp(&m, d) == 0) {
				break;
			}

			if (mulBy10(d, d) == -1) {
				//return -1;
				i--;
				break;
			}

			i++;
		}

		for (k = 0; k < i-1; k++) {
			mulBy10(&e, &e);
		}
		sub(&m, d, &m);
		add(c, &e, c);
	}

	return 0;
}
#include <stdio.h>

#define KETA 30

struct NUMBER
{
	int n[KETA];	//	各桁の値
	int sign;		//	符号変数
};

//	Prototype
void clearByZero(struct NUMBER* a);
void dispNumber(struct NUMBER* a);

int main(int argc, char** argv)
{
	struct NUMBER a;

	clearByZero(&a);
	dispNumber(&a);
	putchar('\n');

	return 0;
}

//
//	多倍長変数の値を0クリアし, 符号をプラスにセット
//
void clearByZero(struct NUMBER* a)
{
	int i;

	for (i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}

	a->sign = 1;	//	符号をプラス側にセット
}

void dispNumber(struct NUMBER* a)
{
	int i;

	if (a->sign == 1) {
		putchar('+');
	}
	else {
		putchar('-');
	}

	for (i = 0; i < KETA; i++)
	{
		printf("%d ", a->n[i]);
	}
}

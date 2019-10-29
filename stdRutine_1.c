#include <stdio.h>

#define KETA 30

struct NUMBER
{
	int n[KETA];	//	�e���̒l
	int sign;		//	�����ϐ�
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
//	���{���ϐ��̒l��0�N���A��, �������v���X�ɃZ�b�g
//
void clearByZero(struct NUMBER* a)
{
	int i;

	for (i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}

	a->sign = 1;	//	�������v���X���ɃZ�b�g
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

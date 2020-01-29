#ifndef MULPREC_H
#define MULPREC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KETA 50
#define RADIX 10000

struct NUMBER
{
	int n[KETA];	//	各桁の値
	int sign;		//	符号変数
};

//	Prototype

void clearByZero(struct NUMBER* a);
void dispNumber(struct NUMBER* a);
void setRnd(struct NUMBER *a, int k);
void copyNumber(struct NUMBER *a, struct NUMBER *b);
void getAbs(struct NUMBER *a, struct NUMBER *b);
int isZero(struct NUMBER *a);
int isOne(struct NUMBER *a);
int mulByRAD(struct NUMBER *a, struct NUMBER *b);
int divByRAD(struct NUMBER *a, struct NUMBER *b);
int setInt(struct NUMBER *a, int x);
int setSign(struct NUMBER *a, int s);
int getSign(struct NUMBER *a);
int numComp(struct NUMBER *a, struct NUMBER *b);
void swap(struct NUMBER *a, struct NUMBER *b);
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d);
int increment(struct NUMBER *a, struct NUMBER *b);
int decrement(struct NUMBER *a, struct NUMBER *b);
int fastPower(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int exponential_N(struct NUMBER *a, struct NUMBER *n, struct NUMBER *c);
int fastDivide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d);

#endif // ! MULPREC_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

#define POW 2

int power(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int factorial(struct NUMBER *a, struct NUMBER *b);	/*###################*/
int gcd(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int lcm(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);

int main()
{
	struct NUMBER a;
	struct NUMBER b;
    struct NUMBER c;
	struct NUMBER d;

    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
	clearByZero(&d);

	setInt(&a, 1919810);
	setInt(&b, 114514);
	//setInt(&c, 1);

	//copyNumber(&a, &b);

	//mulByRAD(&a, &b);
	//exponential_N(&a, &b, &c);

	//increment(&c, &c);
	//decrement(&c, &c);

	/*** Run function ***/

	//printf("\nisZero:%d", isZero(&c));
	//printf("\nisOne:%d", isOne(&c));

	//printf("\nadd:%d\n", add(&b, &a, &c));
	//printf("\nsub:%d\n", sub(&a, &b, &c));

	//printf("\nmultiple:%d\n", multiple(&a, &b, &c));
	printf("\ndivide:%d\n", divide(&a, &b, &c, &d));
	//printf("\nfastDivide:%d\n", fastDivide(&a, &b, &c, &d));

	//printf("\npower:%d\n", power(&a, &b, &c));
	//printf("\npower:%d\n", fastPower(&a, &b, &c));

	//printf("\nfactorial:%d\n", factorial(&a, &b));

	//printf("\ngcd:%d\n", gcd(&a, &b, &c));

	//printf("\nlcm:%d\n", lcm(&a, &b, &c));

	//printf("\nsetSign:%d\n", setSign(&a, 1));

	//printf("\nnumComp:%d\n", numComp(&a, &b));

	//swap(&a, &b);

	dispNumber(&a);
	putchar('\n');
	dispNumber(&b);
	putchar('\n');
	printf("-------------------------------\n");
	dispNumber(&c);
	putchar('\n');
	printf(".\n.\n.\n");
	dispNumber(&d);
	putchar('\n');

	/*sub(&a, &b, &c);

	dispNumber(&c);*/


    return 0;
}

//
//	c <= a ^ b
//
int power(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	struct NUMBER n;

	clearByZero(&n);
	copyNumber(b, &n);

	if (isOne(&n)) {
		return 0;
	}

	multiple(a, a, c);

	decrement(b, &n);

	power(a, &n, c);

	return 0;
}

//
//	b <= a!
//
int factorial(struct NUMBER *a, struct NUMBER *b)
{
	struct NUMBER n;
	struct NUMBER n1;

	clearByZero(&n);
	clearByZero(&n1);

	copyNumber(a, &n);
	decrement(&n, &n1);

	//dispNumber(&n1);

	while (isZero(&n1) == -1) {
		multiple(&n, &n1, b);
		copyNumber(b, &n);
		decrement(&n1, &n1);
		dispNumber(&n1);
	}

	return 0;
	
}

//
//	c <= aとbの最大公約数
//
int gcd(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	struct NUMBER d;
	struct NUMBER e;
	struct NUMBER f;
	struct NUMBER g;

	clearByZero(&d);
	clearByZero(&e);
	clearByZero(&f);
	clearByZero(&g);

	getAbs(a, &d);
	getAbs(b, &e);

	while (1)
	{
		divide(&d, &e, &f, &g);	//d / e = f ... g

		if (isZero(&g) == 0) {
			break;
		}

		copyNumber(&e, &d);
		copyNumber(&g, &e);
	}

	copyNumber(&e, c);
	
	return 0;
}

//
//	c <= aとbの最小公倍数
//
int lcm(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
	struct NUMBER d;
	struct NUMBER e;
	struct NUMBER f;
	struct NUMBER g;
	struct NUMBER dummy;

	clearByZero(&d);
	clearByZero(&e);
	clearByZero(&f);
	clearByZero(&g);

	getAbs(a, &d);
	getAbs(b, &e);
	
	gcd(&d, &e, &f);

	if (isZero(&f) == 0) {
		return -1;
	}

	divide(&d, &f, &g, &dummy);

	multiple(&g, &e, c);

	return 0;
}
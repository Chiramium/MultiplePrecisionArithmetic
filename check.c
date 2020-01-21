#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

//
//  Program Start
//
int main(int argc, char **argv)
{
    struct NUMBER a, b, c, d, e;
    int r;

    clearByZero(&a);
    setInt(&a, 234);

    dispNumber(&a);
    putchar('\n');

    /*srandom(time(NULL));    //  乱数シードの初期化

    clearByZero(&a);    //  a <= 0
    clearByZero(&b);    //  b <= 0
    clearByZero(&c);    //  c <= 0
    clearByZero(&d);    //  d <= 0
    clearByZero(&e);    //  e <= 0

    printf("a \t= ");     //  0が表示されるか確認
    dispNumber(&a);
    printf("\n");

    setRnd(&b, 10);     //  b <= 10桁の乱数(bの初期化はsetRnd()内で行うとする)
    printf("b \t= ");     //  bを表示
    dispNumber(&b);
    printf("\n");

    copyNumber(&b, &c); //  c <= b
    printf("c \t= ");
    dispNumber(&c);
    printf("\n");

    r = mulBy10(&b, &d);    //  d <= b * 10
    printf("b * 10 \t= ");    //  dを表示
    dispNumber(&d);
    printf(", r = %d\n", r);

    r = divBy10(&c, &e);    //  e <= c / 10
    printf("c / 10 \t= ");    //  eを表示
    dispNumber(&e);
    printf(", r = %d\n", r);

    printf("a == 0? --> %d\n", isZero(&a)); //  isZero()の結果を表示
    printf("b == 0? --> %d\n", isZero(&b));
    printf("c == 0? --> %d\n", isZero(&c));
    printf("d == 0? --> %d\n", isZero(&d));

    clearByZero(&a);
	printf("%d\n", setInt(&a, -12345678));
    printf("a \t= ");
	dispNumber(&a);*/

    return 0;
}
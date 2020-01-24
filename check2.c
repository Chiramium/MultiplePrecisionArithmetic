#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

#define N 10000

int main()
{
    struct NUMBER a, b, c, ans;
    //int r;
    int i, n = 0;

    srandom(time(NULL));    //  乱数シードの初期化

    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);

    /*setInt(&a, -12345);
    printf("a = ");
    dispNumber(&a);
    putchar('\n');

    copyNumber(&a, &b);
    setSign(&b, 1);
    printf("b = ");
    dispNumber(&b);
    putchar('\n');

    r = getSign(&b);
    printf("getSign = %d\n", r);

    r = numComp(&a, &b);
    printf("numComp = %d\n", r);*/

    for (i = 0; i < N; i++) {
        int x = 0, y = 0;

        if(1) {
            x = random() % 1000 - 500;
            y = random() % 1000 - 500;
        }

        if (0) {
            x = 134;
            y = 172;
        }

        setInt(&a, x);
        setInt(&b, y);
        setInt(&ans, x - y);

        sub(&a, &b, &c);

        if (numComp(&c, &ans) != 0) {
            printf("---!!ERROR!!---\n");
            dispNumber(&a);
            putchar('\n');
            dispNumber(&b);
            putchar('\n');

            dispNumber(&c);
            putchar('\n');

            printf("%d\n", x);
            printf("%d\n", y);

            dispNumber(&ans);
            putchar('\n');
        }
        else {
            n++;
        }
    }

    printf("\nRESULT : %d\n", n);

    return 0;
}
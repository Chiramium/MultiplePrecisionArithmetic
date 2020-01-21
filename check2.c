#include <stdio.h>
#include <stdlib.h>
#include "mulprec.h"

int main()
{
    struct NUMBER a, b;
    int r;

    setInt(&a, -12345);
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
    printf("numComp = %d\n", r);

    return 0;
}
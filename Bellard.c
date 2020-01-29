#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

//  POWがKETAの約84%の大きさにする
#define POW 42
#define E 100

int bellard(struct NUMBER* answer);
void filePrinter(FILE *fp, struct NUMBER* answer);

int main()
{
    FILE *fp;

    fp = fopen("Bellard_Data.txt", "w");

	struct NUMBER answer;

    clearByZero(&answer);

    printf("Bellard = %d\n", bellard(&answer));

	printf("n= %d", E);
	putchar('\n');
    printf("-------------------------------\n");
	dispNumber(&answer);
	putchar('\n');

    filePrinter(fp, &answer);

    fclose(fp);

    return 0;
}

int bellard(struct NUMBER* answer)
{
    struct NUMBER s[5];
    struct NUMBER t[17];
    struct NUMBER sigma[2];
    struct NUMBER fomula[2];
    struct NUMBER pow;
    struct NUMBER exp;
    struct NUMBER two;
    struct NUMBER four;
    struct NUMBER eight;
    struct NUMBER thirtyTwo;
    struct NUMBER sixtyFour;
    struct NUMBER ten24;
    struct NUMBER n;
    struct NUMBER dummy;

    int i;

    for (i = 0; i < 5;i++) {
        clearByZero(&s[i]);
    }

    for (i = 0; i < 17;i++) {
        clearByZero(&t[i]);
    }

    printf("clearByZero ... ");
    clearByZero(&sigma[0]);
    clearByZero(&sigma[1]);
    clearByZero(&fomula[0]);
    clearByZero(&fomula[1]);
    clearByZero(&pow);
    clearByZero(&exp);
    clearByZero(&two);
    clearByZero(&four);
    clearByZero(&n);
    clearByZero(&dummy);
    clearByZero(&eight);
    clearByZero(&thirtyTwo);
    clearByZero(&sixtyFour);
    clearByZero(&ten24);

    printf("Done\n");

    printf("Value setting ... ");
    two.n[KETA-1] = 2;
    four.n[KETA-1] = 4;
    eight.n[KETA-1] = 8;
    thirtyTwo.n[KETA-1] = 2;
    thirtyTwo.n[KETA-2] = 3;
    sixtyFour.n[KETA-1] = 4;
    sixtyFour.n[KETA-2] = 6;
    ten24.n[KETA-1] = 4;
    ten24.n[KETA-2] = 2;
    ten24.n[KETA-4] = 1;
    printf("Done\n");

    setInt(&exp, POW);

    //i <= E
    for (i = 0; ; i++) {
        printf("\r[PHASE 1] n = %d", i);
        fflush(stdout);

        clearByZero(&s[3]);
        s[3].n[KETA-1] = 1;

        setInt(&n, i);

        multiple(&two, &n, &s[0]);

        increment(&s[0], &s[0]);
        
        fastPower(&four, &n, &s[1]);
        
        multiple(&s[0], &s[1], &s[2]);
        
        exponential_N(&s[3], &exp, &s[3]);

        if (i % 2 == 1) {
            setSign(&s[3], -1);
        }
        else {
            setSign(&s[3], 1);
        }
        
        fastDivide(&s[3], &s[2], &s[4], &dummy);

        /*dispNumber(&s[4]);
        putchar('\n');*/

        if (isZero(&s[4]) == 0) {
            break;
        }

        add(&s[4], &sigma[0], &sigma[0]);
    }
    multiple(&four, &sigma[0], &fomula[0]);

    putchar('\n');

    clearByZero(&n);
    clearByZero(&dummy);

    //i <= E
    for (i = 0; ; i++) {
        printf("\r[PHASE 2] n = %d", i);
        fflush(stdout);

        setInt(&n, i);

        multiple(&four, &n, &t[0]);

        if (0) {
            printf("------------------------\n");
            dispNumber(&t[0]);
            putchar('\n');
            printf("------------------------\n");
        }

        increment(&t[0], &t[1]);
        
        increment(&t[1], &t[2]);

        increment(&t[2], &t[3]);

        if (0) {
            printf("------------------------\n");
            dispNumber(&t[3]);
            putchar('\n');
            printf("------------------------\n");
        }

        multiple(&t[1], &t[2], &t[4]);

        multiple(&t[4], &t[3], &t[5]);

        multiple(&thirtyTwo, &t[2], &t[6]);

        if (0) {
            printf("========================\n");
            dispNumber(&thirtyTwo);
            putchar('\n');
            printf("========================\n");
        }

        if (0) {
            printf("------------------------\n");
            dispNumber(&t[6]);
            putchar('\n');
            printf("------------------------\n");
        }

        multiple(&t[6], &t[3], &t[7]);

        multiple(&eight, &t[1], &t[8]);

        multiple(&t[8], &t[3], &t[9]);

        multiple(&t[1], &t[2], &t[10]);

        add(&t[7], &t[9], &t[11]);

        add(&t[11], &t[10], &t[12]);

        exponential_N(&t[12], &exp, &t[13]);

        fastDivide(&t[13], &t[5], &t[14], &dummy);

        if (isZero(&t[14]) == 0) {
            break;
        }

        fastPower(&ten24, &n, &t[15]);

        fastDivide(&t[14], &t[15], &t[16], &dummy);

        if (isZero(&t[16]) == 0) {
            break;
        }

        if (i % 2 == 1) {
            setSign(&t[16], -1);
        }
        else {
            setSign(&t[16], 1);
        }

        /*dispNumber(&t[16]);
        putchar('\n');*/
        
        add(&t[16], &sigma[1], &sigma[1]);
    }
    fastDivide(&sigma[1], &sixtyFour, &fomula[1], &dummy);

    putchar('\n');

    sub(&fomula[0], &fomula[1], answer);

    //copyNumber(&fomula[0], answer);

    return 0;
}

void filePrinter(FILE *fp, struct NUMBER* answer)
{
    int i;

    for (i = 0; i < KETA; i++) {
        fprintf(fp, "%d", answer->n[i]);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>

int main(int argc, char *argv[]){
    /*
    printf("Storage size for float : %d \n", sizeof(float));
    printf("FLT_MAX     :   %g\n", (float) FLT_MAX);
    printf("FLT_MIN     :   %g\n", (float) FLT_MIN);
    printf("-FLT_MAX    :   %g\n", (float) -FLT_MAX);
    printf("-FLT_MIN    :   %g\n", (float) -FLT_MIN);
    printf("DBL_MAX     :   %g\n", (double) DBL_MAX);
    printf("DBL_MIN     :   %g\n", (double) DBL_MIN);
    printf("-DBL_MAX     :  %g\n", (double) -DBL_MAX);
    printf("Precision value: %d\n", FLT_DIG );
    */

    /*
    printf("CHAR_BIT    :   %d\n", CHAR_BIT);
    printf("CHAR_MAX    :   %d\n", CHAR_MAX);
    printf("CHAR_MIN    :   %d\n", CHAR_MIN);
    printf("INT_MAX     :   %d\n", INT_MAX);
    printf("INT_MIN     :   %d\n", INT_MIN);
    printf("LONG_MAX    :   %ld\n", (long) LONG_MAX);
    printf("LONG_MIN    :   %ld\n", (long) LONG_MIN);
    printf("SCHAR_MAX   :   %d\n", SCHAR_MAX);
    printf("SCHAR_MIN   :   %d\n", SCHAR_MIN);
    printf("SHRT_MAX    :   %d\n", SHRT_MAX);
    printf("SHRT_MIN    :   %d\n", SHRT_MIN);
    printf("UCHAR_MAX   :   %d\n", UCHAR_MAX);
    printf("UINT_MAX    :   %u\n", (unsigned int) UINT_MAX);
    printf("ULONG_MAX   :   %lu\n", (unsigned long) ULONG_MAX);
    printf("USHRT_MAX   :   %d\n", (unsigned short) USHRT_MAX);
    */

    int x;
    unsigned char tx[3] = {0};
    tx[1] = 0xFF;
    tx[2] = 0xF9;
    tx[3] = 0xF3;

    if((tx[3] & 3)!= 0)
        printf("Es x\n");
    uint8_t counter = 0;
    uint8_t sum = 0;
    uint8_t value = 2;
    for(int i= 0;i< 5;i++){
        sum += value;
        if(counter > 3)
            printf("Here %d\n",counter);
        printf("sum %d\n",sum);
        counter++;
    }

    x = (int)tx[1]<<12 | (int)tx[2] << 4 | (int)tx[3]>> 4;

    //int negative = (x & (1 << 19)) != 0;

    if ((x & (1 << 19)) != 0)
        x = x | ~((1 << 20) - 1);  

    printf("dato despu %d\n", x);
}
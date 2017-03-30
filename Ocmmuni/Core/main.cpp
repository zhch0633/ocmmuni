#include <stdio.h>
#include <stdlib.h>
#include <OcmmuniTCP.h>
#include <MathFunctions.h>

int main(int argc, char *argv[])
{
    if (argc < 3){
        // print version info
        printf("%s Version\n", argv[0]);
        printf("Usage: %s base exponent \n", argv[0]);
        HelloFunc();
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);

#if defined (HAVE_POW)
    printf("Now we use the standard library. \n");
    double result = pow(base, exponent);
#else
    printf("Now we use our own Math library. \n");
    double result = power(base, exponent);
#endif
    HelloFunc();
    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

uint64_t f(uint32_t n)
{
    if (n == 1 || n == 2)
        return 2;
    else if (n == 3)
        return 4;
    else
        return (2 * f(n - 1) - f(n - 3));
}

int main()
{
    uint32_t n = 0;
    scanf("%u", &n);
    printf("%llu\n", f(n));
    return 0;
}


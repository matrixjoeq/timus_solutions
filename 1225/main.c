/*
 * 1225. Flags
 * Time limit: 1.0 second
 * Memory limit: 64 MB
 * 
 * [Description]
 * On the Day of the Flag of Russia a shop-owner decided to decorate the show-window
 * of his shop with textile stripes of white, blue and red colors. He wants to satisfy
 * the following conditions:
 *     1. Stripes of the same color cannot be placed next to each other.
 *     2. A blue stripe must always be placed between a white and a red or between a red
 *        and a white one.
 * Determine the number of the ways to fulfill his wish.
 * 
 * [Input]
 * N, the number of the stripes, 1 ≤ N ≤ 45.
 * 
 * [Output]
 * M, the number of the ways to decorate the shop-window.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

static uint64_t f(uint32_t n)
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


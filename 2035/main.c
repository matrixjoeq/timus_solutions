#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define min(x, y) ((x) < (y) ? (x) : (y))

int main()
{
    uint64_t x, y, c;
    scanf("%llu %llu %llu", &x, &y, &c);
    if (x + y < c) {
        printf("Impossible\n");
    }
    else {
        uint64_t a, b;
        if (x < y) {
            uint64_t m = min(x, c);
            for (uint64_t i = m; i >= 0; --i) {
                uint64_t j = c - i;
                if (j <= y) {
                    a = i;
                    b = j;
                    break;
                }
            }
        }
        else {
            uint64_t m = min(y, c);
            for (uint64_t i = m; i >= 0; --i) {
                uint64_t j = c - i;
                if (j <= x) {
                    a = j;
                    b = i;
                    break;
                }
            }
        }
        printf("%llu %llu\n", a, b);
    }
    return 0;
}


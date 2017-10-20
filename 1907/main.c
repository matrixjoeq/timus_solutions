/*
 * 1907. Coffee and Buns
 * Time limit: 1.0 second
 * Memory limit: 64 MB
 *
 * [Description]
 * Planet Ataraxia is known for its education centers. The people who are expected
 * to take high social positions in future are brought up in conditions of continuous
 * training and supervision from the early age. Each education center is a small
 * town with all the necessary utilities. During the construction of a center, a
 * square area is chosen which is divided into equal sections each sized 100 × 100
 * meters. In each of these sections they build one building, which would become
 * residential or academic. The outer perimeter of the center is fenced.
 * After a successful military operation in the Andromeda nebula the active colonization
 * of habitable planets has started. The need for people able to take command and lead
 * people to the new worlds has increased. Therefore, two new education centers should
 * be built on Ataraxia. Discussion about the details of the project in the local
 * administration is already underway for many days. During this time it was decided
 * that the first center will consist of a2 sections and that the second one will
 * consist of no more than n2 sections. The situation is complicated because, according
 * to requirements of the antimonopoly legislation, construction works must be performed
 * by at least two different companies, each of them must build an equal number of
 * buildings and an equal number of 100-meters segments of the fence.
 * You are responsible for resupplying the administration office. You understand that
 * while they are discussing the pros and cons of each possible size of the second
 * center a lot of buns and coffee will be consumed, and it's time to buy them. So
 * you'd like to know how many different sizes of the second center will meet the
 * requirements of antimonopoly legislation and, therefore, will be fully considered
 * by the administration.
 * 
 * [Input]
 * The only line contains integers a and n (1 ≤ a ≤ 1012; 1 ≤ n ≤ 1018).
 * 
 * [Output]
 * Output an amount of different sizes of the second center meeting the requirements
 * of antimonopoly legislation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>
#include <assert.h>

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif // min

static bool is_prime(uint64_t n)
{
    if (n == 0 || n == 1) return true;

    uint64_t divisor = 0;
    // possible max divisor is number / 2
    // otherwise if max_divisor = number / 2 + n (n>=1)
    // other_divisor = number / max_divisor
    // then other_divisor < 2 which is 1.
    for (divisor = n / 2; n % divisor != 0; --divisor) {}
    
    return (divisor == 1);
}

static uint64_t __gcd(uint64_t x, uint64_t y)
{
    if (!x) return y;
    if (!y) return x;
    return __gcd(y % x, x);
}

// greatest common divisor
static uint64_t gcd(uint64_t x, uint64_t y)
{
    uint64_t n = x;
    uint64_t m = 0;
    if (x > y) {
        m = (x % y);
        n = y;
    }
    else if (x < y) {
        m = (y % x);
    }
    else {
        return x;
    }

    return __gcd(n, m);
}

static bool is_even(uint64_t n)
{
    return (n % 2 == 0);
}

static bool is_odd(uint64_t n)
{
    return (n % 2 == 1);
}

static void calc()
{
    uint64_t a, n;
    scanf("%llu %llu", &a, &n);

    uint64_t r = 0;
    for (uint64_t i = 1; i <= n; ++i) {
        if ((is_even(a) && is_even(i)) || (is_odd(a) && is_odd(i)))
            ++r;
        else if (gcd(a * i, a + i) > 1)
            ++r;
    }

    printf("%llu\n", r);
}

int main()
{
    calc();
    return 0;
}


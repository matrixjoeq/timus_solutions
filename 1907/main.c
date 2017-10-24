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
 * that the first center will consist of a^2 sections and that the second one will
 * consist of no more than n^2 sections. The situation is complicated because, according
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
 * The only line contains integers a and n (1 ≤ a ≤ 10^12; 1 ≤ n ≤ 10^18).
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

typedef struct __slist {
    struct __slist* next;
    uint64_t factor;
} slist_t;

static slist_t* list_create_node(slist_t** node, uint64_t value)
{
    assert(node);
    assert(!*node);

    *node = (slist_t*)malloc(sizeof(slist_t));
    assert(*node);

    (*node)->next = 0;
    (*node)->factor = value;

    return *node;
}

static slist_t* list_append_value(slist_t* tail, uint64_t value)
{
    assert(tail);
    assert(!(tail->next));

    slist_t* node = 0;
    list_create_node(&node, value);
    tail->next = node;

    return node;
}

static void list_destroy(slist_t* l)
{
    if (!l) return;
    
    slist_t* p = l->next;
    while (p) {
        free(l);
        l = p;
        p = l->next;
    }

    free(l);
}

static void list_print(slist_t* l)
{
    assert(l);
    while (l) {
        printf("%llu ", l->factor);
        l = l->next;
    }
    printf("\n");
}

static void calc()
{
    uint64_t a, n;
    scanf("%llu %llu", &a, &n);

    // This problem is to find how many numbers in range [1, n],
    // which meets the requirement: gcd(a*a+n*n, 4*(a+n)) > 1.
    // If a*a+n*n is even, gcd(a*a+n*n, 4*(a+n)) must be greater than 1.
    // So, we only need to handle a*a+n*n is odd cases, thus 4 is unnecessary.
    // And since gcd(a, b) = gcd(b%a, a), we get gcd(a*a+n*n, a+n) = gcd(-2an, a+n).
    // Because we are handling a*a+n*n is odd cases, so a and n must be one odd 
    // and the other even => a*n and a+n is odd, thus -2 is unnecessary.
    // Now we need to find gcd(a*n, a+n) > 1 numbers.
    // Assume a = p1*p2*...*ps (pi, 1<=i<=s is prime, without considering duplication)
    // and n = q1*q1*...*qr (qi, 1<=i<=r is prime, without considering duplication).
    // If gcd(a*n, a+n) > 1, there must be a pi == qj, 
    // otherwise a*n = p1*p2*...*ps*q1*q2*...*qr, a+n = o1*o2*...*ot
    // where oi (1<=i<=t) is prime and none of them is the same as pi or qi =>
    // gcd(a*n, a+n) == 1 which is comflicted with assumption. This means gcd(a, n) > 1.
    // On the other hand, if gcd(a, n) > 1, assume d = gcd(a, n), a = d*a', n = d*n'
    // then gcd(a*n, a+n) = gcd(d*d*a'*n', d*(a'+n')) >= d > 1.
    // We get gcd(a*n, a+n) > 1 <=> gcd(a, n) > 1.
    // Finally, we are looking for gcd(a, n) > 1.
    // Use inclusion-exclusion principle to find how many numbers in range [1, n]
    // is not prime to a.
    
    // First, get all prime factors of a.
    slist_t* factors = 0;
    slist_t* tail = 0;
    uint64_t _a = a;
    uint64_t num_factors = 0;
    if (!(_a & 1)) { // a is even
        list_create_node(&factors, 2);
        tail = factors;
        ++num_factors;
        do { _a /= 2; } while (_a % 2 == 0); // remove all 2
    }

    for (uint64_t i = 3; i * i <= _a; i += 2) {
        if (_a % i == 0) {
            ++num_factors;
            if (tail) {
                tail = list_append_value(tail, i);
            }
            else {
                list_create_node(&factors, i);
                tail = factors;
            }

            do { _a /= i; } while (_a % i == 0); // remove all i
        }
    }

    if (_a != 1) {
        ++num_factors;
        if (tail) {
            tail = list_append_value(tail, _a);
        }
        else {
            list_create_node(&factors, _a);
            tail = factors;
        }
    }
    //list_print(factors);
    
    // Following inclusion-exclusion proccess will find all gcd(a, n) > 1 numbers.
    // If a is even, this happens to be the answer. Because gcd(a, n) > 1 covers
    // all even numbers in range [1, n].
    // However, if a is odd, condition gcd(a, n) > 1 and n % 2 == 1 has overlapped
    // region. But none of the two can cover the other. So we need to minus the
    // overlapped region which is counted twice.
    uint64_t r = 0;
    if (a & 1) {
        r += (n + 1) / 2; // add all odd numbers in [1, n]
        n /= 2;
    }
    // inclusion-exclusion process
    for (uint64_t mask = 1; mask < (1 << num_factors); ++mask) {
        uint64_t tmp = 1;
        int c = 0;
        slist_t* x = factors;
        for (uint64_t i = 0; i < num_factors; ++i, x = x->next) {
            if ((1 << i) & mask) {
                ++c;
                tmp *= x->factor;
            }
        }

        if (c & 1) {
            r += (n / tmp);
        }
        else {
            r -= (n / tmp);
        }
    }

    printf("%llu\n", r);
    list_destroy(factors);
}

int main()
{
    calc();
    return 0;
}


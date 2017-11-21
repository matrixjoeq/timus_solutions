/*
 * [Description]
 *
 * [Input]
 *
 * [Output]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_LENGTH(x) (sizeof((x)) / sizeof((x)[0]))

#define s_max_input 100000u
static uint32_t s_rank[s_max_input + 1]; // because node index is 1-based
static uint32_t s_parent[s_max_input + 1];
static uint32_t s_edge_from[s_max_input + 1];
static uint32_t s_edge_to[s_max_input + 1];
static bool     s_skip[s_max_input + 1];
static uint32_t s_thread[s_max_input];
static uint32_t s_count[s_max_input];
static uint32_t s_n_input;
static uint32_t s_m_input;
static uint32_t s_q_input;
static uint32_t s_set_count;

static void get_n_m()
{
    scanf("%u %u", &s_n_input, &s_m_input);
    //printf("n: %u, m: %u\n", s_n_input, s_m_input);
}

static void get_edges()
{
    uint32_t m = 1;
    while (m <= s_m_input)
    {
        scanf("%u %u", &s_edge_from[m], &s_edge_to[m]);
        //printf("edge: %u - %u\n", s_edge_from[m], s_edge_to[m]);
        ++m;
    }
}

static void get_q()
{
    scanf("%u", &s_q_input);
    //printf("q: %u\n", s_q_input);
}

static void get_tears()
{
    uint32_t q = 0;
    while (q < s_q_input)
    {
        scanf("%u", &s_thread[q]);
        //printf("thread: %u\n", s_thread[q]);
        s_skip[s_thread[q]] = true;
        ++q;
    }
}

static void make_set()
{
    for (uint32_t i = 1; i <= s_n_input; ++i)
        s_parent[i] = i;

    s_set_count = s_n_input;
}

static uint32_t find_set(uint32_t x)
{
    /*
    // compress path in this method will cost lot of time
    // result in TLE
    static uint32_t compress[s_max_input + 1];
    static uint32_t index;

    memset(compress, 0, sizeof(compress));
    index = 0;
    while (s_parent[x] != x)
    {
        compress[index++] = x;
        x = s_parent[x];
    }

    for (uint32_t i = 0; i < index; ++i)
        s_parent[compress[i]] = x;

    return x;
    */

    if (s_parent[x] == x)
        return x;
    return s_parent[x] = find_set(s_parent[x]);
}

static void link_set(uint32_t x, uint32_t y)
{
    //printf("link: %u %u\n", x, y);
    if (x == y) return;

    if (s_rank[y] > s_rank[x])
    {
        s_parent[x] = y;
    }
    else
    {
        s_parent[y] = x;
        if (s_rank[x] == s_rank[y])
            s_rank[x] = s_rank[x] + 1;
    }

    --s_set_count;
}

static void union_set(uint32_t x, uint32_t y)
{
    link_set(find_set(x), find_set(y));
}

static void setup_graph()
{
    uint32_t i = 0;
    uint32_t m = 1;
    while (m <= s_m_input)
    {
        if (!s_skip[m])
        {
            union_set(s_edge_from[m], s_edge_to[m]);
        }
        ++m;
    }

    s_count[0] = s_set_count;
    //printf("init set count: %u\n", s_count[0]);
}

static void reverse_add_edges()
{
    uint32_t q = s_q_input - 1;
    uint32_t index = 1;
    while (q > 0)
    {
        union_set(s_edge_from[s_thread[q]], s_edge_to[s_thread[q]]);
        s_count[index] = s_set_count;
        ++index;
        --q;
    }
}

static void output_count()
{
    uint32_t q = s_q_input;
    while (q-- > 0)
    {
        printf("%u", s_count[q]);
        if (q != 0)
            printf(" ");
        else
            printf("\n");
    }
}

int main()
{
    get_n_m();
    get_edges();
    get_q();
    get_tears();
    make_set();
    setup_graph();
    reverse_add_edges();
    output_count();

    return 0;
}


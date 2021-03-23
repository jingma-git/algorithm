// union find
#include <cstdio>
#include <algorithm>

#define MAXN 100

struct Edge
{
    int u, v;
    int w;
    Edge() {}
    Edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
};

Edge e[MAXN];
int p[MAXN];
int n;
int find(int x)
{
    return x == p[x] ? p[x] : p[x] = find(p[x]);
}

int main()
{
    n = 8;
    e[0] = {0, 1, 1};
    e[1] = {1, 3, 3};
    e[2] = {3, 5, 15};
    e[3] = {5, 4, 4};
    e[4] = {4, 2, 5};
    e[5] = {2, 3, 4};
    e[6] = {1, 2, 9};
    e[7] = {0, 2, 12};
    for (int i = 0; i < 6; i++)
    {
        p[i] = i;
    }

    std::sort(e, e + n, [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int x = find(e[i].u);
        int y = find(e[i].v);
        if (x != y)
        {
            sum += e[i].w;
            p[x] = y;
            printf("add edge %d-%d (x=%d, y=%d) sum=%d\n", e[i].u, e[i].v, x, y, sum);
        }
    }
    printf("sum=%d\n", sum);
    return 0;
}
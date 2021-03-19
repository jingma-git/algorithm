// breath first search
// find connected component in a graph (p162 Oil Deposit, Uva 572)

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define MAXN 6

struct Pos
{
    int x, y;
};

char pic[MAXN][MAXN];
int m, n, dis[MAXN][MAXN], vis[MAXN][MAXN];

void fill()
{
    pic[0][2] = '@';
    pic[1][1] = '@';
    pic[2][1] = '@';
    pic[2][3] = '@';
    pic[2][4] = '@';
    pic[3][1] = '@';
    pic[4][3] = '@';
}

void print_pic()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (pic[i][j] == '@')
            {
                printf("@");
            }
            else
            {
                printf("*");
            }
        }

        printf("\n");
    }
}

void print_dis()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (pic[i][j] == '@')
            {
                printf("%3s", "@");
            }
            else
            {
                printf("%3d", dis[i][j]);
            }
        }

        printf("\n");
    }
}

void bfs()
{
    queue<Pos> Q;
    int cnt = 0;

    Q.push({0, 0});
    dis[0][0] = 0;
    vis[0][0] = 1;

    while (!Q.empty())
    {
        Pos p = Q.front();
        Q.pop();
        vis[p.x][p.y] = 1;

        // cout << "visit " << p.x << ", " << p.y << endl;
        for (int r = p.x - 1; r <= p.x + 1; r++)
        {
            for (int c = p.y - 1; c <= p.y + 1; c++)
            {
                if ((r == p.x - 1 && c == p.y - 1) ||
                    (r == p.x - 1 && c == p.y + 1) ||
                    (r == p.x + 1 && c == p.y - 1) ||
                    (r == p.x + 1 && c == p.y + 1))
                    continue;
                if (r >= 0 && r < m && c >= 0 && c < n)
                {
                    if (vis[r][c] == 0 && pic[r][c] != '@')
                    {
                        // cout << "push " << r << ", " << c << " dis=" << dis[p.x][p.y] << endl;
                        Q.push({r, c});
                        dis[r][c] = dis[p.x][p.y] + 1;
                        vis[p.x][p.y] = 1;
                    }
                }
            }
        }
    }
}

int main()
{
    m = 6;
    n = 5;
    fill();
    print_pic();
    memset(vis, 0, sizeof(vis));
    memset(dis, -1, sizeof(vis));

    bfs();

    print_dis();
    return 0;
}
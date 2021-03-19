// breath first search
// find connected component in a graph (p162 Oil Deposit, Uva 572)

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define MAXN 5

struct Pos
{
    int x, y;
};

char pic[MAXN][MAXN];
int m, n, idx[MAXN][MAXN];

void fill()
{
    for (int i = 0; i < m; i++)
        pic[i][4] = '@';
    for (int i = 1; i < m; i++)
        pic[i][1] = '@';
    pic[3][0] = '@';
    pic[4][0] = '@';
    pic[1][2] = '@';
    pic[3][2] = '@';
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

void print_idx()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", idx[i][j]);
        printf("\n");
    }
}

int bfs()
{
    queue<Pos> Q;
    int cnt = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (idx[i][j] == 0 && pic[i][j] == '@')
            {
                cnt++;
                Q.push({i, j});

                while (!Q.empty())
                {
                    Pos p = Q.front();
                    Q.pop();
                    idx[p.x][p.y] = cnt;
                    // cout << "visit " << p.x << ", " << p.y << endl;
                    for (int r = p.x - 1; r <= p.x + 1; r++)
                    {
                        for (int c = p.y - 1; c <= p.y + 1; c++)
                        {
                            if (r >= 0 && r < m && c >= 0 && c < n)
                            {
                                if (idx[r][c] == 0 && pic[r][c] == '@')
                                {
                                    // cout << "push " << r << ", " << c << endl;
                                    Q.push({r, c});
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

int main()
{
    m = 5;
    n = 5;
    fill();
    print_pic();
    memset(idx, 0, sizeof(idx));

    int cnt = bfs();

    printf("num_comps=%d\n", cnt);
    print_idx();
    return 0;
}
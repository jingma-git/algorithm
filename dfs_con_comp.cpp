// depth first search
// find connected component in a graph (p162 Oil Deposit, Uva 572)

#include <iostream>
#include <stack>
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

int dfs_stack()
{
    stack<Pos> s;
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (idx[i][j] == 0 && pic[i][j] == '@')
            {
                cnt++;
                s.push({i, j});
                idx[i][j] = cnt;
                printf("push (%d, %d) cnt=%d\n", i, j, cnt);
                while (!s.empty())
                {
                    Pos p = s.top();
                    int row = -1;
                    int col = -1;
                    for (int r = p.x - 1; r <= p.x + 1; r++)
                    {
                        for (int c = p.y - 1; c <= p.y + 1; c++)
                        {
                            if (r >= 0 && r < m && c >= 0 && c < n)
                            {
                                if (idx[r][c] == 0 && pic[r][c] == '@')
                                {
                                    row = r;
                                    col = c;
                                    break;
                                }
                            }
                        }
                        if (row != -1 && col != -1)
                            break;
                    }

                    if (row != -1 && col != -1)
                    {
                        s.push({row, col});
                        idx[row][col] = cnt;
                        printf("push (%d, %d) cnt=%d\n", row, col, cnt);
                    }
                    else
                    {
                        s.pop();
                        printf("pop (%d, %d) cnt=%d\n", p.x, p.y, cnt);
                    }
                }
            }
        }
    }

    return cnt;
}

void dfs(int i, int j, int cnt)
{
    idx[i][j] = cnt;

    for (int r = i - 1; r <= i + 1; r++)
    {
        for (int c = j - 1; c <= j + 1; c++)
        {
            if (r >= 0 && r < m && c >= 0 && c < n)
                if (idx[r][c] == 0 && pic[r][c] == '@')
                {

                    dfs(r, c, cnt);
                }
        }
    }
}

int dfs_recursive()
{
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (idx[i][j] == 0 && pic[i][j] == '@')
            {
                dfs(i, j, ++cnt);
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
    // int cnt = dfs_stack();
    int cnt = dfs_recursive();

    printf("num_comps=%d\n", cnt);
    print_idx();
    return 0;
}
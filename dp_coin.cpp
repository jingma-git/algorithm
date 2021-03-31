#include <iostream>
#include <map>
#include <vector>

using namespace std;
const int MAXN = 10000;
const int INF = 1 << 30;
int n, S; // number of coins, total money to reach
vector<int> V;
map<int, int> minv, maxv;         // key: total money for state S, val: minimum/maximum #coins to reach S
map<int, int> min_coin, max_coin; // final path

string print_ans(map<int, int> &path, int init_state)
{
    string str = "";
    int s = init_state;
    while (s)
    {
        int j = path[s];
        str += to_string(V[j]) + " ";
        s -= V[j];
    }
    return str;
}

int main()
{
    n = 3;
    S = 9;
    V.resize(n);
    V[0] = 1;
    V[1] = 5;
    V[2] = 10;

    minv[0] = 0;
    maxv[0] = 0;
    for (int s = 1; s < S; s++)
    {
        minv[s] = INF;
        maxv[s] = -INF;
    }

    for (int s = 1; s < S; s++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s >= V[j])
            {
                if (minv[s - V[j]] + 1 < minv[s])
                {
                    minv[s] = minv[s - V[j]] + 1;
                    min_coin[s] = j;
                }

                if (maxv[s - V[j]] + 1 > maxv[s])
                {
                    maxv[s] = maxv[s - V[j]] + 1;
                    max_coin[s] = j;
                }
            }
        }
    }

    for (int s = 0; s < S; s++)
    {
        cout << "total money=" << s << endl;
        cout << "min:" << endl;
        cout << (minv[s] > MAXN ? "unreachable" : print_ans(min_coin, s)) << endl;
        cout << "max:" << endl;
        cout << (maxv[s] < 0 ? "unreachable" : print_ans(max_coin, s)) << endl;
        cout << endl;
    }
    return 0;
}
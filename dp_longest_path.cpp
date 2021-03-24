// https://blog.csdn.net/ccnuacmhdu/article/details/81133637
#include <iostream>
#include <vector>
using namespace std;

struct Rect
{
    int width, height;
    Rect() {}
    Rect(int w, int h) : width(w), height(h) {}
    bool contains(const Rect &other)
    {
        return ((width > other.width && height > other.height) || (height > other.width && width > other.height));
    }
};

int n;
vector<vector<int>> G;
vector<Rect> R;
vector<int> d, nodes;
int dp(int i)
{
    int &ans = d[i];
    if (ans > 0)
        return ans;
    ans = 1;
    for (int j = 0; j < n; j++)
    {
        if (G[i][j])
            ans = max(ans, dp(j) + 1);
    }
    return ans;
}

void print_ans(int i)
{
    printf("%d ", i);
    for (int j = 0; j < n; j++)
    {
        if (G[i][j])
        {
            print_ans(j);
            break;
        }
    }
}

int main()
{
    R.emplace_back(1, 2); //0
    R.emplace_back(3, 4); //1
    R.emplace_back(3, 5); //2
    R.emplace_back(4, 6); //3
    R.emplace_back(5, 6); //4
    R.emplace_back(4, 8); //5
    R.emplace_back(7, 8); //6
    n = R.size();
    G.resize(n);
    for (int i = 0; i < n; i++)
    {
        G[i].resize(n, 0);
    }
    G[0][1] = 1;
    G[0][2] = 1;
    G[1][3] = 1;
    G[1][4] = 1;
    G[1][5] = 1;
    G[2][3] = 1;
    G[2][4] = 1;
    G[2][5] = 1;
    G[3][6] = 1;
    G[4][6] = 1;

    d.resize(n, 0);
    for (int i = 0; i < n; i++)
    {
        dp(i);
        nodes.push_back(i);
    }

    std::sort(nodes.begin(), nodes.end(), [&](int a, int b) {
        return d[a] > d[b];
    });
    int maxd = d[nodes[0]];
    auto it = std::remove_if(nodes.begin(), nodes.end(), [&](int node) {
        return d[node] < maxd;
    });
    nodes.erase(it, nodes.end());
    for (auto node : nodes)
    {
        print_ans(node);
        break;
    }
    cout << endl;
    return 0;
}
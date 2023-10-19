#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int min_v = 2147483647;
int max_v = 1000000000;
int N, K, fill_mask;
vector<vector <int>> v;

void find_min(int bit, int now, int val)
{
    if (bit == fill_mask)
        min_v = min(min_v, val);
    else
        for (int i = 0; i < N; i++)
            if ((bit & (1 << i)) == 0)
                find_min((bit | (1 << i)), i, val + v[now][i]);
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    v.assign(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> v[i][j];
            if (i == j)
                v[i][j] = max_v;
        }
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (i != j && v[i][j] > v[i][k] + v[k][j])
                    v[i][j] = v[i][k] + v[k][j];
    fill_mask = (1 << N) - 1;
    find_min(1 << K, K, 0);
    cout << min_v << "\n";
}
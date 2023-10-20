#include <iostream>
#include <vector>
#define INF 1000000000
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, Q;
	cin >> N >> Q;
	vector<vector<vector<int>>> v(N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1)));
	for (int i = 1; i < N + 1; i++)
		for (int j = 1; j < N + 1; j++)
		{
			cin >> v[i][j][0];
			if (i != j && v[i][j][0] == 0)
				v[i][j][0] = INF;
		}
	for (int k = 1; k < N + 1; k++)
	{
		for (int i = 1; i < N + 1; i++)
			for (int j = 1; j < N + 1; j++)
				v[i][j][k] = v[i][j][k - 1];
		for (int i = 1; i < N + 1; i++)
			for (int j = 1; j < N + 1; j++)
				if (v[i][j][k] > v[i][k][k] + v[k][j][k])
					v[i][j][k] = v[i][k][k] + v[k][j][k];
	}
	for (int i = 0; i < Q; i++)
	{
		int C, s, e;
		cin >> C >> s >> e;
		if (v[s][e][C - 1] == INF)
			cout << -1 << "\n";
		else
			cout << v[s][e][C - 1] << "\n";
	}
}

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int	N, depart, arrive, M;
	long long INF = 100000000000000000;
	long long a_cost = INF;
	cin >> N >> depart >> arrive >> M;

	vector<long long> ans(N);
	vector<long long> earn(N);
	vector<vector<pair<int, long long>>> v(N, vector<pair<int, long long>>());
	for (int i = 0; i < M; i++)
	{
		int from, to;
		long long c;
		cin >> from >> to >> c;
		v[from].push_back({to, c});
	}
	for (int i = 0; i < N; i++)
	{
		long long c;
		cin >> c;
		earn[i] = -c;
	}
	fill(ans.begin(), ans.end(), INF);
	ans[depart] = 0 + earn[depart];
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (ans[j] == INF)
				continue;
			for (pair<int, long long> t : v[j])
				if (ans[t.first] > ans[j] + t.second + earn[t.first])
					ans[t.first] = ans[j] + t.second + earn[t.first];
			a_cost = min(a_cost, ans[arrive]);
		}
	}
	if (ans[arrive] == INF)
		cout << "gg\n";
	else
	{
		long long pre = ans[arrive];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (ans[j] == INF)
					continue;
				for (pair<int, long long> t : v[j])
					if (ans[t.first] > ans[j] + t.second + earn[t.first])
						ans[t.first] = ans[j] + t.second + earn[t.first];
				a_cost = min(a_cost, ans[arrive]);
			}
		}
		if (pre > ans[arrive])
			cout << "Gee\n";
		else
			cout << -a_cost << "\n";
	}
}
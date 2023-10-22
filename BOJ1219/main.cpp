#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int	N, depart, arrive, M;
	long long INF = 1000000000000000000;
	cin >> N >> depart >> arrive >> M;

	vector<long long> ans(N, INF);
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
	ans[depart] = 0 + earn[depart];
	if (N == 1)
	{
		for (int j = 0; j < M; j++)
		{
			if (earn[0] + v[0][j].second < 0)
			{
				cout << "Gee\n";
				exit(0);
			}
		}
		cout << -earn[0] << "\n";
		exit(0);
	}
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (ans[j] == INF)
				continue;
			for (pair<int, long long> t : v[j])
				if (ans[t.first] > ans[j] + t.second + earn[t.first])
					ans[t.first] = ans[j] + t.second + earn[t.first];
		}
	}
	if (ans[arrive] == INF)
		cout << "gg\n";
	else
	{
		vector<bool> check(N, false);
		queue<int> q;
		for (int i = 0; i < N - 1; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (ans[j] == INF)
					continue;
				for (pair<int, long long> t : v[j])
					if (ans[t.first] > ans[j] + t.second + earn[t.first])
						q.push(t.first);
			}
		}
		while(!q.empty())
		{
			int next = q.front();
			q.pop();
			if (!check[next])
			{
				check[next] = true;
				for (pair<int, long long> p : v[next])
					if (!check[p.first])
						q.push(p.first);
			}
		}
		if (check[arrive])
			cout << "Gee\n";
		else
			cout << -ans[arrive] << "\n";
	}
}
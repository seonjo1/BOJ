#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <set>

using namespace std;

vector<int> connectionNum;
vector<vector<int>> v;
vector<vector<int>> check;
vector<int> idxV;
vector<bool> finish;
stack<int> s;
int T, N, M, ans, num;

int dfs(int now)
{
	int nNum = num++;
	idxV[now] = nNum;
	s.push(now);
	for (int next : v[now])
	{
		if (idxV[next] == 0) idxV[now] = min(idxV[now], dfs(next));
		else if (!finish[next]) idxV[now] = min(idxV[now], idxV[next]);
	}

	if (idxV[now] == nNum)
	{
		set<int> set;
		while (s.top() != now)
		{
			finish[s.top()] = true;
			set.insert(s.top());
			s.pop();
		}
		set.insert(s.top());
		finish[now] = true;
		s.pop();

		if (set.size() == 1)
			return idxV[now];
		for (int k : set)
		{
			for (int p : check[k])
			{
				if (set.find(p) == set.end())
					return idxV[now];
			}
		}
		ans++;
	}

	return idxV[now];
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> T;
	while (T-- > 0)
	{
		cin >> N >> M;
		connectionNum.assign(N + 1, 0);
		v.assign(N + 1, vector<int>());
		check.assign(N + 1, vector<int>());
		idxV.assign(N + 1, 0);
		finish.assign(N + 1, false);

		for (int i = 0; i < M; i++)
		{
			int a, b;
			cin >> a >> b;
			v[a].push_back(b);
			check[b].push_back(a);
			connectionNum[b]++;
		}


		num = 1;
		ans = 0;
		for (int i = 1; i <= N; i++)
		{
			if (!finish[i])
				dfs(i);
		}

		for (int i = 1; i <= N; i++)
		{
			if (connectionNum[i] == 0)
				ans++;
		}
		cout << ans << "\n";
	}
	return 0;
}
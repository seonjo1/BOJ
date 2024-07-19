#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;

vector<vector<int>> scc;
vector<bool> check;
vector<int> finish;
vector<int> idx;
stack<int> s;

int T, N, M, num, sccNum;

void dfsCheck(int node)
{
	check[node] = true;
	for (int next : scc[node])
		if (!check[next]) dfsCheck(next);
}

bool isConfused()
{
	for (int i = 0; i < N; i++)
	{
		if (!check[i])
			return true;
	}
	return false;
}

int dfs(int now)
{
	int idxNum = idx[now] = ++num;
	s.push(now);

	for (int next : scc[now])
	{
		if (idx[next] == -1) idx[now] = min(idx[now], dfs(next));
		else if (finish[next] == -1) idx[now] = min(idx[now], idx[next]);
	}

	if (idx[now] == idxNum)
	{
		++sccNum;
		while (s.top() != now)
		{
			finish[s.top()] = sccNum;
			s.pop();
		}
		finish[s.top()] = sccNum;
		s.pop();
	}
	return idx[now];
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
		scc.assign(N, vector<int>());
		finish.assign(N, -1);
		idx.assign(N, -1);
		check.assign(N, false);
		num = 0;
		sccNum = 0;

		for (int i = 0; i < M; i++)
		{
			int A, B;
			cin >> A >> B;
			scc[A].push_back(B);
		}

		for (int i = 0; i < N; i++)
		{
			if (finish[i] == -1)
				dfs(i);
		}
		
		int start = find(finish.begin(), finish.end(), sccNum) - finish.begin();
		dfsCheck(start);
		if (isConfused())
			cout << "Confused\n";
		else
		{
			for (int i = 0; i < N; i++)
			{
				if (finish[i] == sccNum)
					cout << i << "\n";
			}
		}

		if (T != 0)
			cout << "\n";
	}
}
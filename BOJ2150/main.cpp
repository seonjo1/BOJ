#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<bool> finish(10001, false);
vector<int> order(10001, 0);
vector<vector<int>> v(10001);
vector<vector<int>> printVec;
stack<int> s;

int orderNum = 1;
int E, V;
int ans = 0;

bool compare(vector<int> v1, vector<int> v2)
{
	return v1[0] < v2[0];
}

int dfs(int node)
{
	int idx = orderNum;
	order[node] = orderNum++;
	s.push(node);
	for (int next : v[node])
	{
		if (order[next] == 0) order[node] = min(order[node], dfs(next));
		else if (!finish[next]) order[node] = min(order[node], order[next]);
	}
	if (order[node] == idx)
	{
		vector<int> tmp;
		while (s.top() != node)
		{
			tmp.push_back(s.top());
			s.pop();
			finish[tmp.back()] = true;

		}
		tmp.push_back(s.top());
		finish[tmp.back()] = true;
		s.pop();
		ans++;
		printVec.push_back(tmp);
	}
	return order[node];
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> V >> E;

	int a, b;
	for (int i = 0; i < E; i++)
	{
		cin >> a >> b;
		v[a].push_back(b);
	}

	for (int i = 1; i <= V; i++)
	{
		if (!finish[i])
			dfs(i);
	}

	cout << ans << "\n";

	for (vector<int>& scc : printVec)
		sort(scc.begin(), scc.end());

	sort(printVec.begin(), printVec.end(), compare);
	
	for (vector<int> scc : printVec)
	{
		for (int element : scc)
			cout << element << " ";
		cout << "-1\n";
	}
}
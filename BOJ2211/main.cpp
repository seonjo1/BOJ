#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000;

using namespace std;

typedef struct{
	int pre;
	int now;
	int val;
} node;

struct cmp{
	bool operator()(node a, node b){
		return a.val > b.val;
	}
};

int N, M;
vector<pair<int, int>> v[1001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back(make_pair(to, cost));
		v[to].push_back(make_pair(from, cost));
	}
	bool *check = new bool[N + 1];
	int *cost = new int[N + 1];
	for (int i = 1; i < N + 1; i++)
	{
		cost[i] = INF;
		check[i] = false;
	}
	priority_queue<node, vector<node>, cmp> pq;
	queue<pair<int, int>> ans;
	pq.push({0, 1, 0});
	while (!pq.empty())
	{
		int val, pre, now;
		pre = pq.top().pre;
		now = pq.top().now;
		val = pq.top().val;
		pq.pop();
		if (!check[now])
		{
			check[now] = true;
			if (pre != 0)
				ans.push({pre, now});
			for (pair<int, int> next : v[now])
			{
				if (cost[next.first] > val + next.second)
				{
					cost[next.first] = val + next.second;
					pq.push({now, next.first, cost[next.first]});
				}
			}
		}
	}
	cout << ans.size() << "\n";
	while (!ans.empty())
	{
		cout << ans.front().first << " " << ans.front().second << "\n";
		ans.pop();
	}
}
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int island[10001];
int	group[10001];

typedef struct s_bridge
{
	int A;
	int B;
	int C;
	s_bridge(int a, int b, int c) : A(a), B(b), C(c) {}
} t_bridge;

struct cmp{
	bool operator()(t_bridge a, t_bridge b)
	{
		return a.C < b.C;
	}
};

int Find(int x)
{
	if (group[x] == x)
		return x;
	return group[x] = Find(group[x]);
}

int Union(int a, int b)
{
	int x = Find(a);
	int y = Find(b);

	if (x < y)
		return group[y] = x;
	else
		return group[x] = y;
}


int main()
{
	ios::sync_with_stdio();
	cin.tie(0);
	cout.tie(0);
	
	cin >> N >> M;
	for (int i = 1; i <= 10000; i++)
	{
		group[i] = i;
		island[i] = 1000000000;
	}
	priority_queue<t_bridge, vector<t_bridge>, cmp> pq;
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		pq.push(t_bridge(a, b, c));
	}
	int depart, arrive;
	cin >> depart >> arrive;
	if (depart > arrive)
	{
		int tmp = depart;
		depart = arrive;
		arrive = depart;
	}
	while (!pq.empty())
	{
		t_bridge n = pq.top();
		pq.pop();
		int p = Union(n.A, n.B);
		island[p] = min(island[p], n.C);
		if (Find(group[depart]) == Find(group[arrive]))
		{
			cout << island[depart] << "\n";
			exit(0);
		}
	}
}
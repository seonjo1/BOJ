#include <iostream>
#include <vector>
#include <cmath>

#define SUM 0

using namespace std;

vector<long long> tree;
vector<long long> v;

long long getSum(int node, int start, int end, int l, int r)
{
	if (r < start || end < l) return 0;
	else if (l <= start && end <= r) return tree[node];

	int mid = (start + end) / 2;
	return getSum(node * 2, start, mid, l, r) + getSum(node * 2 + 1, mid + 1, end, l, r);
}

void update(int node, int start, int end, int idx, long long diff)
{
	if (idx < start || end < idx) return ;
	tree[node] += diff;
	if (start != end)
	{
		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, diff);
		update(node * 2 + 1, mid + 1, end, idx, diff);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M;
	cin >> N >> M;

	v.resize(N + 1, 0);
	tree.resize(1 << ((int)ceil(log2(N)) + 1), 0);

	for (int i = 0; i < M; i++)
	{
		int cmd, a, b;
		cin >> cmd >> a >> b;
		if (cmd == SUM)
		{
			if (a > b) swap(a, b);
			cout << getSum(1, 1, N, a, b) << "\n";
		}
		else
		{
			update(1, 1, N, a, b - v[a]);
			v[a] = b;
		}
	}
}
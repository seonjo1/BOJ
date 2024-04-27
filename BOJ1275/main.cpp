#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<long long> tree;
vector<long long> v;

long long makeTree(int node, int start, int end)
{
	if (start == end) return tree[node] = v[start];
	int mid = (start + end) / 2;
	return tree[node] = makeTree(node * 2, start, mid) + makeTree(node * 2 + 1, mid + 1, end);
}

long long getSum(int node, int start, int end, int l, int r)
{
	if (r < start || end < l) return 0;
	else if (l <= start && end <= r) return tree[node];
	int mid = (start + end) / 2;
	return getSum(node * 2, start, mid, l, r) + getSum(node * 2 + 1, mid + 1, end, l, r);
}

void update(int node, int start, int end, int idx, long long diff)
{
	if (idx < start || end < idx) return;
	tree[node] += diff;
	if (start == end) return ;
	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, diff);
	update(node * 2 + 1, mid + 1, end, idx, diff);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, Q;
	cin >> N >> Q;
	
	v.resize(N + 1, 0);
	tree.resize((1 << ((int)ceil(log2(N)) + 1)), 0);

	for (int i = 1; i <= N; i++)
		cin >> v[i];
	
	makeTree(1, 1, N);

	for (int i = 0; i < Q; i++)
	{
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		if (x > y) swap(x, y);
		cout << getSum(1, 1, N, x, y) << "\n";
		update(1, 1, N, a, b - v[a]);
		v[a] = b;
	}
}
#include <iostream>
#include <vector>
#include <cmath>

#define MAX 1000000001

using namespace std;

vector<int> tree;
vector<int> v;

int makeTree(int node, int start, int end)
{
	if (start == end) return tree[node] = v[start];
	int mid = (start + end) / 2;
	makeTree(node * 2, start, mid);
	makeTree(node * 2 + 1, mid + 1, end);
	return tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

int getMin(int node, int start, int end, int l, int r)
{
	if (r < start || end < l) return MAX;
	if (l <= start && end <= r) return tree[node];
	int mid = (start + end) / 2;
	return min(getMin(node * 2, start, mid, l, r), getMin(node * 2 + 1, mid + 1, end, l, r));
}

void update(int node, int start, int end, int idx, int val)
{
	if (idx < start || end < idx) return ;
	if (start == end)
		tree[node] = val;
	else
	{
		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M;
	cin >> N;

	v.resize(N + 1, 0);
	tree.resize(1 << ((int)ceil(log2(N)) + 1), 0);

	for (int i = 1; i <= N; i++)
		cin >> v[i];

	makeTree(1, 1, N);
	
	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int A, B, C;
		cin >> A >> B >> C;
		if (A == 1)
			update(1, 1, N, B, C);
		else
		{
			if (B > C) swap(B, C);
			cout << getMin(1, 1, N, B, C) << "\n";
		}
	}
}
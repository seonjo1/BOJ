#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> tree;
int ans;

void makeTree(int node, int start, int end, int n)
{
	if (start == end)
	{
		if (start <= n)
			tree[node] = 1;
	}
	else
	{
		int mid = (start + end) / 2;
		makeTree(node * 2, start, mid, n);
		makeTree(node * 2 + 1, mid + 1, end, n);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

int remove(int node, int start, int end, int idx)
{
	if (start <= idx && idx <= end)
	{
		tree[node]--;
		if (start != end)
		{
			int mid = (start + end) / 2;
			int left = remove(node * 2, start, mid, idx);
			int right = remove(node * 2 + 1, mid + 1, end, idx);
			if (left) ans += (tree[node] - tree[node * 2]);
		}
		return 1;
	}
	return 0;
}

void update(int node, int start, int end, int idx)
{
	if (start <= idx && idx <= end)
	{
		tree[node]++;
		if (start != end)
		{
			int mid = (start + end) / 2;
			update(node * 2, start, mid, idx);
			update(node * 2 + 1, mid + 1, end, idx);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	while (T-- > 0)
	{
		int n, m;
		cin >> n >> m;

		vector<int> v(n + 1, 0);
		for (int i = 1; i < n + 1; i++)
			v[i] = n - i + 1;
		int size = 1 << ((int)ceil(log2(n + m)) + 1);
		tree.resize(size, 0);
		for (int i = 1; i < size; i++)
			tree[i] = 0;
		makeTree(1, 1, n + m, n);
		for (int i = 1; i <= m; i++)
		{
			ans = 0;
			int idx;
			cin >> idx;
			remove(1, 1, n + m, v[idx]);
			v[idx] = n + i;
			update(1, 1, n + m, v[idx]);
			cout << ans << " ";
		}
		cout << "\n";
	}
}
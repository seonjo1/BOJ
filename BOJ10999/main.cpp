#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<long long> tree;
vector<long long> lazy;
vector<long long> v;

long long makeTree(int node, int start, int end)
{
	if (start == end) return tree[node] = v[start];
	int mid = (start + end) / 2;
	return tree[node] = makeTree(node * 2, start, mid) + makeTree(node * 2 + 1, mid + 1, end);
}

void lazy_update(int node, int start, int end)
{
	if (lazy[node] != 0)
	{
		tree[node] += (end - start + 1) * lazy[node];
		if (start != end)
		{
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(int node, int start, int end, int a, int b, long long val)
{
	lazy_update(node, start, end);
	if (b < start || end < a) return ;
	if (a <= start && end <= b)
	{
		tree[node] += val * (end - start + 1);
		if (start != end)
		{
			lazy[node * 2] += val;
			lazy[node * 2 + 1] += val;
		}
		return;
	}
	int mid = (start + end) / 2;
	update(node * 2 , start, mid, a, b, val);
	update(node * 2 + 1, mid + 1, end, a, b, val);	
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long sum(int node, int start, int end, int a, int b)
{
	lazy_update(node, start, end);
	if (b < start || end < a) return 0;
	if (a <= start && end <= b)
		return tree[node];
	int mid = (start + end) / 2;
	return sum(node * 2, start, mid, a, b) + sum(node * 2 + 1, mid + 1, end, a, b);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M, K;
	cin >> N >> M >> K;

	v.resize(N + 1, 0);
	tree.resize((1 << ((int)ceil(log2(N)) + 1)), 0);
	lazy.resize((1 << ((int)ceil(log2(N)) + 1)), 0);
	for (int i = 1; i <= N; i++)
		cin >> v[i];
	makeTree(1, 1, N);
	for(int i = 0; i < (M + K); i++)
	{
		int a, b, c;
		long long d;
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c >> d;
			update(1, 1, N, b, c, d);
		}
		else
		{
			cin >> b >> c;
			cout << sum(1, 1, N, b, c) << "\n";
		}
	}
}
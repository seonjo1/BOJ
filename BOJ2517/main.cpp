#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> tree;
vector<int> v;

int makeTree(int node, int start, int end)
{
	if (start == end) return tree[node] = v[start];

	int mid = (start + end) / 2;
	int left = makeTree(node * 2, start, mid);
	int right = makeTree(node * 2 + 1, mid + 1, end);
	return (tree[node] = max(left, right));
}

int findRank(int node, int start, int end, int i, int val)
{
	if (i < start || tree[node] <= val) return 0;
	else if (start == end)
	{
		if (tree[node] > val) return 1;
		else return 0;
	}
	int mid = (start + end) / 2;
	return (findRank(node * 2, start, mid, i, val) + findRank(node * 2 + 1, mid + 1, end, i, val));
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	v.resize(N + 1, 0);
	tree.resize(1 << ((int)ceil(log2(N)) + 1));

	for (int i = 0; i < N; i++)
		cin >> v[i];
	makeTree(1, 0, N - 1);

	for (int i = 0; i < N; i++)
		cout << findRank(1, 0, N - 1, i, v[i]) + 1 << "\n";
}
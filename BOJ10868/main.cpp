#include <iostream>
#include <vector>
#include <cmath>
#define MAX 1000000000
using namespace std;

vector<int> v;
vector<int> tree;

int makeTree(int node, int start, int end)
{
	if (start == end) return (tree[node] = v[start]);
	
	int mid = (start + end) / 2;
	int left = makeTree(node * 2, start, mid);
	int right = makeTree(node * 2 + 1, mid + 1, end);
	return tree[node] = min(left, right);
}

int find(int node, int start, int end, int a, int b)
{
	if (b < start || end < a) return MAX;
	else if (a <= start && end <= b) return (tree[node]);
	int mid = (start + end) / 2;
	int left = find(node * 2, start, mid, a, b);
	int right = find(node * 2 + 1, mid + 1, end, a, b);
	return min(left, right);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, M;
	cin >> N >> M;

	int h = (int)ceil(log2(N));
	int size = (1 << (h + 1));
	v.resize(N);
	tree.resize(size);

	for (int i = 0; i < N; i++)
		cin >> v[i];

	makeTree(1, 0, N - 1);

	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		cout << find(1, 0, N - 1, a - 1, b - 1) << "\n";
	}
}
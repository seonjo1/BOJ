#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

std::vector<int> tree;
long long sum = 0;

int line(int node, int start, int end, int idx)
{
	if (idx < start || end < idx) return 0;
	if (start == end) return 1;
	int mid = (start + end) / 2;
	int left = line(node * 2, start, mid, idx);
	line(node * 2 + 1, mid + 1, end, idx);
	tree[node]++;
	if (left) sum += tree[node] - left;
	return tree[node];
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int serial[1000001];
	std::queue<int> q;

	int n;
	std::cin >> n;
	tree.resize((1 << ((int)ceil(log2(n)) + 1)), 0);

	int num;
	for (int i = 0; i < n; i++)
	{
		std::cin >> num;
		q.push(num);
	}
	for (int i = 0; i < n; i++)
	{
		std::cin >> num;
		serial[num] = i;
	}
	while (!q.empty())
	{
		line(1, 0, n - 1, serial[q.front()]);
		q.pop();
	}
	std::cout << sum << "\n";
	return 0;
}
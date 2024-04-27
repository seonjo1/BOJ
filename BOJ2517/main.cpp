#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

vector<long long> tree;
vector<pair<int ,int>> v;

int sum;

bool compareT(pair<int, int> a, pair<int, int> b)
{
	return (a.first < b.first);
}

long long getMaxRank(int node, int start, int end, int idx)
{
	if (idx < start || end < idx) return 0;
	else if (start == end) return 1;
	
	int mid = (start + end) / 2;
	int left = getMaxRank(node * 2, start, mid, idx);
	int right = getMaxRank(node * 2 + 1, mid + 1, end, idx);
	++tree[node];
	if (right) sum += (tree[node] - right);
	return tree[node];
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	v.resize(N);
	tree.resize(1 << ((int)ceil(log2(N)) + 1));

	for (int i = 0; i < N; i++)
	{
		v[i] = make_pair(0, i);
		cin >> v[i].first;
	}

	sort(v.begin(), v.end(), compareT);

	long long ans[N];
	for (int i = 0; i < N; i++)
	{
		sum = 0;
		getMaxRank(1, 0, N - 1, v[i].second);
		ans[v[i].second] = v[i].second + 1 - sum;
	}
	for (int i = 0; i < N; i++)
		cout << ans[i] << "\n";
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

vector<long long> tree;
vector<pair<long long, long long>> v;
long long N;
long long sum = 0;

bool compare1(pair<long long, long long> a, pair<long long, long long> b)
{
	if (a.first == b.first)
		return a.second < b.second;
	return (a.first < b.first);
}

long long getSwapNum(long long node, long long start, long long end, long long idx)
{
	if (idx < start || end < idx) return 0;
	else if (start == end) return 1;
	long long mid = (start + end) / 2;
	long long left = getSwapNum(node * 2, start, mid, idx);
	long long right = getSwapNum(node * 2 + 1, mid + 1, end, idx);
	++tree[node];
	if (left) sum += (tree[node] - left);
	return tree[node];
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	v.resize(N);
	tree.resize(1 << ((long long)ceil(log2(N)) + 1), 0);

	for (long long i = 0; i < N; i++)
	{
		v[i] = make_pair(0, i); 
		cin >> v[i].first;
	}
	sort(v.begin(), v.end(), compare1);
	for (long long i = 0; i < N; i++)
		getSwapNum(1, 0, N - 1, v[i].second);
	cout << sum << "\n";
}
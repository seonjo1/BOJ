#include <iostream>
#include <vector>

using namespace std;

vector<int> tree;

int candy;

void takeOutCandy(int node, int start, int end, int rank, int pre, int min)
{
	if (pre != 0)
		min = min + (pre - tree[node]);
	int max = min + tree[node];
	if (min == max) return;
	if (min <= rank && rank < max)
	{
		if (start == end)
			candy = start;
		else
		{
			int mid = (start + end) / 2;
			takeOutCandy(node * 2, start, mid, rank, 0, min);
			takeOutCandy(node * 2 + 1, mid + 1, end, rank, tree[node], min);
		}
		tree[node]--;
	}
}

void insertCandy(int node, int start, int end, int val, int num)
{
	if (val < start || end < val) return;
	tree[node] += num;
	if (start != end)
	{
		int mid = (start + end) / 2;
		insertCandy(node * 2, start, mid, val, num);
		insertCandy(node * 2 + 1, mid + 1, end, val, num);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	tree.resize((1 << 21), 0);
	for (int i = 0; i < n; i++)
	{
		int A, B, C;
		cin >> A;
		if (A == 1)
		{
			cin >> B;
			candy = 0;
			takeOutCandy(1, 1, 1000000, B, 0, 1);
			cout << candy << "\n";
		}
		else
		{
			cin >> B >> C;
			insertCandy(1, 1, 1000000, B, C);
		}
	}
	return 0;
}
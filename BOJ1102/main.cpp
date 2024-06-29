#include <iostream>
#include <cmath>
#include <cstring>

#define MAX 10000000
using namespace std;

int ans = MAX;
int N, P;
int input[16][16];
int dp[(1 << 16)];
int statusSize[1 << 16];

int getStatusSize(int status)
{
	int size = 0;
	for (int i = 0; i < N; i++)
	{
		if ((1 << i) & status)
			size++;
	}
	return size;
}

void makeStatusSize()
{
	int max = (1 << N);
	for (int i = 0; i < max; i++)
		statusSize[i] = getStatusSize(i);
}

int findMin(int status, int idx)
{
	int minVal = MAX;
	for (int i = 0; i < N; i++)
	{
		if (i == idx || !((1 << i) & status)) continue;
		minVal = min(minVal, input[i][idx]);
	}
	return minVal;
}

void letsDP(int status, int val)
{
	if (statusSize[status] >= P)
	{
		ans = min(ans, val);
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			if (!((1 << i) & status))
			{
				int nextValue =  val + findMin(status, i);
				int nextStatus = (1 << i) | status;
				if (dp[nextStatus] > nextValue)
				{
					dp[nextStatus] = nextValue;
					letsDP(nextStatus, nextValue);
				}

			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> input[i][j];

	string inputStr;
	cin >> inputStr;

	int status = 0;
	for (int i = 0; i < inputStr.size(); i++)
		if (inputStr[i] == 'Y')
			status = status | (1 << i);
	cin >> P;
	if (status == 0)
	{
		if (P == 0) cout << "0\n";
		else cout << "-1\n";
		return (0);
	}
	for (int i = 0; i < (1 << N); i++)
		dp[i] = MAX;
	makeStatusSize();
	letsDP(status, 0);
	cout << ans << "\n";
}
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int getChairNum(int n)
{
	int t = 1024;
	int val = 0;
	while (t > 0)
	{
		if (t & n)
			val++;
		t = t >> 1;
	}
	return val;
}

bool isCheating(int n1, int n2)
{
	if ((n1 << 1) & n2)
		return true;
	if ((n1 >> 1) & n2)
		return true;
	return false;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	bool pass[1024];

	for (int i = 0; i < 1024; i++)
		pass[i] = isCheating(i, i);

	int T, N, M;
	cin >> T;
	while (T-- > 0)
	{
		cin >> N >> M;
		int size = (1 << M);
		int dp[N + 1][size];
		for (int i = 0; i <= size; i++)
			dp[0][i] = 0;
		for (int i = 1; i <= N; i++)
		{
			string line;
			cin >> line;
			int block = 0;
			for (int j = 0; j < line.size(); j++)
			{
				if (line[j] == 'x')
					block |= (1 << j);
			}

			for (int k = 0; k < size; k++)
			{
				int chairNum = getChairNum(k);
				
				dp[i][k] = -1;

				if (block & k || pass[k])
					continue ;
				
				for (int l = 0; l < size; l++)
				{
					if (dp[i - 1][l] == -1 || isCheating(k, l))
						continue;
					dp[i][k] = max(dp[i - 1][l] + chairNum, dp[i][k]);
				}
			}
		}

		int maxValue = 0;

		for (int i = 0; i < size; i++)
			maxValue = max(maxValue, dp[N][i]);
		cout << maxValue << "\n";
	}
}
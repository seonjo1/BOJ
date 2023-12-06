#include <iostream>
#include <vector>

using namespace std;
static vector<vector<int>> gear(5, vector<int>(8));

void	cw(int n)
{
	int tmp = gear[n][7];
	for (int i = 7; i > 0; i--)
		gear[n][i] = gear[n][i - 1];
	gear[n][0] = tmp;
}

void	ccw(int n)
{
	int tmp = gear[n][0];
	for (int i = 0; i < 7; i++)
		gear[n][i] = gear[n][i + 1];
	gear[n][7] = tmp;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string s;
	for (int i = 1; i < 5; i++)
	{
		cin >> s;
		for (int j = 0; j < 8; j++)
			gear[i][j] = s[j] - '0';
	}

	int K;
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		int revolve[5] = { 0, 0, 0, 0, 0};
		int n, d;
		cin >> n >> d;
		revolve[n] = d;
		int l = n - 1;
		int ld = -d;
		while (l > 0)
		{
			if (gear[l + 1][6] != gear[l][2])
				revolve[l] = ld;
			else
				break;
			l--;
			ld = -ld;
		}
		int r = n + 1;
		int rd = -d;
		while (r < 5)
		{
			if (gear[r - 1][2] != gear[r][6])
				revolve[r] = rd;
			else
				break;
			r++;
			rd = -rd;
		}
		for (int j = 1; j < 5; j++)
		{
			if (revolve[j] == 1)
				cw(j);
			else if (revolve[j] == -1)
				ccw(j);
		}
	}
	int ans = 0;
	if (gear[1][0] == 1)
		ans += 1;
	if (gear[2][0] == 1)
		ans += 2;
	if (gear[3][0] == 1)
		ans += 4;
	if (gear[4][0] == 1)
		ans += 8;
	cout << ans << endl;
}

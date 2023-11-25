#include <iostream>
#include <vector>

using namespace std;

#define UP 0
#define DOWN 1

int N, L, ans;

void	transpose(vector<vector<int>> &v)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			int tmp = v[i][j];
			v[i][j] = v[j][i];
			v[j][i] = tmp;
		}
	}
}

void	line_check(vector<int> &v, int i, int j, int l_flag)
{
	int x = j - i + 1;
	if (j + 1 == N)
	{
		if (l_flag == DOWN && x < L)
			return;
		ans++;
	}
	else
	{
		if (v[j] == v[j + 1])
			line_check(v, i, j + 1, l_flag);
		else if (v[j] == v[j + 1] + 1)
		{
			if (l_flag == DOWN && x >= L)
				line_check(v, j + 1, j + 1, DOWN);
			else if (l_flag == UP)
				line_check(v, j + 1, j + 1, DOWN);
		}
		else if (v[j] == v[j + 1] - 1)
		{
			if (l_flag == DOWN && x >= 2 * L)
				line_check(v, j + 1, j + 1, UP);
			else if (l_flag == UP && x >= L)
				line_check(v, j + 1, j + 1, UP);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> L;
	vector<vector<int>> v(100,vector<int>(100));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> v[i][j];
	ans = 0;

	for (int i = 0; i < N; i++)
		line_check(v[i], 0, 0, UP);
	transpose(v);
	for (int i = 0; i < N; i++)
		line_check(v[i], 0, 0, UP);
	cout << ans << endl;
}
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> v;
vector<vector<bool>> check;
int n, m, num, cheese, day;
int di[4] = {0, 1, -1, 0};
int dj[4] = {1, 0, 0, -1};

void	bfs(int i, int j)
{
	check[i][j] = true;
	if (v[i][j] == 1)
		return ;
	for (int k = 0; k < 4; k++)
	{
		int i2 = i + di[k];
		int j2 = j + dj[k];
		if (i2 >= 0 && i2 < n && j2 >= 0 && j2 < m)
			if (!check[i2][j2])
				bfs(i2, j2);
	}
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    v.assign(n, vector<int>(m));
	for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> v[i][j];
	bool change = true;
	day = 0;
	while(change)
	{
		num = 0;
		change = false;
		check.assign(n, vector<bool>(m, false));
		for (int i = 0; i < n; i++)
		{
			if (!check[i][0] && v[i][0] == 0)
				bfs(i, 0);
			if (!check[i][m - 1] && v[i][m - 1] == 0)
				bfs(i, m - 1);
		}
		for (int j = 1; j < m; j++)
		{
			if (!check[0][j] && v[0][j] == 0)
				bfs(0, j);
			if (!check[n - 1][j] && v[n - 1][j] == 0)
				bfs(n - 1, j);
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				if (v[i][j] == 1)
				{
					num++;
					if (check[i][j])
					{
						v[i][j] = 0;
						change = true;
					}
				}
			}
		if (!change)
			break;
		day++;
		cheese = num;
	}
	cout << day << "\n" << cheese << "\n";
}
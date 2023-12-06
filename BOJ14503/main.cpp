#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, M, r, c, d, ans;
	cin >> N >> M >> r >> c >> d;
	vector<vector<int>> room(N, vector<int>(M));
	vector<vector<bool>> clean(N, vector<bool>(M, false));

	int dr[] = {0, 1, 0, -1};
	int dc[] = {1, 0, -1, 0};
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> room[i][j];
	if (d == 1)
		d = 3;
	else if (d == 3)
		d = 1;
	
	ans = 0;
	while (1)
	{
		if (!clean[r][c])
		{
			clean[r][c] = true;
			ans++;
		}
		bool dirty = false;
		for (int k = 0; k < 4; k++)
		{
			int sr = r + dr[k];
			int sc = c + dc[k];
			if (sr >= 0 && sr < N && sc >= 0 && sc < M && !clean[sr][sc] && !room[sr][sc])
			{
				dirty = true;
				break;
			}
		}
		if (!dirty)
		{
			int bd = (d + 2) % 4;
			if (bd == 0)
				r--;
			else if (bd == 1)
				c--;
			else if (bd == 2)
				r++;
			else if (bd == 3)
				c++;
			if (r >= 0 && r < N && c >= 0 && c < M && !room[r][c])
				continue;
			else
				break;
		}
		d = (d + 1) % 4;
		if (d == 0 && r - 1 >= 0 && !room[r - 1][c] && !clean[r - 1][c])
			r--;
		else if (d == 1 && c - 1 >= 0 && !room[r][c - 1] && !clean[r][c - 1])
			c--;
		else if (d == 2 && r + 1 < N && !room[r + 1][c] && !clean[r + 1][c])
			r++;
		else if (d == 3 && c + 1 < M && !room[r][c + 1] && !clean[r][c + 1])
			c++;
	}
	cout << ans << endl;
}

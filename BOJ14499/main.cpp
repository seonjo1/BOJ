#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	vector<int> dice = {0, 0, 0, 0, 0, 0};
	int N, M, x, y, K;
	cin >> N >> M >> x >> y >> K;
	vector<vector<int>> board(N, vector<int>(M));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> board[i][j];
	for (int i = 0; i < K; i++)
	{
		int dir;
		cin >> dir;
		if (dir == 1 && y + 1 < M)
		{
			y++;
			int one = dice[2];
			dice[2] = dice[5];
			dice[5] = dice[3];
			dice[3] = dice[0];
			if (board[x][y] == 0)
			{
				board[x][y] = one;
				dice[0] = one;	
			}
			else
			{
				dice[0] = board[x][y];
				board[x][y] = 0;
			}
		}
		else if (dir == 2 && y - 1 >= 0)
		{
			y--;
			int one = dice[3];
			dice[3] = dice[5];
			dice[5] = dice[2];
			dice[2] = dice[0];
			if (board[x][y] == 0)
			{
				board[x][y] = one;
				dice[0] = one;	
			}
			else
			{
				dice[0] = board[x][y];
				board[x][y] = 0;
			}
		}
		else if (dir == 3 && x - 1 >= 0)
		{
			x--;
			int one = dice[1];
			dice[1] = dice[5];
			dice[5] = dice[4];
			dice[4] = dice[0];
			if (board[x][y] == 0)
			{
				board[x][y] = one;
				dice[0] = one;	
			}
			else
			{
				dice[0] = board[x][y];
				board[x][y] = 0;
			}
		}
		else if (dir == 4 && x + 1 < N)
		{
			x++;
			int one = dice[4];
			dice[4] = dice[5];
			dice[5] = dice[1];
			dice[1] = dice[0];
			if (board[x][y] == 0)
			{
				board[x][y] = one;
				dice[0] = one;	
			}
			else
			{
				dice[0] = board[x][y];
				board[x][y] = 0;
			}
		}
		else
			continue;
		cout << dice[5] << "\n";
	}
}
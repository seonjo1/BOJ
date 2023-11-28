#include <iostream>
#include <vector>
#include <queue>
#include <deque>

#define VOID 0
#define APPLE 1
#define SNAKE 2
#define RIGHT 3
#define UP 4
#define LEFT 5
#define DOWN 6

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, K, L;

	cin >> N >> K;
	vector<vector<int>> v(101, vector<int>(101, 0));
	for (int i = 0; i < K; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a][b] = APPLE;
	}
	queue<pair<int, char>> q;
	deque<pair<int, int>> dq;

	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int a;
		char b;
		cin >> a >> b;
		q.push({a, b});
	}

	v[1][1] = SNAKE;
	dq.push_front({1, 1});
	int x = 1;
	int y = 1;
	int now_time = 0;
	int next_time = q.front().first;
	int now_dir = RIGHT;
	int next_dir = q.front().second;
	q.pop();
	while (1)
	{
		now_time++;
		if (now_dir == RIGHT)
			y++;
		else if (now_dir == LEFT)
			y--;
		else if (now_dir == UP)
			x--;
		else if (now_dir == DOWN)
			x++;
		if (x < 1 || y < 1 || x > N || y > N
			|| v[x][y] == SNAKE)
			break;
		if (v[x][y] == VOID)
		{
			v[dq.back().first][dq.back().second] = VOID;
			dq.pop_back();
		}
		dq.push_front({x, y});
		v[x][y] = SNAKE;
		if (now_time == next_time)
		{
			if (next_dir == 'L')
			{
				now_dir++;
				if (now_dir == 7)
					now_dir = 3;
			}
			else
			{
				now_dir--;
				if (now_dir == 2)
					now_dir = 6;
			}
			if (!q.empty())
			{
				next_time = q.front().first;
				next_dir = q.front().second;
				q.pop();
			}
		}
	}
	cout << now_time << "\n";
}
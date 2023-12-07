#include <iostream>
#include <vector>
#include <algorithm>

int N, M, ans;

using namespace std;
void	dfs(vector<pair<int, int>> &camera, vector<vector<int>> &map, int n);

int get_blind_spot_num(vector<vector<int>> &map)
{
	int val = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == 0)
				val++;
	return val;
}

void draw(vector<vector<int>> &map, int i, int j, int d)
{
	if (d == 0)
	{
		i--;
		while (i >= 0)
		{
			if (map[i][j] == 0)
				map[i][j] = 7;
			else if (map[i][j] == 6)
				break;
			i--;
		}
	}
	else if (d == 1)
	{
		j--;
		while (j >= 0)
		{
			if (map[i][j] == 0)
				map[i][j] = 7;
			else if (map[i][j] == 6)
				break;
			j--;
		}
	}
	else if (d == 2)
	{
		i++;
		while (i < N)
		{
			if (map[i][j] == 0)
				map[i][j] = 7;
			else if (map[i][j] == 6)
				break;
			i++;
		}
	}
	else if (d == 3)
	{
		j++;
		while (j < M)
		{
			if (map[i][j] == 0)
				map[i][j] = 7;
			else if (map[i][j] == 6)
				break;
			j++;
		}
	}
}

void CCTV1(vector<pair<int, int>> &camera, vector<vector<int>> &map, int n)
{
	int i = camera[n].first;
	int j = camera[n].second;
	vector<vector<int>> copy_map;
	
	copy_map = map;
	draw(copy_map, i, j, 0);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 1);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 2);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 3);
	dfs(camera, copy_map, n + 1);
}

void CCTV2(vector<pair<int, int>> &camera, vector<vector<int>> &map, int n)
{
	int i = camera[n].first;
	int j = camera[n].second;
	vector<vector<int>> copy_map;
	
	copy_map = map;
	draw(copy_map, i, j, 0);
	draw(copy_map, i, j, 2);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 1);
	draw(copy_map, i, j, 3);
	dfs(camera, copy_map, n + 1);
}

void CCTV3(vector<pair<int, int>> &camera, vector<vector<int>> &map, int n)
{
	int i = camera[n].first;
	int j = camera[n].second;
	vector<vector<int>> copy_map;
	
	copy_map = map;
	draw(copy_map, i, j, 0);
	draw(copy_map, i, j, 1);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 1);
	draw(copy_map, i, j, 2);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 2);
	draw(copy_map, i, j, 3);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 3);
	draw(copy_map, i, j, 0);
	dfs(camera, copy_map, n + 1);
}

void CCTV4(vector<pair<int, int>> &camera, vector<vector<int>> &map, int n)
{
	int i = camera[n].first;
	int j = camera[n].second;
	vector<vector<int>> copy_map;
	
	copy_map = map;
	draw(copy_map, i, j, 0);
	draw(copy_map, i, j, 1);
	draw(copy_map, i, j, 2);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 1);
	draw(copy_map, i, j, 2);
	draw(copy_map, i, j, 3);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 2);
	draw(copy_map, i, j, 3);
	draw(copy_map, i, j, 0);
	dfs(camera, copy_map, n + 1);

	copy_map = map;
	draw(copy_map, i, j, 3);
	draw(copy_map, i, j, 0);
	draw(copy_map, i, j, 1);
	dfs(camera, copy_map, n + 1);
}

void CCTV5(vector<pair<int, int>> &camera, vector<vector<int>> &map, int n)
{
	int i = camera[n].first;
	int j = camera[n].second;
	vector<vector<int>> copy_map;
	
	copy_map = map;
	draw(copy_map, i, j, 0);
	draw(copy_map, i, j, 1);
	draw(copy_map, i, j, 2);
	draw(copy_map, i, j, 3);
	dfs(camera, copy_map, n + 1);
}

void	dfs(vector<pair<int, int>> &camera, vector<vector<int>> &map, int n)
{
	if (n == camera.size())
		ans = min(ans, get_blind_spot_num(map));
	else
	{
		int i = camera[n].first;
		int j = camera[n].second;
		if (map[i][j] == 1)
			CCTV1(camera, map, n);
		else if (map[i][j] == 2)
			CCTV2(camera, map, n);
		else if (map[i][j] == 3)
			CCTV3(camera, map, n);
		else if (map[i][j] == 4)
			CCTV4(camera, map, n);
		else if (map[i][j] == 5)
			CCTV5(camera, map, n);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vector<pair<int, int>> camera;
	vector<vector<int>> map(8, vector<int>(8));

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] != 0 && map[i][j] != 6)
				camera.push_back({i, j});
		}
	ans = N * M;
	if (camera.size() == 0)
	{
		ans = get_blind_spot_num(map);
		cout << ans << endl;
		exit(0);
	}
	dfs(camera, map, 0);
	cout << ans << endl;
}
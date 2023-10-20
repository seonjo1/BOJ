#include <iostream>
#include <vector>
#include <queue>
using namespace std;

long long get_time(long long time, long long period, long long M)
{
	if (time - period <= 0)
		return period + 1;
	else if ((time - period) % M == 0)
		return time + 1;
	else
		return ((time - period) / M + 1) * M + period + 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long INF = 9223372036854775807;
	int N, M;
	cin >> N >> M;
	vector<pair<long long, long long>> *v = new vector<pair<long long, long long>>[N + 1];
	for (int i = 0; i < M; i++)
	{
		long long a, b;
		cin >> a >> b;
		v[a].push_back({b, i});
		v[b].push_back({a, i});
	}
	bool *check = new bool[N + 1];
	long long	*min_time = new long long[N + 1];
	for (int i = 1; i < N + 1; i++)
	{
		check[i] = false;
		min_time[i] = INF;
	}
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
	pq.push({0, 1});
	while (!pq.empty())
	{
		long long time;
		int location;
		time = pq.top().first;
		location = pq.top().second;
		pq.pop();
		if (!check[location])
		{
			check[location] = true;
			for (pair<long long, long long> next : v[location])
			{
				int next_location = next.first;
				long long next_period = next.second;
				long long next_time = get_time(time, next_period, M);
				if (min_time[next_location] > next_time)
				{
					min_time[next_location] = next_time;
					pq.push({next_time, next_location});
				}
			}
		}
	}
	cout << min_time[N] << "\n";
}
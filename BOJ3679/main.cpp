#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
using namespace std;

struct Point
{
	double x;
	double y;
	int idx;
};

int T, N;
vector<Point> v;

bool compareY(Point& p1, Point& p2)
{
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

int ccw(Point& p1, Point& p2, Point& p3)
{
	ll res = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
	if (res > 0)
		return 1;
	else if (res < 0)
		return -1;
	return (0);
}

bool compareAngle(Point& p1, Point& p2)
{
	int ccwValue = ccw(v[0], p1, p2);

	if (ccwValue != 0)
		return ccwValue > 0;
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

bool isUnordered(Point& p1, Point& p2, Point& p3)
{
	if (!(p1.x <= p2.x && p2.x <= p3.x) && !(p1.x >= p2.x && p2.x >= p3.x))
		return true;
	if (!(p1.y <= p2.y && p2.y <= p3.y) && !(p1.y >= p2.y && p2.y >= p3.y))
		return true;
	return false;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> T;

	while (T-- > 0)
	{
		cin >> N;
		
		v.resize(N);

		for (int i = 0; i < N; i++)
		{
			cin >> v[i].x >> v[i].y;
			v[i].idx = i;
		}
		
		sort(v.begin(), v.end(), compareY);
		sort(v.begin() + 1, v.end(), compareAngle);
		v.push_back(v[0]);

		int i = N - 1;
		while (true)
		{
			Point& p1 = v[i + 1];
			Point& p2 = v[i];
			Point& p3 = v[i - 1];
			if (ccw(p1, p2, p3) != 0)
				break;
			i--;
		}
		for (int j = 0; j <= (N - 1 - i) / 2; j++)
			swap(v[i + j], v[N - 1 - j]);
		for (int i = 0; i < N; i++)
			cout << v[i].idx << " ";
		cout << "\n";
	}
}
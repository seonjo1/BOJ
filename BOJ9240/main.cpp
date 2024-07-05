#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Point
{
	long long x;
	long long y;
};

Point operator-(Point& p1, Point& p2)
{
	Point p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

vector<Point> v;
vector<Point> cv;

int N;

double getDist(Point& p1, Point& p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool compareY(Point& p1, Point& p2)
{
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

int ccw(Point v1, Point v2)
{
	long long res = v1.x * v2.y - v1.y * v2.x;
	if (res > 0) return 1;
	else if (res < 0) return -1;
	return 0;
}

bool compareAngle(Point& p1, Point& p2)
{
	int ccwValue = ccw(p1 - v[0], p2 - v[0]);

	if (ccwValue != 0)
		return ccwValue > 0;
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	v.resize(N);

	for (int i = 0; i < N; i++)
		cin >> v[i].x >> v[i].y;
	
	sort(v.begin(), v.end(), compareY);
	sort(v.begin() + 1, v.end(), compareAngle);

	// for (auto p : v)
	// 	cout << "x : " << p.x << " y : " << p.y << "\n";

	stack<Point> s;

	s.push(v[0]);
	s.push(v[1]);

	int i = 2;
	for (; i < N; i++)
	{
		Point p3 = v[i];
		while (s.size() >= 2)
		{
			Point p2 = s.top();
			s.pop();
			Point p1 = s.top();

			if (ccw(p2 - p1, p3 - p1) > 0)
			{
				s.push(p2);
				break;
			}
		}
		s.push(p3);
	}

	while (!s.empty())
	{
		cv.push_back(s.top());
		s.pop();
	}

	// for (auto p : cv)
	// 	cout << "x : " << p.x << " y : " << p.y << "\n";

	int size = cv.size();
	
	cout << fixed << setprecision(6);

	if (size == 2)
	{
		cout << getDist(cv[0], cv[1]) << "\n";
		return 0;
	}

	i = 0;
	int j = 1;

	double ans = 0;
	
	while (i < size)
	{
		ans = max(ans, getDist(cv[i], cv[j]));
		if (ccw(cv[(i + 1) % size] - cv[i], cv[(j + 1) % size] - cv[j]) < 0)
		{
			j++;
			j = j % size;
		}
		else
			i++;
	}

	cout << ans << "\n";
}
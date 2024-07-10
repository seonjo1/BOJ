#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

struct Point
{
	double x;
	double y;
};

int N, L;
vector<Point> v;
stack<Point> s;

int ccw(Point& p1, Point& p2, Point& p3)
{
	long long res = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
	if (res > 0) return 1;
	else if (res < 0) return -1;
	return (0);
}

double getDist(Point& p1, Point& p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
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


void sortVector()
{
	for (int i = 0; i < N; i++)
	{
		if (v[i].y < v[0].y)
			swap(v[0], v[i]);
		else if (v[i].y == v[0].y && v[i].x < v[0].x)
			swap(v[0], v[i]);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> L;

	v.resize(N);

	for (int i = 0; i < N; i++)
		cin >> v[i].x >> v[i].y;
	
	sortVector();
	sort(v.begin() + 1, v.end(), compareAngle);

	s.push(v[0]);
	s.push(v[1]);
	
	for (int i = 2; i < N; i++)
	{
		Point p3 = v[i];
		while (s.size() > 1)
		{
			Point p2 = s.top();
			s.pop();
			Point p1 = s.top();
			if (ccw(p1, p2, p3) > 0)
			{
				s.push(p2);
				break;
			}
		}
		s.push(p3);
	}

	double ans = 0;

	s.push(v[0]);
	
	Point p1 = s.top();
	s.pop();
	
	while (!s.empty())
	{
		Point p2 = s.top();
		s.pop();
		ans += getDist(p1, p2);
		p1 = p2;
	}
	cout << round(ans + 2 * M_PI * L) << "\n";

	return (0);
}
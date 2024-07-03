#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Point
{
	double x;
	double y;
};

int N;
vector<Point> v;

double crossProduct(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - y1 * x2);
}

double ccw(Point p1, Point p2, Point p3)
{
	return (crossProduct(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x, p3.y - p1.y));
}

bool CompareAngle(Point& p1, Point& p2)
{
	double ccwValue = ccw(v[0], p1, p2);
	if (ccwValue != 0)
		return ccwValue > 0;
	else
	{
		if (p1.y == p2.y)
			return p1.x < p2.x;
		return p1.y < p2.y;
	}
}

bool Compare(Point& p1, Point& p2)
{
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
	
	sort(v.begin(), v.end(), Compare);
	v.push_back(v[0]);

	sort(v.begin() + 1, v.end() - 1, CompareAngle);

	stack<Point> s;

	s.push(v[0]);
	s.push(v[1]);

	for (int i = 2; i < N + 1; i++)
	{
		Point p3 = v[i];

		while (s.size() >= 2)
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

	cout << s.size() - 1 << "\n";
}

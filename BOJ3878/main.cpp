#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
	double x;
	double y;
};

vector<Point> v;

int ccw(Point& p1, Point& p2, Point& p3)
{
	long long res = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	if (res > 0) return 1;
	else if (res < 0) return -1;
	return 0;
}

bool compareAngle(Point& p1, Point& p2)
{
	int ccwRes = ccw(v[0], p1, p2);
	if (ccwRes != 0)
		return ccwRes > 0;
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

vector<Point> getConvexHullVector(int N)
{

	v.resize(N);

	for (int i = 0; i < N; i++)
		cin >> v[i].x >> v[i].y;
	
	if (N == 1)
		return (vector<Point>(1, v[0]));
	
	for (int i = 0; i < N; i++)
	{
		if (v[0].y > v[i].y || (v[0].y == v[i].y && v[0].x > v[i].x))
			swap(v[0], v[i]);
	}

	sort(v.begin() + 1, v.end(), compareAngle);

	vector<Point> res;


	res.push_back(v[0]);
	res.push_back(v[1]);

	for (int i = 2; i < N; i++)
	{
		Point p3 = v[i];
		while (res.size() > 1)
		{
			Point p2 = res.back();
			res.pop_back();
			Point p1 = res.back();

			if (ccw(p1, p2, p3) > 0)
			{
				res.push_back(p2);
				break ;
			}
		}
		res.push_back(p3);
	}

	return res;
}

bool isLineInside(Point& p1, Point& p2, Point& p3)
{

	if (ccw(p1, p2, p3) == 0 &&
		(min(p1.x, p2.x) <= p3.x && p3.x <= max(p1.x, p2.x)) &&
		(min(p1.y, p2.y) <= p3.y && p3.y <= max(p1.y, p2.y)))
		return true;
	return false;
}
bool isLineCross(Point& p1, Point& p2, Point& p3, Point& p4)
{
	if (isLineInside(p1, p2, p3))
		return true;
	if (isLineInside(p1, p2, p4))
		return true;
	if (isLineInside(p3, p4, p1))
		return true;
	if (isLineInside(p3, p4, p2))
		return true;

	int ccwRes1 = ccw(p1, p2, p3);
	int ccwRes2 = ccw(p1, p2, p4);
	int ccwRes3 = ccw(p3, p4, p1);
	int ccwRes4 = ccw(p3, p4, p2);
	
	if (ccwRes1 * ccwRes2 == -1 && ccwRes3 * ccwRes4 == -1)
		return true;

	return false;
}

bool canDivide(vector<Point>& v1, vector<Point>& v2)
{
	int n = v1.size();
	int m = v2.size();

	if (n == 1)
		return true;

	if (n == 2)
	{
		if (m == 1)
		{
			if (isLineInside(v1[0], v1[1], v2[0]))
				return false;
			else 
				return true;
		}
		else
		{
			for (int i = 0; i < m; i++)
			{
				if (isLineCross(v1[0], v1[1], v2[i], v2[(i + 1) % m]))
					return false;
			}
			return true;
		}
	}

	for (int i = 0; i < m; i++)
	{
		bool isInsidePoint = true;
		for (int j = 0; j < n; j++)
		{
			if (ccw(v1[j], v1[(j + 1) % n], v2[i]) < 0)
			{
				isInsidePoint = false;
				break;
			}
			
		}
		if (isInsidePoint) return false;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int T, n, m;
	cin >> T;

	while (T-- > 0)
	{
		cin >> n >> m;
		vector<Point> cv1 = getConvexHullVector(n);
		vector<Point> cv2 = getConvexHullVector(m);
		if (canDivide(cv1, cv2) && canDivide(cv2, cv1))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

struct Point
{
	double x;
	double y;

	Point operator-(Point& p)
	{
		Point ret;
		ret.x = this->x - p.x;
		ret.y = this->y - p.y;
		return ret;
	}
};

vector<Point> v;

int T, N;

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

double getDist(Point& p1, Point& p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
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
			cin >> v[i].x >> v[i].y;
		sort(v.begin(), v.end(), compareY);
		sort(v.begin() + 1, v.end(), compareAngle);

		vector<Point> cv;

		cv.push_back(v[0]);
		cv.push_back(v[1]);

		for (int i = 2; i < N; i++)
		{
			Point p3 = v[i];
			while (cv.size() > 1)
			{
				Point p2 = cv.back();
				cv.pop_back();
				Point p1 = cv.back();

				if (ccw(p2 - p1, p3 - p1) > 0)
				{
					cv.push_back(p2);
					break;
				}
			}
			cv.push_back(p3);
		}

		Point ans1;
		Point ans2;
		double ansDist = 0;

		int i = 0;
		int j = 1;
		int size = cv.size();

		if (size == 2)
		{
			cout << (int)cv[0].x << " " << (int)cv[0].y << " " << (int)cv[1].x << " " << (int)cv[1].y << "\n";
			continue ;
		}

		while (i < size)
		{
			if (ccw(cv[(i + 1) % size] - cv[i], cv[(j + 1) % size] - cv[j % size]) < 0)
			{
				double dist = getDist(cv[i], cv[j % size]);
				if (dist > ansDist)
				{
					ans1 = cv[i];
					ans2 = cv[j % size];
					ansDist = dist;
				}
				dist = getDist(cv[(i + 1) % size], cv[j % size]);
				if (dist > ansDist)
				{
					ans1 = cv[(i + 1) % size];
					ans2 = cv[j % size];
					ansDist = dist;
				}
				i++;
			}
			else
			{
				j++;
			}
		}

		cout << (int)ans1.x << " " << (int)ans1.y << " " << (int)ans2.x << " " << (int)ans2.y << "\n";
	}
	return 0;
}
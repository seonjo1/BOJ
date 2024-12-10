#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>


struct Point
{
    double x;
    double y;
};

struct Circle
{
    Point center;
    double radius;
};

int N;
std::vector<Point> points;

double distance(Point p1, Point p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

Circle calculateCircleFromPoints(std::vector<Point>& reservedPoints)
{
    int size = reservedPoints.size();
    Circle circle = {{0, 0}, 0};

    if (size == 1)
    {
        circle.center = reservedPoints[0];
    }
    else if (size == 2)
    {
        circle.center = {
            (reservedPoints[0].x + reservedPoints[1].x) / 2,
            (reservedPoints[0].y + reservedPoints[1].y) / 2
        };
        circle.radius = distance(reservedPoints[0], reservedPoints[1]) / 2.0f;
    }
    else if (size == 3)
    {
        Point& A = reservedPoints[0];
        Point& B = reservedPoints[1];
        Point& C = reservedPoints[2];

        double d = 2 * (
            A.x * (B.y - C.y) + 
            B.x * (C.y - A.y) + 
            C.x* (A.y - B.y)
        );

        double ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
                    (B.x * B.x + B.y * B.y) * (C.y - A.y) +
                    (C.x * C.x + C.y * C.y) * (A.y - B.y)) / d;

        double uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
                    (B.x * B.x + B.y * B.y) * (A.x - C.x) +
                    (C.x * C.x + C.y * C.y) * (B.x - A.x)) / d;

        circle.center = {ux, uy};
        circle.radius = distance(circle.center, A);
    }

    return circle;
}

bool isCircleInvolvePoint(Circle& circle, Point& point)
{
    return distance(circle.center, point) <= circle.radius;
}

Circle welzl(std::vector<Point> reservedPoints, int idx)
{
    if (idx == N || reservedPoints.size() == 3)
    {
        return calculateCircleFromPoints(reservedPoints);
    }

    Point point = points[idx];
    Circle circle = welzl(reservedPoints, idx + 1);

    if (isCircleInvolvePoint(circle, point))
    {
        return circle;
    }

    reservedPoints.push_back(point);
    return welzl(reservedPoints, idx + 1);
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N;

    for (int i = 0; i < N; i++)
    {
        Point input;
        std::cin >> input.x;
        std::cin >> input.y;
        points.push_back(input);
    }

    std::vector<Point> reservedPoints;
    Circle circle = welzl(reservedPoints, 0);

    std::cout << std::fixed << std::setprecision(3) << circle.center.x << " " << circle.center.y << "\n" << circle.radius << "\n";

    return 0;
}
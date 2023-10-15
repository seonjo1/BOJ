#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, num;
    cin >> n;
	priority_queue<int, vector<int>, greater<int>> min;
	priority_queue<int> max;
	for (int i = 0; i < n; i++)
	{
		cin >> num;
		if (max.size() > 0 && min.size() > 0)
		{
			if (min.top() < num)
				min.push(num);
			else
				max.push(num);
		}
		else
			max.push(num);
		while (max.size() < min.size())
		{
			max.push(min.top());
			min.pop();
		}
		while (max.size() > min.size() + 1)
		{
			min.push(max.top());
			max.pop();
		}
		cout << max.top() << "\n";
	}
}
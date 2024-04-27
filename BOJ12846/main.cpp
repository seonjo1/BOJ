#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	
	int ans = 0;
	vector<int> v(N + 2, 0);
	stack<int> s;
	for (int i = 1; i < N + 1; i++)
		cin >> v[i];

	s.push(0);
	for (int i = 1; i < N + 2; i++)
	{
		while (!s.empty() && v[s.top()] > v[i])
		{
			int money = v[s.top()];
			s.pop();
			int day = i - s.top() - 1;
			ans = max(ans, money * day);
		}
		s.push(i);
	}
	cout << ans << "\n";
}
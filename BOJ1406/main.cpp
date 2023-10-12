#include <iostream>
#include <stack>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	stack<char> left;
	stack<char> right;
	string s;
	int n;
    char c;
    cin >> s;
	for (int i = 0; i < s.size(); i++)
		left.push(s[i]);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		char cmd;
		cin >> cmd;
		if (cmd == 'L' && !left.empty())
        {
			c = left.top();
            right.push(c);
            left.pop();
        }
		else if (cmd == 'D' && !right.empty())
        {
            c = right.top();
			left.push(c);
            right.pop();
        }
		else if (cmd == 'B' && !left.empty())
			left.pop();
		else if (cmd == 'P')
		{
			cin >> c;
			left.push(c);
		}
	}
	while (!left.empty())
    {
        c = left.top();
		right.push(c);
        left.pop();
    }
	while (!right.empty())
    {
		cout << right.top();
        right.pop();
    }
}
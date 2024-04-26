#include <iostream>
#include <vector>
#include <string>

using namespace std;

int GCD(int a, int b)
{
	if (a % b == 0)
		return b;
	return GCD(b, a % b);
}

vector<int> Fail(string& pattern)
{
	int size = pattern.size();
	vector<int> fail(size, 0);
	
	int j = 0;
	for (int i = 1; i < size; i++)
	{
		while (j > 0 && pattern[j] != pattern[i])
			j = fail[j - 1];
		if (pattern[i] == pattern[j])
			fail[i] = ++j;
	}
	return fail;
}

int getAnswer(string& str, string& pattern)
{
	vector<int> fail = Fail(pattern);
	int sSize = str.size();
	int pSize = pattern.size();
	int ret = 0;

	for (int i = 0, j = 0; i < sSize; i++)
	{
		while (j > 0 && str[i] != pattern[j])
			j = fail[j - 1];
		if (str[i] == pattern[j])
		{
			if (j == pSize - 1)
			{
				ret++;
				j = fail[j];
			}
			else j++;
		}
	}
	return (ret);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	string str, pattern;
	
	char c;
	for (int i = 0; i < N; i++)
	{
		cin >> c;
		str += c;
	}
	for (int i = 0; i < N; i++)
	{
		cin >> c;
		pattern += c;
	}

	str += str.substr(0, N - 1);

	int up = getAnswer(str, pattern);
	int down = N;
	int gcd = GCD(up, down);
	cout << up / gcd << "/" << down / gcd << endl;
}
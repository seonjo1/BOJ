#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	while (true)
	{
		string s;
		cin >> s;
		if (s == ".") break;
		int size = s.size();

		vector<int> v(size);

		for (int i = 1, j = 0; i < size; i++)
		{
			while (j > 0 && s[i] != s[j])
				j = v[j - 1];
			if (s[i] == s[j])
				v[i] = ++j;
		}
		int num = size - v[size - 1];
		if (num != 1 && (v[size - 1] % num))
			cout << "1\n";
		else
			cout << size / num << endl;
	}
}
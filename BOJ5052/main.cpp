#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

bool isDup;

struct Tri
{
	bool finish;
	Tri* next[10];

	Tri() : finish(false)
	{
		memset(next, 0, sizeof(next));
	}

	~Tri()
	{
		for (int i = 0; i < 10; i++)
			delete next[i];
	}

	void insert(const char *key)
	{
		if (*key == '\0')
			finish = true;
		else
		{
			int i = *key - '0';
			if (next[i] == NULL)
				next[i] = new Tri();
			next[i]->insert(key + 1);
		}
	}

	void dupCheck()
	{
		if (isDup) return;
		if (finish)
		{
			for (int i = 0; i < 10; i++)
			{
				if (next[i] != NULL)
				{
					isDup = true;
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				if (next[i] != NULL)
					next[i]->dupCheck();
			}
		}
	}
};

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t, n;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		isDup = false;
		Tri tri;
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			string str;
			cin >> str;
			tri.insert(str.c_str());
		}
		tri.dupCheck();
		if (isDup) cout << "NO\n";
		else cout << "YES\n";
	}
}
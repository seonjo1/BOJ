#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

int sum;

struct Tri
{
	bool finish;
	int num;
	Tri* next[26];

	Tri() : finish(false), num(0)
	{
		memset(next, 0, sizeof(next));
	}

	~Tri()
	{
		for (int i = 0; i < 26; i++)
			delete next[i];
	}

	void insert(const char *key)
	{
		if (*key == '\0')
			finish = true;
		else
		{
			int i = *key - 'a';
			if (!next[i])
			{
				num++;
				next[i] = new Tri();
			}
			next[i]->insert(key + 1);
		}
	}

	void check(int n)
	{
		if (finish)
			sum += n;

		if (num == 1)
		{
			for (int i = 0; i < 26; i++)
			{
				if (next[i])
				{
					if (finish)
						next[i]->check(n + 1);
					else
						next[i]->check(n);
				}
			}
		}
		else
		{
			for (int i = 0; i < 26; i++)
			{
				if (next[i])
					next[i]->check(n + 1);
			}
		}
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string str;
	while (1)
	{
		int N;
		cin >> N;
		if (cin.eof()) break;

		Tri tri;
		for (int i = 0; i < N; i++)
		{
			string str;
			cin >> str;
			tri.insert(str.c_str());
		}
		sum = 0;
		for (int i = 0; i < 26; i++)
		{
			if (tri.next[i])
				tri.next[i]->check(1);
		}
		cout << fixed << setprecision(2);
		cout << static_cast<double>(sum) / N << endl;
	}
}
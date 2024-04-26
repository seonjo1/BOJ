#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

long long factorial[27];
long long sum = 1;

struct Tri
{
	bool finish;
	int child;
	char *str;
	Tri* next[26];

	Tri() : finish(false), child(0), str(NULL)
	{
		memset(next, 0, sizeof(next));
		if (str) delete str;
	}

	~Tri()
	{
		for (int i = 0; i < 26; i++)
			delete next[i];
	}

	void insert(const char *key, bool go)
	{
		if (*key == '\0')
			finish = true;
		else if (go)
		{
			if (str != NULL)
			{
				char *tmp = str;
				str = NULL;
				finish = false;
				int i = *tmp - 'A';
				this->insert(tmp, true);
				delete tmp;
			}
			int i = *key - 'A';
			if (!next[i])
			{
				child++;
				next[i] = new Tri();
				next[i]->insert(key + 1, false);
			}
			else next[i]->insert(key + 1, true);
		}
		else
		{
			finish = true;
			str = strdup(key);
		}
	}

	void getAnswer()
	{
		if (child)
		{
			if (finish) sum = ((factorial[child + 1] * sum) % 1000000007);
			else sum = ((factorial[child] * sum) % 1000000007);
		}
		for (int i = 0; i < 26; i++)
		{
			if (next[i] != NULL)
				next[i]->getAnswer();
		}
	}

};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	factorial[0] = 1;
	for (int i = 1; i < 27; i++)
		factorial[i] = (factorial[i - 1] * i) % 1000000007;
	
	int N;
	cin >> N;
	vector<string> v;

	string str;
	for (int i = 0; i < N; i++)
	{
		cin >> str;
		v.push_back(str);
	}
	sort(v.begin(), v.end());

	Tri tri;
	for (int i = 0; i < N; i++)
		tri.insert(v[i].c_str(), true);
	tri.getAnswer();
	cout << sum << endl;
}
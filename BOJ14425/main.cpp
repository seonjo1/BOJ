#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

struct Tri
{
	bool finish;
	Tri* next[26];

	Tri() : finish(false)
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
			if (next[i] == NULL)
				next[i] = new Tri();
			next[i]->insert(key + 1);
		}
	}

	bool find(const char *key)
	{
		if (*key == '\0')
			return finish;
		int i = *key - 'a';
		if (next[i] == NULL)
			return false;
		return next[i]->find(key + 1);
	}
};

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string str;
	getline(cin, str);
	
	int N, M;
	stringstream ss(str);
	ss >> N >> M;

	Tri tri;
	for (int i = 0; i < N; i++)
	{
		getline(cin, str);
		tri.insert(str.c_str());
	}

	int num = 0;
	for (int i = 0; i < M; i++)
	{
		getline(cin, str);
		if (tri.find(str.c_str())) num++;
	}
	cout << num << endl;
}
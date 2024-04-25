#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int sum;

struct Tri
{
	bool finish;
	int child;
	Tri* next[26];

	Tri() : finish(false), child(0)
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
				child++;
				next[i] = new Tri();
			}
			next[i]->insert(key + 1);
		}
	}


};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int L;
	cin >> L;
	string ad;
	cin >> ad;

	vector<int> v(L);

	for (int i = 1, j = 0; i < L; i++)
	{
		while (j > 0 && ad[i] != ad[j])
			j = v[j - 1];
		if (ad[i] == ad[j])
			v[i] = ++j;
	}
	cout << L - v.back() << endl;
}
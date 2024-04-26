#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> Fail(string& pattern)
{
	int size = pattern.size();
	vector<int> fv(size);

	for (int i = 1, j = 0; i < size; i++)
	{
		while (j > 0 && pattern[i] != pattern[j])
			j = fv[j - 1];
		if (pattern[i] == pattern[j])
			fv[i] = ++j;
	}
	return fv;
}

int KMP(string& s, string& p)
{
	int num = 0;
	int size = s.size();
	int pSize = p.size();
	vector<int> fv = Fail(p);

	for (int i = 0, j = 0; i < size; i++)
	{
		while (j > 0 && s[i] != p[j])
			j = fv[j - 1];
		if (s[i] == p[j])
		{
			if (j == pSize - 1)
			{
				num++;
				j = fv[j];
			}
			else j++;
		}
	}
	return num;
}

vector<string> shiftOrigin(string& Alpha, string& ori)
{
	vector<string> v;
	int aSize = Alpha.size();
	int oSize = ori.size();
	int idx[oSize];
	for (int i = 0; i < oSize; i++)
		idx[i] = find(Alpha.begin(), Alpha.end(), ori[i]) - Alpha.begin();

	for (int i = 0; i < aSize; i++)
	{
		string shiftOri;
		for (int j = 0; j < oSize; j++)
			shiftOri += Alpha[(idx[j] + i) % aSize];
		v.push_back(shiftOri);
	}
	return v;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	while (T-- > 0)
	{
		string Alpha, ori, enc;
		cin >> Alpha >> ori >> enc;
		vector<string> shiftOri = shiftOrigin(Alpha, ori);
		vector<int> ans;
		int vSize = shiftOri.size();
		for(int i = 0; i < vSize; i++)
		{
			if (KMP(enc, shiftOri[i]) == 1)
				ans.push_back(i);
		}
		if (ans.size() == 0)
			cout << "no solution\n";
		else
		{
			if (ans.size() == 1) cout << "unique: ";
			else cout << "ambiguous: ";
			for (int i = 0; i < ans.size(); i++)
				cout << ans[i] << " ";
			cout << endl;
		}
	}
}
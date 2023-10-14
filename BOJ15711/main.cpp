#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    vector<bool> check(2000001, true);

    for (long long i = 2; i < 2000001; i++)
    {
        if(check[(int)i])
        {
            for (long long j = i * i; j < 2000001; j = j + i)
                check[(int)j] = false;
        }
    }
	vector<int> v;
	for (int i = 3; i < 2000001; i += 2)
		if (check[i])
			v.push_back(i);
    for (int i = 0; i < T; i++)
    {
        long long a, b, sum;
        cin >> a >> b;
        sum = a + b;
		if (sum == 2 || sum == 3)
			cout << "NO\n";
        else if (sum % 2 == 0)
            cout << "YES\n";
        else
        {
			sum = sum - 2;
            bool ok = true;
            for (int j : v)
			{
				if (j >= sum)
					break;
				if (sum % j == 0)
				{
					ok = false;
					break;
				}
			}
			if (ok)
				cout << "YES\n";
			else
				cout << "NO\n";
        }
    }
}
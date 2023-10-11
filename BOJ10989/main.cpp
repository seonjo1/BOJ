#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

    int n, num;
    cin >> n;
    vector<int> v(10001, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        v[num]++;
    }
    for (int i = 1; i < 10001; i++)
    {
        if (v[i] > 0)
            for (int j = 0; j < v[i]; j++)
                cout << i << "\n";
    }
    return 0;
}
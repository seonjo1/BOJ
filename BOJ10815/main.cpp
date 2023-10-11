#include <iostream>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    map<int, int> map;
    int n, m, tmp;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        map.insert({tmp, 1});
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> tmp;
        if (map.find(tmp) != map.end())
            cout << "1 ";
        else
            cout << "0 ";
    }
    cout << "\n";
    return 0;
}
#include <iostream>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    map<string, int> map;
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        if (map.count(s) == 0)
            map.insert({s, 1});
        else
            map[s]++;
    }
    int max = 0;
    for (auto iter = map.begin(); iter != map.end(); iter++)
    {
        if (max < iter->second)
        {
            s = iter->first;
            max = iter->second;
        }
    }
    cout << s << "\n";
    return 0;
}
#include <iostream>
#include <set>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    set<int> set;
    int n, num;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        set.insert(num);
    }
    for (auto iter = set.begin(); iter != set.end(); iter++)
        cout << *iter << " ";
}
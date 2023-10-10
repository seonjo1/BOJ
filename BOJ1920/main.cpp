#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> v;
int binary_search(int num)
{
    int l = 0;
    int r = v.size() - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (v[mid] < num)
            l = mid + 1;
        else if (v[mid] > num)
            r = mid - 1;
        else
            return 1;
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int n, m, num;
    cin >> n;
    v = vector<int>(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> num;
        cout << binary_search(num) << "\n";
    }
    return 0;
}
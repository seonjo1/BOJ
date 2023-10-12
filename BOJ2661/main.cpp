#include <iostream>
#include <vector>

using namespace std;
int n;
vector<int> v;

bool check(int now, int num){
    v[now] = num;
    bool arr[4] = {true, true, true, true};
    for (int i = now; i >= 0; i--)
    {
        arr[v[i]] = !arr[v[i]];
        if (arr[1] && arr[2] && arr[3])
        {
            bool ok = true;
            int j = i;
            int end = (now + i) / 2 + 1; 
            int gap = end - j;
            for (int p = 0; j + p < end; p++)
            {
                if (v[j + p] != v[j + gap + p])
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
                return false;
        }
    }
    return true;
}

bool make_min_case(int now)
{
    if (now == n)
        return 1;
    else
    {
        if (check(now, 1) && make_min_case(now + 1))
            return true;
        if (check(now, 2) && make_min_case(now + 1))
            return true;
        if (check(now, 3) && make_min_case(now + 1))
            return true;
        return false;
    }
}

int main()
{
    cin >> n;
    v = vector<int>(n);
    v[0] = 1;
    make_min_case(0);
    for (int n : v)
        cout << n;
}

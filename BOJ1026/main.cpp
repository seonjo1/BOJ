#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, sum;
    cin >> n;

    vector<int> A(n);
    vector<int> B(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];
    for (int i = 0; i < n; i++)
        cin >> B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i] * B[n - i - 1];
    cout << sum << "\n";
}
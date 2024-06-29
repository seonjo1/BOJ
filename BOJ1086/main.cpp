#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

int N, K;

long long dp[(1 << 15)][100];
vector<int> modVec;
vector<int> lengthVec;
vector<string> strNumVec;
int tenMod[51];

void makeTenMod()
{
	tenMod[0] = 1;
	for (int i = 1; i < 51; i++)
		tenMod[i] = (tenMod[i - 1] * 10) % K ;
}

void makeMod()
{
	for (string number : strNumVec)
	{
		int num = 0;
		int i = 0;
		int length = number.size();
		while (true)
		{
			if (i + 1 != length)
				num = num * 100;
			else
				num = num * 10;
			num = (num + stoi(number.substr(i, 2))) % K;
			i = i + 2;
			if (i >= length)
				break;
		}
		modVec.push_back(num);
		lengthVec.push_back(length);
	}
}


long long doMod(int status, int val)
{
	if (status == (1 << N) - 1)
	{
		if (val == 0)
			return 1;
		else
			return 0;
	}

	if (dp[status][val] == -1)
		return 0;
	else if (dp[status][val] != 0)
		return dp[status][val];

	for (int i = 0; i < N; i++)
	{
		if ((1 << i) & status)
			continue;
		int nextVal = ((val * tenMod[lengthVec[i]]) % K + modVec[i]) % K;
		dp[status][val] += doMod((status | (1 << i)), nextVal);
	}
	if (dp[status][val] == 0)
	{
		dp[status][val] = -1;
		return 0;
	}
	else return dp[status][val];
}

long long factorial(int n)
{
	if (n == 1)
		return 1;
	return n * factorial(n - 1);
}

long long GCD(long long a, long long b)
{
	if (b == 0)
		return a;
	return GCD(b, a % b);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < N; i++)
	{
		string number;
		cin >> number;
		strNumVec.push_back(number);
	}

	cin >> K;

	makeMod();
	makeTenMod();

	long long result = doMod(0, 0);
	if (result == 0)
		cout << result << "/" << 1 << "\n";
	else
	{
		long long factNum = factorial(N);
		long long gcd = GCD(result, factNum);
		cout << result / gcd << "/" << factNum / gcd << "\n";
	}
	
}
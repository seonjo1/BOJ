#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <set>
#include <queue>

using namespace std;

vector<set<int>> scc;
vector<vector<int>> v;
vector<int> finish;
vector<int> idx;
vector<int> ATM;
vector<bool> RST;
vector<int> tsV;


stack<int> s;

int N,M,S,P;

int Num = 1;
int sccNum = 1;

int sccDFS(int now)
{
	int idxNum = idx[now] = Num++;
	s.push(now);
	for (int next : v[now])
	{
		if (!idx[next]) idx[now] = min(idx[now], sccDFS(next));
		else if (!finish[next]) idx[now] = min(idx[now], idx[next]);
	}

	if (idx[now] == idxNum)
	{
		while (s.top() != now)
		{
			finish[s.top()] = sccNum;
			s.pop();
		}
		finish[s.top()] = sccNum;
		s.pop();
		sccNum++;
	}
	return idx[now];
}

struct tsNode
{
	int idx;
	int cn;

	tsNode(int idx, int cn)
		: idx(idx), cn(cn) {};
};

struct compare
{
	bool operator()(tsNode n1, tsNode n2)
	{
		return (n1.cn > n2.cn);
	}
};

int TS(int start)
{
	int ans = 0;
	vector<bool> isValid(sccNum, false);
	vector<bool> checkV(sccNum, false);
	vector<int> sum(sccNum, 0);
	priority_queue<tsNode, vector<tsNode>, compare> pq;

	isValid[start] = true;
	sum[start] = ATM[start];

	for (int i = 1; i < sccNum; i++)
	{
		if (tsV[i] == 0)
			pq.push(tsNode(i, 0));
	}

	while (!pq.empty())
	{
		tsNode now = pq.top();
		pq.pop();
		
		if (checkV[now.idx]) continue;
		checkV[now.idx] = true;
		for (int next : scc[now.idx])
		{
			pq.push(tsNode(next, --tsV[next]));
			if (isValid[now.idx])
			{
				isValid[next] = true;
				sum[next] = max(sum[next], ATM[next] + sum[now.idx]);
			} 
		}
	}

	for (int i = 1; i < sccNum; i++)
		if (RST[i]) ans = max(ans, sum[i]);

	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	v.assign(N + 1, vector<int>());
	finish.assign(N + 1, 0);
	idx.assign(N + 1, 0);
	ATM.assign(N + 1, 0);

	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
	}

	for (int i = 1; i <= N; i++)
	{
		if (!finish[i])
			sccDFS(i);
	}

	scc.assign(sccNum, set<int>());
	ATM.assign(sccNum, 0);
	RST.assign(sccNum, false);
	tsV.assign(sccNum, 0);

	for (int i = 1; i <= N; i++)
	{
		int now = finish[i];
		for (int j : v[i])
		{
			int next = finish[j];
			if (next != now)
				scc[now].insert(next);
		}
	}

	for (int i = 1; i < sccNum; i++)
	{
		for (int j : scc[i])
			tsV[j]++;
	}

	int input;

	for (int i = 1; i <= N; i++)
	{
		cin >> input;
		ATM[finish[i]] += input;
	}

	cin >> S >> P;

	for (int i = 0; i < P; i++)
	{
		cin >> input;
		RST[finish[input]] = true; 
	}

	cout << TS(finish[S]) << "\n";

	return (0);
}
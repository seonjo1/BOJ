#include <iostream>
#include <vector>

std::vector<long long> tree;
std::vector<long long> arr;
int N, K;
int i, j, V;
char C;

void init(int node, int start, int end) {
	if (start == end) {
		tree[node] = arr[start];
	} else {
		int mid = (start + end) / 2;
		init(node * 2, start, mid);
		init(node * 2 + 1, mid + 1, end);
		tree[node] = tree[node * 2] * tree[node * 2 + 1];
	}
}

void update(int node, int start, int end, int idx, long long val) {
	if (start <= idx && idx <= end) {
		if (start == end) {
			tree[node] = val;
		} else {
			int mid = (start + end) / 2;
			update (node * 2, start, mid, idx, val);
			update (node * 2 + 1, mid + 1, end, idx, val);
			tree[node] = tree[node * 2] * tree[node * 2 + 1];
		}
	}
}

long long query(int node, int start, int end, int i, int j) {
	if (j < start || end < i) {
		return 1;
	} else if (i <= start && end <= j) {
		return tree[node];
	} else {
		int mid = (start + end) / 2;
		return query(node * 2, start, mid, i, j) * query(node * 2 + 1, mid + 1, end, i, j);
	}
}

int getSign(int val) {
	if (val > 0) {
		return 1;
	} else if (val == 0) {
		return 0;
	} else {
		return -1;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	while (1) {
		std::cin >> N >> K;
		if (std::cin.eof()) break;
		tree.assign(N * 4, 1);
		arr.assign(N + 1, 1);

		int tmp;
		for (int idx = 0; idx < N; idx++) {
			std::cin >> tmp;
			arr[idx] = getSign(tmp);
		}

		init(1, 0, N - 1);

		for (int k = 0; k < K; k++) {
			std::cin >> C;
			switch (C) {
				case 'C':
					std::cin >> i >> V;
					update(1, 0, N - 1, i - 1, getSign(V));
					break ;
				case 'P':
					std::cin >> i >> j;
					long long result = query(1, 0, N - 1, i - 1, j - 1);
					if (result == 0) std::cout << "0";
					else if (result > 0) std::cout << "+";
					else std::cout << "-";
					break;
			}
		}
		std::cout << "\n";
	}
}
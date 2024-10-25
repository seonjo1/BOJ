#include <vector>
#include <iostream>

// node index 왼쪽 node * 2, 오른쪽 node * 2 + 1
// node index는 1부터 시작, vector index는 0부터 시작
class SegmentTree {
public:
    SegmentTree(int size): n(size) {
        tree.assign(4 * n, 0);
    }

    SegmentTree(const std::vector<long long>& arr): n(arr.size()) {
        tree.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    void update(int index, long long value) {
        update_util(1, 0, n - 1, index, value);
    }

    long long query(int dest) {
        return query_util(1, 0, n - 1, dest);
    }

private:
    int n;
    std::vector<long long> tree;

    void build(const std::vector<long long>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, node * 2, start, mid);
            build(arr, node * 2 + 1, mid + 1, end);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    void update_util(int node, int start, int end, int index, long long value) {
        if (start == end) {
            tree[node] += value;
            return;
        }

        int mid = (start + end) / 2;
        if (index <= mid) {
            update_util(node * 2, start, mid, index, value);
        } else {
            update_util(node * 2 + 1, mid + 1, end, index, value);
        }

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    long long query_util(int node, int start, int end, int dest) {
		if (start == end) {
			return start;
		}
		int mid = (start + end) / 2;
		if (tree[node] - tree[node * 2 + 1] >= dest) {
			return query_util(node * 2, start, mid, dest);
		} else {
			return query_util(node * 2 + 1, mid + 1, end, dest - tree[node * 2]);
		}
    }
};

int N, K;

int main(){
	std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

	std::cin >> N >> K;
	SegmentTree st(65537);
	long long sum = 0;
	int dest = (K + 1) / 2;
	int front = 0;
	std::vector<int> v(N);
	std::cin >> v[0];
	st.update(v[front], 1);
	for (int i = 1; i < K; i++) {
		std::cin >> v[i];
		st.update(v[i], 1);
	}
	sum += st.query(dest);

	for (int i = K; i < N; i++) {
		std::cin >> v[i];
		st.update(v[front], -1);
		st.update(v[i], 1);
		long long result = st.query(dest);
		sum+= result;
		front++;
	}
	std::cout << sum << "\n";
}
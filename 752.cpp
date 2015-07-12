#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

const int INF = 1000000001;

int F(int n){
	return n - (n & (n - 1));
}

//f(k) = k & (k + 1)
//0 <= f(k) <= k for all k >= 0
//max

class Tree{
	int n;
	int k;
	int * left;
	int * right;
	int * A;

public:
	Tree(int * a, int N){
		A = (int*) malloc(sizeof(int) * (N + 1));
		for (int i = 1; i <= N; ++i)
			A[i] = a[i];
		A[0] = -INF;
		k = 0;
		n = 1;
		while (n <= N){
			++k;
			n *= 2;
		}
		left = (int*) malloc(sizeof(int) * (n + 1));
		right = (int*) malloc(sizeof(int) * (n + 1));
		for (int i = 0; i <= n; ++i){
			left[i] = 0;
			right[i] = 0;
		}
		for (int i = 1; i <= N; ++i)
			update(i, A[i]);
	}

	void update(int N, int X){
		A[N] = X;
		int i = N;
		while (i <= n){
			if (A[left[i]] < X)
				left[i] = N;
			i += F(i);
		}
		int j = N;
		while (j > 0){
			if (A[right[j]] < X)
				right[j] = N;
			j -= F(j);
		}
	}

	double max(int L, int R){
		if (L == R)
			return L;
		int res = 0;
		int i = L;
		while (i + F(i) <= R){
			if (A[res] < A[right[i]])
				res = right[i];
			i += F(i);
		}
		if (A[res] < A[i])
			res = i;
		int j = R;
		while (j - F(j) >= L){
			if (A[res] < A[left[j]])
				res = left[j];
			j -= F(j);
		}
		return res;
	}
};

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int N, K, l, r, ans;
	cin >> N;
	int A[N + 1];
	A[0] = -INF;
	for (int i = 1; i <= N; ++i)
		cin >> A[i];
	Tree T = Tree(A, N);
	cin >> K;
	for (int i = 0; i < K; ++i){
		cin >> l >> r;
		ans = T.max(l, r);
		cout << A[ans] << " " << ans << endl;
	}
	return 0;
}
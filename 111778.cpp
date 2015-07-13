#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

//f(k) = k & (k + 1)
//0 <= f(k) <= k for all k >= 0
//2D

class Tree{
	int n;
	int m;
	int ** B;

public:
	Tree(int M, int N){
		n = N;
		m = M;
		B = (int**) malloc(sizeof(int*) * n * m);
		for (int i = 0; i < m; ++i){
			B[i] = (int *) malloc(sizeof(int) * n);
		}
	}

	void update(int x, int y, int d){
		//A[x][y] += d
		while (x < m){
			int i = y;
			while (i < n){
				B[x][i] += d;
				i |= i + 1;
			}
			x |= x + 1;
		}
	}

	int rsq(int x1, int y1, int x2, int y2){
		//rsq[x1, x2][y1, y2]
		return rsq0(x2, y2) - rsq0(x1 - 1, y2) - rsq0(x2, y1 - 1) + rsq0(x1 - 1, y1 - 1);
	}

private:
	int rsq0(int x, int y){
		int sum = 0;
		while (x >= 0){
			int i = y;
			while (i >= 0){
				sum += B[x][i];
				i = (i & (i + 1)) - 1;
			}
			x = (x & (x + 1)) - 1;
		}
		return sum;
	}
};

int main(){
	freopen("input.txt", "r", stdin);
	int N, type, X, Y, A, L, B, R, T;
	Tree FT = Tree(1024, 1024);
	cin >> type;
	while (type < 3){
		switch (type){
			case 0:
			cin >> N;
			break;
			case 1:
			cin >> X >> Y >> A;
			FT.update(X, Y, A);
			break;
			case 2:
			cin >> L >> B >> R >> T;
			cout << FT.rsq(L, B, R, T) << endl;
			break;
		}
		cin >> type;
	}
	return 0;
}
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

//f(k) = k & (k + 1)
//0 <= f(k) <= k for all k >= 0

class Tree{
	int n;
	double * B;

public:
	Tree(double * A, int N, bool zero_init = false){
		n = N;
		B = (double*) malloc(sizeof(double) * n);
		for (int i = 0; i < n; ++i){
			B[i] = 0;
		}
		if (!zero_init){
			for (int i = 0; i < n; ++i){
				update(i, A[i]);
			}
		}
	}

Tree(int * A, int N, bool zero_init = false){
		n = N;
		B = (double*) malloc(sizeof(double) * n);
		for (int i = 0; i < n; ++i){
			B[i] = 0;
		}
		if (!zero_init){
			for (int i = 0; i < n; ++i){
				update(i, A[i]);
			}
		}
	}

	void update(int k, double d){
		//A[k] += d
		while (k < n){
			B[k] += d;
			k = k | (k + 1);
		}
	}

	double rsq(int i, int j){
		//rsq[i, j]
		return rsq0(j) - rsq0(i - 1);
	}

private:
	double rsq0(int k){
		double sum = 0;
		while (k >= 0){
			sum += B[k];
			k = (k & (k + 1)) - 1;
		}
		return sum;
	}
};

int main(){
	int A[8];
	for (int i = 0; i < 8; ++i){
		A[i] = (i * 179) % 8;
		//A[i] = i;
	}
	Tree T = Tree(A, 8);
	for (int i = 0; i < 8; ++i){
		cout << T.rsq(i, i) << " ";
	}
	cout << endl;
	return 0;
}
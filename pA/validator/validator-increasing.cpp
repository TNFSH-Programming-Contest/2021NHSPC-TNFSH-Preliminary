#include <bits/stdc++.h>

#include "testlib.h"

using namespace std;

int main() {
	registerValidation();

	int N = inf.readInt(1, 1000000);
	inf.readEoln();

	int A, pre;
	A = inf.readInt(1, 1000000000);
	for (int i = 2; i <= N; i++) {
		pre = A;
		inf.readSpace();
		A = inf.readInt(1, 1000000000);
		ensure(pre <= A);
	}
	inf.readEoln();

	int Q = inf.readInt(1, 1000000);
	inf.readEoln();

	int X, Y;
	for (int i = 0; i < Q; i++) {
		X = inf.readInt(1, 1000000);
		inf.readSpace();
		Y = inf.readInt(1, 1000000);
		inf.readEoln();
	}

	inf.readEof();

	return 0;
}

#include <bits/stdc++.h>

#include "testlib.h"

using namespace std;

int main() {
	registerValidation();

	int N = inf.readInt(1, 1000000);
	inf.readEoln();

	inf.readInt(1, 1000000000);
	for (int i = 2; i <= N; i++) {
		inf.readSpace();
		inf.readInt(1, 1000000000);
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

		ensure(X <= Y);
	}

	inf.readEof();

	return 0;
}

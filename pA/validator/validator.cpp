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

	for (int i = 0; i < Q; i++) {
		inf.readInt(1, N);
		inf.readSpace();
		inf.readInt(1, N);
		inf.readEoln();
	}

	inf.readEof();

	return 0;
}

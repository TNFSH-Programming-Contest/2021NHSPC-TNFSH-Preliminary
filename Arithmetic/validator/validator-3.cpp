#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main() {
	registerValidation();

	int A = inf.readInt(-1000000000, 1000000000);
	inf.readSpace();
	inf.readChar();
	inf.readSpace();
	int B = inf.readInt(-1000000000, 1000000000);
	inf.readEoln();

	inf.readEof();

	ensure(0 <= A && A <= 10000);
	ensure(0 <= B && B <= 10000);

	return 0;
}

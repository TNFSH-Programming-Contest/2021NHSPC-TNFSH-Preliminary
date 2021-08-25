#include <bits/stdc++.h>
#include "testlib.h"
#define endl '\n'
using namespace std;
char sign[] = {'+', '-', '*', '/'};

void gen_task2() {
	int signid = rnd.next(4);
	int B = rnd.next(1, 10000);

	cout << 0 << " " << sign[signid] << " " << B << endl;
}

void gen_norm(long long MIN_V, long long MAX_V) {
	int A = rnd.next(MIN_V, MAX_V);
	int signid = rnd.next(4);
	int B = rnd.next(MIN_V, MAX_V);

	cout << A << " " << sign[signid] << " " << B << endl;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	registerGen(argc, argv, 1);

	string MODE = argv[1];

	if (MODE == "norm") {
		long long MIN_V = atoll(argv[2]);
		long long MAX_V = atoll(argv[3]);

		gen_norm(MIN_V, MAX_V);
	} else if (MODE == "task2") {
		gen_task2();
	} else {
		return -1;
	}
}

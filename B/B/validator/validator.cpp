#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main() {
	registerValidation();

	int n = inf.readInt(1, 200000);
	inf.readSpace();
	int m = inf.readInt(5, 1000);
	inf.readSpace();
	int k = inf.readInt(1, n);
	inf.readEoln();

	vector<int> v(n);
	for(int i = 0; i < n; i++){
		if(i) inf.readSpace();
		v[i] = inf.readInt(1, n);
	}
	inf.readEoln();
	sort(v.begin(), v.end());
	for(int i = 0; i < n; i++){
		if(v[i] != i + 1) return 3;
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < 5; j++){
			if(j) inf.readSpace();
			int tmp = inf.readInt(1, m);
		}
		inf.readEoln();
	}

	inf.readEof();

	return 0;
}

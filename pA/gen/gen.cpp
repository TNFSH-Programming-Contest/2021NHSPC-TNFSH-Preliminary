#include <bits/stdc++.h>

#include "testlib.h"
#define endl '\n'
using namespace std;

const int _1e6 = 1000000;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	registerGen(argc, argv, 1);

	int taskN = atoi(argv[1]);
	int subtaskN = atoi(argv[2]);

	int maxN = _1e6;
	if (taskN == 2) {
		maxN = 10;
	}

	int N = rnd.next(1, maxN);
	cout << N << endl;

	vector<int> v;
	if (taskN == 1) {
		for (int i = 0; i < N; i++) {
			v.push_back(i + 1);
		}
	} else {
		int a;
		for (int i = 0; i < N; i++) {
			a = rnd.next(1, maxN);
			v.push_back(a);
		}
		if (taskN == 5) {
			if (subtaskN <= 3) {
				sort(v.begin(), v.end());
			} else {
				sort(v.begin(), v.end(), greater<int>());
			}
		} else {
			sort(v.begin(), v.end());
		}
	}

	cout << v[0];
	for (int i = 1; i < N; i++) {
		cout << " " << v[i];
	}
	cout << endl;

	int Q = rnd.next(1, _1e6);
	cout << Q << endl;

	for (int i = 0; i < Q; i++) {
		int X = rnd.next(1, maxN - 1);
		int Y = rnd.next(1, maxN - 1);
		if (taskN <= 3 && X > Y) {
			swap(X, Y);
		}
		if ((Y - X) % 2 != 0) {
			if (Y > X) {
				Y += 1;
			} else {
				X += 1;
			}
		}
		cout << X << " " << Y << endl;
	}
}

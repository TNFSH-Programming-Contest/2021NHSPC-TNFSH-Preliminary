// By xiplus
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int A[1000005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}
	int Q, X, Y;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> X >> Y;
		if (X > Y) {
			swap(X, Y);
		}
		cout << A[(X + Y) / 2] << endl;
	}

	return 0;
}

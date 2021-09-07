#include <bits/stdc++.h>
using namespace std;

const int _1e6 = 1000005;

unordered_map<int, long double> edge[_1e6];
int indeg[_1e6], insrc[_1e6], outdeg[_1e6], outtar[_1e6];
inline long double calcPR(long double a, long double b) {
	return a * b / (a + b);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, E;
	cin >> N >> E;
	int ecnt = E;
	int a, b, c;
	long double r;
	while (E--) {
		cin >> a >> b >> r;
		if (edge[a].count(b) == 0) {
			edge[a][b] = r;
			indeg[b]++;
			insrc[b] = a;
			outdeg[a]++;
			outtar[a] = b;
		} else {
			edge[a][b] = calcPR(edge[a][b], r);
			ecnt--;
		}
	}
	queue<int> squeue;
	for (int i = 1; i <= N; i++) {
		if (indeg[i] == 1 && outdeg[i] == 1) {
			squeue.push(i);
		}
	}

	while (ecnt > 1 && squeue.size() > 0) {
		b = squeue.front();
		squeue.pop();
		a = insrc[b];
		c = outtar[b];
		r = edge[a][b] + edge[b][c];
		edge[a].erase(b);
		edge[b].erase(a);
		ecnt--;
		if (edge[a].count(c) == 0) {
			edge[a][c] = r;
			indeg[c]++;
			insrc[c] = a;
			outdeg[a]++;
			outtar[a] = c;
		} else {
			edge[a][c] = calcPR(edge[a][c], r);
			ecnt--;
			outdeg[a]--;
			indeg[c]--;
			if (indeg[a] == 1 && outdeg[a] == 1) {
				squeue.push(a);
			}
			if (indeg[c] == 1 && outdeg[c] == 1) {
				squeue.push(c);
			}
		}
	}

	cout << setprecision(10) << edge[1][2] << endl;
}

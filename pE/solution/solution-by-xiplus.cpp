#include <bits/stdc++.h>
using namespace std;

const int _1e6 = 1000005;

unordered_map<int, double> edge[_1e6];
int indeg[_1e6], insrc[_1e6], outdeg[_1e6], outtar[_1e6];
inline double calcPR(double a, double b) {
	return 1 / (1 / a + 1 / b);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N, E;
	cin >> N >> E;
	int ecnt = E;
	int a, b, c;
	double r;
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
	// for (int i = 1; i <= N; i++) {
	// 	for (auto it = edge[i].begin(); it != edge[i].end(); it++) {
	// 		cout << i << " " << it->first << " " << it->second << endl;
	// 	}
	// }

	cout << edge[1][2] << endl;
}

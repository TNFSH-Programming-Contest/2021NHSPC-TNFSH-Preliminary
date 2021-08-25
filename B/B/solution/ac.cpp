#include <bits/stdc++.h>
using namespace std;

int rk[200005], pick[200005][10], n, m, k;
vector<int> in[1005];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> rk[i];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= 5; j++){
			cin >> pick[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= 5; j++){
			if(in[pick[rk[i]][j]].size() < k){
				in[pick[rk[i]][j]].push_back(rk[i]);
				break;
			}
		}
	}
	for(int i = 1; i <= m; i++){
		sort(in[i].begin(), in[i].end());
		cout << in[i].size();
		for(auto &j : in[i]){
			cout << " " << j;
		}
		cout << '\n';
	}
}

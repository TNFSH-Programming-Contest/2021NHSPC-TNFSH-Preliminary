#include<bits/stdc++.h>
#define MAXN 1000005
#define double long double
using namespace std;
struct Edge {
	int v;
	double resis;
};
vector<Edge> G[MAXN];
int inDeg[MAXN];
void tandem(int u, int idx) {
	int v = G[u][idx].v;
	G[u][idx] = Edge{G[v].front().v, G[u][idx].resis + G[v].front().resis};
	G[v].clear();
}
void parallel(int u, int pre, int now) {
	G[u][pre].resis = (G[u][pre].resis * G[u][now].resis) / (G[u][pre].resis + G[u][now].resis);
	G[u].erase(G[u].begin() + now);
	inDeg[G[u][pre].v]--;
}
int pre[MAXN];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1,u,v,resis;i<=m;i++) {
		cin >> u >> v >> resis;
		G[u].push_back(Edge{v, (double)resis});
		inDeg[v]++;
	}

	memset(pre, -1, sizeof pre);
	while(true) {
		bool update = false;
		
		for(int i=1;i<=n;i++)
			for(int j=0;j<(int)G[i].size();j++) {
				int v = G[i][j].v;
				if(inDeg[v] == 1 && (int)G[v].size() == 1)
					tandem(i, j), update = true;
			}
		for(int i=1;i<=n;i++) {
			for(int j=0;j<(int)G[i].size();j++) {
				int v = G[i][j].v;
				if(pre[v] != -1)
					parallel(i, pre[v], j), update = true, j--;
				else
					pre[v] = j;
			}
			for(Edge e : G[i])	pre[e.v] = -1;
		}

		if(!update)	break;
	}
	cout << setprecision(10) << G[1].front().resis << endl;
	return 0;
}

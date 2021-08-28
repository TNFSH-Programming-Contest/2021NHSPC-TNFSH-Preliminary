#include<bits/stdc++.h>
#define MAXN 1000005
#define double long double
using namespace std;
map<int, double> G[MAXN], rG[MAXN];
void parallel(int u, int v, double anotherResis) {
	G[u][v] = (G[u][v] * anotherResis) / (G[u][v] + anotherResis);
	rG[v][u] = (rG[v][u] * anotherResis) / (rG[v][u] + anotherResis);
}
void tandem(int front, int mid, int back) {
	double newResis = (*rG[mid].begin()).second + (*G[mid].begin()).second;
	G[front].erase(mid);	G[mid].erase(back);
	rG[mid].erase(front);	rG[back].erase(mid);

	if(G[front].find(back) != G[front].end())
		parallel(front, back, newResis);
	else
		G[front][back] = rG[back][front] = newResis;
}
bool inq[MAXN];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1,u,v,resis;i<=m;i++) {
		cin >> u >> v >> resis;
		if(G[u].find(v) != G[u].end())
			parallel(u, v, resis);
		else
			G[u][v] = rG[v][u] = resis;
	}

	queue<int> tandemQueue;
	for(int i=1;i<=n;i++)	if((int)G[i].size() == 1 && (int)rG[i].size() == 1)	tandemQueue.push(i), inq[i] = true;
	while(!tandemQueue.empty()) {
		int mid = tandemQueue.front();	tandemQueue.pop();
		inq[mid] = false;
		int front = (*rG[mid].begin()).first, back = (*G[mid].begin()).first;
		tandem(front, mid, back);
		if(!inq[front] && (int)G[front].size() == 1 && (int)rG[front].size() == 1)	tandemQueue.push(front), inq[front] = true;
		if(!inq[back] && (int)G[back].size() == 1 && (int)rG[back].size() == 1)	tandemQueue.push(back), inq[back] = true;
	}
	cout << setprecision(10) << (*G[1].begin()).second << endl;
	return 0;
}

// Solution by 19nya, @ 08.29.21
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define fpt long double
#define chk(a,b) (!(a.find(b)==a.end()))
unordered_map<int,fpt> g[5000019];
vector<int> revmap[5000019],nxtmap[5000019];
int indeg[5000019],outdeg[5000019];
bool removed[5000019];

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
	for(int i=0;i<m;i++){
		int f,to;fpt omg;
		cin>>f>>to>>omg;
		if(chk(g[f],to)) g[f][to]=1.0l/((1.0l/omg)+(1.0l/g[f][to]));
		else{
			g[f][to]=omg;
			indeg[to]++;
			outdeg[f]++;
			revmap[to].push_back(f);
			nxtmap[f].push_back(to);
		}
	}
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(indeg[i]==1&&outdeg[i]==1)q.push(i);
	}
	while(q.size()>=1){
		int now=q.front(),f,to;
		q.pop();
		for(int i=0;i<revmap[now].size();i++){
			if(removed[revmap[now][i]])continue;
			f=revmap[now][i];
			break;
		}
		for(int i=0;i<nxtmap[now].size();i++){
			if(removed[nxtmap[now][i]])continue;
			to=nxtmap[now][i];
			break;
		}
		if(chk(g[f],to)){
			fpt nr=g[f][now]+g[now][to];
			g[f][to]=1.0l/((1.0l/nr)+(1.0l/g[f][to]));
			outdeg[f]--;
			indeg[to]--;
			if(indeg[f]==1&&outdeg[f]==1) q.push(f);
			if(indeg[to]==1&&outdeg[to]==1) q.push(to);
		}else{
			nxtmap[f].push_back(to);
			revmap[to].push_back(f);
			g[f][to]=g[f][now]+g[now][to];
		}
		removed[now]=1;
	}
	cout<<setprecision(10)<<g[1][2]<<endl;
	return 0;
}

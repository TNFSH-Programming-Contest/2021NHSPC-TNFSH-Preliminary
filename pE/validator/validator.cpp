#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
struct Node{
	vector<int> to;
	int indeg, outdeg;
} G[1000010];
bool visited[1000010],leaved[1000010];

bool dfs_check_DAG(int id){
	//cout<<id<<endl;
	if(visited[id]&&!leaved[id]){
		//cout<<id<<" FAIL"<<endl;
		return false;
	}
	if(visited[id]) return true;
	visited[id] = true;
	for(int t:G[id].to){
		bool c = dfs_check_DAG(t);
		if(!c) return false;
	}
	//visited[id] = false;
	leaved[id] = true;
	return true;
}

int main() {
	registerValidation();

	int N = inf.readInt(1, 1000000);
	inf.readSpace();
	int M = inf.readInt(1, 1000000);
	inf.readEoln();
	ensuref(N<=1000000&&M<=1000000, "N,M should less than 1000000.");
	for(int i=0;i<M;i++){
		int a,b,r;
		a = inf.readInt(1,N);
		inf.readSpace();
		b = inf.readInt(1,N);
		inf.readSpace();
		r = inf.readInt(1,30);
		inf.readEoln();
		G[a].to.push_back(b);
		G[a].outdeg++;
		G[b].indeg++;
	}
	//inf.readEoln();
	inf.readEof();
	//cout<<dfs_check_DAG(1)<<endl;
	ensuref(G[1].indeg==0,"Node 1's in degree should be 0");
	ensuref(G[2].outdeg==0,"Node 2's out degree should be 0");
	ensuref(dfs_check_DAG(1)==true, "Not a DAG");
	return 0;
}

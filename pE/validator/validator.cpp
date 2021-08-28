#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
struct Node{
	vector<int> to;
} G[1000010];
bool visited[1000010],leaved[1000010];

bool dfs_check_DAG(int id){
	if(visited[id]&&!leaved[id]) return false;
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
	for(int i=0;i<M;i++){
		int a,b,r;
		a = inf.readInt(1,N);
		inf.readSpace();
		b = inf.readInt(1,N);
		inf.readSpace();
		r = inf.readInt(1,30);
		inf.readEoln();
		G[a].to.push_back(b);
	}
	//inf.readEoln();
	inf.readEof();
	dfs_check_DAG(1);
	return 0;
}

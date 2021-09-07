#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
struct Node{
	vector<int> to;
	int indeg, outdeg;
} G[1000010];
bool visited[1000010],leaved[1000010];

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
		G[a].outdeg++;
		G[b].indeg++;
	}
	//inf.readEoln();
	inf.readEof();
	for(int i=1;i<=N;i++){
		if(!(G[i].outdeg<=1&&G[i].indeg<=1)){
			printf("%d\n",i);
		}
		ensuref(G[i].outdeg<=1&&G[i].indeg<=1, "Node in-degree or out-degree greater than 1");
	}
	return 0;
}

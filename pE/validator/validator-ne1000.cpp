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
	ensuref(N<=1000&&M<=1000, "N,M should less than 1000.");
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
	return 0;
}

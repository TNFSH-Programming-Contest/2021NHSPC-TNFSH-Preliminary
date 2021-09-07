#include <bits/stdc++.h>
#include "testlib.h"
#define endl '\n'
using namespace std;
const int Rmin = 5;
const int Rmax = 30;
int NodeLimit, EdgeLimit;

struct Edge{
	int from,to,r;
};
struct Circuit{
	int from,to;
	long double r;
	vector<int> edges;
	Circuit(){}
	Circuit(int from,int to,long double r,int edge):from(from),to(to),r(r){edges.push_back(edge);}
};
vector<Circuit> C;
vector<Edge> E;
int count_C, count_E, count_N;
int NodeID;
map<int,int> nodemap;

void merge_parallel(int ca,int cb){
	for(int e:C[cb].edges){
		if(E[e].from==C[cb].from)E[e].from = C[ca].from;
		if(E[e].to==C[cb].to)E[e].to = C[ca].to;
		C[ca].edges.push_back(e);
	}
	C[ca].r = 1.0/(1.0/C[ca].r + 1.0/C[cb].r);
	C.erase(C.begin()+cb,C.begin()+cb+1);
	count_C--;
	count_N-=2;
}

void concat_series(int ca,int cb){
	for(int e:C[cb].edges){
		if(E[e].from==C[cb].from)E[e].from = C[ca].to;
		C[ca].edges.push_back(e);
	}
	C[ca].to = C[cb].to;
	C[ca].r = C[ca].r + C[cb].r;
	C.erase(C.begin()+cb,C.begin()+cb+1);
	count_C--;
	count_N--;
}

void new_edge(){
	int a,b,r;
	a = NodeID++;
	b = NodeID++;
	r = rnd.next(Rmin, Rmax);
	C.push_back(Circuit(a,b,r,E.size()));
	E.push_back(Edge({a,b,r}));
	count_C++;
	count_E++;
	count_N+=2;
}

int node_remap(int node){
	if(nodemap.find(node)==nodemap.end()){
		nodemap[node] = NodeID++;
	}
	return nodemap[node];
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	registerGen(argc, argv, 1);

	// gen {Nodes} {Edges} {S(eries)/P(arallel)/B(oth)} {seed}
	NodeLimit = atoi(argv[1]);
	EdgeLimit = atoi(argv[2]);

	int model = 1, moder = 2;
	if(argv[3][0]=='S') moder = 1;
	else if(argv[3][0]=='P') model = 2;

	while((count_E<EdgeLimit&&count_N+2<=NodeLimit) || count_C>1){
		int op1 = rnd.next(1,((count_N+2<=NodeLimit&&count_E<EdgeLimit)?2:1));
		if(op1==1 && count_C>1){ //merge
			int op2 = rnd.next(model,moder);
			shuffle(C.begin(),C.end());
			if(op2==1){
				concat_series(C.size()-2,C.size()-1);
			}
			else if(op2==2){
				merge_parallel(C.size()-2,C.size()-1);
			}
		}
		else if(op1==2){ //new edge
			new_edge();
		}
	}

	NodeID = 3;
	nodemap[C[0].from] = 1;
	nodemap[C[0].to] = 2;

	cout<<count_N<<" "<<count_E<<endl;
	for(Edge e:E){
		cout<<node_remap(e.from)<<" "<<node_remap(e.to)<<" "<<e.r<<endl;
	}
	//cout<<setprecision(10)<<C[0].r<<endl;
}

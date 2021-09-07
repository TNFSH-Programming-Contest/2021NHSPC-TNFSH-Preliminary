#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
struct Edge{
	int node,rev_edgeid;
	long double r;
	Edge(int node,int rev_edgeid,long double r):node(node),rev_edgeid(rev_edgeid),r(r){}
};
struct Node{
	vector<Edge> edge_in,edge_out;
	map<int,int> node_in,node_out;
	int indeg,outdeg;
	int debug;
	bool removed;
} graph[1000010];
queue<int> toRemove, toMerge;

int DEBUG = 1;

void debug_trace(int node){
	//cout<<node<<endl;
	if(graph[node].debug==DEBUG)return ;
	if(graph[node].removed)return ;
	graph[node].debug = DEBUG;
	for(Edge e:graph[node].edge_out){
		if(e.node==-1) continue;
		cout<<node<<" "<<e.node<<" "<<e.r<<endl;
	}
	for(Edge e:graph[node].edge_out){
		if(e.node==-1) continue;
		debug_trace(e.node);
	}
}

void debug_output(int node,int n){
	cout<<endl<<"DEBUG:"<<endl;
	for(int i=1;i<=n;i++){
		if(graph[i].removed) continue;
		cout<<"Node "<<i<<": indeg="<<graph[i].indeg<<", outdeg="<<graph[i].outdeg<<", node_in="<<graph[i].node_in.size()<<", node_out="<<graph[i].node_out.size()<<endl;
	}
	debug_trace(node);
	DEBUG++;
}

inline void increase_node_count(int a,int b){
	if(graph[a].node_out.find(b)==graph[a].node_out.end())graph[a].node_out[b]=1;
	else graph[a].node_out[b]++;
	if(graph[b].node_in.find(a)==graph[b].node_in.end())graph[b].node_in[a]=1;
	else graph[b].node_in[a]++;
}

inline void build_edge(int a,int b,long double r){
	int edges_a,edges_b;
	edges_a = graph[a].outdeg++;
	edges_b = graph[b].indeg++;
	
	graph[a].edge_out.push_back(Edge(b,edges_b,r));
	graph[b].edge_in.push_back(Edge(a,edges_a,r));
	increase_node_count(a,b);
}

inline void check_to_merge(int node){
	//cout<<"Check "<<node<<" to merge."<<endl;
	//cout<<"Node "<<node<<": "<<"node_in="<<graph[node].node_in.size()<<", node_out="<<graph[node].node_out.size()<<endl;
	if((graph[node].node_in.size()==1 && graph[node].indeg>1) ||
	   (graph[node].node_out.size()==1 && graph[node].outdeg>1)){
	   	//cout<<"Put "<<node<<" to merge queue."<<endl;
		toMerge.push(node);
	}
}

inline void remove_node(int node){
	//cout<<"Remove "<<node<<endl;
	if(graph[node].indeg!=1 || graph[node].outdeg!=1 || graph[node].removed){
		return ;
	}
	int front,front_edge,back,back_edge;
	front = graph[node].edge_in[0].node;
	front_edge = graph[node].edge_in[0].rev_edgeid;
	back = graph[node].edge_out[0].node;
	back_edge = graph[node].edge_out[0].rev_edgeid;
	long double r = graph[node].edge_in[0].r + graph[node].edge_out[0].r;
	
	//cout<<"Removing "<<front<<"->"<<node<<"->"<<back<<endl;
	
	graph[front].edge_out[front_edge] = Edge(back, back_edge, r);
	graph[back].edge_in[back_edge] = Edge(front, front_edge, r);
	
	graph[front].node_out[node]--;
	//cout<<"Update front node "<<front<<" node_out["<<node<<"]="<<graph[front].node_out[node]<<endl;
	if(graph[front].node_out[node]<=0)graph[front].node_out.erase(graph[front].node_out.find(node));
	graph[back].node_in[node]--;
	//cout<<"Update back node "<<back<<" node_in["<<node<<"]="<<graph[back].node_in[node]<<endl;
	if(graph[back].node_in[node]<=0)graph[back].node_in.erase(graph[back].node_in.find(node));
	increase_node_count(front,back);
	graph[node].removed = 1;
	check_to_merge(front);
	check_to_merge(back);
}

void remove_node_trace(int node){
	if(graph[node].indeg!=1 || graph[node].outdeg!=1){
		return ;
	}
	remove_node_trace(graph[node].edge_in[0].node);
	remove_node(node);
}
/*
inline void merge_parallel(int node){
	for(Edge e:graph[node].edge_in){
		remove_node_trace(e.node);
	}
	long double r=0;
	for(Edge e:graph[node].edge_in){
		r += 1.0/e.r;
	}
	int front = graph[node].edge_in[0].node;
	graph[node].edge_in[0] = Edge(front, 0, r);
	graph[front].edge_out[0] = Edge(node, 0, r);
	graph[node].indeg = 1;
	graph[front].outdeg = 1;
}
*/
inline void check_to_remove(int node){
	if(graph[node].indeg==1 && graph[node].outdeg==1){
		toRemove.push(node);
	}
}
inline void merge_parallel(int node){
	if(graph[node].node_in.size()==1 && graph[node].indeg>1){
		//cout<<"Merge "<<node<<endl;
		int es = graph[node].edge_in.size();
		long double r=0;
		int front=-1,front_edge,node_edge;
		for(int i=0;i<es;i++){
			Edge e = graph[node].edge_in[i];
			if(e.node==-1) continue;
			r += 1/e.r;
			if(front==-1){
				front = e.node;
				front_edge = e.rev_edgeid;
				node_edge = i;
			}
			graph[e.node].edge_out[e.rev_edgeid].node = -1;
			graph[e.node].outdeg--;
			graph[node].edge_in[i].node = -1;
			graph[node].indeg--;
		}
		r = 1/r;
		graph[front].outdeg++;
		graph[node].indeg++;
		if(graph[front].outdeg==1){
			graph[front].edge_out[front_edge].node = -1;
			front_edge = 0;
		}
		node_edge = 0;
		graph[node].edge_in[node_edge] = Edge(front,front_edge,r);
		graph[front].edge_out[front_edge] = Edge(node,node_edge,r);
		graph[front].node_out[node] = 1;
		graph[node].node_in[front] = 1;
		check_to_remove(front);
	}
	
	if(graph[node].node_out.size()==1 && graph[node].outdeg>1){
		//cout<<"Merge "<<node<<endl;
		int es = graph[node].edge_out.size();
		long double r=0;
		int back=-1,back_edge,node_edge;
		for(int i=0;i<es;i++){
			Edge e = graph[node].edge_out[i];
			if(e.node==-1) continue;
			r += 1/e.r;
			if(back==-1){
				back = e.node;
				back_edge = e.rev_edgeid;
				node_edge = i;
			}
			graph[e.node].edge_in[e.rev_edgeid].node = -1;
			graph[e.node].indeg--;
			graph[node].edge_out[i].node = -1;
			graph[node].outdeg--;
		}
		r = 1/r;
		graph[back].indeg++;
		graph[node].outdeg++;
		if(graph[back].indeg==1){
			graph[back].edge_in[back_edge].node = -1;
			back_edge = 0;
		}
		node_edge = 0;
		graph[node].edge_out[node_edge] = Edge(back,back_edge,r);
		graph[back].edge_in[back_edge] = Edge(node,node_edge,r);
		graph[back].node_in[node] = 1;
		graph[node].node_out[back] = 1;
		check_to_remove(back);
	}
	check_to_remove(node);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;
		long double r;
		cin>>a>>b>>r;
		build_edge(a,b,r);
	}
	//long double ans=0.0;
	//cin>>ans;
	for(int i=1;i<=n;i++){
		check_to_remove(i);
		check_to_merge(i);
	}
	//cout<<"start"<<endl;
	//remove_node_trace(4);
	//debug_output(1,n);
	while((!toRemove.empty() || !toMerge.empty()) && (graph[1].outdeg>1 || graph[1].edge_out[0].node!=2)){
		while(!toRemove.empty()){
			remove_node(toRemove.front());
			toRemove.pop();
		}
		while(!toMerge.empty()){
			merge_parallel(toMerge.front());
			toMerge.pop();
		}
		//debug_output(1,n);
	}
	for(Edge e:graph[1].edge_out){
		if(e.node==-1)continue;
		cout<<setprecision(10)<<e.r<<endl;
		//cout<<setprecision(10)<<fabsl(e.r-ans)<<endl;
		/*assert(fabsl(e.r-ans)<(long double)0.000001);
		if(fabsl(e.r-ans)>=(long double)0.000001){
			cerr<<"Wrong Answer"<<endl;
		}*/
		break;
	}
	return 0;
}

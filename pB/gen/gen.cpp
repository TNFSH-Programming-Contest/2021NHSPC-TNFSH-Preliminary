#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

vector<array<int, 5>> v;
vector<int> rk, tmp;
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	int subtask = atoi(argv[1]);
	int n, m, k;
	if(subtask == 1){
		n = rnd.next(1, 200000);
		k = n;
		m = rnd.next(5, 1000);
		rk = rnd.perm(n, 1);
		for(int i = 0; i < n; i++){
			array<int, 5> arr;
			tmp = rnd.perm(m, 1);
			for(int j = 0; j < 5; j++) arr[j] = tmp[j];
			v.push_back(arr);
		}
	}
	else if(subtask == 2){
		n = rnd.next(1, 200000);
		k = rnd.next(1, min(n, 100));
		m = 5;
		rk = rnd.perm(n, 1);
		for(int i = 0; i < n; i++){
			array<int, 5> arr;
			tmp = rnd.perm(m, 1);
			for(int j = 0; j < 5; j++) arr[j] = tmp[j];
			if(i) arr = v.back();
			v.push_back(arr);
		}
	}
	else if(subtask == 3){
		n = rnd.next(1, 5000);
		k = rnd.next(1, min(n, 100));
		m = rnd.next(5, 1000);
		rk = rnd.perm(n, 1);
		for(int i = 0; i < n; i++){
			array<int, 5> arr;
			tmp = rnd.perm(m, 1);
			for(int j = 0; j < 5; j++) arr[j] = tmp[j];
			v.push_back(arr);
		}
	}
	else{
		n = rnd.next(1, 200000);
		k = rnd.next(1, min(n, 1000));
		m = rnd.next(5, 1000);
		rk = rnd.perm(n, 1);
		for(int i = 0; i < n; i++){
			array<int, 5> arr;
			tmp = rnd.perm(m, 1);
			for(int j = 0; j < 5; j++) arr[j] = tmp[j];
			v.push_back(arr);
		}
	}
	cout << n << " " << m << " " << k << '\n';
	for(int i = 0; i < n; i++){
		cout << rk[i] << " \n"[i==n-1];
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 5; j++){
			cout << v[i][j] << " \n"[j==4];
		}
	}
}

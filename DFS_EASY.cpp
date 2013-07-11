/*
  Autor: 		Krzysztof Jamroz
	Zadanie:	acm.uva.es - zadanie 280
*/

#include<iostream>
#include <queue>
using namespace std;

#define SIZE 101

int n,m,a;
vector<int>G[SIZE];
vector<int>A[SIZE];
vector<int>V;
bool visit[SIZE];
queue<int>q;

void start(){
	for(int i=1;i<=n;i++){
		A[i].clear();
		for(int j=1;j<=n;j++)visit[j]=false;
		q.push(i);
		while(!q.empty()){
			int x = q.front();
			q.pop();
			for(int j=0;j<G[x].size();j++)
				if(!visit[G[x][j]]){
					visit[G[x][j]]=true;
					q.push(G[x][j]);
				}
		}
		for(int j=1;j<=n;j++)
			if(!visit[j])
				A[i].push_back(j);
	}
	for(int i=0;i<m;i++){
		cout<<A[V[i]].size();
		for(int j=0;j<A[V[i]].size();j++)
			cout<<" "<<A[V[i]][j];
		cout<<"\n";
	}
}

void readTest(){
	cin>>n;
	int i,j;
	while(n!=0){
		for(i =1;i<SIZE;i++)G[i].clear();
		cin>>i;
		while(i!=0){
			cin>>j;
			while(j!=0){
				G[i].push_back(j);
				cin>>j;
			}
			cin>>i;
		}
		cin>>m;
		V.clear();
		for(i=0;i<m;i++){
			cin>>a;
			V.push_back(a);
		}
		start();
		cin>>n;
	}
}



int main(){
	ios_base::sync_with_stdio(0);
	readTest();
	return 0;
}

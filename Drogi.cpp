/*
    Autor: 		Krzysztof Jamroz
	Zadanie:	Drogi, Potyczki Algorytmiczne 2005
*/


#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int n,m;
vector<int> G[10001];
vector<int> GT[10001];
vector<int> H[10001];
vector<int> HT[10001];
int sss[10001];
int ns;
int sssF[10001],ttt;
bool sssvis[10001];

void sss_dfs(int v) {
	sssvis[v]=1;
	for(int i=0;i<G[v].size();++i)
	if(!sssvis[G[v][i]]) 
		sss_dfs(G[v][i]);
	sssF[ttt++]=v;
}
 
void sss_dfs2(int v) {
	sss[v]=ns;
	sssvis[v]=1;
	for(int i=0;i<GT[v].size();++i)
	if(!sssvis[GT[v][i]]) 
		sss_dfs2(GT[v][i]);
}

void compute_sss(){
	ttt=0;
	for(int i=0;i<n;++i)
		if(!sssvis[i])
			sss_dfs(i);
	for(int i=0;i<n;++i)
		sssvis[i] = 0;
	ns=0;
	for(int i=ttt-1;i>=0;--i)
		if(!sssvis[sssF[i]]){
			sss_dfs2(sssF[i]);
			++ns;
		} 
}

void transposeGraph(){
	for(int i=0;i<n;++i)
		for(int j=0;j<G[i].size();++j)
			GT[G[i][j]].push_back(i);
}


void buildGraphH(){
	for(int i=0;i<n;i++)
		for(int j=0;j<G[i].size();j++)
			if(sss[i]!=sss[G[i][j]]){
				H[sss[i]].push_back(sss[G[i][j]]);
				HT[sss[G[i][j]]].push_back(sss[i]);
			}
}

void solve(){
	if(ns==1){
		cout<<"0\n";
		return;
	}
	int a=0,b=0;
	for(int i=0;i<ns;i++){
		if(H[i].empty())
			a++;
		if(HT[i].empty())
			b++;
	}
	cout<<max(a,b)<<"\n";
}

void readGraph(){
	int a,b;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>a>>b;
		--a;--b;
		G[a].push_back(b);
	}
}

int main(){
	readGraph();
	transposeGraph();
	compute_sss();
	buildGraphH();
	solve();
	return 0;
}

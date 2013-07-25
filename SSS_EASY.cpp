/*
    Autor: 		Krzysztof Jamroz
	Zadanie:	spoj.sphere.com - zadanie 51
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n,m;
vector<int> G[10001];
vector<int> GT[10001];
int H[10001];
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
		sssvis[i]=H[i]=sss[i]=0;
	for(int i=0;i<n;++i)
		if(!sssvis[i])
			sss_dfs(i);
	for(int i=0;i<n;++i)
		sssvis[i]=H[i]=sss[i]=0;
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


void solve(){
	for(int i=0;i<n;i++)
		for(int j=0;j<G[i].size();j++)
			if(sss[i]!=sss[G[i][j]])
				H[sss[G[i][j]]]++;
	int count=0;
    for(int i=0;i<ns;++i)
		if(!H[i])
            ++count;
    if(count>1)
        cout<<"0\n";
	else{
		count=0;
		for(int i=0;i<n;++i) 
        	if(!H[sss[i]]) 
            	++count;
        cout<<count<<"\n";
    }		
}

void readGraph(){
	cin>>n;
	for(int i=0;i<n;++i){
		G[i].clear();
		GT[i].clear();
	}
	int j;
	for(int i=0;i<n;i++){
		cin>>m;
		while(m--){
			cin>>j;
			--j;
			G[j].push_back(i);
		}
	}
}

int main() {
	int t;
	cin>>t;
	while(t--){
		readGraph();
		transposeGraph();
		compute_sss();
		solve();
	}
	return 0;
}

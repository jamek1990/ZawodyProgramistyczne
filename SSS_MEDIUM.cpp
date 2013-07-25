/*
    Autor: 		Krzysztof Jamroz
	  Zadanie:	acm.uva.es - zadanie 247
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int n,m;
vector<int> G[10001];
vector<int> GT[10001];
vector<string> H[10001];
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
		sssvis[i]=sss[i]=0;
	for(int i=0;i<n;++i)
		if(!sssvis[i])
			sss_dfs(i);
	for(int i=0;i<n;++i)
		sssvis[i]=sss[i]=0;
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

map<string ,int> book;
map<int ,	string> book2;
bool  readGraph(){
	cin>>n>>m;
	if(n==0 && m==0)return false;
	string a,b;
	int x,y;
	int ile=0;
	book.clear();
	book2.clear();
	for(int i=0;i<n;++i){
		G[i].clear();
		GT[i].clear();
		H[i].clear();
	}
	for(int i=0;i<m;i++){
		cin>>a>>b;
		if(book.find(a)!=book.end())
			x=(book.find(a))->second;
		else{
			x=ile;
			book.insert(pair<string,int>(a,ile));
			book2.insert(pair<int,string>(ile,a));
			ile++;
		}
		if(book.find(b)!=book.end())
			y=(book.find(b))->second;
		else{
			y=ile;
			book.insert(pair<string,int>(b,ile));
			book2.insert(pair<int,string>(ile,b));
			ile++;
		}
		G[x].push_back(y);
	}
	return true;
}

void solve(int nr){
	for(int i=0;i<n;i++)
		H[sss[i]].push_back((book2.find(i))->second);
	cout<<"Calling circles for data set "<<nr<<":\n";
	for(int i=0;i<ns;i++){
		cout<<H[i][0];
		for(int j=1;j<H[i].size();j++)
			cout<<", "<<H[i][j];
		cout<<"\n";
	}
			
}

int main() {
	int t=0;
	while(readGraph()){
		t++;
		if(t>1)cout<<"\n";
		transposeGraph();
		compute_sss();
		solve(t);
	}
	return 0;
}

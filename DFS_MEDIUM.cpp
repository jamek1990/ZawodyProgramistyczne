/*
  Autor: 		Krzysztof Jamroz
	Zadanie:	spoj.sphere.com - zadanie 38
*/


#include<iostream>
#include <queue>

using namespace std;

int n,m;
bool labyrinth[1001][1001];
int G[1100000][4];
int GS[1100000];
int visit[1100000];
queue<int>q;
int maxLength;

int x[4]={-1,1,0,0};
int y[4]={0,0,-1,1};


void readTest(){
	cin>>m>>n;
	string s;
	for(int i=0;i<n;i++){
		cin>>s;
		for(int j=0;j<m;j++)
			if(s[j]=='.')
				labyrinth[i][j]=true;
			else
				labyrinth[i][j]=false;
	}
}

inline bool inside(int a, int b){
	if(a< 0 || a>=m)return false;
	if(b< 0 || b>=n)return false;
	return true;
}

void createGraph(){
	for(int i=0;i<m*n;i++)GS[i]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<4;k++)
				if(inside(j+x[k],i+y[k]) && labyrinth[i][j] && labyrinth[i+y[k]][j+x[k]])
					G[i*m+j][GS[i*m+j]++]=((i+y[k])*m+j+x[k]);
}

void maximumRopeLength(){
	maxLength=0;
	for(int i=0;i<=m*n;i++)visit[i]=0;
	for(int i=0;i<m*n;i++){
		if(!visit[i]){
			int mlength=0;
			int y=i;
			int length = 0;
			q.push(i);
			q.push(length);
			visit[i]=1;
			while(!q.empty()){
				int x = q.front();
				q.pop();
				length = q.front();
				q.pop();
				if(mlength<length){
					mlength=length;
					y=x;
				}
				for(int j=0;j<GS[x];j++)
					if(!visit[G[x][j]]){
						visit[G[x][j]]=1;
						q.push(G[x][j]);
						q.push(length+1);
						if(maxLength<length+1)
							maxLength=length+1;
					}
			}
			length = 0;
			q.push(y);
			q.push(length);
			visit[y]=2;
			while(!q.empty()){
				int x = q.front();
				q.pop();
				length = q.front();
				q.pop();
				for(int j=0;j<GS[x];j++)
					if(visit[G[x][j]]!=2){
						visit[G[x][j]]=2;
						q.push(G[x][j]);
						q.push(length+1);
						if(maxLength<length+1)
							maxLength=length+1;
					}
			}	
		}
	}
}

void writeTest(){
	cout<<"Maximum rope length is "<<maxLength<<".\n";
}
int main(){
	ios_base::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		readTest();
		createGraph();
		maximumRopeLength();
		writeTest();
	}
	return 0;
}

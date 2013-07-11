/*
  Autor: 		Krzysztof Jamroz
	Zadanie:	spoj.sphere.com - zadanie 206
*/


#include<iostream>
#include <queue>

using namespace std;

int n,m;
bool bitmap[182][182];
int answer[182][182];
bool visit[182][182];
queue<int>q;

int x[4]={-1,1,0,0};
int y[4]={0,0,-1,1};


void readTest(){
	cin>>n>>m;
	string s;
	for(int i=0;i<n;i++){
		cin>>s;
		for(int j=0;j<m;j++)
			if(s[j]=='1')
				bitmap[i][j]=true;
			else
				bitmap[i][j]=false;
	}
}

inline bool inside(int a, int b){
	if(a< 0 || a>=m)return false;
	if(b< 0 || b>=n)return false;
	return true;
}


//computes the distance to the nearest white pixel
void distance(){
	int dist=0,xx,yy;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			visit[i][j]=false;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(bitmap[i][j]){
				q.push(i*m+j);
				visit[i][j]=true;
			}
	q.push(-1);
	while(!q.empty()){
		while(q.front()!=-1){
			xx=q.front()%m;
			yy=q.front()/m;
			answer[yy][xx]=dist;
			q.pop();
			for(int i=0;i<4;i++)
				if(inside(xx+x[i],yy+y[i]) && !visit[yy+y[i]][xx+x[i]]){
					q.push((yy+y[i])*m+xx+x[i]);
					visit[yy+y[i]][xx+x[i]]=true;
				}
		}
		q.pop();
		if(q.empty())break;
		q.push(-1);
		dist++;
	}
			
}

void writeTest(){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			cout<<answer[i][j]<<" ";
		cout<<"\n";
	}
	
}
int main(){
	int t;
	cin>>t;
	while(t--){
		readTest();
		distance();
		writeTest();
	}
	cin>>t;
	return 0;
}

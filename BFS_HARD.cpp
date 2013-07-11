/*
  Autor: 		Krzysztof Jamroz
	Zadanie:	spoj.sphere.com - zadanie 212
*/


#include <iostream>
#include <queue>
#include <set>


using namespace std;

int n,m;
int cubes[100][100];
bool visit[100][100];
long long answer;
pair<int,int> p;
set<pair<int,int> >q;
set<pair<int,int> >::iterator it;

int x[4]={-1,1,0,0};
int y[4]={0,0,-1,1};


void readTest(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
				cin>>cubes[i][j];
	}
}

inline bool inside(int a, int b){
	if(a< 0 || a>=m)return false;
	if(b< 0 || b>=n)return false;
	return true;
}

void water(){
	answer=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			visit[i][j]=false;
	for(int i=0;i<n;i++){
		p.first=cubes[i][0];
		p.second=i*m;
		q.insert(p);
		visit[i][0]=true;
		p.first=cubes[i][m-1];
		p.second=i*m+m-1;
		q.insert(p);
		visit[i][m-1]=true;
	}
	for(int i=1;i<m-1;i++){
		p.first=cubes[0][i];
		p.second=i;
		q.insert(p);
		visit[0][i]=true;
		p.first=cubes[n-1][i];
		p.second=(n-1)*m+i;
		q.insert(p);
		visit[n-1][i]=true;
	}
	int xx,yy,h;
	while(!q.empty()){
		it=q.begin();
		q.erase(it);
		h=(*it).first;
		xx=(*it).second%m;
		yy=(*it).second/m;
		for(int i=0;i<4;i++)
			if(inside(xx+x[i],yy+y[i]) && !visit[yy+y[i]][xx+x[i]]){
				visit[yy+y[i]][xx+x[i]]=true;
				if(cubes[yy+y[i]][xx+x[i]]<=h){
					answer+=(h-cubes[yy+y[i]][xx+x[i]]);
					cubes[yy+y[i]][xx+x[i]]=h;
				}
				p.first=cubes[yy+y[i]][xx+x[i]];
				p.second=(yy+y[i])*m+xx+x[i];
				q.insert(p);
			}
	}
}

void writeTest(){
	cout<<answer<<"\n";
}


int main(){
	int t;
	cin>>t;
	while(t--){
		readTest();
		water();
		writeTest();
	}
	cin>>t;
	return 0;
}

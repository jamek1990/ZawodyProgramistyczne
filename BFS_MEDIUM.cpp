/*
  Autor: 		Krzysztof Jamroz
	Zadanie:	spoj.sphere.com - zadanie 135
*/


#include <iostream>
#include <queue>
#include <set>


using namespace std;

int n;
int road[30][30];
int period[30][30];
bool visit [6000][30][30];
long long tim;
pair<int,int> p;


int x[5]={-1,1,0,0,0};
int y[5]={0,0,-1,1,0};


void readTest(){
	cin>>n;
	string s;
	for(int i=0;i<n;i++){
		cin>>s;
		for(int j=0;j<n;j++)
			if(s[j]=='.')
				road[i][j]=0;
			else
				road[i][j]=1;	
	}
	for(int i=0;i<n;i++){
		cin>>s;
		for(int j=0;j<n;j++)
			period[i][j]=(int)s[j]-48;
	}
}

inline bool inside(int a, int b){
	if(a< 0 || a>=n)return false;
	if(b< 0 || b>=n)return false;
	return true;
}

void timeToWork(){
	tim=0;
	queue<pair<int,int> >q;
	for(int t=0;t<n*n*9;t++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				visit[t][i][j]=false;
	p.first=0;
	p.second=0;
	q.push(p);
	int xx,yy;
	while(!q.empty()){
		p=q.front();
		q.pop();
		xx=p.second%n;
		yy=p.second/n;
		tim=p.first+1;
		if(tim>n*n*9+1){tim=0;break;
		}
		if(xx==n-1 && yy==n-1)break;
		for(int i=0;i<5;i++)
			if(inside(xx+x[i],yy+y[i]) && !visit[tim][yy+y[i]][xx+x[i]])
				if (!(road[yy+y[i]][xx+x[i]]==1 && period[yy+y[i]][xx+x[i]]==0)
					&&((road[yy+y[i]][xx+x[i]]==0 && period[yy+y[i]][xx+x[i]]==0)
						||((tim/period[yy+y[i]][xx+x[i]])%2==road[yy+y[i]][xx+x[i]]))){
						
					visit[tim][yy+y[i]][xx+x[i]]=true;
					p.first=tim;
					p.second=(yy+y[i])*n+xx+x[i];
					q.push(p);
				}
		if(q.empty())tim=0;
	}
}


void writeTest(){
	if(tim)
		cout<<tim-1<<"\n";
	else
		cout<<"NO\n";
}


int main(){
	int t;
	cin>>t;
	while(t--){
		readTest();
		timeToWork();
		writeTest();
	}
	cin>>t;
	return 0;
}

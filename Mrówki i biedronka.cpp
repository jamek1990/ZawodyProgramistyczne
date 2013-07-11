#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N,K,L;
vector<int> G[5001];
queue<int>q;
bool visit[5001];
int ant[5001];
bool antV[5001];
int tree[5001];
int kill[5001];


void writeTest(){
  for(int i=1;i<=K;i++)
		cout<<ant[i]<<" "<<kill[i]<<"\n";
}

void buildTree(){
	for(int i=1;i<=N;i++)
		visit[i]=false;
	visit[1]=true;
	tree[1]=-1;
	q.push(1);
	while(!q.empty()){
		int y=q.front();
		q.pop();
		for(int i=0;i<G[y].size();i++)
			if(!visit[G[y][i]]){
				visit[G[y][i]]=true;
				tree[G[y][i]]=y;
				q.push(G[y][i]);
			}
	}

}

void moveRoot(int x){
	int z;
	int y=tree[x];
	tree[x]=-1;
	while(y!=-1){
		z=y;
		y=tree[y];
		tree[z]=x;
		x=z;
	}
}

bool onAnts(int x){
	for(int k=1;k<=K;k++)
		if(ant[k]==x){
			kill[k]++;
			return true;
		}
	return false;	
}

void tagVertex(int x){
	q.push(x);
	while(!q.empty()){
		int y = q.front();
		q.pop();
		for(int i=0;i<G[y].size();i++)
			if(!visit[G[y][i]] && G[y][i]!=tree[y]){
				visit[G[y][i]]=true;
				q.push(G[y][i]);
			}
	}
}

void ladybugSet(int x){
	if(onAnts(x))return;
	moveRoot(x);
	for(int i=1;i<=N;i++)
		visit[i]=false;
	for(int i=1;i<=K;i++)
		tagVertex(ant[i]);
	int ok = false;
	while(true){
		for(int i=1;i<=K;i++){
			if(!visit[ant[i]] && !antV[tree[ant[i]]]){
				antV[ant[i]]=false;
				ant[i]=tree[ant[i]];
				antV[ant[i]]=true;
				if(ant[i]==x){kill[i]++;ok=true;}
			}
		}
		if(ok)break;
		for(int i=1;i<=K;i++)
			tagVertex(ant[i]);
	}
}

void readTree(){
	int a,b;
 	cin>>N;
	for(int i=0;i<N-1;i++){  
		cin>>a>>b; 
		G[a].push_back(b);
		G[b].push_back(a);
  	}
  	buildTree();
}

void readAnts(){
	cin>>K;
  	for(int i=1;i<=K;i++){
  		cin>>ant[i];
  		antV[ant[i]]=true;
  	}
}

void readLadybug(){
	int x;
	cin>>L;
	while(L--){
		cin>>x;
		ladybugSet(x);
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	readTree();
	readAnts();
	readLadybug();
	writeTest();
   return 0;
}

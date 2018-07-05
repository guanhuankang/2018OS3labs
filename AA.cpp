#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 1000
#define lc (root<<1)
#define rc ((root<<1)+1)
#define INF 1000000000
/*
status : 0 END 1 Ready 2 Running
*/
typedef struct pcb{
	int time;
	int nice;
	int status;
	int name;
	friend bool operator < (struct pcb A,struct pcb B){
		return A.nice < B.nice;
	}
} PCB;

typedef struct node{
	int l,r;
	int index;
} Node;

Node tree[MAXN<<2];
PCB pcb[MAXN];
int n;

void build(int l,int r,int root){
	//cout<<l<<" "<<r<<" "<<root<<endl;
	tree[root].l = l;
	tree[root].r = r;
	if(l==r){
		tree[root].index = l;
		return;
	}
	int mid = (l+r)/2;
	build(l,mid,lc);
	build(mid+1,r,rc);
	if(pcb[tree[lc].index].nice<pcb[tree[rc].index].nice){
		tree[root].index = tree[rc].index;
	}else{
		tree[root].index = tree[lc].index;
	}
	return;
}

void update(int x,int nice,int time,int root){
	int l = tree[root].l;
	int r = tree[root].r;
	if(l==r){
		tree[root].index = x;
		pcb[x].nice = nice;
		pcb[x].time = time;
		return;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		update(x,nice,time,lc);
	}else{
		update(x,nice,time,rc);
	}
	if(pcb[tree[lc].index].nice>pcb[tree[rc].index].nice){
		tree[root].index = tree[lc].index;
	}else{
		tree[root].index = tree[rc].index;
	}
	return;
}

int query(int l,int r,int root){
	if(l==tree[root].l&&r==tree[root].r){
		return tree[root].index;
	}
	int _l = tree[root].l;
	int _r = tree[root].r;
	int _mid = (l+r)/2;
	if(r<=_mid){
		return query(l,r,lc);
	}
	if(l>_mid){
		return query(l,r,rc);
	}
	int lcnice = query(l,_mid,lc);
	int rcnice = query(_mid+1,r,rc);
	if(pcb[lcnice].nice>pcb[rcnice].nice){
		return lcnice;
	}else{
		return rcnice;
	}
	return -1;
}

int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	cin>>n;
	int nice,time,name;
	for(int i=1;i<=n;i++){
		cin>>name>>nice>>time;
		pcb[i].nice = nice;
		pcb[i].time = time;
		pcb[i].status = 1;
		pcb[i].name = i;
	}
	build(1,n,1);
	int index = query(1,n,1);
	while(pcb[index].nice != -INF){
		nice = pcb[index].nice;
		time = pcb[index].time;
		cout<<"Name:"<<pcb[index].name<<" Nice:"<<nice<<" Time:"<<time<<endl;
		if(time-1==0){
			update(index,-INF,time-1,1);
		}else{
			update(index,nice-1,time-1,1);
		}
		index = query(1,n,1);
	}
	return 0;
}
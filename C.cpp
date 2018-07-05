#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
#define C 8
#define T 2
#define R 4
#define Csize 8
#define Tsize 4
#define Rsize 1

char disk[64];
char cmd[1000];
int fc;
bool strequ(char* s,string m){
	int i=0;
	while(s[i]==m[i]&&m[i]!=0){
		i++;
	}
	return s[i]==m[i];
}

void allocate(int size){
	if(fc<size){
		cout<<"Memory Limit Error"<<endl;
		return;
	}
	if(size<=0)return;
	for(int c=0;c<C;c++){
		for(int t=0;t<T;t++){
			for(int r=0;r<R;r++){
				if(disk[c*Csize+t*Tsize+r*Rsize]==0){
					disk[c*Csize+t*Tsize+r*Rsize] = 1;
					printf("(allocate)  cylinder:%d track:%d record:%d\n", c,t,r);
					fc--;
					allocate(size-1);
					return;
				}
			}
		}
	}
	cout<<"Memory Limit Error"<<endl;
}

void kfree(int cylinder,int track,int record){
	if(disk[cylinder*Csize+track*Tsize+record*Rsize]==1){
		disk[cylinder*Csize+track*Tsize+record*Rsize] = 0;
		fc++;
		printf("(free)  cylinder:%d track:%d record:%d\n", cylinder,track,record);
	}else{
		cout<<"free fail!"<<endl;
	}
}

void query(){
	for(int i=0;i<C;i++){
		for(int j=0;j<Csize;j++){
			printf("%d", disk[i*Csize+j]);
		}
		printf("\n");
	}
	cout<<endl;
}

int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);

	memset(disk,0,sizeof(disk));
	int cylinder,track,record;
	int cas  = 1;
	fc = 64;
	while(scanf("%s",cmd)!=EOF && strequ(cmd,"exit")==false){
		if(strequ(cmd,"allocate")){
			printf("%d\n", cas++);
			int size;
			cin>>size;
			allocate(size);
			printf("--------------------------------------------------\n");
		}else if(strequ(cmd,"free")){
			cin>>cylinder>>track>>record;
			printf("%d\n", cas++);
			kfree(cylinder,track,record);
			printf("--------------------------------------------------\n");
		}else if(strequ(cmd,"query")){
			printf("%d\n", cas++);
			query();
			printf("--------------------------------------------------\n");
		}else{
			cout<<"Error"<<endl;
			//exit(1);
		}
	}
	return 0;
}
/*
allocate 5
query
free 0 0 0
query
allocate 1
query
allocate 10
query
allocate 60
query

*/
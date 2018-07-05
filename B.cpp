#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

typedef struct block{
	int addr,len;
	int name,status;
	struct block *next,*last;
} Block;

typedef struct pro{
	int addr,len;
	int valid;
	Block* bk;
} PRO;
void query();
char cmd[100];
Block *Head;
map<int,PRO> RPRO;

bool strequ(char* s,string m){
	int i=0;
	while(s[i]==m[i]&&m[i]!=0){
		i++;
	}
	return s[i]==m[i];
}

Block* FirstFit(int name,int size){
	Block* cbk = Head;
	while(cbk){
		if(cbk->status==0&&cbk->len>=size){
			cbk->name = name;
			cbk->status = 1;
			if(cbk->len==size)return cbk;
			Block* nbk = (Block*)malloc(sizeof(Block));
			nbk->len = cbk->len - size;
			nbk->addr = cbk->addr + size;
			nbk->status = 0;
			nbk->last = cbk;
			nbk->next = cbk->next;
			if(cbk->next)cbk->next->last = nbk;
			cbk->len = size;
			cbk->next = nbk;
			return cbk;
		}
		cbk = cbk->next;
	}
	return NULL;
}

void allocate(){
	int name,size;
	cin>>name>>size;
	if(RPRO[name].valid==1){
		printf("Fail to run Program %d. It has ran at Addr:%d Size:%d", \
			name,RPRO[name].addr,RPRO[name].len);
		return;
	}
	Block* bk = FirstFit(name,size);
	if(bk==NULL){
		printf("Fail to run Program %d. Memory Limit Error!",name);
		return;
	}
	RPRO[name].addr = bk->addr;
	RPRO[name].len = bk->len;
	RPRO[name].valid = 1;
	RPRO[name].bk = bk;
	printf("Run program %d successfully! Run at Addr:%d Size:%d",name,bk->addr,bk->len);
	return;
}

void freep(){
	int name;
	cin>>name;
	cout<<"Name:"<<name<<endl;
	if(RPRO[name].valid==0){
		printf("Can't find program %d. Free fail!", name);
		return;
	}
	RPRO[name].valid = 0;
	Block* bk = RPRO[name].bk;
	bk->status = 0;
	printf("Free program %d successfully!(Addr:%d Size:%d)", name,bk->addr,bk->len);
	//cout<<"***"<<bk->name<<endl;
	if(bk->last!=NULL && bk->last->status==0){
		//cout<<"###"<<bk->last->name<<endl;
		bk->last->len += bk->len;
		bk->last->next = bk->next;
		if(bk->next!=NULL)bk->next->last = bk->last;
		Block *tmp = bk->last;
		free(bk);
		bk = tmp;
	}
	if(bk->name==2)cout<<"Helo"<<endl;
	if(bk->next && bk->next->status==0){
		bk->len += bk->next->len;
		Block* tmp = bk->next;
		if(bk->next->next)bk->next->next->last = bk;
		bk->next = bk->next->next;
		free(tmp);
	}
	return;
}

void queryp(){
	int name;
	cin>>name;
	if(RPRO[name].valid==0){
		printf("Can't find program %d. Query fail!", name);
		return;		
	}
	printf("Program %d run at Addr:%d Size:%d",name, RPRO[name].addr,RPRO[name].len);
	return;
}

void query(){
	int num = 0;
	Block* bk = Head;
	while(bk){
		printf("Block Num:%d\t", num++);
		printf("Addr:%d Size:%d Status:%d Program:%d\n",\
			bk->addr,bk->len,bk->status,bk->name);
		bk = bk->next;
	}
	return;
}

int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);

	Head = (Block*)malloc(sizeof(Block));
	Head->addr = 0;
	Head->len = 128*1024;
	Head->status = 0;
	Head->next = Head->last = NULL;

	int cas = 1;
	while(scanf("%s",cmd)!=EOF && strequ(cmd,"exit")==false){
		if(strequ(cmd,"allocate")){
			printf("%d  | ", cas++);
			allocate();
			printf("\n------------------------------------------------------\n");
		}else if(strequ(cmd,"free")){
			printf("%d  | ", cas++);
			freep();
			printf("\n------------------------------------------------------\n");
		}else if(strequ(cmd,"queryprogram")){
			printf("%d  | ", cas++);
			queryp();
			printf("\n------------------------------------------------------\n");			
		}else if(strequ(cmd,"query")){
			printf("%d  | \n", cas++);
			query();
			printf("------------------------------------------------------\n");				
		}else{
			cout<<"Error"<<endl;
			//exit(1);
		}
	}
	return 0;
}
/*
allocate 1 10
allocate 2 20
allocate 3 30
allocate 4 40
allocate 5 1000000
query
free 2
query
free 1
query
free 3
query
free 4
query

*/
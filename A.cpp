#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
/*
status : 0 END 1 Ready 2 Running
*/
typedef struct pcb{
	int time;
	int nice;
	int status;
	int name;
	struct pcb *next;
	friend bool operator < (struct pcb A,struct pcb B){
		return A.nice < B.nice;
	}
} PCB;

priority_queue<PCB> pcbq;
vector<PCB> finishq;

void Disp(int t){
	if(pcbq.empty()){
		cout<<"Time "<<t<<endl;
		printf("Finish queue: ");
		for(int i=0;i<finishq.size();i++){
			printf("%d ", finishq[i].name);
		}
		printf("\n");
		cout<<"----------------------------------------------------------------\n"<<endl;
		return;
	}
	priority_queue<PCB> tmp;
	PCB cur = pcbq.top();
	pcbq.pop();
	tmp.push(cur);
	cout<<"Time "<<t<<endl;
	printf("PCB No.%d is running. It's nice is %d, and it need %d (time) to finish.\n", cur.name,cur.nice,cur.time);	
	printf("Ready queue: ");
	while(!pcbq.empty()){
		cur = pcbq.top();
		pcbq.pop();
		tmp.push(cur);
		printf("%d(%d) ", cur.name, cur.nice);
	}
	printf("\n");
	printf("Finish queue: ");
	for(int i=0;i<finishq.size();i++){
		printf("%d ", finishq[i].name);
	}
	printf("\n");
	while(!tmp.empty()){
		pcbq.push(tmp.top());
		tmp.pop();
	}
	cout<<"----------------------------------------------------------------\n"<<endl;
	return;
}

int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);

	int n;
	int name;
	int nice,time;

	cin>>n;
	while(n--){
		cin>>name>>nice>>time;
		PCB pcb;
		pcb.name = name;
		pcb.time = time;
		pcb.nice = nice;
		pcb.status = 1;
		pcb.next = NULL;
		pcbq.push(pcb);
	}

	int t = 0;
	PCB cur;
	while(pcbq.empty()==false){
		Disp(t++);
		cur = pcbq.top();
		pcbq.pop();
		cur.time--;
		cur.nice--;
		if(cur.time==0){
			cur.status = 0;
			finishq.push_back(cur);
		}else{
			pcbq.push(cur);
		}
	}
	Disp(t++);
	cout<<"\nFinish--A"<<endl;
	return 0;
}

/*
3
1 4 2
2 2 2
3 6 3
//cin>>name>>nice>>time;
*/
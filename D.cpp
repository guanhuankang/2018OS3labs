#include <sys/types.h>
#include <unistd.h>
#include <cstdio>

using namespace std;

void child(){
	sleep(1);
	for(int i=0;i<10000;i++){;;;}
}

void parent(){
	sleep(2);
	for(int i=0;i<10000;i++){;;;}
}

int main(){
	freopen("1.out","w",stdout);
	pid_t pid;
	pid = fork();
	if(pid==0){
		printf("I am a child!PID:%d\n",getpid());
		child();
	}else if(pid>0){
		printf("I am parent!PID:%d\n",getpid());
		parent();
	}else{
		printf("ERROR\n");
	}
	return 0;	
}
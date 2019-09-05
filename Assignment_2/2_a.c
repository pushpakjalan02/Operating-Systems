#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void handler(int sig){

	printf("\n");

	int stat;
	int pid = fork();
	if(pid == 0){
		printf("Child:\n");
	}
	else{
		wait(&stat);
		printf("Parent:\n");
	}
	printf("%d\n", getpid());
	printf("%d\n", getppid());
	exit(0);
}

int main(int argc, char* argv[]){
	signal(SIGINT, handler);
	while(1);
}

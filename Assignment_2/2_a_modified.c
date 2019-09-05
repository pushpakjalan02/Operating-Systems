#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void handler(int sig){

	printf("Signal ID: %d\n", sig);	
	exit(0);
}

int main(int argc, char* argv[]){
	signal(SIGINT, handler);
	printf("Hey! My Process ID is: %d\n", getpid());
	while(1);
}

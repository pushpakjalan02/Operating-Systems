#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>

int main(int argc, char *argv[]){
	pid_t pid = atoi(argv[1]);
	int sig = atoi(argv[2]);
	
	printf("Starting to kill\n");
	kill(pid, sig);
	printf("Killed PID: %d\n\n", pid);
}

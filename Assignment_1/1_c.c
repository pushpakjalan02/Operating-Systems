#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char* argv[]){
	int pid;
	int stat;
	if((pid = fork()) == 0){		
		if((pid = fork()) == 0){
			printf("\n\nInside Grandchild Process: \nRoll No: CSB17002\n");
			exit(1);
		}
		else{
			wait(&stat);
			printf("\n\nInside Child Process: \nPID: %d, PPID: %d\n", getpid(), getppid());
			printf("Exit Status of Grandchild: %d\n", WEXITSTATUS(stat));
			printf("Overlaying HelloWorld\n");
			char *argv[] = {"./HelloWorld", NULL};
			execv(argv[0], argv);

		}
	}
	else{
		wait(&stat);
		printf("\n\nInside Parent:\nProcess Id: \nChild Process Id:\nGrandChild Process Id: \n" );
		printf("Exit Status of Child: %d\n", WEXITSTATUS(stat));
		exit(0);
	}
}
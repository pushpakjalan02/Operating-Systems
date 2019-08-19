#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<utmp.h>

int main(int argc, char* argv[]){
	int pid;
	int stat;
	int count;
	struct utmp user;
	if((pid = fork()) == 0){		
		count++;		
		if((pid = fork()) == 0){
			count++;			
			printf("\n\nInside Grandchild Process: \nRoll No: CSB17002\n");
			FILE *fp = fopen("1_a.txt", "w");		
			fprintf(fp, "GrandChild PID: %d\n", getpid());	
			fprintf(fp, "\nCount of Processes: %d\n", count);			
			fclose(fp);
			exit(1);
		}
		else{
			wait(&stat);
			printf("\n\nInside Child Process: \nPID: %d, PPID: %d\n", getpid(), getppid());
			printf("Exit Status of Grandchild: %d\n", WEXITSTATUS(stat));
			exit(0);
		}
	}
	else{
		wait(&stat);
		char buffer[100];
		FILE *fp = fopen("1_a.txt", "r");	
		printf("\n\nInside Parent:\nProcess Id: %d\nChild Process Id: %d\n", getpid(), pid );
		while(fgets(buffer, 100, fp) != NULL)
			printf("%s", buffer);	
		printf("Exit Status of Child: %d\n", WEXITSTATUS(stat));
		exit(0);
	}
}

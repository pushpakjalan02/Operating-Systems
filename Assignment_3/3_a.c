#include<stdio.h>  
#include<stdlib.h> // For exit(0) 
#include<signal.h> // For using signal()
#include<unistd.h> // For using fork()
#include<sys/wait.h>

void childprocess(int p[2]){

	printf("\n\nInside Child:\n\n");

	int *no = (int*)malloc(sizeof(int));

	pid_t pid_child = getpid();
	write(p[1], &pid_child, sizeof(pid_t));

	printf("Enter No. of terms: ");
	scanf("%d", no);
	write(p[1], no, sizeof(int));

	int a = 0, b = 1, i;
	write(p[1], &a, sizeof(int));
	write(p[1], &b, sizeof(int));

	for(i = 3; i <= *no; i++){
		int temp = a + b;	
		write(p[1], &temp, sizeof(int));
		a = b;
		b = temp;
	}
}

void parentprocess(int p[2]){

	printf("\nInside Parent:\n\n");

	pid_t pid_child;
	read(p[0], &pid_child, sizeof(pid_t));
	printf("Child Process ID: %d\n\n", pid_child);

	int* no = (int*)malloc(sizeof(int));
	read(p[0], no, sizeof(int));

	while(*no > 0){
		int* temp = (int*) malloc(sizeof(int));
		read(p[0], temp, sizeof(int));
		printf("%d\n", *temp);		
		(*no)--;
	}

	int signal;
	read(p[0], &signal, sizeof(int));
	printf("\nSignal ID for which handler function has been genereated: %d\n", signal);

}

void handler(int sig){

	int p[2];
	if(pipe(p) < 0){
		exit(0);
	}

	int pid = fork();
	if(pid == 0){
		childprocess(p);
		write(p[1], &sig, sizeof(int));	
	}
	else{
		int stat;
		wait(&stat);
		parentprocess(p);
		printf("\nTerminated\n\n");
	}
	exit(0);
}

int main(int argc, char *argv[]){
	signal(SIGINT, handler);
	while(1);
}

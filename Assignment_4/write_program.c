#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>

int file_descriptor;

void handler_function(int sig){
	close(file_descriptor);
	exit(0);
}

int main(int argc, char* argv[]){
	signal(SIGINT, handler_function);

	char *pathname = "mnode";
	char buffer[1000];

	mknod(pathname, 0777|S_IFIFO, 0);

	file_descriptor = open(pathname,  O_WRONLY | O_NONBLOCK);

	while(1){

		memset(buffer, 0x0, sizeof(buffer));
		
		printf("Enter String:\n");	
		scanf("%[^\n]%*c", buffer);
		buffer[strlen(buffer)] = '\n';
		buffer[strlen(buffer)+1] = '\0';
		
		write(file_descriptor, (void*) buffer, (size_t)strlen(buffer)+2);			
	}
}

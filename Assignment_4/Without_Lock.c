#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>

int file_descriptor;

void signal_handler(int sig){
	close(file_descriptor);
	exit(0);
}

int main(int argc, char* argv[]){
	char *pathname = "mnode";

	file_descriptor = open(pathname, O_RDWR);

	signal(SIGINT, signal_handler);

	char buffer[100];

	while(1){
		memset(buffer, 0x0, sizeof(buffer));
		int no_bytes = read(file_descriptor, (void*)buffer, (size_t)sizeof(buffer));
		int current = 0;
		while(current < no_bytes){
			printf("%s", &buffer[current]);
			current += strlen(&buffer[current]) + 2;
		}
	}
}

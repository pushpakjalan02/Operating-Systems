#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int file_descriptor;

void signal_handler(int sig){
	close(file_descriptor);
	return;
}

int main(int argc, char* argv[]){
	char *pathname = "mynode";

	file_descriptor = open(pathname, O_RDWR);

	signal(SIGINT, signal_handler);

	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	fcntl(file_descriptor, F_SETLK, &lock);

	while(1){
		char buffer[100];
		read(file_descriptor, (void*)buffer, (size_t)sizeof(buffer));
		printf("%s\n\nPress Enter for Next\n",buffer);
		scanf("%*[\n]");
	}
}

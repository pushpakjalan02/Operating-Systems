#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[]){
	char *pathname = "mynode";
	char buffer[1000];
	int file_descriptor;	

	mknod(pathname, 0777 | S_IFIFO, 0);
	
	file_descriptor = open(pathname, O_RDWR);

	sleep(15);

	read(file_descriptor, (void*)buffer, (size_t)sizeof(buffer));
	printf("Received Data: %s\n", buffer);
	
	strcpy(buffer,"Done");

	write(file_descriptor, (const void*)buffer, (size_t)strlen(buffer)+1);

	close(file_descriptor);

	return 0;
}

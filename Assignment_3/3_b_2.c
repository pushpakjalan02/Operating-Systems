#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[]){
	char *pathname = "mynode";
	int file_descriptor;

	file_descriptor = open(pathname, O_RDWR);

	char buffer[1000];
	printf("Enter String:\n");	
	scanf("%[^\n]", buffer);

	write(file_descriptor, (const void*)buffer, (size_t)strlen(buffer)+1);

	sleep(15);

	read(file_descriptor, (void*)buffer, (size_t)sizeof(buffer));

	printf("Acknowledgement: %s\n", buffer);

	close(file_descriptor);

	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* print(void* arg){
	printf("%s\n", (char*) arg);
	int *ptr = (int*)malloc(sizeof(int));
	*ptr = 105;
	pthread_exit((void*)ptr);
}

int main(int argc, char* argv[]){
	pthread_t thread_id;
	void *ptr;
	pthread_create(&thread_id, NULL, print, "Hello, World!");
	pthread_join(thread_id, &ptr);
	printf("Returned Value: %d\nTerminated\n", *((int*)ptr));
}

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int main(int argc, char* argv[]){
	key_t key;
	int sem_set_identifier;

	key = ftok("/home/pushpakjalan/Desktop/OS/Assignment_7/file.txt", 1);
	sem_set_identifier = semget(key, 1, 0666 | IPC_CREAT);
}
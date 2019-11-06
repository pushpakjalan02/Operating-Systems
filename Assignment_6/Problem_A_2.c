#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

struct shm{
	int pid;
};

int main(){
	struct shm* sh_mem;
	key_t key;
	int shm_id;

	key = ftok("/home/pushpakjalan/Desktop/OS/Assignment_6/a_1.txt", 'A');
	shm_id = shmget(key, 100, 0);
	sh_mem = shmat(shm_id, NULL, 0);
	
	printf("Process ID of Sibling: %d\n", sh_mem -> pid);

	shmdt(sh_mem);

	printf("Terminated\n");
}
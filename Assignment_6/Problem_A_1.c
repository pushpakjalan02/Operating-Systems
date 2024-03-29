#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
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
	shm_id = shmget(key, 100, 0777 | IPC_CREAT);
	sh_mem = shmat(shm_id, NULL, 0);
	
	printf("Hello, World!, My PID is: %d\n", getpid());
	sh_mem -> pid = getpid();

	shmdt(sh_mem);

	sleep(10);

	shmctl(shm_id, IPC_RMID, NULL);

	printf("Terminated\n");
}
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *__buf;
};

void wait_operation(int sem_set_identifier){
	struct sembuf sops[2];

	sops[0].sem_num = 0;
	sops[0].sem_op = 0;
	sops[0].sem_flg = 0;

	sops[1].sem_num = 0;
	sops[1].sem_op = 1;
	sops[1].sem_flg = 0;

	if(semop(sem_set_identifier, sops, 2) == -1){
		perror("semop() error");
		exit(1);
	}

	return;
}

void signal_operation(int sem_set_identifier){
	struct sembuf sops[1];

	sops[0].sem_num = 0;
	sops[0].sem_op = -1;
	sops[0].sem_flg = 0;

	if(semop(sem_set_identifier, sops, 1) == -1){
		perror("semop() error");
		exit(1);
	}

	return;
}

int main(int argc, char* argv[]){
	key_t key;
	int sem_set_identifier;
	int count = 1;

	key = ftok("/home/pushpakjalan/Desktop/OS/Assignment_7/file.txt", 1);
	sem_set_identifier = semget(key, 1, 0666 | 0);

	sleep(5);

	while(1){

		wait_operation(sem_set_identifier);

		FILE *fp = fopen("file.txt","r");
		char buffer[1000];
		fgets(buffer, 1000, fp);
		printf("%d. %s\n", count, buffer);
		count++;
		
		signal_operation(sem_set_identifier);

	}

}

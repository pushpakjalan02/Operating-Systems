#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>

struct my_msg{
	long type;
	char message[100];
};

int main(int argc, char* argv[]){
	key_t key = ftok("myfile", 70);
	if(key == -1){
		printf("Error\n");
		exit(0);	
	}
	int msg_q_identifier = msgget(key, IPC_CREAT | 0666);
	if(msg_q_identifier == -1){
		printf("Error\n");
		exit(0);
	}
	struct my_msg m_send;

	msgrcv(msg_q_identifier, (void*)&m_send, sizeof(m_send.message), 1, 0);

	printf("Received: %s\n", m_send.message);
	printf("Thanks for using.\n\n");
}

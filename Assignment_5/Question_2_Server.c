#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_CLIENT 5
#define MAX_MSG_LEN 1000

void* process_connection(void* new_serv_sock){
	int sock = *((int*)new_serv_sock);	

	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	getpeername(sock, (struct sockaddr *) &addr, &addr_size);

	char buffer[1000];
	char client_addr[100];
	memset(buffer, 0x0, sizeof(buffer));		
	memset(client_addr, 0x0, sizeof(client_addr));	
	strcpy(client_addr, inet_ntoa(addr.sin_addr));
	
	recv(sock, (void*)buffer, (size_t)sizeof(buffer), 0);	
	
	send(sock, (const void*)client_addr, (size_t)strlen(client_addr)+1, 0);	
	sleep(2);
	send(sock, (const void*)buffer, (size_t)strlen(buffer)+1, 0);

	close(sock);
}

int main(int argc, char* argv[]){

	int serv_sock, new_serv_sock;
	
	int client_addr_len, recv_data_len;

	if(argc < 3){
		printf("usage: %s <IP Address> <Port>", argv[0]);
		exit(1);
	}

	struct sockaddr_in client_addr, server_addr;
	char buffer[MAX_MSG_LEN];
	
	bzero((char*)&server_addr, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0){
		perror("Cannot open socket\n");
		exit(1);
	}

	if(bind(serv_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
		perror("Cannot Bind Port");
		exit(1);
	}

	listen(serv_sock, MAX_CLIENT);

	while(1){
		client_addr_len = sizeof(client_addr);
		new_serv_sock = accept(serv_sock, (struct sockaddr *) &client_addr, &client_addr_len);

		pthread_t thread_id;
		pthread_create(&thread_id, NULL, process_connection, (void*)&new_serv_sock);
	}
}



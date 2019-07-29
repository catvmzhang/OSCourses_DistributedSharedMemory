#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int socketfd;
	char serverIP[] = "172.31.43.21";

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1){
		printf("Create socket fail !\n");
		return 0;
	}

	int nRecvBuf = 32*1024;
	setsockopt(socketfd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf,sizeof(int));
	
	struct sockaddr_in serverInfo;
	bzero(&serverInfo, sizeof(serverInfo));
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr.s_addr = inet_addr(serverIP);
	serverInfo.sin_port = htons(8700);

	if( connect(socketfd, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == -1){
		printf("Connection error\n");
		return 0;
	}

	char msg[] = "draw 1000000";
	char inputBuffer[64] = {};
	send(socketfd, msg, sizeof(msg), 0);
	//for(int i=0;i<10;i++){
	for(;;){
		int status = recv(socketfd, inputBuffer, sizeof(inputBuffer), 0);
		if(status == -1){
			printf(" Receive fail! \n");
		}
		printf("%s \n",inputBuffer);
		memset(inputBuffer, '\0', sizeof(inputBuffer));
	}

	close(socketfd);

	return 0;
}

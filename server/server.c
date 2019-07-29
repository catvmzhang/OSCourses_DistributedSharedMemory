#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include "def.h"

#define MAX_LIST_NUM 10000000
#define MAX_SOCKET_QUEUE_NUM 100
#if (DEBUG)
	#define LOGD(...) printf(__VA_ARGS__)
#else
	#define LOGD(...)
#endif

struct list_d *list;

void* getNum(void* param){
	int fd = ((struct param_d*)param)->fd;
	int times = ((struct param_d*)param)->times;
	char buf[64];
	memset(buf, '\0', sizeof(buf));

	for(int i=0;i<times;i++){
		int num = list->atomic_pop(list);
		sprintf(buf, "%d", num);
		send(fd, buf, sizeof(buf), 0);
		LOGD("send to: %d [%d]: %s \n", fd, i, buf);
		memset(buf, '\0', sizeof(buf));
	}

	free((struct param_d*)param);
	pthread_exit(NULL);
}

int main()
{
	int socketfd, clientSocketfd;
	char inputBuffer[256] = {};
	char msg[] = "message from server !\n";

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1){
		printf("Create socket fail ! \n");
		return 0;
	}

	struct sockaddr_in serverInfo, clientInfo;
	int addrlen = sizeof(clientInfo);
	bzero(&serverInfo, sizeof(serverInfo));

	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(8700);
	bind(socketfd, (struct sockaddr*)&serverInfo, sizeof(serverInfo));
	listen(socketfd, MAX_SOCKET_QUEUE_NUM);

	listInit(&list, MAX_LIST_NUM);

	while(1){
		clientSocketfd = accept(socketfd, (struct sockaddr*)&clientInfo, &addrlen);
		recv(clientSocketfd, inputBuffer, sizeof(inputBuffer), 0);
	
		struct param_d *param = (struct param_d*)malloc(sizeof(struct param_d));	
		sscanf(inputBuffer, "%*s %d", &param->times);
		param->fd = clientSocketfd;

		LOGD("Get: '%s' form fileDescriptor:%d times:%d\n", inputBuffer, clientSocketfd,param->times);
		pthread_t thread;
		pthread_create(&thread, NULL, getNum, (void*)param);
	}

	return 0;
}

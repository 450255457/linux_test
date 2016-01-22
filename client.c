/*****************************************
> File Name : client.c
> Description : g++ -g -o Client client.c
> Author : linden
> Date : 2015-10-29
*******************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

#define MAX_FILE_SIZE 65535
#define MAX_SIZE 1024

typedef struct SOCKET_LIST
{
	int client_socket;
	struct SOCKET_LIST * next;
}Node;

int add(Node **root,int value)
{
	Node *node=NULL;
	node=(Node *)malloc(sizeof(Node));
	if(!node)
		return 0;
	if(*root)
	{
		node->client_socket=value;
		node->next=*root;
		*root=node;
	}
	else
	{
		node->client_socket=value;
		node->next=NULL;
		*root=node;
	}
	return 1;
}

int setfilesize();

int main(int argc,char **argv)
{
	if(argc!=4)
	{
		printf("./cmd ip port num\n");
		exit(1);
	}
	setfilesize();
	extern int errno;
	int client_socket;
	struct sockaddr_in server_addr;
	socklen_t length=sizeof(struct sockaddr_in);
	bzero(&server_addr,length);
	server_addr.sin_family=AF_INET;
	if(inet_aton(argv[1],&server_addr.sin_addr)==0)
	{
		printf("IP Address is error:%s",strerror(errno));
		exit(1);
	}
	server_addr.sin_port=htons(atoi(argv[2]));
	int count=atoi(argv[3]);
	Node *head,*pos;
	for(;count>0;count--)
	{
		if((client_socket=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			printf("create client_socket failed:%s\n",strerror(errno));
			exit(1);
		}
		add(&head,client_socket);
	}
	int iscon=0;
	while(1)
	{
		char data[MAX_SIZE] = { 0 };
		char recvbuff[MAX_SIZE] = {0};
		int i=atoi(argv[3]);
		struct timeval start,end;
		gettimeofday(&start,NULL);
		int count=0;
		for(pos=head;i>0;pos=pos->next,i--)
		{
			client_socket=pos->client_socket;
			if(iscon==0)
			{
				if(connect(client_socket,(struct sockaddr*)&server_addr,length)<0)
				{
					printf("connect failed:%s\n",strerror(errno));
					exit(1);
				}
			}
			sprintf(data,"Hello World,%d",count++);
			if(send(client_socket,data,strlen(data),0)<0)
			{	
				printf("send data failed:%s\n",strerror(errno));
				exit(1);
			}
			printf("send success:%d, send_buff:%s\n", client_socket, data);
			if (recv(client_socket, recvbuff, MAX_SIZE,0) < 0)
			{
				printf("recv data failed:%s\n", strerror(errno));
				exit(1);
			}
			printf("recv success:%d, recv_buff:%s\n", client_socket, recvbuff);
			usleep(10);
		}
		gettimeofday(&end,NULL);
		double sec=(int)(end.tv_sec-start.tv_sec);
		double usec=(int)(end.tv_usec-start.tv_usec);
		if(usec<0)
		{
			sec--;
			usec+=1000000;
		}
		printf("used time:%fs\n",sec+usec/1000000);
		iscon=1;
		sleep(10);
	}
	return 0;
}

int setfilesize()
{
	struct rlimit rt;
	rt.rlim_max=rt.rlim_cur=MAX_FILE_SIZE;
	if(setrlimit(RLIMIT_NOFILE,&rt)==-1)
	{
		printf("set file size failed:%s\n",strerror(errno));
		return -1;
	}
	return 0;
}

/*****************************************
> File Name : tcp_server.h
> Description : tcp_server head file
	g++ -g -o TcpServer tcp_server.cpp thread_pool.cpp -lpthread
> Author : linden
> Date : 2015-10-13
*******************************************/

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <err.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

#include "locker.h"

#define IPADDRESS	"0.0.0.0"
#define SERVERPORT	8090
#define MAX_EVENT_NUMBER 10
#define BUFFER_SIZE 1024
#define CONNECTION_BACKLOG	5

class CTcpServer
{
public:
	CTcpServer();
	~CTcpServer();
	int socket_bind_listen(const char *ip,int nPort);
	int runServer(void);
	void reset_oneshot(int epollfd, int fd);
protected:

private:
	locker m_arglocker;	//传入队列的锁
};

CTcpServer::CTcpServer()
{
}

CTcpServer::~CTcpServer()
{
}
#endif

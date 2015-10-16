/*****************************************
> File Name : tcp_server.cpp
> Description : tcp_server
> Author : linden
> Date : 2015-10-13
*******************************************/

#include "tcp_server.h"
#include "thread_pool.h"

using namespace std;

CTcpServer Server;
CThreadPool thread_pool;

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

/*将fd上的EPOLLIN和EPOLLET事件注册到epollfd指示的epoll内核事件表中，参数oneshot指定是否注册fd上的EPOLLONESHOT事件*/
void addfd(int epollfd, int fd, bool oneshot)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	if (oneshot)
	{
		event.events |= EPOLLONESHOT;
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

void CTcpServer::reset_oneshot(int epollfd, int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

void* worker(void* arg)
{
	
}

int CTcpServer::socket_bind_listen(const char *ip,int nPort)
{
	int listen_fd;
	struct sockaddr_in server_addr;
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);	//protocol通常为0，表示按给定的域和套接字类型选择默认协议
	if (listen_fd == -1){
		cout << "Error->socket:" << strerror(errno) << endl;
		return -1;
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.s_addr = INADDR_ANY;
	//inet_pton将点分十进制IP转换为整数
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(nPort);

	//设置发送时限和接收时限
	struct timeval timeout = { 100, 0 };	//100s
	setsockopt(listen_fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(struct timeval));
	setsockopt(listen_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));

	//允许地址的立即重用	
	int opt = 1;
	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
		printf("Error->setsockopt:%s\n", strerror(errno));
		return -1;
	}

	if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		err(1, "bind failed");
	}
	if (listen(listen_fd, CONNECTION_BACKLOG) < 0) {
		err(1, "listen failed");
	}
	return listen_fd;
}

int CTcpServer::runServer(void)
{
	int listen_fd = socket_bind_listen(IPADDRESS, SERVERPORT);
	struct epoll_event events[MAX_EVENT_NUMBER];	//内核需要监听的事
	int epollfd = epoll_create1(0);
	if (epollfd == -1) {
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}
	addfd(epollfd, listen_fd, false);
	thread_pool.threadpool_init();
	for (;;)
	{
		int nfds = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);	//等待I/O事件
		if (0 == nfds)
		{
			printf("TcpServer is running...\n");
			continue;
		}
		else if ((nfds < 0) && (errno != EINTR))	//epoll遭遇EINTR(Interrupted system call)
		{			
			cout << "Error->epoll_wait:" << strerror(errno) << endl;
			break;
		}
		//ET模式
		for (int i = 0; i < nfds; ++i)
		{
			int sockfd = events[i].data.fd;
			if (sockfd == listen_fd)
			{
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				int connfd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addrlength);
				addfd(epollfd, connfd, true);
			}
			else if (events[i].events & EPOLLIN)
			{
				m_arglocker.lock();
				thread_para arg;
				arg.epollfd = epollfd;
				arg.sockfd = sockfd;
				m_arglocker.unlock();
				thread_pool.append(&arg);
			}
			else
			{
				printf("Error:something else happened \n");
			}
		}
	}
	close(listen_fd);
	close(epollfd);
	thread_pool.threadpool_destroy();
}
int main(int argc, char* argv[])
{
	/*if (argc <= 2)
	{
	printf("usage: %s ip_address port_number\n", basename(argv[0]));
	return 1;
	}
	const char* ip = argv[1];
	int port = atoi(argv[2]);*/
	Server.runServer();
	return 0;
}

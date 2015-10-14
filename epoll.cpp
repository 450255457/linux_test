/*****************************************
> File Name : epoll.cpp
> Description : epoll demo
> Author : linden
> Date : 2015-10-13
*******************************************/

#include "epoll.h"

struct fds
{
	int epollfd;
	int sockfd;
};

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

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

void reset_oneshot(int epollfd, int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

void* worker(void* arg)
{
	int sockfd = ((fds*)arg)->sockfd;
	int epollfd = ((fds*)arg)->epollfd;
	printf("start new thread to receive data on fd: %d\n", sockfd);
	char buf[BUFFER_SIZE];
	memset(buf, '\0', BUFFER_SIZE);
	while (1)
	{
		int ret = recv(sockfd, buf, BUFFER_SIZE - 1, 0);
		if (ret == 0)
		{
			close(sockfd);
			printf("foreiner closed the connection\n");
			break;
		}
		else if (ret < 0)
		{
			if (errno == EAGAIN)
			{
				reset_oneshot(epollfd, sockfd);
				printf("read later\n");
				break;
			}
		}
		else
		{
			printf("get content: %s\n", buf);
			sleep(5);
		}
	}
	printf("end thread receiving data on fd: %d\n", sockfd);
}

int socket_bind_listen(const char *ip, int nPort){
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

int runServer(void) 
{
	int listen_fd = socket_bind_listen(IPADDRESS, SERVERPORT);
	epoll_event events[MAX_EVENT_NUMBER];	//是否要加struct
	int epollfd = epoll_create1(0);
	if (epollfd == -1) {
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}
	addfd(epollfd, listen_fd, false);

	for (;;)
	{
		int nfds = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		if (nfds == -1)
		{
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

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
				pthread_t thread;
				fds fds_for_new_worker;
				fds_for_new_worker.epollfd = epollfd;
				fds_for_new_worker.sockfd = sockfd;
				pthread_create(&thread, NULL, worker, (void*)&fds_for_new_worker);
			}
			else
			{
				printf("something else happened \n");
			}
		}
	}
	close(listen_fd);
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
	runServer();
	return 0;
}

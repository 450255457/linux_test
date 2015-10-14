/*****************************************
> File Name : epoll.h
> Description : epoll head file
	g++ -g -o epoll epoll.h epoll.cpp -lpthread
> Author : linden
> Date : 2015-10-13
*******************************************/

#ifndef _EPOLL_H_
#define _EPOLL_H_

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

#define IPADDRESS	"0.0.0.0"
#define SERVERPORT	8090
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024
#define CONNECTION_BACKLOG	5

#endif
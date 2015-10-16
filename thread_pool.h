﻿/*****************************************
> File Name : thread_pool.cpp
> Description : 
> Author : linden
> Date : 2015-10-16
*******************************************/

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <unistd.h>
#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>

#include "locker.h"

typedef struct _thread_para
{
	int epollfd;
	int sockfd;
	char buf[BUFFER_SIZE];
}thread_para;

//线程池类
class CThreadPool{
public:
	
	CThreadPool();
	~CThreadPool();

	int threadpool_init(int thread_number = 10, int max_requests = 10000 );
	void threadpool_destroy();
	//往请求队列中添加任务
    bool append( void* request );
private:
	static void* worker( void* arg );
	void run();

    //int m_thread_number;			//线程池中的线池数
    int m_max_requests;				//请求队列中允许的最大请求数
    pthread_t* m_threads;			//描述线程池的数组,其大小为m_thread_number
    std::list< void* > m_workqueue;	//请求队列
    locker m_queuelocker;			//保护请求队列的互斥锁
    sem m_queuestat;				//是否有任务需要处理
    bool m_stop;					//是否结束线程
};

CThreadPool::CThreadPool(){

}

CThreadPool::~CThreadPool(){

}
#endif

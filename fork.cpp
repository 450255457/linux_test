/*****************************************
> File Name : fork.cpp
> Description : fork示例代码
	gcc -g -o fork fork.cpp
> Author : linden
> Date : 2016-01-22
*******************************************/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();
	if (0 > pid)
	{
		perror("fork error:");
	}
	else if (0 == pid)
	{
		printf("This is the child process: %d.\n", getpid());
	}
	else
	{
		printf("This is the parent process: %d.\n", getpid());
	}

	//判断子进程结束：wait子进程结束或者捕捉信号SIGCHLD
	int status;
	if (wait(status) != pid) 
	{
		perror("Error --> wait:");
	}
	printf("status = %d\n", status);
	return 0;
}
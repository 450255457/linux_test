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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void pre_exit(int status)
{
	if (WIFEXITED(status))
	{
		printf("normal termination,exit status = %d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("abnormal termination,signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
			WCOREDUMP(status) ? " (core fire generated) " : "");
#else
			"");
#endif
	}
	else if (WIFSTOPPED(status))
	{
		printf("child stopped,signal number = %d\n",WSTOPSIG(status));
	}
}

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
		printf("This is the child process: %d, ppid = %d.\n", getpid(),getppid());
		exit(0);
	}
	printf("This is the parent process: %d.\n", getpid());

	//判断子进程结束：wait子进程结束
	int status;
	if (wait(&status) != pid) 
	{
		perror("Error --> wait:");
	}
	pre_exit(status);
	return 0;
}
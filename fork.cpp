/*****************************************
> File Name : fork.cpp
> Description : forkÊ¾Àý´úÂë
	gcc -g -o fork fork.cpp
> Author : linden
> Date : 2016-01-22
*******************************************/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

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
		printf("This is the child process: %d.\n", gitpid());
	}
	else
	{
		printf("This is the parent process: %d.\n", gitpid());
	}
	
	printf("pid = %d, ppid = %d\n", getpid(), getppid());
	return 0;
}
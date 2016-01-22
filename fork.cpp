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
	
	return 0;
}
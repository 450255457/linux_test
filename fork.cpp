/*****************************************
> File Name : fork.cpp
> Description : fork两次，避免僵死进程
	gcc -g -o fork fork.cpp
> Author : linden
> Date : 2016-01-25
*******************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "Fork error!\n");
		exit(-1);
	}
	else if (pid == 0) /* first child */
	{
		if ((pid = fork()) < 0)
		{
			fprintf(stderr, "Fork error!\n");
			exit(-1);
		}
		else if (pid > 0)
			exit(0); /* parent from second fork == first child */
		/*
		* We're the second child; our parent becomes init as soon
		* as our real parent calls exit() in the statement above.
		* Here's where we'd continue executing, knowing that when
		* we're done, init will reap our status.
		*/
		sleep(2);
		printf("Second child, parent pid = %d\n", getppid());
		exit(0);
	}

	if (waitpid(pid, NULL, 0) != pid) /* wait for first child */
	{
		fprintf(stderr, "Waitpid error!\n");
		exit(-1);
	}

	/*
	* We're the parent (the original process); we continue executing,
	* knowing that we're not the parent of the second child.
	*/
	exit(0);
}
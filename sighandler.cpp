/*****************************************
> File Name : sighandler.cpp
> Description : 信号处理僵尸进程
	g++ -g -o sighandler sighandler.cpp
> Author : linden
> Date : 2016-02-23
*******************************************/

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	pid_t pid = fork();
	if (0 > pid)
	{
		perror("fork error:");
		exit(-1);
	} 
	else if (0 == pid)
	{
		cout << "\nIm in child process:" << getpid() << endl;
		exit(0);
	}
	else
	{
		cout << "\nIm in parent process." << endl;
		sleep(600);
	}
	return 0;
}

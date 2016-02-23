/*****************************************
> File Name : sighandler.cpp
> Description : 信号处理程序
	g++ -g -o sighandler sighandler.cpp
> Author : linden
> Date : 2016-02-23
*******************************************/

#include <iostream>

using namespace std;

static void sig_usr(int signo)	/* argument is signal number */
{
	if (signo == SIGUSR1)
	{
		cout << "received SIGUSR1." << endl;
	}
	else if (signo == SIGUSR2)
	{
		cout << "received SIGUSR2." << endl;
	}
	else
	{
		cout << "received signal " << signo << endl;
	}
}
int main(int argc, char *argv[])
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		cout << "can't catch SIGUSR1" << endl;
	}
	else if (signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		cout << "can't catch SIGUSR2" << endl;
	}
	for (;;)
	{
		pause();
	}
	return 0;
}

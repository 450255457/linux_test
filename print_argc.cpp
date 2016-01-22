/*****************************************
> File Name : print_argc.cpp
> Description : mainº¯ÊýÊ¾Àý´úÂë
	gcc -g -o printArgc print_argc.cpp
> Author : linden
> Date : 2016-01-22
*******************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i = 0;
	for (i = 0; argv[i] != NULL; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	exit(0);
}
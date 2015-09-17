/*****************************************
> File Name : comm_strings_main.cpp
> Description : some public function
	g++ -g -o comm_strings_main.cpp comm_strings.h
> Author : linden
> Date : 2015-08-07
*******************************************/

#include "comm_strings.h"

using namespace std;

int main()
{
	string str = "	1 2	3	";
	printf("str = %s\n", str.c_str());
	printf("str = %s\n", Trim(str).c_str());
}
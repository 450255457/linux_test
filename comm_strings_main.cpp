/*****************************************
> File Name : public_function.cpp
> Description : some public function
> Author : linden
> Date : 2015-08-07
*******************************************/

#include "comm_strings.h"

int main()
{
	string str = "	1 2	3	";
	printf("str = %s\n", str.c_str());
	printf("str = %s\n", Trim(str).c_str());
}
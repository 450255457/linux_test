/*****************************************
> File Name : comm_strings_main.cpp
> Description : some public function
	g++ -g -o comm_strings_main comm_strings_main.cpp comm_strings.h comm_strings.cpp
> Author : linden
> Date : 2015-08-07
*******************************************/

#include "comm_strings.h"

using namespace std;

int main()
{
	std::string str = "	1 a	b	I Miss You";
	printf("str = %s\n", str.c_str());
	Trim(str);
	printf("str = %s\n", str.c_str());
	ToUpper(str);
	printf("str = %s\n", str.c_str());
	ToLower(str);
	printf("str = %s\n", str.c_str());
	char cstr[] = "what is the hell...";
	string sstr = Format(cstr);
	printf("sstr = %s\n", str.c_str());
	return 0;
}
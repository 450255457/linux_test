/*****************************************
> File Name : operator_overloading.cpp
> Description : 重载运算符+
	g++ -g -o operator_overloading operator_overloading.cpp
> Author : linden
> Date : 2016-01-26
*******************************************/
#include <iostream>

using namespace std;

struct Complex {
   Complex( double r, double i ) : re(r), im(i)/*构造函数初始值列表*/ {}
   Complex operator+( Complex &other );
   void Display( ) {   cout << re << ", " << im << endl; }
private:
   double re, im;
};

// Operator overloaded using a member function
Complex Complex::operator+( Complex &other ) {
   return Complex( re + other.re, im + other.im );
}

int main() {
   Complex a = Complex( 1.2, 3.4 );
   Complex b = Complex( 5.6, 7.8 );
   Complex c = Complex( 0.0, 0.0 );

   c = a + b;
   c.Display();
}
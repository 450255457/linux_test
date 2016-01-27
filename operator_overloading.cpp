/*****************************************
> File Name : operator_overloading.cpp
> Description : 重载运算符
	g++ -g -o operator_overloading operator_overloading.cpp
> Author : linden
> Date : 2016-01-26
*******************************************/
#include <iostream>

using namespace std;

struct Complex {
	Complex( double r, double i ) : re(r), im(i)/*构造函数初始值列表*/ {}
	Complex operator+( Complex &other );
	friend Complex operator-(const Complex & A, const Complex & B);
	friend istream &operator>>(istream &in, Complex &other);
	friend ostream &operator<<(ostream &out, Complex &other);
	void Display( ) {   cout << re << ", " << im << endl; }
private:
	double re, im;
};

// Operator overloaded using a member function
Complex Complex::operator+( Complex &other ) {
   return Complex( re + other.re, im + other.im );
}

//全局运算符重载
Complex operator-(const Complex & A, const Complex & B)
{
	Complex C(0.0,0.0);
	C.re = A.re - B.re;
	C.im = B.im - B.im;
	return C;
}

//重载输入运算符
istream &operator>>(istream &in, Complex &other)
{
	in >> other.re >> other.im;
	return in;
}

//重载输出运算符
ostream &operator<<(ostream &out, Complex &other)
{
	cout << other.re << " " << other.im;
	return out;
}

int main() {
	Complex a = Complex(0.0, 0.0);
	Complex b = Complex(0.0, 0.0);
	Complex c = Complex(0.0, 0.0);

	cin >> a >> b;
   /*
	   在类 Complex 中重载了运算符"+"，该重载只对 Complex 对象有效。
	   当执行c = a + b 语句时，编译器检测到"+"号左边（"+"号具有左结合性）是一个 Complex 对象，就会调用运算符重载函数，该语句会被转换为： a.operator+(b)
   */
	c = a + b;
	cout << a << " + " << b << " = " <<c << endl;
	c = a - b;
	cout << a << " - " << b << " = " << c << endl;
	//c.Display();
	
}
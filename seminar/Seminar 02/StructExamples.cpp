#include<iostream>
//Група тестови структури - 1
struct E {};

struct A
{
    char a[3];
	short b;
	double c[4];
	char d;
};

struct B
{
    char a;
};

struct C 
{
    short a;
};


//Група тестови структури - 2
struct D 
{
    double  a;
    int     b;
    int     c;
};

struct F 
{
    int     a;
    double  b;
    int     c;
};

//Група тестови структури - 3
struct J
{
    E e;
    D d;
    int a;
};

struct I
{
    F f[2];
    char ch[3];
};

int main(){
    //Група тестови структури - 1
    std::cout<< "The size of E is " << sizeof(E) << std::endl;
    std::cout<< "The size of A is " << sizeof(A) << std::endl;
    std::cout<< "The size of B is " << sizeof(B) << std::endl;
    std::cout<< "The size of C is " << sizeof(C) << std::endl;

    //Група тестови структури - 2
    std::cout<< "The size of D is "<< sizeof(D) << std::endl;
    std::cout<< "The size of F is "<< sizeof(F) << std::endl;

    //Група тестови структури - 3
    std::cout<< "The size of J is "<< sizeof(J) << std::endl;
    std::cout<< "The size of I is "<< sizeof(I) << std::endl;
} 
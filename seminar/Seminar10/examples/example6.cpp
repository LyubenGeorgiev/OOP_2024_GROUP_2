#include<iostream>

class A{
public:
    static int cnt;
    A(){
        cnt++;
        std::cout<<"A() ";
    }
};
int A::cnt = 0;
class B: public A{
public:
    B(){
        cnt++;
        std::cout<<"B() ";
    }
};
class C: public B{
public:
    C(){
        cnt++;
        std::cout<<"C() ";
    }
};
int main(){
    C arr[2];
    std::cout<<B::cnt;
}
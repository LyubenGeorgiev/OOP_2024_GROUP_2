#include<iostream>

class A{
public: 
    void print(){ std::cout<<"In A"<<std::endl; }
};
class B : public A{
public:
    void print(){ std::cout<<"In B"<<std::endl; }
};
class C : public B{}; 
int main(){
    C c;
    c.print();
}
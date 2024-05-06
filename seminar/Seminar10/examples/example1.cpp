#include<iostream>

class Base{
    public: 
    ~Base(){
        std::cout<<"~Base() ";
    }
};
class Derived : public Base{
    public:
    ~Derived(){
        std::cout<<"~Derived() ";
    }
};
int main(){
    Derived d;
}
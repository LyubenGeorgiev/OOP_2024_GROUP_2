#include"MyString.h"
#include<cstring>

//private 
void MyString::copyFrom(const MyString& other){
    size = other.size;
    data = new char[size + 1];
    strcpy(data, other.data);
}

void MyString::free(){
    delete[] data;
    data = nullptr;
}
   
//public   
MyString::MyString(){
    data = new char[1];
    data[0] = '\0';
    size = 0;
}

MyString::MyString(const char* initData){
    size = strlen(initData);
    data = new char[size + 1];
    strcpy(data, initData);
}

MyString::~MyString(){
    free();
}

MyString::MyString(const MyString& other){
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}


unsigned MyString::length() const{
    return size;
} 

void MyString::print() const{
    std::cout << data << std::endl;
}

int main(){
    MyString str("OOP_2024");
    unsigned sz = str.length();
    MyString str1 = str;
    str.print();
    std::cout << sz << std::endl;
    MyString str1("oop_sem");
    str1 = str1;
}
#include<iostream>
#include<fstream> 

void printCode(){
    std::ifstream code("printMyCode.cpp");

    if(!code.is_open()){
        return;
    }

    while(!code.eof()){
        char ch = code.get();
        std::cout<< ch;
    }
}

int main(){
    printCode();
}
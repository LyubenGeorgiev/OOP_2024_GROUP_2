#include<iostream>

static int globalCounter;

void counterStatic(){
    globalCounter++;
    std::cout<<"globalCounter: "<< globalCounter <<std::endl;
}

void counterStatic2(){
    static int functionCounter;
    functionCounter++;
    std::cout<<"static in function: "<< functionCounter << std::endl;
}

void nonStaticCounter(){
    int scopeCounter = 0;
    scopeCounter++;
    std::cout<<"regular variable: "<< scopeCounter << std::endl;
}

int main(){
    for(int i = 0; i < 3; i++){
        counterStatic();
    }
       for(int i = 0; i < 3; i++){
        counterStatic2();
    }
       for(int i = 0; i < 3; i++){
        nonStaticCounter();
    }
}
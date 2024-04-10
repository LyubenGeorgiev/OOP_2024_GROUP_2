#include<iostream>

static int globalCounter;

//static function can only acess static variables ans static functions
static void counterStatic(){
    globalCounter++;
}

static void printStaticGlobal(){
    counterStatic();
    std::cout<<"global static: "<< globalCounter<<std::endl;
}

int main(){
    for(int i = 0; i < 3; i++){
        printStaticGlobal();
    }
   
}
#include<iostream>
class Example{
    private:
    //if we have a static member than we will 
    //have only one instance of the variable 
    static int liveObjectsCount;
    const int magicValue;

    public:
    Example(int val) :magicValue(val){
        liveObjectsCount++;
        std::cout<<"liveObjects: "<< liveObjectsCount <<std::endl;
    }
    Example():Example(42) { }

    Example(const Example& other):magicValue(other.magicValue){
        liveObjectsCount++;
        std::cout<<"liveObjects: "<< liveObjectsCount <<std::endl;
    }

    Example& operator=(const Example& other) = delete;

    ~Example(){
        std::cout<<"liveObjects: "<< liveObjectsCount <<std::endl;
        liveObjectsCount--;
    }
};

// whenever we use a static member in class
// we have to tell the compiler that we 
// have used a static variable like this:
int Example::liveObjectsCount = 0;

int main(){
    Example e1;
    Example e2(6);
}
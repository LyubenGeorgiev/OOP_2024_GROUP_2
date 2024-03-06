#include<iostream>
#include<fstream>

int main(){
    std::ifstream file("seekFile.txt");
    if(!file.is_open()){
        return -1;
    }
    int currPos = file.tellg();
    char ch;
    std::cout<< "Current Position is: " << currPos << " ";
    ch = file.get();
    std::cout<< "Current Character is: " << ch << std::endl;

    //Example 1
    file.seekg(4, std::ios::beg);
    currPos = file.tellg();
    std::cout<< "Current Position is: " << currPos << " ";
    ch = file.get();
    std::cout<< "Current Character is: " << ch << std::endl;

    file.seekg(0, std::ios::beg);

    //Example 2;
    file.seekg(2, std::ios::cur);
    currPos = file.tellg();
    std::cout<< "Current Position is: " << currPos << " ";
    ch = file.get();
    std::cout<< "Current Character is: " << ch << std::endl;


    //Example 2
    file.seekg(-1, std::ios::end);
    currPos = file.tellg();
    std::cout<< "Current Position is: " << currPos <<" ";
    ch = file.get();
    std::cout<< "Current Character is: " << ch << std::endl;
    std::cout<< "Current Position is tellg: " << file.tellg() <<std::endl;
    
    //Example 3
    file.seekg(-2, std::ios::cur);
    currPos = file.tellg();
    std::cout<< "Current Position is: " << currPos << " ";
    ch = file.get();
    std::cout<< "Current Character is: " << ch << std::endl;

}
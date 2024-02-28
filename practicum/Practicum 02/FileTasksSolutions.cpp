#include<iostream>
#include<fstream>

unsigned getCharCount(std::ifstream& file, char ch){

      if( !file.is_open()){
        std::cout<<"The file could not open!" <<std::endl;
        return 0;
    }

    size_t currentPosition = file.tellg();
    file.seekg(0, std::ios::beg);
    unsigned int count = 0;

    while(true){
        char current = file.get();
        if(file.eof()){
            break;
        }
        if(current == ch){
            count++;
        }
    }
    file.clear();
    file.seekg(currentPosition);
    return count;
}

unsigned getLinesCount(const char* fileName){
    std::ifstream file(fileName);

    if(!file.is_open()){
        std::cout<<"The file could not open!" <<std::endl;
        return;
    }

    return getCharCount(file, '\n') + 1;
}

void printSumFromFile(const char* fileName){
    std::ifstream file(fileName);

    if(!file.is_open()){
        std::cout<<"The file could not open!" <<std::endl;
        return;
    }

    int first, second;
    file >> first >> second;
    std::cout<< first + second << std::endl;
    file.close();
}

unsigned findMaxNumFromFile(const char* fileName) {
    std::ifstream file(fileName);

     if(!file.is_open()){
        std::cout<<"The file could not open!" <<std::endl;
        return -1;
    }

    unsigned maxNumber = 0;
    unsigned currentNumber;
    while(!file.eof()){
        file >> currentNumber;
        if(currentNumber > maxNumber){
            maxNumber = currentNumber;
        }
    }

    file.close();
    return maxNumber;
}


int main(){
   printSumFromFile("sum.txt");
   std::cout<<findMaxNumFromFile("maxNumber.txt") <<std::endl;
}
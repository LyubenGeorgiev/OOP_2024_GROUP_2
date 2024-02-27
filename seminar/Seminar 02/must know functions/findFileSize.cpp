#include<iostream>
#include<fstream>

size_t getFileSize(std:: ifstream& file){
    //1. запазваме къде е текущата позиция на get указателя 
    size_t currentPos = file.tellg();

    //2. преместваме get указателя в края 
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();

    //3. възстановяваме оригиналната позиция на get указателя във файла
    file.seekg(currentPos);

    return fileSize;
}

int main(){

}
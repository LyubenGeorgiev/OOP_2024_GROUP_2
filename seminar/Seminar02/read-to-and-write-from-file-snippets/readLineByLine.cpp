#include<iostream>
#include<fstream>

void readFromFile(const char* fileName){
   std::ifstream file;
   file.open(fileName);

   // Задължително проверяваме дали файлът се е отворил
    if(!file.is_open()){
        return;
    }

    //Четем файла ред по ред
    char tempLine[1024];
    while(!file.eof()){
        file.getline(tempLine, 1024);
        std::cout << tempLine << std::endl;
    }

    file.close();
}

int main(){
    readFromFile("myFile2.txt");
}
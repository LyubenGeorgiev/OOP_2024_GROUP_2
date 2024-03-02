#include<iostream>
#include<fstream>

void readFromFile(const char* fileName){
   std::ifstream file;
   file.open(fileName);

   // Задължително проверяваме дали файлът се е отворил
    if(!file.is_open()){
        return;
    }

    //Четем файла дума по дума
    char tempWord[100];
    while(!file.eof()){
        file >> tempWord;
        std::cout << tempWord << std::endl;
    }

    file.close();
}

int main(){
    readFromFile("myFile.txt");
}
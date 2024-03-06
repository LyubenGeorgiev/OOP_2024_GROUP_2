#include<iostream>
#include<fstream>

void readFromFile(const char* fileName){
   std::ifstream file;
   file.open(fileName);

   // Задължително проверяваме дали файлът се е отворил
    if(!file.is_open()){
        return;
    }

    //Четем символ по символ
    char ch;
    while(true){
        //вариант 1
        file.get(ch);
        //вариант 2
        // ch = file.get()
        if(ch == file.eof()){
            break;
        }
        std::cout << ch << std::endl;
    }

    file.close();
}

int main(){
    readFromFile("myFile.txt");
}
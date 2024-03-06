#include<iostream>
#include<fstream>

void copyToFile(const char* sourceFileName, const char* destFileName){
    std::ifstream sourceFile(sourceFileName);
    if(!sourceFile.is_open()){
        return;
    }

    std::ofstream destFile(destFileName);
    if(!destFile.is_open()){
        return;
    }
    while(!sourceFile.eof()){
        char buff[1024];
        sourceFile.getline(buff, 1024);
        destFile << buff<< std::endl;
    }
    sourceFile.close();
    destFile.close();
}

int main() {
    copyToFile("file1.txt", "copyFile1.txt");
}
// Напишете функция, която:
// записва масив от цели числа в двоичен файл
#include<iostream>
#include<fstream>

size_t getFileSize(std::ifstream& file) {
	size_t currentPos = file.tellg();

	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
    
	file.seekg(currentPos);
	return fileSize;
}

int main(){
    std::ifstream file("myArray.dat", std::ios::binary);

    if(!file.is_open()){
        return -1;
    }
    unsigned int fileSize = getFileSize(file);
    int arraySize = fileSize / sizeof(int);
    int* arr = new int[arraySize];

    file.read((char*)arr, arraySize * sizeof(int));

    for(int i = 0; i < arraySize; i++){
        std::cout<< arr[i] << " ";
    }
   // std::cout<<sizeof(arr)<<std::endl;
    file.close();

    delete[] arr;
}
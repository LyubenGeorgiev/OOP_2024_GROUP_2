// Напишете функция, която:
// записва масив от цели числа в двоичен файл
#include<iostream>
#include<fstream>

int main(){

    int arr[9] = {1, 2, 3, 4 ,5, 6, 6, 11, 15};
    std::ofstream file("myArray.dat", std::ios::binary);

    if(!file.is_open()){
        return -1;
    }

    file.write((const char*)arr, sizeof(arr));
    file.close();
}
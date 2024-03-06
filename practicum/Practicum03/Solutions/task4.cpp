#include <iostream>
#include <fstream>


int size(const char* filename) {
    std::ifstream in(filename);

    if (!in) {
        return -1;
    }

    in.seekg(0, std::ios::end);
    int size = in.tellg();
    
    in.close();

    return size;
}

int main() {
    std::cout << size("input1.txt");

    return 0;
}
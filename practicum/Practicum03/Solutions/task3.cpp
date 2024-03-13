#include <iostream>
#include <fstream>


typedef unsigned char byte;

void unusedBytes(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cout << "Error opening for reading from " << filename << '\n';
        return;
    }

    // Note this could also be bool array
    int byteCounts[256] = {0, };

    byte b;
    while (in.read((char*)&b, sizeof(b))) {
        byteCounts[b]++;
    }

    in.close();

    int count = 0;
    for (byte i = 0; i < 256; i++) {
        if (byteCounts[i] == 0) {
            std::cout << "Byte " << (int)i << " is not used\n";
            count++;
        }
    }
    std::cout << "Total " << count << " unused bytes\n";
}
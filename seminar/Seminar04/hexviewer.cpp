#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

typedef unsigned char byte;

struct Hexviewer {
    byte* data = nullptr;
    std::size_t size = 0;
    char* filename = nullptr;
};

int getFileSize(std::ifstream& in) {
    int current = in.tellg();
    in.seekg(0, std::ios::end);
    int size = in.tellg();
    in.seekg(current, std::ios::beg);

    return size;
}

Hexviewer newHexviewer(const char *filename) {
    std::ifstream in(filename, std::ios::binary);

    if (!in.is_open()) {
        std::cout << "Error opening " << filename;
        return {};
    }

    Hexviewer hv;
    
    hv.size = getFileSize(in);

    hv.data = new byte[hv.size];

    in.read((char*)hv.data, hv.size);

    hv.filename = new char[strlen(filename) + 1];
    strcpy(hv.filename, filename);

    in.close();

    return hv;
}

void printHexAt(const Hexviewer &hv, int i) {
    assert(i < hv.size);
    assert(i >= 0);

    byte b = hv.data[i];

    // [0,255]
    char first = b / 16;
    char second = b % 16;

    if (first > 9) {
        std::cout << (char)('A' + first - 10);
    } else {
        std::cout << (char)('0' + first);
    }

    if (second > 9) {
        std::cout << (char)('A' + second - 10);
    } else {
        std::cout << (char)('0' + second);
    }
}

void printAt(const Hexviewer &hv, int i) {
    assert(i < hv.size);
    assert(i >= 0);

    byte b = hv.data[i];

    if (b >= 'a' && b <= 'z' || b >= 'A' && b <= 'Z') {
        std::cout << b;
    } else {
        std::cout << '.';
    }
}

void change(Hexviewer &hv, int i, byte newVal) {
    assert(i < hv.size);
    assert(i >= 0);

    hv.data[i] = newVal;
}

void pop_back(Hexviewer &hv) {
    hv.size--;
}

void push_back(Hexviewer &hv, byte newVal) {
    byte* newData = new byte[hv.size + 1];

    for (int i = 0; i < hv.size; i++) {
        newData[i] = hv.data[i];
    }
    newData[hv.size] = newVal;

    delete[] hv.data;

    hv.data = newData;
    hv.size++;
}

void save(const Hexviewer &hv) {
    std::ofstream out(hv.filename, std::ios::binary | std::ios::trunc);

    if (!out.is_open()) {
        std::cout << "Error opening " << hv.filename;
    }

    out.write((const char*)hv.data, hv.size);

    out.close();
}

void freeHexviewer(Hexviewer &hv) {
    delete[] hv.data;
    hv.data = nullptr;
    delete[] hv.filename;
    hv.filename = nullptr;
    hv.size = 0;
}

int main() {
    Hexviewer hv = newHexviewer("data");

    std::cout << "size is " << hv.size << '\n';
    for (int i = 0; i < hv.size; i++) {
        printHexAt(hv, i);
        std::cout << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < hv.size; i++) {
        printAt(hv, i);
        std::cout << "  ";
    }

    freeHexviewer(hv);

    return 0;
}
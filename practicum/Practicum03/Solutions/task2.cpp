#include <iostream>
#include <fstream>


bool isComposite(int number) {
    for (int i = 2; i < number; i++) {
        if (number % i == 0) {
            return true;
        }
    }

    return false;
}

void split(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cout << "Error opening for reading from " << filename << '\n';
        return;
    }

    std::ofstream prime("prime.dat", std::ios::binary);
    if (!prime.is_open()) {
        in.close();

        std::cout << "Error opening for writing from prime.dat\n";
        return;
    }

    std::ofstream composite("composite.dat", std::ios::binary);
    if (!composite.is_open()) {
        in.close();
        prime.close();

        std::cout << "Error opening for writing from composite.dat\n";
        return;
    }

    int number;
    while (in.read((char*)&number, sizeof(number))) {
        if (isComposite(number)) {
            composite.write((const char*)&number, sizeof(number));
        } else {
            prime.write((const char*)&number, sizeof(number));
        }
    }

    in.close();
    prime.close();
    composite.close();
}
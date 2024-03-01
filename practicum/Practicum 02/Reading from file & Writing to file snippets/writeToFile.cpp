#include <iostream>
#include <fstream> 
int main ()
{
    // tempInfo.txt се създава, ако не е съществувал до сега
    std::ofstream tempFile("tempInfo.txt"); 

    if (!tempFile.is_open())
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    // Пишем текст
    tempFile << "New info\n"; 
    // Пишем числа
    tempFile << 5 + 7 << "\n"; 

    tempFile.close(); 
}

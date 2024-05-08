#pragma once
#include "FileReader.h"
class CSVFileReader : public FileReader
{
	static int getCharCount(std::ifstream& ifs, char ch);
public:
	CSVFileReader(const MyString& filePath);
	void read(int*& arr, size_t& size) const override;
};


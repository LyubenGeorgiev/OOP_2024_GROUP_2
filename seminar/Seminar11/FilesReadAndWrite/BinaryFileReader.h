#pragma once
#include "FileReader.h"
class BinaryFileReader : public FileReader
{
	static size_t getFileSize(std::ifstream& inFile);
public:
	BinaryFileReader(const MyString& filePath);
	void read(int*& arr, size_t& size) const override;
};


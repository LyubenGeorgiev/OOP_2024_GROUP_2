#pragma once
#include "MyString.h"
class FileReader
{
protected:
	MyString filePath;

public:
	FileReader(const MyString& filePath);
	virtual void read(int*& arr, size_t& size) const = 0;
	virtual ~FileReader() = default;
};


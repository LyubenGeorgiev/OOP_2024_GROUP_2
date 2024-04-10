#include "String.h"
#pragma warning (disable:4996)
#include <cstring>
#include <cassert>

StringPool String::pool;

String::String() : String("") {}

String::String(const char* text) {
	data = pool.getString(text);
	size = strlen(data);
}

String::String(const String& other) {
	data = pool.getString(other.c_str());
	size = other.size;
}

char String::operator[](size_t index) const {
	if (index >= size)
		throw std::out_of_range("String::operator[] out of range!");

	return data[index];
}

String& String::operator=(const String& other) {
	if (this != &other)
	{
		pool.removeString(data);
		data = pool.getString(other.c_str());
		size = other.size;
	}

	return *this;
}

const char* String::c_str() const {
	return data;
}

size_t String::length() const {
	return size;
}

bool String::empty() const {
	return (size == 0);
}

String::~String() {
	pool.removeString(c_str());
}

bool operator==(const String& lhs, const String& rhs)
{
	// if you make it friend you can directly compare the data pointers
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	return os << str.c_str();
}
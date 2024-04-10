#pragma once
#include <iostream>
#include "StringPool.h"

class String {
private:
	const char* data;
	unsigned size;

	static StringPool pool;

public:
	String();
	String(const char* text);
	String(const String& other);

	char operator[](size_t index) const;
	char& operator[](size_t index);		// за домашно

	String& operator=(const String& other);

	const char* c_str() const;

	size_t length() const;
	bool empty() const;

	~String();
};


bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
std::ostream& operator<<(std::ostream& os, const String& str);
String operator+(const String& lhs, const String& rhs); // за домашно
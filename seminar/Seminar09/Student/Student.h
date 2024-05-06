#pragma once
#include "MyString.h"
#include <iostream>

class Student
{
	MyString name;
	unsigned age;

public:
	Student();
	Student(const char* name, unsigned age);
};
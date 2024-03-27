#pragma once
#include<iostream>

class MyString{
    char* data;
    unsigned size;

    void copyFrom(const MyString& data);
    void free();

public:
    MyString();
    MyString(const char* data);
    ~MyString(); 

    MyString(const MyString& other);
    MyString& operator=(const MyString& other);

    unsigned length() const;  
    void print() const;
};
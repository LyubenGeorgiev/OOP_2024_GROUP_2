#pragma once

class SetOfNumbers{
private:
    unsigned char* data;
    unsigned maxNumber;

    void copyFrom(const SetOfNumbers& other);
    void free();

    unsigned getBucketIndex(unsigned number) const;
    unsigned getBucketsCount() const;
    unsigned char getMask(unsigned number) const;
    
public:
    SetOfNumbers() = default;
    SetOfNumbers(unsigned n);

    SetOfNumbers(const SetOfNumbers& other);
    SetOfNumbers& operator=(const SetOfNumbers& other);
    ~SetOfNumbers();

    bool contains(unsigned number) const;
    bool addNumber(unsigned number);
    bool removeNumber(unsigned number);

    void print() const;
};
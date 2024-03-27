#include"BitSet.h"
#include<iostream> 

//private:   
void SetOfNumbers::copyFrom(const SetOfNumbers& other){
    unsigned bucketsCount = other.getBucketsCount();
    data = new unsigned char[bucketsCount];
    for(int i = 0; i < bucketsCount; i++){
        data[i] = other.data[i];
    }
}
    
void SetOfNumbers::free(){
    delete[] data;
}

unsigned SetOfNumbers::getBucketIndex(unsigned number) const{
    return number / 8;
}
    
unsigned SetOfNumbers::getBucketsCount() const{
    return (maxNumber + 1) / 8 + 1;
}

unsigned char SetOfNumbers::getMask(unsigned number) const {
    unsigned indexInBucket = number % 8;

    char mask = 1;
    mask = mask << (7 - indexInBucket);
    return mask;
}

//public:
SetOfNumbers::SetOfNumbers(unsigned n){
    unsigned sz = n/8 + 1;
    data = new unsigned char[sz];
    for(unsigned i = 0; i < sz; i++){
        data[i] = 0;
    }
    maxNumber = n - 1;
}

SetOfNumbers::SetOfNumbers(const SetOfNumbers& other){
    copyFrom(other);
}
    
SetOfNumbers& SetOfNumbers::operator=(const SetOfNumbers& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}
    
SetOfNumbers::~SetOfNumbers(){
    free();
}

bool SetOfNumbers::contains(unsigned number) const{
    unsigned bucketIndex = getBucketIndex(number);
    unsigned char mask = getMask(number);

    return (mask & data[bucketIndex]);
}

bool SetOfNumbers::addNumber(unsigned number){
       if (number > maxNumber || contains(number)){
            return false;
       }
       unsigned bucketIndex = getBucketIndex(number);
       unsigned char mask = getMask(number);

      data[bucketIndex] |= mask;
      return true;
}

bool SetOfNumbers::removeNumber(unsigned number){
    if (number > maxNumber || !contains(number)){
        return false;
    }

    unsigned bucketIndex = getBucketIndex(number);
    unsigned char mask = getMask(number);

    data[bucketIndex] ^= mask;

    return true;
}

void SetOfNumbers::print() const{
    std::cout << "{ ";
    unsigned current = 0;
    for (int i = 0; i < getBucketsCount(); i++)
    {
        for (unsigned char j = 128; j >= 1; j >>= 1) //128 is 2^7
        {
            if (data[i] & j)
                std::cout << current << " ";
            current++;
        }
    }
    std::cout << "} " << std::endl;
}

int main(){
    
}
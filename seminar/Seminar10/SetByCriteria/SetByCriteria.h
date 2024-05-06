#pragma oncr
#include "SetOfNumbers.h"

class SetByCriteria : private SetOfNumbers{
public:
    struct Criteria{
        Criteria(bool (*incl)(unsigned n)): _incl(incl){}
        bool (*_incl)(unsigned n);
    };
private: 
    Criteria myCr;
    void fillSet();
public:
    SetByCriteria(unsigned n, bool (*incl)(unsigned n));
    bool contains(int i) const;
    void print() const;

    void setInclude(bool (*incl)(unsigned n));
};


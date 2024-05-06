#include "SetByCriteria.h"

SetByCriteria::SetByCriteria(unsigned n, bool (*incl)(unsigned n)) : SetOfNumbers(n),  myCr(incl){
    for (unsigned i = 0; i < n; i++){
        if (myCr._incl(i)) {
            addNumber(i);
        }
    }
}

void SetByCriteria::fillSet() {
    for (unsigned i = 0; i < SetOfNumbers::getMaxNumber(); i++) {
        if (myCr._incl(i)){
            addNumber(i);
        }
    }
}


bool SetByCriteria::contains(int i) const {
    return SetOfNumbers::contains(i);
}
void SetByCriteria::print() const {
    SetOfNumbers::print();
}


void SetByCriteria::setInclude(bool (*incl)(unsigned n)){
    myCr._incl = incl;
    removeAll();
    fillSet();
}
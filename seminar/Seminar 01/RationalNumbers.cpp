#include<iostream>

//Дефинираме структура, която ни описва рационално число 
//Всяко рационално число дефинираме като наредена двойка 
//от числител и знаменател
struct Rational{
    int num;
    int denom;
};

//Проверерка дали даденaта дроб е валидна
//Не искаме 0 в знаменател :)
bool isValid(const Rational& fraction){
    return fraction.denom != 0;
}

void printRationalNumber(const Rational& fraction){
    std::cout<<fraction.num<<"/"<<fraction.denom<<std::endl;
}

//Намираме най-голям общ делител с алгоритъм на Евклид
unsigned findGcd(unsigned a, unsigned b){
    if(b > a){
        std::swap(a, b);
    }
    while(b != 0){
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// Операция съкращаване   
void reduceFraction(Rational& fraction){
    if(!isValid(fraction)){
        std::cout<<"The given fraction is not valid. 0 in denominator!\n";
    }
    else {
        int gcdFrac = findGcd(fraction.num, fraction.denom);
        fraction.denom /= gcdFrac;
        fraction.num /= gcdFrac;
    }
}

//Имитираме работата на оператор += за дроби
// a / b += c/ d  
// a / b = a*d + c *b / b* d 
// Съкращаваме новата стойност на a/b 
// Връщаме Rational&, за да можем да влагаме 
// извикванията на addToFraction
Rational& addToFraction(Rational& lhs, const Rational& rhs){
    lhs.num *= rhs.denom;
        lhs.num += rhs.num * lhs.denom;
    lhs.denom *= rhs.denom;
    reduceFraction(lhs);
    return lhs;
}

Rational addTwoFractions(const Rational& lhs, const Rational& rhs){
    Rational sumTwo = lhs;
    addToFraction(sumTwo, rhs);
    return sumTwo;
}

int main(){
    Rational f1 = {1, 2};
    Rational f2 = {1, 3};
    Rational f3 = {1, 2};

    //Пример за вложено извикване на addToFraction
    addToFraction(addToFraction(f1, f2), f1);
    printRationalNumber(f1);
}
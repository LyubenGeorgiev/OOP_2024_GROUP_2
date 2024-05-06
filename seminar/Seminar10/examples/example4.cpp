#include<iostream>
using namespace std;

class Base {};

class Derived: public Base {};

int main() {
    Base *bp = new Derived;
   // Derived *dp = new Base; // error
}
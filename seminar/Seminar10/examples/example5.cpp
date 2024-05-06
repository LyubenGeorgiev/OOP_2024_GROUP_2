#include <iostream>
using namespace std;

class Animal {
  public:
  int legs = 4;
};
class Dog : public Animal {
  public:
  int tail = 1;
};
int main() {
  Dog d;
  cout << d.legs;
  cout << d.tail;
}
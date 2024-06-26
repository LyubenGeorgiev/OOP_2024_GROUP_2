# 🖥️Предефиниране на оператори. Приятелски класове и функции. 🖥️

### ☠️Не пишем А(){}, a използваме А() = default; За да напишем A() = default, то член данните ни задължително трябва да са инициализирани или да имат дефолтен конструктор☠️

Кaкво ще се случи, ако се извика копи конструктора на `Test`?
```cpp
class Test{
    int t = 0;
public:
    Test() = default;
    Test(Test other);
}
```

**Отговор:** В копи конструктора на Test извикваме копи конструктора на Test, защото подаваме тест по копие и това ни препраща към копи конструктора на Test, в който сме и се получава бездънна рекурсия.

Нужно ли е да разписваме голямо 4 в тази ситуация?
```cpp
class A{
    char* name = nullptr;
public:
    А() = default;
    A(const A&);
    A& operator=(const A&);
    ~A();
};

class X{
    A obj;
};
```

В тази ситуация не трябва да се разписва голямата четворка на X, защото въпреки, че Х работи с "външен ресурс" копи конструкторът на Х ще извика копи конструктора на А и данните ще се копират без проблем. Аналогично за оператор = и деструктора, даже и дефолтния конструктор на Х.

### ☠️Koгато викаме К.К. , първо се викат К.К. на член-данните☠️


## Предефениране на оператори

Предефинирането на оператори ни позволява да дефинираме поведение на оператор, който се прилага върху операнда(и) от даден тип. Те са функции със специални имена: ключовата дума operator последвана от символа на респективния оператор (например operator=). Както всяка функция, те имат return type, лист от аргументи и тяло.

### в C++ има три вида оператори:

 - Унарни (на един аргумент)
 - Бинарни (на два аргумента)
 - Тернарен (на три аргумента) - **НЕ МОЖЕ ДА СЕ ПРЕДЕФИНИРА**

### Операторите се характеризират с:
 -  Приоритет 
 -  Асоциативност 
 -  Позиция на оператора спярмо аргумента - *префиксен*, *инфиксен* и *суфиксен*

```
Разглеждаме израза a~b~c~d~f. Нека бинарната операция ~ е:
- ляво асоциативна. Тогава израза приема вида ((((a~b)~c)~d)~f) - слагаме скобки в ляво
- дясно асоциативна. Тогава израза приема вида (a~(b~(c~(d~f)))) - слагаме скобки от дясно
```
### ☠️ Можем да предефинираме единствено съществуващи вече оператори и не можем да създаваме нови "операторни" символи☠️

### Списъка на операторите в C++:
| Оператор                                       | Асоциативност                   |
|------------------------------------------------|---------------------------------|
| () [] -> . ++ - -                              |         ляво асоциативен         |
|  + - ! ~ ++ - - (type)* & sizeof               |         дясно асоциативен        |
| * / %                                          |         ляво асоциативен         |
|  + -        									 |         ляво асоциативен         |
|    << >>      								 |         ляво асоциативен         |
|  <  <=  >  >=         						 |         ляво асоциативен         |
|    ==  !=       								 |         ляво асоциативен         |
|      &     									 |         ляво асоциативен         |
|     ^      									 |         ляво асоциативен         |
|      \|     									 |         ляво асоциативен         |
|       &&    									 |         ляво асоциативен         |
|      \|\|     								 |         ляво асоциативен         |
|      ?:    									 |         дясно асоциативен        |
|     =  +=  -=  *=  /=  %=  >>=  <<=  &=  ^=    |         дясно асоциативен        |

- Пример за унарни оператори: ++, --, *
- Пример за бинарни опеартори: +=,+, - ...


## Въпрос: Кога дефинираме един оператор като член-функция?

При предефиниране на оператори трябва да решим - да се дефинира ли като член-функция или не. В някои случаи нямаме избор, в други няма да успеем да дефинираме оператора подходящо, ако е дефиниран като член-функция.
Следните "правила" могат да се следват като насока при решаване на този проблем:

- Присвояващия (=), индексния ([] - за достъпване на елемент, предимно при контейнери), function-call (()) и member access (-> - за достъпване на елементи, при итератори и smart pointer-и) трябва да бъдат дефинирани като членове;
- Съставните присвояващи оператори обикновено трябва да бъдат дефинирани като членове. За разлика от = обаче, те не са задължени да бъдат такива;
- Оператори, които променят състоянието на техния обект (такива като операторите за инкрементиране, декрементиране и дереференциране) обикновено се дефинират като членове;
- Симетричните оператори - тези, които могат да преобразуват коя-да е от операндите, напр. аритметичните, релационните, побитовите - обикновено се дефинират извън класа;

Aко първият операнд на даден оператор е наш обект Х, то този оператор може да бъде написан като вътрешен за класа.

### ☠️Поне един от параметрите в предефинирания оператор трябва да бъде дефиниран от нас тип (можем да предефинираме operator+(int, Mystring), но не и operator+(int, double))☠️
### ☠️Всички оператори запазват своята *приоритетност* и *асоциативност*, броя и позицията на *аргументите* си☠️

### ☠️ Ограничения
- почти всеки съществуващ оператор в C++ може да бъде предефиниран
- изключенията са: 
    - conditional ?:
    - sizeof
    - scope ::
    - member selector .
    - pointer member selector .*
    - typeid и casting
    
## Приятелски класове и приятелски функции
Декларират се със запазената дума **friend** пред прототипа на функцията.  
**Дефиниция:** Приятелксата функция е външна функция за клас, която има достъп до private и protected член-данните.

```cpp
class A{
    int n;
    int x;

    public:
    friend void f(A obj);
};

void f(A obj){
    obj.n++;
    obj.x++;
}
```

**Дефиниция** Приятелски клас е външен клас, който има достъп до private и protected членовете на текущия клас.

Приятелски класове/функции:

- Не се наследяват
- Не са транзитивни (приятелски клас на ваш приятелски клас, не е приятелски клас на вас)
- Може да се напишат в private, protected, public частта на class-a (Добрата практика е само в public)

## Предефиниране на оператор за поток:
```cpp
ostream& operator<<(ostream& os, const A& obj){
    ...
    return os
}
istream& operator>>(ifstream& is, A& obj){
    ...
    return is;
} 
```
Operator << и operator >> трябва да са външни за класа, защото ако бяха вътрешни, то левият параметър щеше да е обекта (логично е левият параметър да е потока, а десният - обекта).

Ако функцията(оperator>>) e външна, то тя променя член-данните на обекта и ако нямаме реализирани мутатори(сетъри), то тогава трябва (а и е по-удобно, дори и да имаме мутатори) да я направим приятелска.

Какво би станало, ако някой от оператор >> или оператор << бяха вътрешни за класа?

```cpp
class A{
    int n;
public:
    A(int _n) : n(_n){}
    std::ostream& operаtor<<(std::ostream& os){
        os << n;
        return os;
    }
};

int main(){
    A a(42);
    a << std::cout; // Outputs 42
    n.operator<<(std::cout); // може да го напишем и така
    std::cout << a; // ERROR!
} 
```

![crying_cat](img/crying_cat.jpg)

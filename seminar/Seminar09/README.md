# 🖥️Move семантики🖥️

## Exceptions - бърз преговор
- Обработка
- Видове грешки
- Изключения в конструкторите
- Изключения в деструкторите

## Exception safety
Дадена операция върху обект е exception safety, ако обектът остане във валидно състояние, дори когато операцията е прекратена от хвърлянето на изключение.
### Нива на сигурност 
- ***No-throw guarantee*** – гарантирано е, че няма да бъде хвърлено изключение
- ***Strong exception safety*** – възможно е да бъде хвърлена грешка, но въпреки това обектът няма да промени състоянието си (т.е. обектът ще запази непокътнати оригиналните си стойности)
```cpp
Strong& operator=(String const& other){
    String temp(other);
    temp.swap(*this);
    return *this;
}
```
Предоставянето на силна гаранция може да бъде скъпо. Например, представете си, че обектът `Strong` в примера разпределя големи количества памет. Вместо да използва повторно вече разпределената памет, временното трябва да разпредели нова памет само за да освободи старата след размяната.

- ***Basic (weak) exception safety*** – възможно е да се хвърли изключение, но обектът може да се използва и след това. (т.е. обектът ще бъде във валидно състояние, което обаче е възможно да се различава от оригиналното)

- ***No exception safety*** – нямаме гаранция за нищо

Както Strong exception safety, така и Basic exception safety са в сила при условие, че операцията не оставя обекта в невалидно състояние. Също така и двете нива гарантират, че няма leak-ове на ресурси. Това означава, че за да постигнем добро ниво на сигурност, трябва да се погрижим при хвърляне на изключение, операцията не само да оставя обектите в добре дефинирани състояния, но и да освободи придобитите ресурси (като външна памет, потоци и т.н.) или предаде на обект, който гарантира, че ще се погрижи за правилното освобождаване ресурсите

## Моve сематики

### Tипове стойности в С++
- ***lvalue*** – изрази (прoменливи/обекти/функции, връщащи референция към някакъв тип), които притежават някакъв адрес в паметта
-	***prvalue*** – литерали (7, nullptr, false)/функции, връщащи по копие
- ***xvalue*** – идва от expiring value и се отнася за обекти, които са към края на жизнения си цикъл
- ***rvalue = prvalue + xvalue*** – изрази, които не са lvalue

### Rvalue reference
***Rvalue reference*** - Важният детайл дотук е, че rvalue изразите се отнасят главно към обекти, които са временни, т.е. са пред изтриване. Би било хубаво да можем по някакъв начин да можем да разпознаваме точно такива обекти, т.е. да разпознаваме дали някакъв израз връща някаква временна променлива и да го пренапишем по различен начин, ако случаят е такъв. Точно тук идва и ролята на rvalue референциите. До C++11 референции към константна rvalue са възможни, но те не могат да изменят обекта. При C++11 се въвежда нов тип референция, а именно rvalue референцията, която позволява референция към rvalue. С други думи, rvalue референциите са идеалният начин за разпознаване дали една стойност заема място в паметта или не. За разлика от lvalue референциите, те се пишат с &&. Т.к. rvalue референциите могат да сочат единствено към временни обекти. Това означава, че код, който използва rvalue референция свободно може да си присвои ресурсите му. Въпреки, че rvalue референции не могат да сочат към lvalue-та, можем да cast-нем lvalue към xvalue(в съответстващата й rvalue референция). На практика move казва на компилатора да третира x като rvalue.(конвентира x, който е lvalue, към xvalue) Добре, с какво ни помагат този вид референции? Ами, вече разполагаме с апарат, който еднозначно ни казва кога един израз е lvalue и кога е rvalue, т.е. можем да предефинираме една функционалност да работи по два различни начина - по един при работа с lvalue изрази, а по друг с rvalue такива. 

```cpp
int i = 42;
int &r = i; // ok: r refers to i
int &&rr = i; // error: cannot bind an rvalue reference to an lvalue

int &r2 = i * 42; // error: i * 42 is an rvalue
const int &r3 = i * 42; // ok: we can bind a reference to const to an rvalue
int &&rr2 = i * 42; // ok: bind rr2 to the result of the multiplication
```

- ако искаме да пренасочим rvalue reference към lvalue, можем да преобразуваме lvalue към xvalue, използвайки функцията `std::move()`

- това е временно преобразуване - обекта си остава lvalue и животът му не се прекратява

```cpp
int x = 5;
int&& xRRef = x;   //Error: rvalue reference cannot be bound to an lvalue

int&& xRRef = std::move(x);  //Ok
```

## Предимства
- rvalue референциите удължават живота на обекта
- неконстантните rvalue референции позволяват да променяме стойността
 - можем да предефинираме фунцкионалности, в които спестяваме излишни копия, ако обектите са временни
- компилаторът сам преценява коя функция да извика - в зависимост от това дали му се подаде lvalue или rvalue

```cpp
void print(const MyString& str) {
        std::cout << str;
}
 
void print(MyString&& str) {
        std::cout << str;
}

MyString name = "Pesho";

print(name);  //lvalue
print("Ivan");   //rvalue
```

### Move конструктор & Move Assignment оператор
Move конструкторът, както и копи конструкторът, приема референция към същия тип, с разликата, че това е rvalue референция, при това неконстантна. Идеята е следната - при създаване на обекта, крадем ресурсите на обекта, към който е референцията и го оставяме в такова състояние, че последващото му изтриване да не навреди на новосъздадения обект. При примитивните типове данни това е просто копиране. Вече при указателите, при които наша имплементация на copy контрола би наложила дълбоко копиране, е малко по-различно
```cpp
Student::Student(Student&& other): noexcept: name(other.name), age(other.age){
    other.name = nullptr;
}
```

Т.е. слагаме name да сочи към парчето памет, към което сочи toMove.name (а не заделяме наново динамична памет!), също казваме age = toMove.age. В тялото слагаме името на toMove да сочи към nullptr, т.е. при изтриване той няма да навреди по никакъв начин на обекта, в който местим ресурсите.

### Синтезирани move операции 
```cpp
Person& operator=(Person&& other) noexcept{
    if(this != &other){
        free(); // Free the resources associated with this
        name = other.name;
        age = other.age;
        other.name = nullptr; //put other in a state where deleting won't cause problem in further uses of this
    }
    return *this;
}
```
Както и при копи конструктура, copy assignment оператора и деструктура, компилаторът автоматично ще синтезира move конструктор и move assignment оператор. Единствената разлика тук е, че условията, при които той прави това са различни. За разлика от копи операциите, за някои класове компилаторът изобщо не създава move конструктор и move assignment оператор. В частност, ако един клас дефинира свой copy конструктор, copy assignment оператор или деструктор, то move конструкторът и copy assignment операторът няма да бъдат синтезирани. Aко един клас няма move операции, то се използват copy такива (даже върху временни обекти, като точно това целим да избегнем), ако такива има разбира се. Компилаторът ще създаде move конструктор и move assignment оператор ако класът няма дефиниран copy control и ако всеки член може да бъде "преместен". Компилаторът може да премества вградени типове, а също и класове, които имат съответната move операция дефинирана. При примитивните типове данни местенето е просто копиране. Ако експлицитно помолим компилатора да генерира move операция чрез =default, и компилаторът не успее да синтезира такъв, то той бива маркиран като =deleted.


## Пример за UniquePtr - обект, който държи указател към друг обект
Към този обект трябва да има най-много един насочен указател (може да е различен от този, който го е създал)
Unique указателят ни помага да управляваме паметта като предотвратява изтичането на памет.
Забранени са оп= и к.к. (нямаме копиране, за да гарантираме, че към даден обект може да бъде насочен само един указател, от там идва името)
Причината, поради която се налага това, е че указателят към даден обект трябва да бъде уникален (т.е. единствен) и да наложи уникална собственост над ресурсите (т.е. да няма друг указател насочен към тях). Копирането на unique pointer, както и присвояването, би довело до два unique указателя, всеки от тях вярващ, че е негова отговорност да се грижи за ресурсите, към които е насочен.
Но можем да използване move семантиките и по този начин да преместим собствеността на уникален указател.

### Със съдействието на К.Калемджиева

## 📚Допълнителни материали📚
- [exceptions](https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm)
- [lvalues and rvalues in C++](https://www.youtube.com/watch?v=fbYknr-HPYE) - the Cherno
- [Move semantics in C++](https://www.youtube.com/watch?v=ehMg6zvXuMY&t=37s) -the Cherno
- [std::move and the Move Assignment Operator in C++](https://www.youtube.com/watch?v=OWNeCTd7yQE&t=5s) - the Cherno
## [🧩Куиз с въпроси от семинар 9🧩](https://docs.google.com/forms/d/e/1FAIpQLSf0K6AJolGpYpyMUlDJ48KmWFSVWRrIsJtVVTR3Flkorg9NMw/viewform)
![happy_corgi](img/happy_corgi.jpg)
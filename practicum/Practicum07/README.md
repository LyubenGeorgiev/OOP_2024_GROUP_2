# Още предефиниране на оператори и приятели

## Задача 1 :clock3:
Нека работим в неймспейс `time`:

Да се реализира клас `Duration`, който няма сетъри (секундите са private) и се създава с дефолтен конструктор слагащ секундите на 0. Оператор ++, -- нека да добавят/махат секунда от `Duration`. Направете константи от тип `Duration` за секунда, минута, час. Искаме да предефинираме оператор +, +=, -, -= за нашият клас. Понеже би било удобно човека да напише нещо като:
* `dur += 5 * time::Second`
* `dur += 5 * time::Minute`
* `dur += 5 * time::Hour`

Съответно бихме очаквали да работят и наобратно:
* `dur += time::Second * 5`
* `dur += time::Minute * 5`
* `dur += time::Hour * 5`

Съответно се налага да предефинираме оператор *

Искаме също всякакви оператори за сравнение <,>,==, <=,>=,!=.

## Задача 2 :clock3:
Да се реализира клас `Time`, за целта композирайте `Duration` в `Time` като внимавайте с това че часът е ограничен между [00:00:00 - 23:59:59]. Предефинирайте следните оператори за час:

```Time t1, t2, t3, t4, t5;```

* `t3 = t1 + t2`
* `t4 = t1 + 5 (добавя 5 часа)`
* `t5 = 6 + t1 (добавя 6 часа)`
* `++t3 (добавя 1 час)`
* `t4++ (добавя 1 час)`
* `t1 < t2`
* `std::cout << t1 << t2 << t3 << t4 << t5`
* `std::cin >> t1 >> t2 >> t3 >> t4 >> t5`
* `t1[Time::HOURS] = t2[Time::HOURS] = t3[Time::HOURS] = t4[Time::HOURS] = t5[Time::HOURS]`
* `t1[Time::MINUTES] = t2[Time::MINUTES] = t3[Time::MINUTES] = t4[Time::MINUTES] = t5[Time::MINUTES]`
* `Time::HOURS, Time::MINUTES, Time::SECONDS са от изброим тип`

## Бонус (Big number) :eight::six::seven::six::two::four::eight::eight::five::seven::five:...:eight::seven:
Реализирайте клас `BigNumber`, който представя цяло число (положително или отрицателно) с голяма дължина - "дълго число". Както знаем, най-големият примитивен тип, използван за цели числа в С++, е `long long int`, но той поддържа "само" :clown_face: числата от -(2^63) до (2^63)-1. Целта на нашата задача е да работим дори с още по-големи числа, които практически нямат ограничение в дължината си.

За представяне на числата трябва да използвате саморазширяващи се масиви с елементи от тип `char`, като всеки един символ представя една десетична цифра.

### Конструктори :hammer_and_wrench:

Един обект от класа `BigNumber` трябва да може да се конструира по всеки един от следните три начина:

```c++
/**
 * @brief Default constructor, sets the value of the number to 0
 */
BigNumber();

/**
 * @brief Constructor with parameter
 * 
 * @param number a number represented as a string
 */
BigNumber(const char* number);

/**
 * @brief Constructor with parameter
 * 
 * @param number a number represented as an integer
 */
BigNumber(long long int number);
```

### Копиране и унищожаване :infinity:

Гарантирайте, че обектите от тип `BigNumber` могат да се копират и унищожават коректно. Ако е нужно, реализирайте експлицитно всички функции от Rule of 3. Ако това не е нужно, следвайте Rule of 0.

### Оператори :heavy_plus_sign::heavy_minus_sign::heavy_multiplication_x::heavy_division_sign:

Предефинирайте следните оператори:

```c++
bool operator == (const BigNumber& other) const;
bool operator != (const BigNumber& other) const;
bool operator < (const BigNumber& other) const;
bool operator > (const BigNumber& other) const;

BigNumber& operator += (const BigNumber& other);
BigNumber operator + (const BigNumber& other) const;
BigNumber& operator -= (const BigNumber& other);
BigNumber operator - (const BigNumber& other) const;
BigNumber& operator *= (const BigNumber& other);
BigNumber operator * (const BigNumber& other) const;

BigNumber& operator ++ ();
BigNumber operator ++ (int);

BigNumber& operator -- ();
BigNumber operator -- (int);

BigNumber& operator - ();

BigNumber& operator /= (const BigNumber& other);
BigNumber operator / (const BigNumber& other) const;
BigNumber& operator %= (const BigNumber& other);
BigNumber operator % (const BigNumber& other) const;
```

### Четене и писане от конзолата :keyboard::printer:

Реализирайте подходящи методи за:

- четене на дълго число от конзолата 
- отпечатването на дълго число на конзолата


### Демо :sunglasses:

Демонстрирайте реализацията на вашия клас чрез кратка програма, тестваща функционалността на всички изброени по-горе методи и оператори.

### Малко тестове :heavy_check_mark::x:

Ако реализацията на вашия клас е правилна, всички редове би трябвало да върнат `true`:

```c++
std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") > BigNumber("4767846784647856547476")) << std::endl;
std::cout << std::boolalpha << (BigNumber("4767846784647856547476") < BigNumber("7643276342876783246893247")) << std::endl;
std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") != BigNumber("4767846784647856547476")) << std::endl;
std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") == BigNumber("7643276342876783246893247")) << std::endl;

std::cout << std::boolalpha << ((BigNumber("12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("12350033579332211025")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") - BigNumber("4354678097643135")) == BigNumber("12341324223136924755")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("53761457511741137249987999149935150")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") / BigNumber("4354678097643135")) == BigNumber("2835")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") % BigNumber("4354678097643135")) == BigNumber("166494416280165")) << std::endl;

std::cout << std::boolalpha << ((BigNumber("-12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("-12341324223136924755")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("-12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("-53761457511741137249987999149935150")) << std::endl;
```

### :warning: Забележки

- Погрижете се за правилното използване на динамична памет и не допускайте memory leaks
- Целете се към максимално спазване на чист код
- Не е позволено използването на `std::string`
- Позволено е използването на библиотеките `<cstring>`, `<cassert>` и `<cstddef>`
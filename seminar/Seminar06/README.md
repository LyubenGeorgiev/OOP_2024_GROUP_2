# 🖥️ Семинар 6: Динамична памет в класове. Голяма четворка. 🖥️

## Голямата четворка
- Конструктор по подразбиране (конструктор без параметри)
- Конструктор за копиране
- Оператор =
- Деструктор

## ☠️Разписваме голямата 4-ка винаги, когато имаме "външен ресурс" в класа ☠️

## Задачи:

**Задача 1:** Да се напише клас `MyString`, които съдържа полета за:
- низ с проиволна дължина
- дължина на масива
Напишете и метод, който връща дължината на низа. 

**Задача 2:**  Напишете клас Set, който съдържа множество от числа (без повторения) в диапазона от 0 до n-1, където n е подадено в началото (1 <= n <= 1000). Класът трябва да пази дали съдържа дадено число в битове, т.е ако съдържа дадено число, съответвеният последователен бит ще бъде 1, в противен случай 0. Пример:

{3, 4, 6} => битове на множеството ще бъдат 00011010

{1, 8, 9} => 01000000 11000000

Класът трябва да има следните функции.

- Добавяне на число
- Проверка дали съдържа число
- Принтиране на всички числа, които съдържа
- Принтиране на това как е представено в паметта
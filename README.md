# Библиотека, реализующая работу с поляризованными полиномами над произвольным полем.

## Использует библиотеку FieldVec отсюда (библиотека добавлена в исходные файлы проекта):
https://github.com/ShuryginDM/FieldVec

## Как и при любом другом использовании FieldVec необходимо явным образом указать значение FieldVec::q (притом q должно быть простым, иначе может произойти throw DivisionOnZero)

### Лучше использовать BoolFieldElem, чем FieldElem при FieldVec::q == 2

### Сам неприводимый многочлен необходимо указывать самостоятельно перед первой инициализацией (пример получения таких многочленов есть в примерах Example1 и Example1_1 здесь https://github.com/ShuryginDM/FieldVec ). Перед инициализацией элемента FieldElem необходимо установить значение FieldElem::irreducible_polynominal а для BoolFieldElem BoolFieldElem::irreducible_polynominal

### Документация, сгенерированная в Doxygen лежит в директории Docs

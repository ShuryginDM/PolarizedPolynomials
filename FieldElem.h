/**
* @mainpage Библиотека работы с поляризованными полиномами над произвольным полем.
* @author Шурыгин Дмитрий Михайлович, 318 ВМК МГУ, 2017
* [FieldVecLink]: https://github.com/ShuryginDM/FieldVec
* @warning для работы требуется [библиотека FieldVec][FieldVecLink]
*/

#ifndef FIELD_ELEM_H
#define FIELD_ELEM_H

#include <algorithm>
#include <iostream>

#include "FieldVec.h"


/**
* @brief Класс, реализующий элемент произвольного поля.
*
* @details Реализует работу с поляризованным полиномом над полем
* из \f[FieldVec::q ^ {FieldElem::irreducible\_polynomial.size()} \f] элементов \n
* Перед первой инициализацией переменной класса FieldElem должны быть явно \n
* указаны FieldVec::q и FieldElem::irreducible_polynomial \n
* q должно принимать значения >= 2 \n
* irreducible_polynomial - неприводимый полином необходимой степени. Пример получения такого
* [FieldVecLink]: https://github.com/ShuryginDM/FieldVec
* полинома есть в [примере использования библиотеки FieldVec Example1][FieldVecLink]
*/
class FieldElem
{
public:
    /**
    * Элемент поля - остаток от деления на неприводимый многочлен irreducible_polynomial
    */
    static FieldVec irreducible_polynomial;
    
    /**
    * Конструктор. Создает полином, равный 0 в поле
    */
    FieldElem(){}

    /**
    * Конструктор. Создает полином, равный z в виде записи этого числа в FieldVec::q-ричной системе счисления
    */
    FieldElem(unsigned long long z);

    FieldElem(FieldVec &t);

    FieldElem &operator+=(FieldElem &a);

    FieldElem operator+(FieldElem &a);

    FieldElem &operator*=(FieldElem &a);

    FieldElem operator*(FieldElem &a);

    /**
    * Возведение элемента в степень p. При p=0 степень равна 1.
    */
    FieldElem pow(unsigned int p);

    bool operator==(const FieldElem &a){
        return v == a.v;
    }

    inline bool operator!=(const FieldElem &rhs){ return !(*this == rhs); }

    /**
    * Вывод в виде целого неотрицательного числа, запись v которого - запись в FieldVec::q-ричной системе счисления
    * (в обратном порядке)
    */
    friend std::ostream& operator<<(std::ostream& os, FieldElem &z){
        unsigned long long w = 0;
        for(int i = z.v.size() - 1; i >= 0 ; i--){
            w *= FieldVec::q;
            w += z.v[i];
        }
        os << w;
        return os;
    }
private:
    /**
    * Элемент поля - остаток от деления на неприводимый многочлен irreducible_polynomial
    */
    FieldVec v;
};

/**
* @brief Класс, реализующий элемент поля из 2 ^ k элементов
*
* @details Реализует работу с поляризованным полиномом над полем
* из \f[2 ^ {BoolFieldElem::irreducible\_polynomial.size()} \f] элементов \n
* Перед первой инициализацией переменной класса BoolFieldElem должен быть явно \n
* указан BoolVec::irreducible_polynomial \n
* irreducible_polynomial - неприводимый полином необходимой степени. Пример получения такого
* [FieldVecLink]: https://github.com/ShuryginDM/FieldVec
* полинома есть в [примере использования библиотеки FieldVec Example1][FieldVecLink] \n\n
* ###Лучше использовать этот класс, чем FieldElem при FieldVec::q == 2.
*/
class BoolFieldElem
{
public:
    /**
    * Элемент поля - остаток от деления на неприводимый многочлен irreducible_polynomial
    */
    static BoolVec irreducible_polynomial;
    
    /**
    * Конструктор. Создает полином, равный 0 в поле
    */
    BoolFieldElem(){}

    /**
    * Конструктор. Создает полином, равный z в виде записи этого числа в двоичной системе счисления
    */
    BoolFieldElem(unsigned long long z);

    BoolFieldElem(BoolVec &t);

    BoolFieldElem &operator+=(BoolFieldElem &a);

    BoolFieldElem operator+(BoolFieldElem &a);

    BoolFieldElem &operator*=(BoolFieldElem &a);

    BoolFieldElem operator*(BoolFieldElem &a);

    /**
    * Возведение элемента в степень p. При p=0 степень равна 1.
    */
    BoolFieldElem pow(unsigned int p);

    bool operator==(const BoolFieldElem &a){
        return v == a.v;
    }

    inline bool operator!=(const BoolFieldElem &rhs){ return !(*this == rhs); }

    /**
    * Вывод в виде целого неотрицательного числа, запись v которого - запись в FieldVec::q-ричной системе счисления
    * (в обратном порядке)
    */
    friend std::ostream& operator<<(std::ostream& os, BoolFieldElem &z){
        unsigned long long w = 0;
        for(int i = z.v.size() - 1; i >= 0 ; i--){
            w <<= 1;
            w ^= z.v[i];
        }
        os << w;
        return os;
    }
private:
    /**
    * Элемент поля - остаток от деления на неприводимый многочлен irreducible_polynomial
    */
    BoolVec v;
};

#endif

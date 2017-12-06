#ifndef POLARIZED_MONOMIAL_H
#define POLARIZED_MONOMIAL_H

#include <vector>

#include "FieldElem.h"

/**
* @brief Класс, используемый для того, чтобы показать тип исключения "разное число переменных"
*
* @details Может появляться в нескольких случаях:
* - длины вектора поляризации и вектора степеней монома различны при инициализации монома
* - длины вектора поляризации и вектора значений переменных различны
* - была изменена длина вектора поляризации после инициализации монома
*/
class DifferentSize{};

/**
* @brief Класс, реализующий поляризованный моном над произвольным полем с произвольным числом переменных
*
* @details Реализует работу с поляризованным полиномом над полем
* из \f[FieldVec::q ^ {FieldElem::irreducible\_polynomial.size()} \f] элементов \n
* Перед первой инициализацией переменной класса PolarizedMonomial должны быть явно \n
* указаны FieldVec::q, FieldElem::irreducible_polynomial и PolarizedMonomial::polarization \n
* q должно принимать значения >= 2 \n
* polarization - поляризация монома.
* @warning одновременно возможна работа только с мономами с одинаковой поляризацией
*/
class PolarizedMonomial{

public:

    /**
    * Поляризация монома. При работе с несколькими мономами, у всех мономов будет одинаковая поляризация
    */
    static std::vector<FieldElem> polarization;

    /**
    * Конструктор. Количество элементов pows должно совпадать с количеством элементов polarization
    * @throw DifferentSize если количество элементов pows и количество элементов polarization различны
    */
    PolarizedMonomial(std::vector<unsigned int> &pows);

    PolarizedMonomial();

    PolarizedMonomial(PolarizedMonomial &m);

    /**
    * Функция подсчета значения монома в точке
    * @throw DifferentSize если Количество элементов p не равно числу переменных монома
    */
    FieldElem val_in_point(std::vector<FieldElem> &p);

    /**
    * мономы равны, если равны степени при соответствующих переменных
    * @throw DifferentSize если число переменных монома a и текущего монома не равны
    * @throw DifferentSize если число переменных монома a и число элементов вектора поляризации не равны
    */
    bool operator==(PolarizedMonomial &a);

    /**
    * Произведение монома на моном. Просто складывает степени при соответствующих переменных
    * @throw DifferentSize если число переменных монома m и текущего монома не равны
    * @throw DifferentSize если число переменных монома m и число элементов вектора поляризации не равны
    */
    PolarizedMonomial &operator*=(PolarizedMonomial &m);

    /**
    * Произведение монома на моном. Просто складывает степени при соответствующих переменных
    * @throw DifferentSize если число переменных монома m и текущего монома не равны
    * @throw DifferentSize если число переменных монома m и число элементов вектора поляризации не равны
    */
    PolarizedMonomial operator*(PolarizedMonomial &m);

    friend std::ostream& operator<<(std::ostream& os, const PolarizedMonomial &q){
        unsigned int count = 0;  
        for(unsigned int i = 0; i < polarization.size(); i++){
            if(!(q.powers[i])){
                continue;
            }
            count++;
            FieldElem t = polarization[i];
            os << "(x_{" << i+1 << "}";
            if(t != 0){
                os << " + " << t << ")";
            }else{
                os << ")";
            }
            if(q.powers[i] > 1){
                os << "^{" << q.powers[i] << "}";
            }
        }
        if(!count){
            os << "1";
        }
        return os;
    }

private:
    std::vector<unsigned int> powers;
};


/**
* @brief Класс, реализующий поляризованный моном над полем четной характеристики
*
* @details Реализует работу с поляризованным полиномом над полем
* из \f[2 ^ {FieldElem::irreducible\_polynomial.size()} \f] элементов \n
* Перед первой инициализацией переменной класса v должны быть явно \n
* указаны BoolFieldElem::irreducible_polynomial и BoolPolarizedMonomial::polarization \n
* @warning одновременно возможна работа только с мономами с одинаковой поляризацией \n \n
* Лучше использовать BoolPolarizedMonomial, чем PolarizedMonomial с FieldVec::q == 2
*/
class BoolPolarizedMonomial{

public:

    /**
    * Поляризация монома. При работе с несколькими мономами, у всех мономов будет одинаковая поляризация
    */
    static std::vector<BoolFieldElem> polarization;

    /**
    * Конструктор. Количество элементов pows должно совпадать с количеством элементов polarization
    * @throw DifferentSize если количество элементов pows и количество элементов polarization различны
    */
    BoolPolarizedMonomial(std::vector<unsigned int> &pows);

    BoolPolarizedMonomial(BoolPolarizedMonomial &m);

    BoolPolarizedMonomial();

    /**
    * Функция подсчета значения монома в точке
    * @throw DifferentSize если Количество элементов p не равно числу переменных монома
    */
    BoolFieldElem val_in_point(std::vector<BoolFieldElem> &p);

    /**
    * мономы равны, если равны степени при соответствующих переменных
    * @throw DifferentSize если число переменных монома a и текущего монома не равны
    * @throw DifferentSize если число переменных монома a и число элементов вектора поляризации не равны
    */
    bool operator==(BoolPolarizedMonomial &a);

    /**
    * Произведение монома на моном. Просто складывает степени при соответствующих переменных
    * @throw DifferentSize если число переменных монома m и текущего монома не равны
    * @throw DifferentSize если число переменных монома m и число элементов вектора поляризации не равны
    */
    BoolPolarizedMonomial &operator*=(BoolPolarizedMonomial &m);

    /**
    * Произведение монома на моном. Просто складывает степени при соответствующих переменных
    * @throw DifferentSize если число переменных монома m и текущего монома не равны
    * @throw DifferentSize если число переменных монома m и число элементов вектора поляризации не равны
    */
    BoolPolarizedMonomial operator*(BoolPolarizedMonomial &m);

    friend std::ostream& operator<<(std::ostream& os, const BoolPolarizedMonomial &q){
        unsigned int count = 0;  
        for(unsigned int i = 0; i < polarization.size(); i++){
            if(!(q.powers[i])){
                continue;
            }
            count++;
            BoolFieldElem t = polarization[i];
            os << "(x_{" << i+1 << "}";
            if(t != 0){
                os << " + " << t << ")";
            }else{
                os << ")";
            }
            if(q.powers[i] > 1){
                os << "^{" << q.powers[i] << "}";
            }
        }
        if(!count){
            os << "1";
        }
        return os;
    }

private:
    std::vector<unsigned int> powers;
};

#endif

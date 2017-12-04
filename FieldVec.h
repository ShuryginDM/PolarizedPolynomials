/**
*@mainpage Библиотека работы с кольцом многочленов над кольцом вычетов из q элементов.
*@author Шурыгин Дмитрий Михайлович, 318 ВМК МГУ, 2017
*/

#ifndef FIELDVEC_H
#define FIELDVEC_H

#include <vector>
#include <iostream>

/**
* @brief Класс, используемый для того, чтобы показать тип исключения "кольцо вычетов по модулю 0"
*/
class NullField{};

/**
* @brief Класс, используемый для того, чтобы показать тип исключения "кольцо вычетов по модулю 1"
*/
class OneField{};

/**
* @brief Класс, используемый для того, чтобы показать тип исключения "не является полем вычетом"
*/
class NotPrimal{};

/**
* @brief Класс, используемый для того, чтобы показать тип исключения "деление на 0"
*/
class DivisionOnZero{};


/**
* @class FieldVec
* @brief Основной класс.
*
* Реализует работу с кольцом многочленов над кольцом вычетов из q элементов
* Пример использования приведен в 
*
*\example Example1.cpp
*/
class FieldVec{

public:

    /**
    * @var q статическая переменная. Возможна работа только с кольцом полиномов только над кольцом вычетов по одному модулю.
    * В начале программы явным образом должно быть прописано 
    * FieldVec::q = <Количество элементов кольца вычетов>; (без <>)
    * Программа может некорректно обрабатывать старые векторы при изменении q
    */
    static unsigned int q;
    
    /**
    * @function FieldVec(void) Конструктор. При таком создании полином представляется в виде 0 * x ^ 0
    * @throw NullField если q == 0
    * @throw OneField если q == 1
    */
    FieldVec(void);

    /**
    * @function FieldVec(std::vector<unsigned int> v) Конструктор. Если в векторе v нет элементов, то полином представляется в виде 0 * x ^ 0,
    * иначе - коэффициентом при x^i будет v[i] 
    * @param[in] v Вектор коэффициентов. В v[i] коэффициент при x^i.
    * @throw NullField Если q == 0
    * @throw OneField Если q == 1
    */
    FieldVec(std::vector<unsigned int> &v);


    /** 
    * @function FieldVec(std::vector<unsigned int> v) Конструктор.
    * Записывает в var представление числа t в q-ричной системе счисления (в обратном порядке)
    */
    FieldVec(unsigned long long t);


    FieldVec(FieldVec const &v);

    /**
    * @function push_back(unsigned int t) Функция расширения вектора коэффициентов полинома.
    * @param[in] t Если хранится полином с максимальной степенью s (перед которой коэффициент, возможно, равен 0), то
    * к этому полиному добавляется t * q ^ (s + 1).
    */
    void push_back(const unsigned int &t);
    /**
    * @function size Показывает, сколько элементов находится в векторе коэффициентов
    * @return Максимальная степень x в этом многочлене (перед которой коэффициент, возможно, равен 0)
    */
    int size() const;

    /**
    * @param[in] t Степень монома x ^ t
    * @return lvalue коэффициент при x ^ t в полиноме. Если максимальная степень s (перед которой коэффициент, возможно, равен 0)
    *и s < t, то максимальная степень становиться равна t, а кожффициент при ней - 0.
    */
    unsigned int &operator[](const unsigned int &t);

    /**
    * @function operator+ Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec operator+(const FieldVec &v);
    /**
    * @function operator+= Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec &operator+=(const FieldVec &v);

    /**
    * @function operator* Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec operator*(const FieldVec &v);

    /**
    * @function operator*= Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю q
    */
    FieldVec &operator*=(const FieldVec &v);

    /**
    * @function operator== Оператор сравнение полиномов на равенство в кольце полиномов над кольцом вычетов по модулю q
    */
    bool operator==(const FieldVec &v);


    FieldVec operator-();

    FieldVec operator-(const FieldVec &v);

    FieldVec &operator-=(const FieldVec &v);


    /**
    * @function operator% Оператор вычисления остатка от деления полиномов в кольце полиномов над полем вычетов по модулю q
    * @throw NotPrimal если q - не простое число (в данном случае если коэффициент при наивысшей степени x является делителем q и
    * при этом не равен q)
    * @throw DivisionOnZero если v - вектор, состоящий из 0
    * @return остаток от деления на полином v
    */
    FieldVec operator%(const FieldVec &v);

    /**
    * @function operator/ Оператор вычисления результата деления полиномов в кольце полиномов над полем вычетов по модулю q
    * @throw NotPrimal если q - не простое число
    * @throw DivisionOnZero если v - вектор, состоящий из 0
    * @return результат деления на полином v
    */
    FieldVec operator/(FieldVec &v);

    friend std::ostream& operator<<(std::ostream &os, const FieldVec &v){
        os << "(";
        for(int i = 0; i < v.size() - 1; i++){
            os << v.var[i] << ";";
        }
        os << v.var[v.size() - 1];
        os << ")";
        return os;
    }

    /**
    * Префиксный инкремент. Подразумевается, что если v - объект класса FieldVec, то после ++v
    * к var[0] прибавляется 1. Если var[0] + 1 == q, то var[0] становится равным 0, а к var[1] прибавляется 1
    * (и так до тех пор, пока не дойдет до var[i], такого, что var[i] + 1 != q)
    */
    FieldVec &operator++(void);

    /**
    * Постфиксный инкремент. Подразумевается, что если v - объект класса FieldVec, то после v++
    * к var[0] прибавляется 1. Если var[0] + 1 == q, то var[0] становится равным 0, а к var[1] прибавляется 1
    * (и так до тех пор, пока не дойдет до var[i], такого, что var[i] + 1 != q)
    */
    FieldVec &operator++(int l);
    /**
    * @function tex_print
    * @brief Вывод полинома наподобие формулы LaTeX.
    * 
    * 
    * @param[in] std::ostream &os - поток вывода
    * @param[in] char *name - имя переменной (по умолчанию "x")
    *
    * ##Пример использования 1:
    *
    * Пусть q == 5, а в переменной FieldVec p хранится вектор коэффициентов
    * @code
    * (0;2;1;3;2;3)
    * @endcode
    * Тогда в результате выполнения команды
    * @code
    * p.tex_print(std::cout);
    * @endcode
    * на стандартный поток вывода поступит
    * @code
    * 3 x ^ { 5 } + 2 x ^ { 4 } + 3 x ^ { 3 } + x ^ { 2 } + 2 x 
    * @endcode
    *
    * И сама формула выглядит так:
    * \f[3 x ^ { 5 } + 2 x ^ { 4 } + 3 x ^ { 3 } + x ^ { 2 } + 2 x \f]
    *
    * ##Пример использования 2:
    *
    * Пусть q == 4, в переменной FieldVec p хранится вектор коэффициентов
    * @code
    * (2;3;1)
    * @endcode
    * а в переменной FieldVec r хранится вектор коэффициентов
    * @code
    * (3;2;1)
    * @endcode
    * Тогда в результате выполнения команды
    * @code
    * (p * r).tex_print(std::cout, "v_{12}");
    * @endcode
    * на стандартный поток вывода поступит
    * @code
    * v_{12} ^ { 4 } + v_{12} ^ { 3 } + 3 v_{12} ^ { 2 } + v_{12} + 2
    * @endcode
    *
    * И сама формула выглядит так:
    * \f[v_{12} ^ { 4 } + v_{12} ^ { 3 } + 3 v_{12} ^ { 2 } + v_{12} + 2 \f]
    */
    void tex_print(std::ostream &os, const char *name = "x");


    /**
    * @function set Устанавливает коэфиициент при x ^ z равным t % q 
    */
    void set(const unsigned int &z, const unsigned int &t);

private:
    /**
    * @var var - вектор коэффициентов. var[i] - коэффициент при x^i
    * Если не было явного объявления коэффициентов вектора, то в var лежит ровно одно значение:
    * var[0] == 0
    */
    std::vector<unsigned int> var;
    
};


/**
* @class BoolVec
* @brief Основной класс.
* 
* Реализует работу с кольцом многочленов над полем вычетов из 2 элементов
* Лучше оптимизирован, чем FieldVec с q == 2
* Пример использования приведен в
* 
* \example Example1.cpp
*/
class BoolVec{

public:
    
    /**
    * @function FieldVec(void) Конструктор. При таком создании полином представляется в виде 0 * x ^ 0
    */
    BoolVec();

    /**
    * @function FieldVec(std::vector<unsigned int> v) Конструктор. Если в векторе v нет элементов, то полином представляется в виде 0 * x ^ 0,
    * иначе - коэффициентом при x^i будет v[i] 
    * @param[in] v Вектор коэффициентов. В v[i] коэффициент при x^i.
    */
    BoolVec(std::vector<bool> &v);


    BoolVec(BoolVec const &v);

    /** 
    * @function FieldVec(std::vector<unsigned int> v) Конструктор.
    * Записывает в var представление числа t в двоичной системе счисления (в обратном порядке)
    */
    BoolVec(unsigned long long t);

    /**
    * @function push_back(unsigned int t) Функция расширения вектора коэффициентов полинома.
    * @param[in] t Если хранится полином с максимальной степенью s (перед которой коэффициент, возможно, равен 0), то
    * к этому полиному добавляется t * q ^ (s + 1).
    */
    void push_back(const bool &t);
    /**
    * @function size Показывает, сколько элементов находится в векторе коэффициентов
    * @return Максимальная степень x в этом многочлене (перед которой коэффициент, возможно, равен 0)
    */
    int size() const;

    /**
    * @param[in] t Степень монома x ^ t
    * @return rvalue коэффициент при x ^ t в полиноме
    */
    bool operator[](const unsigned int &t);

    /**
    * @function operator+ Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю 2
    */
    BoolVec operator+(const BoolVec &v);
    /**
    * @function operator+= Оператор сложения полиномов в кольце полиномов над кольцом вычетов по модулю 2
    */
    BoolVec &operator+=(const BoolVec &v);

    /**
    * @function operator* Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю 2
    */
    BoolVec operator*(const BoolVec &v);

    /**
    * @function operator*= Оператор умножения полиномов в кольце полиномов над кольцом вычетов по модулю 2
    */
    BoolVec &operator*=(const BoolVec &v);

    /**
    * @function operator== Оператор сравнение полиномов на равенство в кольце полиномов над кольцом вычетов по модулю 2
    */
    bool operator==(const BoolVec &v);


    BoolVec operator-();

    BoolVec operator-(const BoolVec &v);

    BoolVec &operator-=(const BoolVec &v);


    /**
    * @function operator% Оператор вычисления остатка от деления полиномов в кольце полиномов над полем вычетов по модулю 2
    * @throw DivisionOnZero если v - вектор, состоящий из 0
    * @return остаток от деления на полином v
    */
    BoolVec operator%(const BoolVec &v);

    /**
    * @function operator/ Оператор вычисления результата деления полиномов в кольце полиномов над полем вычетов по модулю 2
    * @throw DivisionOnZero если v - вектор, состоящий из 0
    * @return результат деления на полином v
    */
    BoolVec operator/(BoolVec &v);

    /**
    * Префиксный инкремент. Подразумевается, что если v - объект класса BoolVec, то после ++v
    * к var[0] прибавляется 1. Если var[0] + 1 == q, то var[0] становится равным 0, а к var[1] прибавляется 1
    * (и так до тех пор, пока не дойдет до var[i], такого, что var[i] + 1 != q)
    */
    BoolVec &operator++(void);

    /**
    * Постфиксный инкремент. Подразумевается, что если v - объект класса BoolVec, то после v++
    * к var[0] прибавляется 1. Если var[0] + 1 == q, то var[0] становится равным 0, а к var[1] прибавляется 1
    * (и так до тех пор, пока не дойдет до var[i], такого, что var[i] + 1 != q)
    */
    BoolVec &operator++(int l);

    friend std::ostream& operator<<(std::ostream &os, const BoolVec &v){
        os << "(";
        for(int i = 0; i < v.size() - 1; i++){
            os << v.var[i] << ";";
        }
        os << v.var[v.size() - 1];
        os << ")";
        return os;
    }

    /**
    * @function tex_print
    * @brief Вывод полинома наподобие формулы LaTeX.
    * 
    * 
    * @param[in] std::ostream &os - поток вывода
    * @param[in] char *name - имя переменной (по умолчанию "x")
    *
    * ##Пример использования 1:
    *
    * Пусть BoolVec p хранится вектор коэффициентов
    * @code
    * (0;1;1)
    * @endcode
    * Тогда в результате выполнения команды
    * @code
    * p.tex_print(std::cout);
    * @endcode
    * на стандартный поток вывода поступит
    * @code
    * x ^ { 2 } + x 
    * @endcode
    *
    * И сама формула выглядит так:
    * \f[x ^ { 2 } + x \f]
    *
    * ##Пример использования 2:
    *
    * Пусть BoolVec p хранится вектор коэффициентов
    * @code
    * (0;1;1)
    * @endcode
    * а в переменной BoolVec r хранится вектор коэффициентов
    * @code
    * (1;1;1)
    * @endcode
    * Тогда в результате выполнения команды
    * @code
    * (p * r).tex_print(std::cout, "v_{12}");
    * @endcode
    * на стандартный поток вывода поступит
    * @code
    * v_{12} ^ { 4 } + v_{12}
    * @endcode
    *
    * И сама формула выглядит так:
    * \f[v_{12} ^ { 4 } + v_{12} \f]
    */
    void tex_print(std::ostream &os, const char *name = "x");

    /**
    * @function set Устанавливает коэфиициент при x ^ z равным b 
    */
    void set(const unsigned int &z, const bool &b);

private:
    /**
    * @var var - вектор коэффициентов. var[i] - коэффициент при x^i
    * Если не было явного объявления коэффициентов вектора, то в var лежит ровно одно значение:
    * var[0] == 0
    */
    std::vector<bool> var;
    
};

#endif /*FIELDVEC_H*/

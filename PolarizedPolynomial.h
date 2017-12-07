#ifndef POLARIZED_POLYNOMIAL_H
#define POLARIZED_POLYNOMIAL_H

#include <vector>

#include "PolarizedMonomial.h"

/**
* @brief Класс, реализующий работу с поляризованными полиномами над произвольным полем
*
* @details Представляет собой вектор пар моном - коэффициент.
*/
class PolarizedPolynomial{

public:
    PolarizedPolynomial(){
        max_complexity = 0;
    }

    PolarizedPolynomial(std::vector<PolarizedMonomial *> &mon, std::vector<FieldElem> &coef){
        if(mon.size() != coef.size()){
            throw DifferentSize{};
        }
        monomials = mon;
        coefficient = coef;
        max_complexity = mon.size();
    }

    /**
    * считает значение полинома в точке
    */
    FieldElem val_in_point(std::vector<FieldElem> &p){
        FieldElem res;
        FieldElem z;
        for(unsigned int i = 0; i < max_complexity; i++){
            PolarizedMonomial t = *monomials[i];
            FieldElem q = t.val_in_point(p);
            z = coefficient[i] * q;
            res += z;
        }
        return res;
    }

    void add(PolarizedMonomial &m, FieldElem &coef){
	for(int i = 0; i < max_complexity; i++){
	    if(m == *monomials[i]){
		coefficient[i] += coef;
	    	return;
	    }
	}
	monomials.push_back(&m);
	coefficient.push_back(coef);
	max_complexity++;
    }

    friend std::ostream& operator<<(std::ostream& os, PolarizedPolynomial &q){
        for(unsigned int i = 0; i + 1 < q.max_complexity; i++){
            os << q.coefficient[i] << " * " << *q.monomials[i] << " + ";
        }
        os << q.coefficient[q.max_complexity - 1] << " * " << *q.monomials[q.max_complexity - 1];
        return os;
    }

private:
    unsigned int max_complexity;
    std::vector<PolarizedMonomial *> monomials;
    std::vector<FieldElem> coefficient;

};


/**
* @brief Класс, реализующий работу с поляризованными полиномами над полем четной характеристики
*
* @details Представляет собой вектор пар моном - коэффициент.
*/
class BoolPolarizedPolynomial{

public:
    BoolPolarizedPolynomial(){
        max_complexity = 0;
    }

    BoolPolarizedPolynomial(std::vector<BoolPolarizedMonomial> &mon, std::vector<BoolFieldElem> &coef){
        if(mon.size() != coef.size()){
            throw DifferentSize{};
        }
        monomials = std::vector<BoolPolarizedMonomial>(mon.size());
        for(int i = 0; i < mon.size(); i++){
            monomials[i] = mon[i];
        }
        coefficient = coef;
        max_complexity = mon.size();
    }

    /**
    * считает значение полинома в точке
    */
    BoolFieldElem val_in_point(std::vector<BoolFieldElem> &p){
        BoolFieldElem res;
        BoolFieldElem z;
        for(unsigned int i = 0; i < this->max_complexity; i++){
            BoolPolarizedMonomial t = this->monomials[i];
            BoolFieldElem q = t.val_in_point(p);
            z = this->coefficient[i] * q;
            res += z;
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, BoolPolarizedPolynomial &q){
        for(unsigned int i = 0; i + 1 < q.max_complexity; i++){
            os << q.coefficient[i] << " * " << q.monomials[i] << " + ";
        }
        os << q.coefficient[q.max_complexity - 1] << " * " << q.monomials[q.max_complexity - 1];
        return os;
    }

private:
    unsigned int max_complexity;
    std::vector<BoolPolarizedMonomial> monomials;
    std::vector<BoolFieldElem> coefficient;

};

#endif

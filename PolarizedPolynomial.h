#ifndef POLARIZED_POLYNOMIAL_H
#define POLARIZED_POLYNOMIAL_H

#include <vector>
#include <utility>

#include "FieldElem.h"

class DifferentSize{};


class PolarizedMonomial{

public:
    PolarizedMonomial(std::vector<unsigned int> &pows){
        var_number = pows.size();
        for(unsigned int i = 0; i < var_number; i++){
            polarization.push_back(FieldElem());
        }
        powers = pows;
    }

    PolarizedMonomial(std::vector<unsigned int> &pows, std::vector<FieldElem> &pol){
        if(pows.size() != pol.size()){
            throw DifferentSize();
        }
        var_number = pows.size();
        polarization = pol;
        powers = pows;
    }

    FieldElem val_in_point(std::vector<FieldElem> &p){
        if(p.size() != var_number){
            throw DifferentSize();
        }
        FieldElem res;
        FieldElem t;
        FieldElem z;
        for(unsigned int i = 0; i < var_number; i++){
            t = (p[i] + polarization[i]);
            z = t.pow(powers[i]);
            res += z;
        }
        return res;
    }

    bool operator==(PolarizedMonomial &a){
        if(var_number != a.var_number){
            return false;
        }
        for(unsigned int i = 0; i < var_number; i++){
            if(polarization[i] != a.polarization[i]){
                return false;
            }
            if(powers[i] % 3 != a.powers[i] % 3){
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const PolarizedMonomial &q){
        for(unsigned int i = 0; i + 1 < q.var_number; i++){
            if(!(q.powers[i])){
                os << "1";
                continue;
            }
            FieldElem t = q.polarization[i];
            os << "(x_" << i+1;
            if(t != 0){
                os << " + " << t << ")";
            }else{
                os << ")";
            }
            if(q.powers[i] > 1){
                os << "^" << q.powers[i];
            }
        }
        return os;
    }

    unsigned int get_var_number(){
        return var_number;
    }
private:
    unsigned int var_number;
    std::vector<FieldElem> polarization;
    std::vector<unsigned int> powers;
};

class PolarizedPolynomial{

public:
    PolarizedPolynomial(){
        complexity = 0;
    }

    PolarizedPolynomial(std::vector<PolarizedMonomial> &mon, std::vector<FieldElem> &coef){
        if(mon.size() != coef.size()){
            throw DifferentSize();
        }
        monomials = mon;
        coefficient = coef;
        complexity = mon.size();
    }

    bool push_back(PolarizedMonomial &t, unsigned int q){
        for(unsigned int i = 0; i < complexity; i++){
            if(t == monomials[i]){
                return false;
            }
            
        }
        complexity++;

        monomials.push_back(t);
        coefficient.push_back(q);
        return true;
    }

    FieldElem val_in_point(std::vector<FieldElem> &p){
        if(p.size() != monomials[0].get_var_number()){
            throw DifferentSize();
        }
        FieldElem res;
        FieldElem z;
        for(unsigned int i = 0; i < complexity; i++){
            PolarizedMonomial t = monomials[i];
            FieldElem q = t.val_in_point(p);
            z = coefficient[i] * q;
            res += z;
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, PolarizedPolynomial &q){
        for(unsigned int i = 0; i + 1 < q.complexity; i++){
            os << q.coefficient[i] << " * " << q.monomials[i] << " + ";
        }
        os << q.coefficient[q.complexity - 1] << " * " << q.monomials[q.complexity - 1];
        return os;
    }

private:
    unsigned int complexity;
    std::vector<PolarizedMonomial> monomials;
    std::vector<FieldElem> coefficient;

};

#endif
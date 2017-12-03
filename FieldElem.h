#ifndef FIELD_ELEM_H
#define FIELD_ELEM_H

#include <algorithm>
#include <iostream>

#include "FieldVec.h"

class FieldElem
{
public:
    static FieldVec irreducible_polynominal;
    
    FieldElem(){
    }

    FieldElem(unsigned long long z){
        v = FieldVec(z) % irreducible_polynominal;
    }

    FieldElem(FieldVec &t){
        v = t % irreducible_polynominal;
    }

    FieldElem &operator +=(FieldElem &a){
        v += a.v;
        return *this;
    }

    FieldElem operator +(FieldElem &a){
        FieldElem b = *this;
        b += a;
        return b;
    }

    FieldElem &operator *=(FieldElem &a){
        v = (v * a.v) % irreducible_polynominal;
        return *this;
    }

    FieldElem operator *(FieldElem &a){
        FieldElem r = *this;
        r *= a;
        return r;
    }

    FieldElem pow(unsigned int p){
        FieldElem power(0);
        power.v[0] = 1;
        for(int i = 0; i < irreducible_polynominal.size(); i++){
            power.v.push_back(1);
        }
        if(p == 0){
            return power;
        }
        p = p % FieldVec::q;
        if(p == 0){
            p += FieldVec::q;
        }
        while(p){
            power *= *this;
            p--;
        }
        return power;
    }

    bool operator==(const FieldElem &a){
        return v == a.v;
    }

    inline bool operator!=(const FieldElem &rhs){ return !(*this == rhs); }

    friend std::ostream& operator<<(std::ostream& os, FieldElem &z){
        unsigned long long w = 0;
        for(int i = 0; i < z.v.size(); i++){
            w *= FieldVec::q;
            w += z.v[i];
        }
        os << w;
        return os;
    }
private:
    FieldVec v;
};

unsigned int FieldVec::q = 2;
FieldVec FieldElem::irreducible_polynominal(0);

#endif

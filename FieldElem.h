#ifndef FIELD_ELEM_H
#define FIELD_ELEM_H

#include <algorithm>
#include <iostream>

#include "FieldVec.h"

class FieldElem
{
public:
    static FieldVec irreducible_polynominal;
    
    FieldElem(){}

    FieldElem(unsigned long long z);

    FieldElem(FieldVec &t);

    FieldElem &operator +=(FieldElem &a);

    FieldElem operator +(FieldElem &a);

    FieldElem &operator *=(FieldElem &a);

    FieldElem operator *(FieldElem &a);

    FieldElem pow(unsigned int p);

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

#endif

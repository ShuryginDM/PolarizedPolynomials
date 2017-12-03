#include "FieldElem.h"

FieldVec::q = 2;
FieldVec FieldElem::irreducible_polynominal(0);

FieldElem::FieldElem(unsigned long long z){
    v = FieldVec(z) % irreducible_polynominal;
}

FieldElem::FieldElem(FieldVec &t){
    v = t % irreducible_polynominal;
}

FieldElem &FieldElem::operator+=(FieldElem &a){
    v += a.v;
    return *this;
}

FieldElem FieldElem::operator+(FieldElem &a){
    FieldElem b = *this;
    b += a;
    return b;
}

FieldElem &FieldElem::operator*=(FieldElem &a){
    v = (v * a.v) % irreducible_polynominal;
    return *this;
}

FieldElem FieldElem::operator*(FieldElem &a){
    FieldElem r = *this;
    r *= a;
    return r;
}

FieldElem FieldElem::pow(unsigned int p){
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


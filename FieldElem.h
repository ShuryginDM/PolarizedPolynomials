#ifndef FIELD_ELEM_H
#define FIELD_ELEM_H

#include <algorithm>
#include <iostream>

class FieldElem
{
public:
    FieldElem(unsigned int t = 0){
        c1 = t & 1;
        c2 = (t >> 1) & 1;
    }

    FieldElem(const FieldElem &t){
        c1 = t.c1;
        c2 = t.c2;
    }

    FieldElem &operator +=(FieldElem a){
        c1 ^= a.c1;
        c2 ^= a.c2;
        return *this;
    }

    FieldElem operator +(FieldElem &a){
        FieldElem sum_(a);
        sum_.c1 ^= c1;
        sum_.c2 ^= c2;
        return sum_;
    }

    FieldElem operator *(FieldElem &a){
        FieldElem mul_;
        mul_.c2 = a.c2 * c2;
        mul_.c1 = (a.c2 & c1) ^ (c2 & a.c1);
        if(c1 && a.c1){
            mul_.c2 = !mul_.c2;
            mul_.c1 = !mul_.c1;
        }
        return mul_;
    }

    FieldElem &operator *=(FieldElem &a){
        FieldElem mul_;
        mul_.c2 = a.c2 * c2;
        mul_.c1 = (a.c2 & c1) ^ (c2 & a.c1);
        if(c1 && a.c1){
            mul_.c2 = !mul_.c2;
            mul_.c1 = !mul_.c1;
        }
        c1 = mul_.c1;
        c2 = mul_.c2;
        return *this;
    }

    FieldElem pow(unsigned int p){
        FieldElem power(1);
        if(p == 0){
            return power;
        }
        p = p % 3;
        if(p == 0){
            p += 3;
        }
        while(p){
            power *= *this;
            p--;
        }
        return power;
    }

    bool operator==(const FieldElem &a){
        return c1 == a.c1 && c2 == a.c2;
    }

    inline bool operator!=(const FieldElem &rhs){ return !(*this == rhs); }

    bool operator!(){
        return !(c1 | c2);
    }

    bool operator==(const unsigned int &a){
        return *this == FieldElem(a);
    }

    bool operator<(const FieldElem &a) const{
        if(c1 & !(a.c1)){
            return false;
        }
        if(!(a.c1) && c2 && !(a.c2)){
            return false;
        }
        return true;
    }

    inline bool operator!=( const unsigned int &rhs){ return !(*this == rhs); }


    friend std::ostream& operator<<(std::ostream& os, const FieldElem &q){
        os << q.c1 * 2 + q.c2;
        return os;
    }
private:
    bool c1, c2;
};

#endif
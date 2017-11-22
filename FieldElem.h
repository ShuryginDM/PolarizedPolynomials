#ifndef FIELD_ELEM_H
#define FIELD_ELEM_H

#include <vector>
#include <algorithm>
#include <iostream>
/**
*Класс, используемый для того, чтобы показать тип исключения
*"Попытка суммирования элементов разных полей"
*/
class SumOfDifferentFields {};

/**
*Класс, используемый для того, чтобы показать тип исключения
*"Попытка посчитать произведение элементов разных полей"
*/
class MulOfDifferentFields {};

class FieldElem
{
public:
    FieldElem(unsigned int new_size, unsigned int t = 0){
        size = new_size;
        for(unsigned int i = 0; i < size; i++){
            elem.push_back(t & 1);
            t >>= 1;
        }
    }

    FieldElem(const FieldElem &t){
        size = t.size;
        elem = t.elem;
    }

    const bool operator [](int &i){
        return elem[i];
    }

    FieldElem operator +=(FieldElem &a){
        if(size != a.size){
            throw SumOfDifferentFields();
        }
        for(unsigned int i = 0; i < size; i++){
            elem[i] = elem[i] ^ a.elem[i];
        }
        return *this;
    }

    FieldElem operator +(FieldElem &a){
        if(size != a.size){
            throw SumOfDifferentFields();
        }
        FieldElem sum_(a);
        for(unsigned int i = 0; i < size; i++){
            sum_.elem[i] = sum_.elem[i] ^ elem[i];
        }
        return sum_;
    }

    FieldElem operator *(FieldElem &a){
        if(size != a.size){
            throw MulOfDifferentFields();
        }
        FieldElem full_mul_(2 * size - 1);
        FieldElem mul_(size);
        for(unsigned int i = 0; i < size; i++){
            for(unsigned int j = 0; j < size; j++){
                full_mul_.elem[i+j] = full_mul_.elem[i+j] ^ (elem[i] & a.elem[j]);
            }
        }
        for(unsigned int i = 2 * size - 2; i >= size; i--){
            if(full_mul_.elem[i]){
                for(unsigned int j = 0; j <= size; j++){
                    full_mul_.elem[i-j] = !full_mul_.elem[i-j];
                }
            }
        }
        for(unsigned int i = 0; i < size; i++){
            mul_.elem[i] = full_mul_.elem[i];
        }
        return mul_;
    }

    FieldElem operator *=(FieldElem &a){
        if(size != a.size){
            throw MulOfDifferentFields();
        }
        FieldElem full_mul_(2 * size - 1);
        FieldElem mul_(size);
        for(unsigned int i = 0; i < size; i++){
            for(unsigned int j = 0; j < size; j++){
                full_mul_.elem[i+j] = full_mul_.elem[i+j] ^ (elem[i] & a.elem[j]);
            }
        }
        for(unsigned int i = 2 * size - 2; i >= size; i--){
            if(full_mul_.elem[i]){
                for(unsigned int j = 0; j <= size; j++){
                    full_mul_.elem[i-j] = !full_mul_.elem[i-j];
                }
            }
        }
        for(unsigned int i = 0; i < size; i++){
            mul_.elem[i] = full_mul_.elem[i];
        }
        return mul_;
    }

    FieldElem pow(unsigned int p){
        if(p == 0){
            FieldElem power(1);
            return power;
        }else{
            FieldElem power(*this);
            for(unsigned int i = 1; i < p; i++){
                power = power * *this;
            }
            return power;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const FieldElem& q){
        unsigned int a = 0;
        for(auto i = q.elem.rbegin(); i < q.elem.rend(); i++){
            a <<= 1;
            a |= *i;
        }
        os << a;
        return os;
    }
private:
    std::vector<bool> elem;
    unsigned int size;
};

#endif
#include "PolarizedMonomial.h"

std::vector<FieldElem> PolarizedMonomial::polarization;

std::vector<BoolFieldElem> BoolPolarizedMonomial::polarization;


PolarizedMonomial::PolarizedMonomial(){
     for(unsigned int i = 0; i < polarization.size(); i++){
        powers.push_back(0);
    }
}

PolarizedMonomial::PolarizedMonomial(std::vector<unsigned int> &pows){
    if(pows.size() != PolarizedMonomial::polarization.size()){
        throw DifferentSize{};
    }
    powers = pows;
}

PolarizedMonomial::PolarizedMonomial(PolarizedMonomial &m){
    powers = m.powers;
}

FieldElem PolarizedMonomial::val_in_point(std::vector<FieldElem> &p){
    if(p.size() != powers.size()){
        throw DifferentSize();
    }
    if(p.size() != PolarizedMonomial::polarization.size()){
        throw DifferentSize();
    }
    FieldElem res(1);
    FieldElem t;
    FieldElem z;
    for(unsigned int i = 0; i < powers.size(); i++){
        t = (p[i] + polarization[i]);
        z = t.pow(powers[i]);
        res *= z;
    }
    return res;
}

bool PolarizedMonomial::operator==(PolarizedMonomial &a){
    if(powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    if(a.powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    for(unsigned int i = 0; i < polarization.size(); i++){
        if(powers[i] != a.powers[i]){
            return false;
        }
    }
    return true;
}

PolarizedMonomial &PolarizedMonomial::operator*=(PolarizedMonomial &m){
    if(powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    if(m.powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    for(int i = 0; i < polarization.size(); i++){
        powers[i] += m.powers[i];
    }
    return *this;
}

PolarizedMonomial PolarizedMonomial::operator*(PolarizedMonomial &m){
    if(powers.size() != PolarizedMonomial::polarization.size()){
        throw DifferentSize{};
    }
    if(m.powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    PolarizedMonomial mul_(powers);
    mul_ *= m;
    return mul_;
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

BoolPolarizedMonomial::BoolPolarizedMonomial(std::vector<unsigned int> &pows){
    if(pows.size() != BoolPolarizedMonomial::polarization.size()){
        throw DifferentSize{};
    }
    powers = pows;
}

BoolPolarizedMonomial::BoolPolarizedMonomial(BoolPolarizedMonomial &m){
    powers = m.powers;
}

BoolFieldElem BoolPolarizedMonomial::val_in_point(std::vector<BoolFieldElem> &p){
    if(p.size() != powers.size()){
        throw DifferentSize();
    }
    if(p.size() != BoolPolarizedMonomial::polarization.size()){
        throw DifferentSize();
    }
    BoolFieldElem res(1);
    BoolFieldElem t;
    BoolFieldElem z;
    for(unsigned int i = 0; i < p.size(); i++){
        t = (p[i] + polarization[i]);
        z = t.pow(powers[i]);
        res *= z;
    }
    return res;
}

bool BoolPolarizedMonomial::operator==(BoolPolarizedMonomial &a){
    if(powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    if(a.powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    for(unsigned int i = 0; i < polarization.size(); i++){
        if(powers[i] != a.powers[i]){
            return false;
        }
    }
    return true;
}

BoolPolarizedMonomial &BoolPolarizedMonomial::operator*=(BoolPolarizedMonomial &m){
    if(powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    if(m.powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    for(int i = 0; i < polarization.size(); i++){
        powers[i] += m.powers[i];
    }
    return *this;
}

BoolPolarizedMonomial BoolPolarizedMonomial::operator*(BoolPolarizedMonomial &m){
    if(powers.size() != BoolPolarizedMonomial::polarization.size()){
        throw DifferentSize{};
    }
    if(m.powers.size() != polarization.size()){
        throw DifferentSize{};
    }
    BoolPolarizedMonomial mul_(powers);
    mul_ *= m;
    return mul_;
}

BoolPolarizedMonomial::BoolPolarizedMonomial(){
     for(unsigned int i = 0; i < polarization.size(); i++){
        powers.push_back(0);
    }
}
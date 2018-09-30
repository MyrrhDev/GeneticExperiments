/** @file Individuo.cc
    @brief Código de la clase Individuo
*/

#include "Individuo.hh"

Individuo::Individuo(){
}

void Individuo::asigna_nombre(string bname) {
    name = bname;
}

bool Individuo::recoge_sex() {
    return sex;
}

void Individuo::asigna_sex(bool bsex) {
    if (not bsex) sex = false; //mujer
    else sex = true; //hombre
}

void Individuo::asignar_parametros(Cromosomas c) {
    sexs = c;
    croms = c;
}

void Individuo::asignar_cromosomas(bool bsex) {
    sexs.anadir_cromosoma_sexs(bsex);
    croms.anadir_cromosomas();
}

void Individuo::asignar_cromsex(Cromosomas bsex) {
    sexs = bsex;
}

void Individuo::asignar_cromnorm(Cromosomas bcroms) {
    croms = bcroms;
}

Cromosomas Individuo::obtener_cromosomas_sex() {
    return sexs;
}

Cromosomas Individuo::obtener_cromosomas() {
    return croms;
}
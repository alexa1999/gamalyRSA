#ifndef ELGAMAL_H
#define ELGAMAL_H
#include<string>
#include<NTL/ZZ.h>
#include "funciones.h"
#include<sstream>
class gamal{
private:
    ZZ p,d,e1,e2,r;
    int bits;
    string alfabeto="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    int longitud = alfabeto.length();
public:
    gamal(int bits);
    gamal(ZZ e_1,ZZ e_2, ZZ p_0,int bits);
    string cifrar(string mensaje);
    string decifrar(string mensaje);
    void generarClaves(int bits);
};


#endif // ELGAMAL_H

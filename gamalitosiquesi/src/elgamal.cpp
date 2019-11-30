#include "elgamal.h"



void gamal::generarClaves(int bits){

    mathLib m;
    ZZ a,r_0;

    GenPrime(a,bits);
    // a = m.genetareRandom(11,bits,5,10);
    // while(!m.testMiller(a,10)){
        // a = GenPrime(bits);
        // a = m.genetareRandom(11,bits,5,10);
    // }
    p=a;
    e1 = m.fingGen(p);
    GenPrime(d,bits-1);
    // d = m.genetareRandom(11,bits,5,10);
    GenPrime(r_0,bits);
    // r_0 = m.genetareRandom(11,bits,5,10);
    while(d<1 && d>p-2 && r_0<1 && r_0>p-2){
        GenPrime(d,bits-1);
        GenPrime(r_0,bits);
        // d = m.genetareRandom(11,bits,5,10);
        // r_0 = m.genetareRandom(11,bits,5,10);
    }
    r=r_0;
    e2 = m.modularExpo(e1,d,p);
    cout<<"e1: "<<e1<<endl;
    cout<<"e2: "<<e2<<endl;
    cout<<"p: "<<p<<endl;
    cout<<"d: "<<d<<endl;
}

gamal::gamal(int bits_){
    bits=bits_;
    generarClaves(bits);
}

gamal::gamal(ZZ e_1,ZZ e_2, ZZ p_0, int bits_){
    bits=bits_;
    e1 = e_1;
    e2 = e_2;
    p = p_0;
}

string zToString(const ZZ &z) {
    stringstream buffer;
    buffer << z;
    return buffer.str();
}

string numberToString(int numero){
    stringstream ss;
	ss << numero;
	return ss.str();
}

string gamal::cifrar(string mensaje){
    string res,lString,mensajeC,c1_string;
    int c1_temp;
    mathLib m;
    ZZ c1;
    ZZ N,Km;
    N=p;

    // GenPrime(r,bits/2);

    // r=GenGermainPrime_ZZ((bits-4));

    // r = m.genetareRandom(11,bits,5,10);
    GenPrime(r,bits-2);

    std::cout << "r " << r << '\n';

    c1= m.modularExpo(e1,r,p);
    Km = m.modularExpo(e2,r,p);
    std::cout << "km " << Km << '\n';
    c1_string =zToString(c1);
    c1_temp = c1_string.length();
    int lenMaxString = numberToString(longitud).length();
    int lenN = zToString(N).length();
    int k = lenN-1;

    int numOfZeros;
    int l;
    ZZ numGroups;
    for(int i = 0;i<mensaje.length();i++){
        l = alfabeto.find(mensaje[i]);
        lString = numberToString(l);
        numOfZeros = lenMaxString-lString.length();
        string temp(numOfZeros,'0');
        temp.append(lString);
        res.append(temp);
    }

    string posW = numberToString(alfabeto.find('w'));
    while(m.getModInt(res.length(),k)!=0){
        res.append(posW);
    }
    std::cout << "res " << res<< '\n';
    numGroups = conv<ZZ>(res.length()/k);
    long long i;
    int ini = 0;
    int fin = k;
    for(i=0;i<numGroups;i++){
        ZZ numCifrar(INIT_VAL,res.substr(ini,fin).c_str());
        std::cout << i << " base  " << numCifrar;
        // numCifrar = m.modularExpo(numCifrar,clavePublica,N);
        // std::cout << " numCifrar " << numCifrar << '\n';
        numCifrar = m.getMod(numCifrar*Km,p);
        string t = zToString(numCifrar);
        int diff = (lenN)-t.length();
        string actualString = t;
        if(diff!=0){
            string temp(diff,'0');
            temp.append(t);
            actualString = temp;
        }
        mensajeC+=actualString;
        std::cout  << " result:  " <<  actualString << '\n';
        // std::cout << " mensajeC " << mensajeC << '\n';
        ini+=k;
    }
    if(c1_temp<lenN){
        int tempo = lenN-c1_temp;
        string temp(tempo,'0');
        temp+=c1_string;
        temp+=mensajeC;
        mensajeC=temp;
        // std::cout << '\n' << " mensajeC if " << mensajeC << '\n';


    }else{
        c1_string+=mensajeC;
        // mensajeC = c1_temp;
        mensajeC = c1_string;
        // std::cout << '\n' << " mensajeC else " << mensajeC << '\n';

    }
    cout<<"Mensaje Cifrado: "<<mensajeC<<endl;
    return mensajeC;
}

string gamal::decifrar(string mensaje){
    mathLib m;
    ZZ Km;
    ZZ N;
    N = p;
    int lenP = zToString(p).length();
    ZZ c1(INIT_VAL,mensaje.substr(0,lenP).c_str());
    Km=m.modularExpo(c1,d,p);
    Km=m.Inversa(Km,p);
    string grupo,res,MensajeDes;
    int numMaxofChars = numberToString(longitud).length();
    ZZ nLen,menLen,numGrupos,dp,dq,D,c,numLetras;
    nLen = conv<ZZ>(zToString(N).length());
    menLen = conv<ZZ>(mensaje.length());
    numGrupos = menLen/nLen;
    long long i;
    int inicio = lenP;
    c=0;
    for(i=1;i<numGrupos;i++){
        grupo = mensaje.substr(inicio,conv<int>(nLen));
        ZZ valGrupo(INIT_VAL,grupo.c_str());
        D=m.getMod(valGrupo*Km,p);
        if(zToString(D).length() < conv<int>(nLen)){
            string temp((conv<int>(nLen)-zToString(D).length())-1,'0');
            temp.append(zToString(D));
            res+=temp;
        }else{
           res+=zToString(D);
        }

        c++;
        inicio+=conv<int>(nLen);
    }
    inicio = 0;
    numLetras = conv<ZZ>(res.length())/conv<ZZ>(numberToString(longitud).length());
    for(i=0;i<numLetras;i++){
        ZZ temp(INIT_VAL,res.substr(inicio,numMaxofChars).c_str());
        if(alfabeto[conv<int>(temp)]=='w'){
            break;
        }
        MensajeDes+=alfabeto[conv<int>(temp)];
        inicio+=numMaxofChars;
    }
    return MensajeDes;

}

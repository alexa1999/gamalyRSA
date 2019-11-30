#include <iostream>
#include"elgamal.h"

using namespace std;

int main(){

  int opcion;
  string mensaje="amo su inocencia amo sus errores";
  ZZ e1,e2,p;
  string c2;
  int bits=1024;
  gamal receptor(bits);
  while(true){
      cout<<"1 para decifrar : "<<endl;
      cout<<"2 para cifrar  : "<<endl;
      cin>>opcion;
      if(opcion==1){
          cout<<"Ingrese el c2: "<<endl;
          cin>>c2;
          cout<<"Mensaje decifrado: "<<receptor.decifrar(c2)<<endl;
      }
      if(opcion==2){
          cout<<"Ingrese e1: "<<endl;
          cin>>e1;
          cout<<"Ingrese e2: "<<endl;
          cin>>e2;
          cout<<"Ingrese p: "<<endl;
          cin>>p;
          gamal emisor(e1,e2,p,bits);
          emisor.cifrar(mensaje);

      }
  }

    return 0;
}

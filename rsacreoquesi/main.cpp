#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include<fstream>
#include <sstream>
#include <vector>
#include <sstream>
#include "rsa.h"

using namespace std;
using namespace NTL;

int main()
{
	//    Emisor.eB=receptor.e;
	//    Emisor.NB=receptor.N;
	//ZZ e, n;
	cout << " Claves Generadas: " << endl;
	rsa r(256);
	int op;
	do {
		cout << " ELIGE UNA OPCION: " << endl;
		cout << " 1. ENCRIPTAR " << endl;
		cout << " 2. DESENCRIPTAR " << endl;
		cout << " 3. SALIR " << endl;
		cin >> op;
		switch (op)
		{
		case 1:
		{
			string linea;
			string message;
			ifstream MSJ("mensaje.txt");
			if (MSJ.is_open())
			{
				while (!MSJ.eof())
				{
					getline(MSJ, linea);
					message += linea;
				}
				MSJ.close();
			}
			//cout << message << endl;

			/*cout << "Ingrese e: ";
			cin >> e;
			cout << "ingrese n: ";
			cin >> n;*/
			//rsa r(e, n);
			ZZ e, n;
			cout << "Ingrese e: ";
			cin >> e;
			cout << "ingrese n: ";
			cin >> n;
			string Cipher = r.cifrar(message, e, n);
			cout << "MSJ Cifrado: " << endl << Cipher << endl;
			ofstream ciphertext;
			ciphertext.open("cifrado.txt");
			ciphertext << Cipher;
			break;
		}

		case 2:
		{

			string Cipher;
			string linea;
			ifstream CIPHER("cifrado.txt");
			if (CIPHER.is_open())
			{
				while (!CIPHER.eof())
				{
					getline(CIPHER, linea);//lee linea a linea reconociendo el enter
					Cipher += linea;
				}
				CIPHER.close();
			}
			//
			//cout << Cipher << endl;
			string Descipher;
			/*cout << e << endl;
			cout << n << endl;
			rsa r(e,n);*/
			Descipher = r.descifra(Cipher);
			cout << "MSJ Descifrado: " << endl;
			cout << Descipher << endl;

			break;
		}
		}

	} while (op != 4);

	system("pause");
	return 0;

}

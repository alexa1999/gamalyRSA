#include "rsa.h"

rsa::rsa(int nBits)
{
	mathLib m;
	this->nBits = nBits;
	cout << "Generando p y q ..." << endl;
	generatePrimerNumbers();
	/*GenPrime(p, nBits);
	GenPrime(q, nBits);

	while (p == q) {
		GenPrime(p, nBits);
		GenPrime(q, nBits);
	}*/
	n = p * q;
	phiN = (p - ZZ(1)) * (q - ZZ(1));
	cout << "Generando e ..." << endl;
	generarE();
	dp = m.modulo(d, p - 1);
	dq = m.modulo(d, q - 1);

	mostrar();
}

rsa::rsa(ZZ e_, ZZ n_)
{
	mathLib x;
	e = e_;
	n = n_;
	Ndig = x.zz_a_string(n).size();
}

rsa::rsa(string m_)
{
	cifrado = m_;
}

void rsa::generatePrimerNumbers()
{
	RC4 r(nBits);
	mathLib m;
	string binario;
	vector <string> a;


	int count = 0;
	ZZ number;

	binario = r.generateRandomNumber();
	binario[0] = '1';
	binario[binario.size() - 1] = '1';
	number = r.convertirBinaryToZZ(binario);

	while (!m.fermatTest(20, number, nBits)) {
		binario = r.generateRandomNumber();
		binario[0] = '1';
		binario[binario.size() - 1] = '1';
		number = r.convertirBinaryToZZ(binario);
	}

	this->p = number;

	binario = r.generateRandomNumber();
	binario[0] = '1';
	binario[binario.size() - 1] = '1';
	number = r.convertirBinaryToZZ(binario);

	while (!m.fermatTest(20, number, nBits)) {
		binario = r.generateRandomNumber();
		binario[0] = '1';
		binario[binario.size() - 1] = '1';
		number = r.convertirBinaryToZZ(binario);
	}

	this->q = number;


    for(int i=0;i<20;i++)
    {
        cout<<a[i]<<endl;
    }



	/*for (int i = 0; i < binario.size() - nBits - 1; i++)
	{
		string tem = binario.substr(i, nBits);
		tem[tem.size()-1] = '1';
		tem[(nBits / 2)] = '1';
		tem[(nBits / 2)+1] = '1';
		number = r.convertirBinaryToZZ(tem);
		//cout << tem << endl;
		if (number == 0) {
			continue;
		}

		if (p.fermatTest(10, number))
		{
			if (count == 0)
			{
				this->p = number;
				++count;
				continue;
			}
			else if(count == 1)
			{
				this->q = number;
				++count;
				break;
			}
			break;
		}
	}*/
}

void rsa::mostrar()
{
	cout << "PhiN: " << phiN << endl;
	cout << "N: " << n << endl;
	cout << "p: " << p << endl;
	cout << "q: " << q << endl;
	cout << "e: " << e << endl;
	cout << "d: " << d << endl;
	cout << "dq: " << dq << endl;
	cout << "dp: " << dp << endl;

}

void rsa::generarE()
{
	srand(time(NULL));
	mathLib r;
	ZZ t;

	//cout << "T = " << t << endl;

	//t = r.getMod(phiN,t);
	//cout << "T*T - phi = " << t << endl;
	phiN = (p - ZZ(1)) * (q - ZZ(1));
	//Genera 1 < e < Phi
	RandomBnd(e, phiN);
	while (GCD(e, phiN) != 1 || e == 1)
		RandomBnd(e, phiN);
	//Inversa de e
	d = r.algEuclidesExt(e, phiN);
	d = r.modulo(d, phiN);

	/*if (r.algEuclides(t, phiN) == 1)
	{

	}
	else
		generarE();*/

}

string rsa::cifrar(string _mensaje, ZZ _e, ZZ _n)
{
	mathLib x;
	mensaje = _mensaje;
	_mensaje = toNumbers(_mensaje);
	//cout << _mensaje << endl;
	string rub, fd;
	string rubtmp, fdtmp;

	//Ndig = zToString(n).length();
	Ndig = x.zz_a_string(_n).size();
	k = Ndig - 1;

	//NdigB = zzToString(n).length();
	NdigB = x.zz_a_string(_n).length();
	kB = NdigB - 1;
	string resTemp = toBloques(_mensaje, Ndig);
	string res;
	ZZ opera;
	int nBloques = resTemp.length() / k;
	for (int i = 0; i < nBloques; ++i)
	{

		opera = x.string_a_zz(resTemp.substr(i * k, k));
		opera = x.expoMB(opera, _e, _n);
		res += formatZZ(opera, Ndig);
	}
	return res;
}

string rsa::toNumbers(string _mensaje)
{
	string res, digAct;
	int digsizAlf = to_string(alfabeto.size()).length();
	for (int i = 0; i < _mensaje.size(); ++i)
	{
		digAct = _mensaje[i];
		res += formatInt(alfabeto.find(digAct), digsizAlf);
	}
	return res;
}

string rsa::formatInt(int num, int dig)
{
	string res;
	res = to_string(num);
	int difeSize = dig - res.length();
	while (difeSize > 0)
	{
		res = '0' + res;
		difeSize--;
	}
	return res;
}

string rsa::toBloques(string _mensaje, int sizN)
{
	mathLib x;
	string fill = to_string(22);
	int k = sizN - 1;
	int ite = x.Modulo(_mensaje.length(), k);
	if (ite == 0)
		return _mensaje;
	ite = k - ite;
	int i = 0;
	while (i < ite)
	{
		_mensaje += fill[x.Modulo(i, fill.length())];
		i++;
	}
	return _mensaje;
}

string rsa::formatZZ(ZZ num, int dig)
{
	string res;
	mathLib x;
	//res += zzToString(num);
	res += x.zz_a_string(num);
	int difeSize = dig - res.length();
	while (difeSize > 0)
	{
		res = '0' + res;
		difeSize--;
	}
	return res;
}

string rsa::descifrar(string _mensaje)
{
	string res;
	ZZ opera;
	mathLib x;
	int nBloques = _mensaje.length() / (Ndig);
	//cout << Ndig << endl;
	//cout << nBloques << endl;
	for (int i = 0; i < nBloques; i++)
	{
		//opera = Stringtozz(_mensaje.substr(i * Ndig, Ndig));
		opera = x.string_a_zz(_mensaje.substr(i * (Ndig), (Ndig)));
		//  << "Opera Des: " << opera << endl;
		ap = x.expoMB(opera, dp, p);
		aq = x.expoMB(opera, dq, q);
		vector<ZZ>a = { ap,aq };
		vector<ZZ>P = { p,q };
		opera = x.resch(a, P);
		//cout << "Opera Des: " << opera << endl;
		res += formatZZ(opera, k);
	}
	return res;
}

string rsa::descifra(string msn)
{
	string res;
	string resTemp, fdtmp, rubtmp;
	mathLib x;
	//Ndig = zzToString(N).length();
	Ndig = x.zz_a_string(n).length();
	k = Ndig - 1;

	//NdigB = zzToString(N).length();
	NdigB = x.zz_a_string(n).length();
	kB = Ndig - 1;

	//firmadigital

	//rsa
	resTemp = descifrar(msn);

	//Convertir a mensaje
	res = fromBloques(resTemp, alfabeto.length());

	return res;
}

string rsa::fromBloques(string msn, int sizAlf)
{
	string res, digAct;
	int digsizAlf = to_string(sizAlf).length();
	int pos;

	int ite = msn.length() / digsizAlf;
	for (int i = 0; i < ite; i++)
	{
		pos = stoi(msn.substr(i * digsizAlf, digsizAlf));
		res += alfabeto[pos % alfabeto.size()];
	}
	return res;
}

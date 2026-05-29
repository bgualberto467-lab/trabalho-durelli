#ifndef CONVERSOR_HPP
#define CONVERSOR_HPP

#include <string>
#include <iostream>

using namespace std;

// funcoes auxiliares
int charParaValor(char c);
char valorParaChar(int v);
void separarIntFrac(string numero, string &parteInt, string &parteFrac);
string tiraZerosEsq(string s);
string tiraZerosDir(string s);

// F1
string decimalParaBase(long long numero, int base);

// F2
long long baseParaDecimal(string numero, int base);

// F3
string binarioParaOctal(string bin);
string binarioParaHex(string bin);
string octalParaBinario(string oct);
string hexParaBinario(string hex);

// F4
string octalParaHex(string oct);
string hexParaOctal(string hex);

// F6
string converterFracionario(string numero, int baseOrig, int baseDest, bool &truncado);

// F10
void maiorComKBits(int k, string &dec, string &bin, string &oct, string &hex);

#endif

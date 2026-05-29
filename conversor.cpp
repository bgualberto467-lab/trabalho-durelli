#include "conversor.hpp"
#include <cmath>
#include <iostream>

using namespace std;

int charParaValor(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1; // invalido
}

char valorParaChar(int v) {
    if (v >= 0 && v < 10) return '0' + v;
    return 'A' + (v - 10);
}

void separarIntFrac(string numero, string &parteInt, string &parteFrac) {
    parteInt = "";
    parteFrac = "";
    bool achou = false;
    for (int i = 0; i < numero.size(); i++) {
        if (numero[i] == '.' || numero[i] == ',') {
            achou = true;
            continue;
        }
        if (achou == false)
            parteInt = parteInt + numero[i];
        else
            parteFrac = parteFrac + numero[i];
    }
    if (parteInt == "")
        parteInt = "0";
}

// tira zeros da esquerda tipo "007" vira "7"
string tiraZerosEsq(string s) {
    int i = 0;
    while (i < s.size() - 1 && s[i] == '0') {
        i++;
    }
    return s.substr(i);
}

string tiraZerosDir(string s) {
    int fim = s.size();
    while (fim > 0 && s[fim - 1] == '0') {
        fim--;
    }
    return s.substr(0, fim);
}

// F1 - pega o numero decimal e converte pra qualquer base
// funciona dividindo pelo base e guardando os restos
string decimalParaBase(long long numero, int base) {
    if (numero == 0) return "0";

    string resultado = "";
    bool negativo = false;

    if (numero < 0) {
        negativo = true;
        numero = -numero;
    }

    while (numero > 0) {
        int resto = numero % base;
        resultado = valorParaChar(resto) + resultado;
        numero = numero / base;
    }

    if (negativo) {
        resultado = "-" + resultado;
    }

    return resultado;
}

// F2 - converte de qualquer base pro decimal
// usa o metodo posicional (Horner)
long long baseParaDecimal(string numero, int base) {
    long long resultado = 0;
    int inicio = 0;
    bool negativo = false;

    if (numero[0] == '-') {
        negativo = true;
        inicio = 1;
    }

    for (int i = inicio; i < numero.size(); i++) {
        int v = charParaValor(numero[i]);
        if (v == -1 || v >= base) {
            return 0;
        }
        resultado = resultado * base + v;
    }

    if (negativo) resultado = -resultado;

    return resultado;
}

// F3 - agrupamento de bits pra octal (3 em 3)
string binarioParaOctal(string bin) {
    // completar com zeros a esquerda pra ficar multiplo de 3
    while (bin.size() % 3 != 0) {
        bin = "0" + bin;
    }

    string resultado = "";
    for (int i = 0; i < bin.size(); i = i + 3) {
        int v = (bin[i] - '0') * 4 + (bin[i + 1] - '0') * 2 + (bin[i + 2] - '0');
        resultado = resultado + valorParaChar(v);
    }

    return tiraZerosEsq(resultado);
}

// agrupa 4 em 4 bits pro hex
string binarioParaHex(string bin) {
    while (bin.size() % 4 != 0) {
        bin = "0" + bin;
    }

    string resultado = "";
    for (int i = 0; i < bin.size(); i = i + 4) {
        int v = (bin[i] - '0') * 8 + (bin[i + 1] - '0') * 4 + (bin[i + 2] - '0') * 2 + (bin[i + 3] - '0');
        resultado += valorParaChar(v);
    }

    return tiraZerosEsq(resultado);
}

string octalParaBinario(string oct) {
    string resultado = "";
    for (int i = 0; i < oct.size(); i++) {
        int v = charParaValor(oct[i]);
        // converte cada digito octal em 3 bits
        string bits = "";
        for (int j = 0; j < 3; j++) {
            bits = (char)('0' + v % 2) + bits;
            v = v / 2;
        }
        resultado = resultado + bits;
    }
    return tiraZerosEsq(resultado);
}

string hexParaBinario(string hex) {
    string resultado = "";
    for (int i = 0; i < hex.size(); i++) {
        int v = charParaValor(hex[i]);
        string bits = "";
        for (int j = 0; j < 4; j++) {
            bits = (char)('0' + v % 2) + bits;
            v = v / 2;
        }
        resultado += bits;
    }
    return tiraZerosEsq(resultado);
}

// F4 - octal <-> hex passando pelo binario como ponte
string octalParaHex(string oct) {
    string bin = octalParaBinario(oct);
    return binarioParaHex(bin);
}

string hexParaOctal(string hex) {
    string bin = hexParaBinario(hex);
    return binarioParaOctal(bin);
}

// F6 - converte numeros com virgula entre bases
string converterFracionario(string numero, int baseOrig, int baseDest, bool &truncado) {
    truncado = false;

    string parteInt = "";
    string parteFrac = "";
    separarIntFrac(numero, parteInt, parteFrac);

    // checar se eh negativo
    bool negativo = false;
    if (parteInt.size() > 0 && parteInt[0] == '-') {
        negativo = true;
        parteInt = parteInt.substr(1);
        if (parteInt == "") parteInt = "0";
    }

    // parte inteira: vai pro decimal e depois pra base destino
    long long intDecimal = baseParaDecimal(parteInt, baseOrig);
    string intDestino = decimalParaBase(intDecimal, baseDest);

    // parte fracionaria
    string fracDestino = "";
    if (parteFrac != "") {
        // calcula o valor fracionario em decimal
        double valorFrac = 0.0;
        double potencia = 1.0 / baseOrig;
        for (int i = 0; i < parteFrac.size(); i++) {
            int digito = charParaValor(parteFrac[i]);
            valorFrac = valorFrac + digito * potencia;
            potencia = potencia / baseOrig;
        }

        // converte multiplicando pela base destino
        int casas = 0;
        int maxCasas = 16;
        while (valorFrac > 0.000000000001 && casas < maxCasas) {
            valorFrac = valorFrac * baseDest;
            int dig = (int)floor(valorFrac);
            if (dig >= baseDest) dig = baseDest - 1; // seguranca
            fracDestino = fracDestino + valorParaChar(dig);
            valorFrac = valorFrac - dig;
            casas++;
        }

        if (valorFrac > 0.000000000001) truncado = true;
        fracDestino = tiraZerosDir(fracDestino);
    }

    string resultado = intDestino;
    if (fracDestino != "") {
        resultado = resultado + "," + fracDestino;
    }
    if (negativo && resultado != "0") {
        resultado = "-" + resultado;
    }

    return resultado;
}

// F10 - acha o maior numero com k bits (que e 2^k - 1)
void maiorComKBits(int k, string &dec, string &bin, string &oct, string &hex) {
    if (k <= 0) {
        dec = "0"; bin = "0"; oct = "0"; hex = "0";
        return;
    }

    // binario: k bits todos 1
    bin = "";
    for (int i = 0; i < k; i++) {
        bin = bin + "1";
    }

    // decimal: 2^k - 1
    long long potencia = 1;
    for (int i = 0; i < k; i++) {
        potencia = potencia * 2;
    }
    long long valor = potencia - 1;
    dec = decimalParaBase(valor, 10);

    // octal e hex usando as funcoes de agrupamento
    oct = binarioParaOctal(bin);
    hex = binarioParaHex(bin);
}

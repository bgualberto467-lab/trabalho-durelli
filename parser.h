#pragma once
#include <string>

// As 4 bases que o programa suporta
#define BASE_DECIMAL 10
#define BASE_BINARIO 2
#define BASE_OCTAL 8
#define BASE_HEX 16

// Struct que guarda os dados da conversao
struct Entrada {
    string valor;       // o numero digitado pelo usuario
    int baseOrigem;     // base do numero original
    int baseDestino;    // base para onde vai converter
};

// Verifica se um caractere e valido para a base informada
bool digitoValido(char c, int base);

// Valida o valor inteiro digitado pelo usuario
bool validarValor(string valor, int base);

// Le os dados do usuario pelo terminal
Entrada lerDoUsuario();

// Le os dados de uma linha do CSV (para o modo batch)
Entrada lerDoCSV(string valor, int baseOrigem, int baseDestino);

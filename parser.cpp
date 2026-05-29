#include <iostream>
#include "parser.h"
using namespace std;

// Verifica se o caractere e valido para a base
// Ex: '8' nao e valido em octal, 'G' nao e valido em hex
bool digitoValido(char c, int base) {
    // converte para maiuscula para facilitar a comparacao
    if (c >= 'a' && c <= 'z')
        c = c - 32;

    if (base == BASE_BINARIO) {
        return c == '0' || c == '1';
    }

    if (base == BASE_OCTAL) {
        return c >= '0' && c <= '7';
    }

    if (base == BASE_DECIMAL) {
        return c >= '0' && c <= '9';
    }

    if (base == BASE_HEX) {
        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
    }

    return false;
}

// Percorre cada caractere do valor e verifica se e valido
bool validarValor(string valor, int base) {
    if (valor == "") {
        cout << "Erro: voce nao digitou nenhum valor!" << endl;
        return false;
    }

    for (int i = 0; i < valor.size(); i++) {
        // ignora o ponto ou virgula (separador decimal)
        if (valor[i] == '.' || valor[i] == ',')
            continue;

        if (!digitoValido(valor[i], base)) {
            cout << "Erro: o digito '" << valor[i] << "' nao e valido para a base " << base << endl;

            // mensagem de ajuda dependendo da base
            if (base == BASE_BINARIO)
                cout << "  Dica: binario so aceita 0 e 1" << endl;
            else if (base == BASE_OCTAL)
                cout << "  Dica: octal so aceita digitos de 0 a 7" << endl;
            else if (base == BASE_HEX)
                cout << "  Dica: hexadecimal aceita 0-9 e A-F" << endl;

            return false;
        }
    }

    return true;
}

// Mostra as opcoes de base e le a escolha do usuario
int escolherBase(string mensagem) {
    int opcao;
    cout << mensagem << endl;
    cout << "  1 - Decimal (base 10)" << endl;
    cout << "  2 - Binario (base 2)" << endl;
    cout << "  3 - Octal (base 8)" << endl;
    cout << "  4 - Hexadecimal (base 16)" << endl;
    cout << "  Escolha: ";
    cin >> opcao;

    // converte a opcao para o numero da base
    if (opcao == 1) return BASE_DECIMAL;
    if (opcao == 2) return BASE_BINARIO;
    if (opcao == 3) return BASE_OCTAL;
    if (opcao == 4) return BASE_HEX;

    // se digitou algo invalido, usa decimal como padrao
    cout << "Opcao invalida, usando decimal." << endl;
    return BASE_DECIMAL;
}

// Le os dados da conversao digitados pelo usuario
Entrada lerDoUsuario() {
    Entrada e;

    e.baseOrigem  = escolherBase("\nBase de ORIGEM:");
    e.baseDestino = escolherBase("\nBase de DESTINO:");

    // fica pedindo o valor ate o usuario digitar algo valido
    bool valido = false;
    while (!valido) {
        cout << "\nDigite o valor: ";
        cin >> e.valor;

        // troca virgula por ponto
        for (int i = 0; i < e.valor.size(); i++) {
            if (e.valor[i] == ',')
                e.valor[i] = '.';
        }

        // converte letras minusculas para maiusculas
        for (int i = 0; i < e.valor.size(); i++) {
            if (e.valor[i] >= 'a' && e.valor[i] <= 'z')
                e.valor[i] = e.valor[i] - 32;
        }

        valido = validarValor(e.valor, e.baseOrigem);
        if (!valido)
            cout << "Tente novamente." << endl;
    }

    return e;
}

// Monta a struct Entrada a partir dos dados do CSV
Entrada lerDoCSV(string valor, int baseOrigem, int baseDestino) {
    Entrada e;
    e.valor       = valor;
    e.baseOrigem  = baseOrigem;
    e.baseDestino = baseDestino;
    return e;
}

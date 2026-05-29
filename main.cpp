#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <limits>
#include <ctime>
#include "conversor.hpp"
using namespace std;

int main() {

    int baseOrigem, baseDestino;
    string valor;
    int opcao;

    int bases[4] = {2, 8, 10, 16};

    // inicializa o sorteador de numeros aleatorios
    srand(time(0));

    do {

        cout << "=== CONVERSOR DE BASES ===" << endl;
        cout << "[1] conversao simples" << endl;
        cout << "[2] passo a passo" << endl;
        cout << "[3] modo batch" << endl;
        cout << "[4] quiz" << endl;
        cout << "[5] calculadora de maximos" << endl;
        cout << "[0] sair" << endl;
        cout << endl;

        cin >> opcao;

        if (opcao == 1) {

            cout << "\nVoce escolheu conversao simples\n" << endl;

            cout << "Base de origem (2, 8, 10 ou 16): ";
            cin >> baseOrigem;

            cout << "Base de destino (2, 8, 10 ou 16): ";
            cin >> baseDestino;

            cout << "Digite o valor: ";
            cin >> valor;

            bool truncado;
            string resultado = converterFracionario(valor, baseOrigem, baseDestino, truncado);

            cout << "\nResultado: " << resultado << endl;

            if (truncado) {
                cout << "Aviso: resultado fracionario foi truncado em 16 casas!" << endl;
            }

            cout << "\nPressione ENTER para voltar ao menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } else if (opcao == 2) {

            cout << "\nVoce escolheu passo a passo\n" << endl;

            cout << "Base de origem (2, 8, 10 ou 16): ";
            cin >> baseOrigem;

            cout << "Base de destino (2, 8, 10 ou 16): ";
            cin >> baseDestino;

            cout << "Digite o valor: ";
            cin >> valor;

            long long numero = baseParaDecimal(valor, baseOrigem);

            cout << "\n--- PASSO A PASSO ---" << endl;
            cout << "Valor em decimal: " << numero << endl;
            cout << "Divisoes sucessivas:\n" << endl;

            long long temp = numero;

            while (temp > 0) {
                int resto = temp % baseDestino;
                cout << temp << " / " << baseDestino << " = " << temp / baseDestino
                     << " (resto " << valorParaChar(resto) << ")" << endl;
                temp = temp / baseDestino;
            }

            string resultado = decimalParaBase(numero, baseDestino);
            cout << "\nResultado final: " << resultado << endl;

            cout << "\nPressione ENTER para voltar ao menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } else if (opcao == 3) {

            cout << "\nVoce escolheu modo batch\n" << endl;

            ifstream entrada("entrada.csv");
            ofstream saida("saida.csv");

            if (!entrada.is_open()) {
                cout << "Erro ao abrir entrada.csv" << endl;
            } else {

                string linha;
                int contador = 0;

                // pula o cabecalho
                getline(entrada, linha);

                while (getline(entrada, linha)) {

                    if (linha.empty()) continue;

                    stringstream ss(linha);
                    string valorCSV, origemCSV, destinoCSV;

                    getline(ss, valorCSV, ';');
                    getline(ss, origemCSV, ';');
                    getline(ss, destinoCSV, ';');

                    if (valorCSV.empty() || origemCSV.empty() || destinoCSV.empty()) {
                        cout << "Linha invalida: " << linha << endl;
                        continue;
                    }

                    int baseOrigemCSV = atoi(origemCSV.c_str());
                    int baseDestinoCSV = atoi(destinoCSV.c_str());

                    bool truncado;
                    string resultado = converterFracionario(valorCSV, baseOrigemCSV, baseDestinoCSV, truncado);

                    saida << valorCSV << ";" << baseOrigemCSV << ";" << baseDestinoCSV << ";" << resultado << endl;
                    contador++;
                }

                entrada.close();
                saida.close();

                cout << "Conversoes realizadas: " << contador << endl;
                cout << "Arquivo saida.csv criado com sucesso!" << endl;
            }

            cout << "\nPressione ENTER para voltar ao menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } else if (opcao == 4) {

            cout << "\nVoce escolheu quiz\n" << endl;

            // escolha do nivel
            cout << "Escolha o nivel de dificuldade:" << endl;
            cout << "[1] Basico      (0 a 15)" << endl;
            cout << "[2] Iniciante   (0 a 255)" << endl;
            cout << "[3] Medio       (0 a 4095)" << endl;
            cout << "[4] Avancado    (0 a 65535)" << endl;
            cout << "[5] Expert      (0 a 1048575)" << endl;

            int nivel;
            cin >> nivel;

            // define o valor maximo baseado no nivel
            int valorMax;
            if (nivel == 1) valorMax = 15;
            else if (nivel == 2) valorMax = 255;
            else if (nivel == 3) valorMax = 4095;
            else if (nivel == 4) valorMax = 65535;
            else if (nivel == 5) valorMax = 1048575;
            else valorMax = 15;

            int quantas;
            cout << "\nQuantas perguntas? (1 a 10): ";
            cin >> quantas;

            int acertos = 0;

            for (int i = 0; i < quantas; i++) {

                // sorteia bases diferentes
                int idxOrig = rand() % 4;
                int idxDest = rand() % 4;
                while (idxDest == idxOrig)
                    idxDest = rand() % 4;

                int baseOrig = bases[idxOrig];
                int baseDest = bases[idxDest];

                // sorteia um numero 
                int numero = rand() % (valorMax + 1);

                // converte o numero para a base de origem
                string pergunta = decimalParaBase(numero, baseOrig);

                // calcula a resposta 
                string correta = decimalParaBase(numero, baseDest);

                // mostra a pergunta
                cout << "\nPergunta " << i+1 << "/" << quantas << endl;
                cout << "Converta " << pergunta << " (base " << baseOrig << ") para base " << baseDest << ": ";

                string resposta;
                cin >> resposta;

                // converte resposta para maiusculo para comparar
                for (int j = 0; j < resposta.size(); j++) {
                    if (resposta[j] >= 'a' && resposta[j] <= 'z')
                        resposta[j] = resposta[j] - 32;
                }

                if (resposta == correta) {
                    cout << "CORRETO!" << endl;
                    acertos++;
                } else {
                    cout << "Incorreto. A resposta era: " << correta << endl;
                }
            }

            cout << "\nFim do quiz! Acertos: " << acertos << "/" << quantas << endl;

            if (acertos == quantas)
                cout << "Perfeito! Excelente!" << endl;
            else if (acertos >= quantas / 2)
                cout << "Bom resultado!" << endl;
            else
                cout << "Continue praticando!" << endl;

            cout << "\nPressione ENTER para voltar ao menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } else if (opcao == 5) {

            cout << "\nVoce escolheu calculadora de maximos\n" << endl;

            int k;
            cout << "Quantos bits? (1 a 64): ";
            cin >> k;

            string dec, bin, oct, hex;
            maiorComKBits(k, dec, bin, oct, hex);

            cout << "\nMaximo com " << k << " bits (2^k - 1):" << endl;
            cout << "  Decimal     : " << dec << endl;
            cout << "  Binario     : " << bin << endl;
            cout << "  Octal       : " << oct << endl;
            cout << "  Hexadecimal : " << hex << endl;

            cout << "\nPressione ENTER para voltar ao menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } else if (opcao == 0) {

            cout << "\nSaindo..." << endl;

        } else {

            cout << "\nOpcao invalida!" << endl;

            cout << "\nPressione ENTER para voltar ao menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (opcao != 0);

    return 0;
}
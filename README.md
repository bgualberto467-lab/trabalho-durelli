[README.md](https://github.com/user-attachments/files/28310369/README.md)
# Conversor Universal de Sistemas de Numeração

**GCC241 – Introdução à Computação | UFLA 2026/1**

## Integrantes

|Nome|Responsabilidades|
|-|-|
|Bruno Gualberto|`parser.cpp`, `formatador.cpp`, `main.cpp`, F5, F7, F8, F9|
|Vinicius Carvalho|`conversor.cpp`, F1, F2, F3, F4, F6, F10|

## Linguagem

C++ (padrão C++17)

## Estrutura do Projeto

```
projeto/
├── src/
│   ├── parser.cpp       # Leitura e validação de entradas (F5)
│   ├── parser.h
│   ├── conversor.cpp    # Algoritmos de conversão (F1–F4, F6, F10)
│   ├── conversor.h
│   ├── formatador.cpp   # Exibição e modo passo-a-passo (F7)
│   ├── formatador.h
│   └── main.cpp         # CLI: menus, batch (F8), quiz (F9)
├── tests/
│   └── test\_conversor.cpp
├── entrada\_exemplo.csv
└── README.md
```

## Como Compilar

```bash
g++ -std=c++17 -Wall -o conversor src/main.cpp src/parser.cpp src/formatador.cpp src/conversor.cpp
```

## Como Executar

```bash
./conversor
```

## Modos de Uso

### 1\. Conversão simples

Escolha a opção `\[1]` no menu. Informe a base de origem, a base de destino e o valor.

### 2\. Modo passo a passo (F7)

Escolha a opção `\[2]`. Exibe o trace completo do algoritmo de conversão.

### 3\. Modo batch CSV (F8)

Escolha a opção `\[3]`. O programa lê um arquivo `entrada.csv` com formato:

```
valor;base\_origem;base\_destino
1010;2;10
FF;16;10
```

E grava `saida.csv` com:

```
valor;base\_origem;resultado;base\_destino
```

Exemplo de uso com o arquivo incluído:

```bash
# No menu, escolha \[3] e informe "entrada\_exemplo.csv"
```

### 4\. Modo quiz (F9)

Escolha a opção `\[4]`. Selecione o nível de dificuldade (1–5) e o número de perguntas. O programa gera conversões aleatórias e verifica suas respostas.

### 5\. Calculadora de máximos (F10)

Escolha a opção `\[5]`. Informe o número de bits `k` e o programa exibe `2^k - 1` nas 4 bases.

## Exemplos de Uso

|Entrada|Base Origem|Base Destino|Resultado|
|-|-|-|-|
|`1010`|Binário (2)|Decimal (10)|`10`|
|`255`|Decimal (10)|Binário (2)|`11111111`|
|`FF`|Hex (16)|Octal (8)|`377`|
|`10.625`|Decimal (10)|Binário (2)|`1010.101`|

## Como Rodar os Testes

```bash
g++ -std=c++17 -o testes tests/test\_conversor.cpp src/parser.cpp src/formatador.cpp src/conversor.cpp
./testes
```

## Limitações Conhecidas

* Números negativos não são suportados.
* Parte fracionária limitada a 16 casas (truncamento indicado explicitamente).
* Não utiliza nenhuma função de conversão de base da biblioteca padrão.

## Vídeo de Demonstração

\[Link do vídeo aqui]


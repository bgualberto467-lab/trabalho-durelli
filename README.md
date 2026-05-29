# Conversor Universal de Sistemas de Numeração

**GCC241 – Introdução à Computação | UFLA 2026/1**

## Integrantes

| Nome | Responsabilidades |
|------|-------------------|
| Bruno Gualberto| main.cpp, parser.cpp, parser.h |
| Vinicius Carvalho | conversor.cpp, conversor.hpp |

## Linguagem

C++ (padrão C++17)

## Estrutura do Projeto

```text
trabalho/
├── main.cpp
├── parser.cpp
├── parser.h
├── conversor.cpp
├── conversor.hpp
├── entrada.csv
├── saida.csv
├── README.md
├── .gitignore
└── .vscode/
```

## Como Compilar

```bash
g++ -std=c++17 -o conversor main.cpp parser.cpp conversor.cpp
```

## Como Executar

```bash
./conversor
```

## Arquivo CSV

O arquivo `entrada.csv` contém os valores utilizados para conversão em lote.

Exemplo:

```text
1010;2;10
FF;16;10
```

O programa gera automaticamente o arquivo `saida.csv`.

## Funcionalidades

- Conversão entre bases numéricas
- Conversão em lote usando CSV
- Interface via terminal
- Conversão passo a passo

## Limitações

- Não suporta números negativos
- Parte fracionária limitada
- Não utiliza bibliotecas prontas de conversão

## Vídeo de Demonstração

[Adicionar link do vídeo]
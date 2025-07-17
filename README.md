# Projeto-hashtags

## Identificação do Aluno
Nome: Leandro Arthur Marinho Ferreira
Matrícula: 20230067840

## Descrição:
 Leitura de um arquivo "hashtags.txt" contendo pares
 "peso   #hashtag", armazenamento em vetor de objetos,
 busca por prefixo e ordenação por popularidade (peso).   
 Interface de terminal simples.

## Como Compilar e Rodar o Programa
1. Ter um compilador C++ instalado (ex: g++).
2. Compilar manualmente:
   g++ -std=c++17 -Wall -O2 hashtag_suggester.cpp -o hashtag_suggester
3. Com Makefile:
 ```bash
make        # Compila o programa
make run    # Compila e executa
make clean  # Remove o executável
```

## Funcionalidades
- Leitura de hashtags a partir de um arquivo `hashtags.txt` (formato: `peso<TAB>#hashtag`);
- Busca de hashtags com base em prefixos digitados (case-insensitive);
- Ordenação por popularidade (peso);
- Interface simples via terminal

## Conceitos Aplicados
- Programação orientada a objetos (herança, classes, abstratas);
- Leitura e manipulação de arquivos;
- Ordenação e filtragem de dados;
- Interface por linha de comando;
- Organização modular e reutilização de código.

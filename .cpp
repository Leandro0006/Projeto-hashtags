// ------------------------------------------------------------
// Projeto: Assistente de Sugestão de Hashtags
// Linguagem: C++17
// Autor: Leandro Arthur (equipe)
// Data: 02/07/2025
// ------------------------------------------------------------
// Descrição:
//  Leitura de um arquivo "hashtags.txt" contendo pares
//  "peso<TAB>#hashtag", armazenamento em vetor de objetos,
//  busca por prefixo (case‑insensitive) e ordenação por
//  popularidade (peso). Interface de terminal simples.
// ------------------------------------------------------------
// Compilação (exemplo):
//  g++ -std=c++17 -Wall -O2 hashtag_suggester.cpp -o hashtag_suggester
// ------------------------------------------------------------

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//-------------------------------------------------------------
// Estrutura que representa uma hashtag e seu peso (popularidade)
//-------------------------------------------------------------
struct Hashtag {
    int weight;          // popularidade
    std::string tag;     // texto da hashtag (ex: "#tiktok")

    // Converte a hashtag para lowercase – útil para buscas sem case‑sensitivity
    std::string lowercase() const {
        std::string result = tag;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }
};

//-------------------------------------------------------------
// Carrega as hashtags a partir de um arquivo texto.
// Formato esperado por linha: <peso><TAB><#hashtag>
//-------------------------------------------------------------
std::vector<Hashtag> loadHashtags(const std::string &filename) {
    std::vector<Hashtag> hashtags;
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Não foi possível abrir " + filename);
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        int w = 0;
        std::string tag;
        if (iss >> w >> tag) {
            hashtags.push_back({w, tag});
        }
    }
    return hashtags;
}

//-------------------------------------------------------------
// Sugere hashtags que começam com um determinado prefixo.
//  - Filtra por prefixo (não diferencia maiúsc./minúsc.)
//  - Ordena por peso decrescente
//  - Limita o número máximo de resultados (default = 10)
//-------------------------------------------------------------
std::vector<Hashtag> suggest(const std::vector<Hashtag> &all, const std::string &prefix,
                             std::size_t maxResults = 10) {
    // Converte prefixo para minúsculas
    std::string prefixLower = prefix;
    std::transform(prefixLower.begin(), prefixLower.end(), prefixLower.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // Filtra
    std::vector<Hashtag> filtered;
    for (const auto &h : all) {
        if (h.lowercase().rfind(prefixLower, 0) == 0) { // começa com prefixo?
            filtered.push_back(h);
        }
    }

    // Ordena por popularidade (peso) decrescente
    std::sort(filtered.begin(), filtered.end(),
              [](const Hashtag &a, const Hashtag &b) { return a.weight > b.weight; });

    // Limita tamanho do vetor
    if (filtered.size() > maxResults) {
        filtered.resize(maxResults);
    }
    return filtered;
}

//-------------------------------------------------------------
// Programa principal
//-------------------------------------------------------------
int main() {
    const std::string DATAFILE = "hashtags.txt";
    std::vector<Hashtag> database;

    try {
        database = loadHashtags(DATAFILE);
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << "\n";
        return 1;
    }

    std::cout << "\nAssistente de Busca de Hashtags\n";
    std::cout << "(Digite 'sair' para encerrar)\n\n";

    std::string input;
    while (true) {
        std::cout << "Digite um prefixo de hashtag (ou ’sair’ para encerrar): ";
        std::cin >> input;
        if (input == "sair")
            break;

        auto results = suggest(database, input);
        if (results.empty()) {
            std::cout << "Nenhuma hashtag encontrada com esse prefixo.\n\n";
        } else {
            std::cout << "\nSUGESTÕES:\n";
            for (const auto &h : results) {
                std::cout << h.tag << " (" << h.weight << ")\n";
            }
            std::cout << '\n';
        }
    }

    std::cout << "Até logo!\n";
    return 0;
}

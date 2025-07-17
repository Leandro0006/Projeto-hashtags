#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>gg
#include <string>
#include <vector>
#include <memory>

// Classe base abstrata para sugestões genéricas
class Suggester {
public:
    virtual std::vector<std::string> suggest(const std::string& prefix, std::size_t maxResults = 10) = 0;
    virtual ~Suggester() {}
};

// Classe que representa uma hashtag e seu peso (popularidade)
class Hashtag {
    int weight;          // popularidade
    std::string tag;     // texto da hashtag (ex: "#tiktok")

public:
    Hashtag() : weight(0), tag("") {} // Construtor padrão necessário
    Hashtag(int w, const std::string& t) : weight(w), tag(t) {}

    int getWeight() const { return weight; }
    std::string getTag() const { return tag; }

    std::string lowercase() const {
        std::string result = tag;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }
};

// Classe de sugestões baseada em hashtags
class HashtagSuggester : public Suggester {
    std::vector<Hashtag> all;

public:
    HashtagSuggester(const std::vector<Hashtag>& data) : all(data) {}

    std::vector<std::string> suggest(const std::string& prefix, std::size_t maxResults = 10) override {
        std::string prefixLower = prefix;
        std::transform(prefixLower.begin(), prefixLower.end(), prefixLower.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        std::vector<Hashtag> filtered;
        for (const auto& h : all) {
            if (h.lowercase().rfind(prefixLower, 0) == 0) {
                filtered.push_back(h);
            }
        }

        std::sort(filtered.begin(), filtered.end(),
                  [](const Hashtag& a, const Hashtag& b) { return a.getWeight() > b.getWeight(); });

        if (filtered.size() > maxResults) {
            filtered.resize(maxResults);
        }

        std::vector<std::string> results;
        for (const auto& h : filtered) {
            results.push_back(h.getTag() + " (" + std::to_string(h.getWeight()) + ")");
        }

        return results;
    }
};

// Carrega as hashtags a partir de um arquivo texto
std::vector<Hashtag> loadHashtags(const std::string& filename) {
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
            hashtags.emplace_back(w, tag);
        }
    }
    return hashtags;
}

// Programa principal
int main() {
    const std::string DATAFILE = "hashtags.txt";
    std::vector<Hashtag> database;

    try {
        database = loadHashtags(DATAFILE);
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << "\n";
        return 1;
    }

    std::unique_ptr<Suggester> suggester(new HashtagSuggester(database));

    std::cout << "\nAssistente de Sugestão de Hashtags\n";
    std::cout << "(Digite 'sair' para encerrar)\n\n";

    std::string input;
    while (true) {
        std::cout << "Digite um prefixo de hashtag: ";
        std::cin >> input;
        if (input == "sair")
            break;

        auto results = suggester->suggest(input);
        if (results.empty()) {
            std::cout << "Nenhuma hashtag encontrada com esse prefixo.\n\n";
        } else {
            std::cout << "\nSUGESTÕES:\n";
            for (const auto& line : results) {
                std::cout << line << "\n";
            }
            std::cout << '\n';
        }
    }

    std::cout << "Até logo!\n";
    return 0;
}

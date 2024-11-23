#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "trie.cpp"

// Função que avalia uma palavra individualmente usando a Trie fornecida
void avaliate_individual_word(const std::string& word, const Trie& dicionario);

int main() {
    // Lê uma linha de entrada do usuário
    std::string input_line;
    std::getline(std::cin, input_line);
    
    // Usa um stream para separar o nome do arquivo e as palavras
    std::istringstream iss(input_line);
    std::string filename;
    iss >> filename; // O primeiro token é o nome do arquivo

    // Abre o arquivo especificado
    std::ifstream arquivo_dicionario(filename);
    if (!arquivo_dicionario.is_open()) {
        // Se o arquivo não puder ser aberto, exibe erro e encerra o programa
        std::cout << "input=" << filename << std::endl;
        std::cout << "output=erro" << std::endl;
        return 1;
    }

    Trie dicionario;
    std::string linha;
    unsigned long posicao_atual = 0;

    // Lê cada linha do arquivo e adiciona as palavras à Trie
    while (std::getline(arquivo_dicionario, linha)) {
        if (linha.empty()) continue; // Ignora linhas vazias
        
        // Encontra as palavras dentro de colchetes '[palavra]'
        size_t start = linha.find('[');
        size_t end = linha.find(']');
        if (start != std::string::npos && end != std::string::npos) {
            // Extrai a palavra entre os colchetes
            std::string palavra = linha.substr(start + 1, end - start - 1);
            dicionario.insert(palavra, posicao_atual, linha.length());
        }
        // posição atual + 1 (para o caractere de nova linha)
        posicao_atual += linha.length() + 1;
    }
    arquivo_dicionario.close();

    std::string word;
    while (iss >> word) {
        if (word == "0") {
            break;
        }
        avaliate_individual_word(word, dicionario);
    }

    return 0;
}

// Func que avalia uma palavra individualmente
void avaliate_individual_word(const std::string& word, const Trie& dicionario) {
    // Conta quantos prefixos começam com a palavra fornecida
    int quantidade_prefixos = dicionario.countPrefix(word);
    
    if (quantidade_prefixos > 0) {
        std::cout << word << " is prefix of " << quantidade_prefixos << " words" << std::endl;
        
        // Verifica se a palavra está no dicionário e obtém posição e comprimento
        unsigned long posicao, comprimento;
        if (dicionario.search(word, posicao, comprimento)) {
            std::cout << word << " is at (" << posicao << "," << comprimento << ")" << std::endl;
        }
    } else {
        std::cout << word << " is not prefix" << std::endl;
    }
}

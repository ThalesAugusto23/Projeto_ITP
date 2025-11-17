#include <fstream>
#include <string>
#include "../sequencia/sequencia.h"

struct Cor {
    int r, g, b;
};

class Paleta {
    Sequencia<Cor> cores;

    void lerArquivo(const std::string& arquivo) {
        std::ifstream hexx(arquivo);
        std::string s;
        if (hexx.is_open()) {
            while(std::getline(hexx, s)) {
                cores.adicionar(converter(s));
            }
        } else {
            std::cerr << "Erro ao abrir arquivo";
        }
    }

    Cor converter(std::string s) {
        int r, g, b;

        r = std::stoi(s.substr(1, 2), nullptr, 16);
        g = std::stoi(s.substr(3, 2), nullptr, 16);
        b = std::stoi(s.substr(5, 2), nullptr, 16);

        return Cor{r,g,b};
    }


public:
    Paleta(){};
    
    Paleta(const std::string& arquivo) {
        lerArquivo(arquivo);
    }

    void adicionarCor(Cor cor) {
        cores.adicionar(cor);
    }

    int obterTamanho(){
        return cores.obterTamanho();
    }

    Cor obterCor(int indice) {
        if (indice < 0 || indice >= cores.obterTamanho()) {
            return Cor{0, 0, 0};
        }
        return cores[indice];
    }

};
#include <fstream>
#include <string>
#include <sstream>
#include "../sequencia/sequencia.h"

struct Cor {
    int r, g, b;
};

class Paleta {
    Sequencia<Cor> cores;

    void lerArquivo(const std::string& arquivo) {
        std::ifstream hexx(arquivo);
        std::string s;
        
        while(std::getline(hexx, s)) {
            cores.adicionar(converter(s));
        }
    }

    Cor converter(std::string s) {
        std::stringstream ss;
        int r, g, b;

        ss << std::hex << s.substr(1, 2);
        ss >> r;
        ss.clear();

        ss << std::hex << s.substr(3, 2);
        ss >> g;
        ss.clear();

        ss << std::hex << s.substr(5, 2);
        ss >> b;

        Cor cor = {r, g, b};
        return cor;
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
        cores.obterTamanho();
    }

    Cor obterCor(int indice) {
        return cores[indice];
    }

};
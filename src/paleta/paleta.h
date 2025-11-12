#include <fstream>
#include <string>
#include <cstdlib>
#include "../sequencia/sequencia.h"

struct Cor {
    int r, g, b;
};

class Paleta {
    Sequencia<Cor> cores;

    void lerArquivo(const std::string& arquivo) {
        std::ifstream hexx(arquivo);
        std::string s;
        for (int i = 0; i < 32; i++)
        {
            hexx >> s;
            cores.adicionar(converter(s));
        }
        

    }

    Cor converter(std::string s) {
        Cor cor;
        int aux;
        int aux2;
        int r,g,b;
        for(int i = 1; i < s.size(); i+2) {
            if (s[i] == 'A') {
                aux = 10;
            } else if (s[i] == 'B'){
                aux = 11;
            } else if (s[i] == 'C'){
                aux = 12;
            } else if (s[i] == 'D'){
                aux = 13;
            } else if (s[i] == 'E'){
                aux = 14;
            } else if (s[i] == 'F'){
                aux = 15;
            } else {
                aux = s[i] - '0';
            }

            if (s[i+1] == 'A') {
                aux2 = 10;
            } else if (s[i+1] == 'B'){
                aux2 = 11;
            } else if (s[i+1] == 'C'){
                aux2 = 12;
            } else if (s[i+1] == 'D'){
                aux2 = 13;
            } else if (s[i+1] == 'E'){
                aux2 = 14;
            } else if (s[i+1] == 'F'){
                aux2 = 15;
            } else {
                aux2 = s[i+1] - '0';
            }

            if (i < 2) {
                r = 16*aux + aux2;
            } else if (i < 4) {
                g = 16*aux + aux2;
            } else {
                b = 16*aux + aux2;
            }
            
        }
        cor = {r, g, b};
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
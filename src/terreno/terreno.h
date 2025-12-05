#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "../imagem/imagem.h"
#include <iomanip>

class Terreno {
int linhas; // quantidade de linhas da matriz
int colunas; // quantidade de colunas da matriz
int *altitudes; // matriz dinâmica de altitudes

    //Diamond Step: calcula o ponto central de um quadrado
void passoDiamond(int x, int y, int tamanho, float desloc) {
    int meio = tamanho / 2;

    int a = at(x, y);
    int b = at(x, y + tamanho);
    int c = at(x + tamanho, y);
    int d = at(x + tamanho, y + tamanho);

    int media = (a + b + c + d) / 4;
    float ruido = (rand() % 2000) / 1000.0f - 1.0f;

    // rand() % 2000 --> numero aleatório entre 0 a 1999
    // / 1000.0f - 1.0f --> divide por 1000 e subtrai 1, logo o intervalo será de -1 a 1
    // isso é ruído e nao rugosidade

    at(x + meio, y + meio) = media + desloc * ruido;
}

// --- Função auxiliar para o Square Step ---
int mediaSquare(int x, int y, int tamanho, float desloc) {
    int soma = 0;
    int contador = 0;
    int meio = tamanho / 2;
    
    // calculamos a media dos pontos ao redor do ponto central

    // CIMA
    if (x - meio >= 0) {
        soma += at(x - meio, y);
        contador++;
    }

    // BAIXO
    if (x + meio <= linhas-1) {
        soma += at(x + meio, y);
        contador++;
    }

    // ESQUERDA
    if (y - meio >= 0) {
        soma += at(x, y - meio);
        contador++;
    }

    // DIREITA
    if (y + meio <= colunas-1) {
        soma += at(x, y + meio);
        contador++;
    }
    
    // os contadores servem para indicar se existem ou nao pontos ao redor do ponto central

    // adiciona ruído
    int media = soma / contador;
    float ruido = (rand() % 2000) / 1000.0f - 1.0f;

    return media + desloc * ruido;
}

// --- Square Step ---
void passoSquare(int x, int y, int tamanho, float desloc) {
    at(x, y) = mediaSquare(x, y, tamanho, desloc);
}

//Diamond-Square completo
void gerarTerreno(float rugosidade) {
    int tamanho = linhas - 1;
    float desloc = tamanho*2.0f;

    // Inicializa cantos aleatórios
    at(0, 0) = rand() % 5000; // valores aleatorios de 0 a 4999
    at(0, tamanho) = rand() % 5000;
    at(tamanho, 0) = rand() % 5000;
    at(tamanho, tamanho) = rand() % 5000;

    while (tamanho > 1) { // enquanto houver quadrados para dividir
        int metade = tamanho / 2;

        // Diamond (central)
        for (int x = 0; x < linhas - 1; x += tamanho) {
            for (int y = 0; y < colunas - 1; y += tamanho) {
                passoDiamond(x, y, tamanho, desloc);
            }
        }

        // Square (ao redor)
        for (int x = 0; x < linhas; x += metade) {
            for (int y = ((x%tamanho == 0 ? metade : 0)); y < colunas; y += tamanho) {
                passoSquare(x, y, tamanho, desloc);
            }
        }

        tamanho /= 2;
        desloc *= rugosidade;
    }
}

public:
    Terreno(int n, float rugosidade = 0.5) {
        linhas = pow(2, n) + 1;
        colunas = linhas;
        altitudes = new int[linhas * colunas];

        gerarTerreno(rugosidade);

    }

    ~Terreno() {
        delete[] altitudes; // libera memoria
    }

    //Função de acesso na matriz 1D
    inline int& at(int x, int y) {
        return altitudes[x * colunas + y];
    }
    
    int obterLargura(){ 
        return colunas; 
    }

    int obterProfundidade(){ 
        return linhas; 
    }

    float obterAltitude(int x, int y) {
        return at(x, y);
    }

    // Salvar em arquivo
    void salvarTerreno(const std::string &nome) const {
        std::ofstream arq(nome);

        arq << linhas << " " << colunas << "\n";

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                arq << altitudes[i*colunas+j] << " ";
            }
            arq << "\n";
        }

        arq.close();
    }


    // Ler de arquivo
    void lerTerreno(const std::string &nome) {
        std::ifstream arq(nome);

        int novaL, novaC;
        arq >> novaL >> novaC;

        if(linhas != novaL || novaC != colunas) {
            delete[] altitudes;
            colunas = novaC;
            linhas = novaL;
            altitudes = new int[linhas * colunas];
        }

        for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
        arq >> altitudes[i * colunas + j];


        arq.close();
    }

    Imagem criarImagem (const Paleta& p) {
        Imagem img(colunas, linhas);

        int totalCores = p.obterTamanho();
        if (totalCores == 0) {
            std::cerr << "Paleta vazia!\n";
            return img; // imagem preta
        }

        // Encontrar menor e maior altitude para mapear para a paleta
        int minAlt = altitudes[0];
        int maxAlt = altitudes[0];

        for (int i = 0; i < linhas * colunas; i++) {
            if (altitudes[i] < minAlt) minAlt = altitudes[i];
            if (altitudes[i] > maxAlt) maxAlt = altitudes[i];
        }

        // int altBase = at(0,0); // altitude do ponto superior-esquerdo

        for (int x = 1; x < linhas; x++) {
            for (int y = 1; y < colunas; y++) {

                int altBase = at(x-1,y-1);
                int alt = at(x, y);

                // normaliza altitude para índice da paleta
                float t = float(alt - minAlt) / float(maxAlt - minAlt);
                int indice = t * (totalCores - 1);

                Cor c = p.obterCor(indice);

                // --- escurecer caso altitude < altitude(0,0) ---
                if (alt < altBase) {
                    c.r = c.r * 0.7;
                    c.g = c.g * 0.7;
                    c.b = c.b * 0.7;
                }

                img(y, x) = c; // lembre-se do operador img(x,y)
            }
        }

        return img;


    }
};

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>


class Terreno {
int linhas; // quantidade de linhas da matriz
int colunas; // quantidade de colunas da matriz
float *altitudes; // matriz dinâmica de altitudes

    //Diamond Step: calcula o ponto central de um quadrado
void passoDiamond(int x, int y, int tamanho, float desloc) {
    int meio = tamanho / 2;

    float a = at(x, y);
    float b = at(x, y + tamanho);
    float c = at(x + tamanho, y);
    float d = at(x + tamanho, y + tamanho);

    float media = (a + b + c + d) / 4.0f;
    float ruido = (rand() % 2000) / 1000.0f - 1.0f;

    // rand() % 2000 --> numero aleatório entre 0 a 1999
    // / 1000.0f - 1.0f --> divide por 1000 e subtrai 1, logo o intervalo será de -1 a 1
    // isso é ruído e nao rugosidade

    at(x + meio, y + meio) = media + desloc * ruido;
}

// --- Função auxiliar para o Square Step ---
float mediaSquare(int x, int y, int tamanho, float desloc) {
    float soma = 0.0f;
    int contador = 0;
    int meio = tamanho / 2;
    
    // calculamos a media dos pontos ao redor do ponto central

    // CIMA
    if (x - meio >= 0) {
        soma += at(x - meio, y);
        contador++;
    }

    // BAIXO
    if (x + meio < linhas) {
        soma += at(x + meio, y);
        contador++;
    }

    // ESQUERDA
    if (y - meio >= 0) {
        soma += at(x, y - meio);
        contador++;
    }

    // DIREITA
    if (y + meio < colunas) {
        soma += at(x, y + meio);
        contador++;
    }
    
    // os contadores servem para indicar se existem ou nao pontos ao redor do ponto central

    // adiciona ruído
    float media = soma / contador;
    float ruido = (rand() % 2000) / 1000.0f - 1.0f;

    return media + desloc * ruido;
}

// --- Square Step ---
void passoSquare(int x, int y, int tamanho, float desloc) {
    int meio = tamanho / 2;

    if (x - meio >= 0)
        at(x - meio, y) = mediaSquare(x - meio, y, tamanho, desloc);

    if (x + meio < linhas)
        at(x + meio, y) = mediaSquare(x + meio, y, tamanho, desloc);

    if (y - meio >= 0)
        at(x, y - meio) = mediaSquare(x, y - meio, tamanho, desloc);

    if (y + meio < colunas)
        at(x, y + meio) = mediaSquare(x, y + meio, tamanho, desloc);
}

//Diamond-Square completo
void gerarTerreno(float rugosidade) {
    int tamanho = linhas - 1;
    float desloc = tamanho * rugosidade;

    // Inicializa cantos aleatórios
    at(0, 0) = rand() % 10000; // valores aleatorios de 0 a 9999
    at(0, tamanho) = rand() % 10000;
    at(tamanho, 0) = rand() % 10000;
    at(tamanho, tamanho) = rand() % 10000;

    while (tamanho > 1) { // enquanto houver quadrados para dividir
        int metade = tamanho / 2;

        // Diamond (central)
        for (int x = 0; x < linhas - 1; x += tamanho) {
            for (int y = 0; y < colunas - 1; y += tamanho) {
                passoDiamond(x, y, tamanho, desloc);
            }
        }

        // Square (ao redor)
        for (int x = 0; x < linhas - 1; x += tamanho) {
            for (int y = 0; y < colunas - 1; y += tamanho) {
                passoSquare(x + metade, y + metade, tamanho, desloc);
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
        altitudes = new float[linhas * colunas];

        gerarTerreno(rugosidade);

    }

    ~Terreno() {
        delete[] altitudes; // libera memoria
    }

    //Função de acesso na matriz 1D
    inline float& at(int x, int y) {
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
            altitudes = new float[linhas * colunas];
        }

        for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
        arq >> altitudes[i * colunas + j];


        arq.close();
    }
};

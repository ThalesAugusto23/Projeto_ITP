#include <iostream>
#include "../terreno/terreno.h"
#include <ctime>

int main() {
    srand(time(nullptr));
    
    while (true) {
        std::cout << "---------------------------------\n";
        std::cout << "1 - Criar paleta manualmente\n";
        std::cout << "2 - Ler arquivo com a paleta \n";
        std::cout << "3 - Sair\n";
        std::cout << "---------------------------------\n";
        
        int n;
        std::cout << "R: ";
        std::cin >> n;
        if (n == 1) {
            Paleta p;
            while (true) {
                std::cout << "---------------------------------\n";
                std::cout << "1 - Adicionar cor\n";
                std::cout << "2 - Gerar imagem\n";
                std::cout << "---------------------------------\n";

                std::cout << "R: ";
                std::cin >> n;
                if (n == 1) {
                    int r, g, b;
                    std::cout << "---------------------------------\n";
                    std::cout << "Valor red da cor:\n";
                    std::cin >> r;

                    std::cout << "Valor green da cor:\n";
                    std::cin >> g;

                    std::cout << "Valor blue da cor:\n";
                    std::cin >> b;

                    Cor cor = {r, g, b};

                    p.adicionarCor(cor);
                } else if (n==2){
                    std::cout << "---------------------------------\n";
                    std::cout << "Tamanho da imagem a ser gerada: (máx 11)\n";
                    std::cin >> n;
                    Terreno t(n);
                    std::cout << "Nome do arquivo para salvar a imagem:\n";
                    std::string s;
                    std::cin >> s;
                    Imagem img = t.criarImagem(p);
                    img.salvarPPM(s);
                    std::cout << "Imagem criada!\n";

                    break;
                } else {
                    continue;
                }
            }
        } else if (n == 2) {
            std::cout << "---------------------------------\n";
            std::cout << "Nome do arquivo a ser lido:\n";
            std::string s;
            std::cin >> s;
            Paleta p(s);
            while (true) {
                std::cout << "---------------------------------\n";
                std::cout << "1 - Adicionar cor\n";
                std::cout << "2 - Gerar imagem\n";
                std::cout << "---------------------------------\n";

            
                std::cin >> n;
                if (n == 1) {
                    int r, g, b;
                    std::cout << "Valor red da cor:\n";
                    std::cin >> r;

                    std::cout << "Valor green da cor:\n";
                    std::cin >> g;

                    std::cout << "Valor blue da cor:\n";
                    std::cin >> b;

                    Cor cor = {r, g, b};

                    p.adicionarCor(cor);
                } else {
                    std::cout << "Tamanho da imagem a ser gerada: (máx 11)\n";
                    std::cin >> n;
                    Terreno t(n);
                    std::cout << "Nome do arquivo para salvar a imagem:\n";
                    std::string s;
                    std::cin >> s;
                    Imagem img = t.criarImagem(p);
                    img.salvarPPM(s);
                    std::cout << "Imagem criada!\n";
                    break;
                }
            }
        }
        else if (n == 3) {
            return 0;
        }
    }

    Paleta p("cores.hex");
    Terreno t(10);
    Imagem img = t.criarImagem(p);
    img.salvarPPM("img.ppm");

    return 0;
}
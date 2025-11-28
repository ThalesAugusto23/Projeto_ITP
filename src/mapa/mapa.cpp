#include <iostream>
#include "../terreno/terreno.h"

int main() {
    std::cout << "Nome do arquivo da paleta:\n";
    std::string s;
    std::getline(std::cin, s);
    Paleta p(s);

    std::cout << "Tamanho do mapa de altitudes:\n";
    int n;
    std::cin >> n;
    Terreno t(n);

    std::cout << "Nome do arquivo da imagem PPM a ser salvo:\n";
    std::cin >> s;

    Imagem img = t.criarImagem(p);
    img.salvarPPM(s);

    return 0;
}
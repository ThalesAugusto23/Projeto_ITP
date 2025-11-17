#include "../paleta/paleta.h"

using Pixel = Cor;

class Imagem {
    int largura, altura;
    Pixel *matriz;

public:
    Imagem(int l=0, int a=0) : largura(l), altura(a){
        matriz = new Pixel[largura * altura];
        for (int i = 0; i < altura; i++)
        {
            for (int j = 0; j < largura; j++)
            {
                matriz[i * largura + j] = {0, 0, 0};
            }
        }
    }

    ~Imagem() {
        delete [] matriz;
    };

    Pixel& operator()(int x, int y) {
        return matriz[y * largura + x];
    }


    int obterLargura() {
        return largura;
    }

    int obterAltura() {
        return altura;
    }

    bool lerPPM(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);

        if(!arquivo){return false;}

        std::string p3;
        arquivo >> p3;

        if (p3 != "P3") {return false;}

        arquivo >> largura >> altura;
        int maxCor;
        arquivo >> maxCor;

        delete [] matriz;

        matriz = new Pixel[altura * largura];

        for (int i = 0; i < altura*largura; i++)
        {
            int r, g, b;
            arquivo >> r >> g >> b;
            matriz[i].r = r;
            matriz[i].g = g;
            matriz[i].b = b;
        }

        return true;
    }

    bool salvarPPM(const std::string& nomeArquivo) {
        std::ofstream arquivo(nomeArquivo);

        arquivo << "P3\n";
        arquivo << largura << " " << altura << "\n";
        arquivo << "255\n";

        for (int i = 0; i < largura*altura; i++)
        {
            arquivo << matriz[i].r << " " << matriz[i].g << " " << matriz[i].b << "\n";
        }
        
        return true;
    }
};
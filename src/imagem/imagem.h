#include "../paleta/paleta.h"



class Imagem {
    int largura, altura;
    Cor **pixels = new Cor *[largura];

public:
    Imagem(int l, int a) : largura(l), altura(a){
        for (int i = 0; i < l; i++)
        {
            pixels[i] = new Cor[altura];
        }

        for (int i = 0; i < largura; i++)
        {
            for (int j = 0; j < altura; j++)
            {
                pixels[i][j] = {0,0,0};
            }
            
        }
    }

    ~Imagem() {
        delete [] pixels;
    }



    int obterLargura() {
        return largura;
    }

    int obterAltura() {
        return altura;
    }
};
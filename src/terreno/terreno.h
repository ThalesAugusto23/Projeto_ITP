#include <cmath>
#include <random>

class Terreno {
    int tamanho;
    float *matriz;


    float randFloat(float amplitude) {
        static std::mt19937 gen(
            std::chrono::steady_clock::now().time_since_epoch().count()
        );
        std::uniform_real_distribution<float> dist(-amplitude, amplitude);
        return dist(gen);
    }

    void diamondStep() {
        int passo = tamanho-1;
        while (passo > 1) {
            for (int i = 0; i < tamanho-1; i +=(tamanho-1)/2)
            {
            for (int j = 0; j < tamanho-1; j +=(tamanho-1)/2)
            {
                float c1 = matriz[i*tamanho+j];
                float c2 = matriz[(i+tamanho-1) * tamanho + j];
                float c3 = matriz[i*tamanho + (j + tamanho-1)];
                float c4 = matriz[(i+tamanho-1) * tamanho + j + tamanho - 1];

                float media = (c1 + c2 + c3 + c4) / 4.0;

                matriz[((tamanho-1)/2) * tamanho + ((tamanho-1)/2)] = media + randFloat(10.0);
            }
            }
            passo /= 2;
        }
        
    }

    void squareStep() {
        int passo = tamanho-1;
        while(passo > 1) {
            int meio = passo / 2;
            for (int y = 0; y < tamanho-1; y += passo) {
                    for (int x = 0; x < tamanho - 1; x += passo) {

                        float c1 = matriz[y*tamanho+x];
                        float c2 = matriz[(y+passo)*tamanho+x];
                        float c3 = matriz[y*tamanho+y+passo];
                        float c4 = matriz[(y+passo)*tamanho+(x+passo)];

                        float media = (c1 + c2 + c3 + c4) / 4.0f;

                        matriz[(y+meio)*tamanho+x+meio] = media + randFloat(10.0);
                    }
                }
                passo /= 2;

    }
    }

public:

    Terreno(int n){
        tamanho = pow(2, n) + 1;
        matriz = new float[tamanho*tamanho];
        gerarMapa();
    }

    ~Terreno() {

    }

    int obterLargura() {
        return tamanho;
    }
    
    int obterProfundidade() {
        return tamanho;
    }

    void gerarMapa() {
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);
        
        std::uniform_int_distribution<> distrib(1, 100);

        matriz[0*tamanho+0] = distrib(gen);
        matriz[0*tamanho+tamanho-1] = distrib(gen);
        matriz[(tamanho-1)*tamanho] = distrib(gen);
        matriz[(tamanho-1)*tamanho+tamanho-1] = distrib(gen);

        diamondStep();
        squareStep();
        
    }

    float* obterMatriz() { return matriz; }

};
template <typename T>
class Sequencia {
    int capacidade, tamanho;
    T *dados = nullptr;

    void aumentarCapacidade() {
        capacidade *= 2;
        T *novo = new T[capacidade];

        for (int i = 0; i < tamanho; i++)
        {
            novo[i] = dados[i];
        }

        delete[] dados;
        dados = novo;
    }

public:
    Sequencia(int cap=2) : capacidade(cap), tamanho(0) {
        dados = new T[capacidade];
    }

    int obterTamanho() {
        return tamanho;
    }

    void adicionar(T elemento) {
        if (tamanho >= capacidade) {
            aumentarCapacidade();
        }
        dados[tamanho] = elemento;
        tamanho++;
    }

    T& operator[](int indice) {
        if (indice < 0 || indice >= tamanho) {
            std::cerr << "Erro: índice inválido";
        }
        return dados[indice];
    }

    void removerUltimo() {
        if (tamanho <= 0) {
            std::cerr << "Erro: remoção de sequência vazia";
        }
        tamanho--;
    }
};
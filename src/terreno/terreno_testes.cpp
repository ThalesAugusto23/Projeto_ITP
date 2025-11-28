#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "terreno.h"

TEST_CASE("Testa a criação de um terreno de uma única célula") {
  Terreno terreno(0); // 2^0 + 1 = 1
  CHECK(terreno.obterLargura() == 2);
  CHECK(terreno.obterProfundidade() == 2);
}

TEST_CASE("Testa a geração aleatória de altitudes") {
  Terreno terreno(2);
  CHECK(terreno.obterLargura() == 5);
  CHECK(terreno.obterProfundidade() == 5);
}


// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing".

// --- 1) Testar se o tamanho gerado está correto ---
TEST_CASE("Terreno gerado tem tamanho correto para n=3") {
    // n = 3 → matriz 9x9
    Terreno t(3);

    CHECK(t.obterLargura() == 9);
    CHECK(t.obterProfundidade() == 9);
}

//

TEST_CASE("Rugosidade zero remove ruído do algoritmo Diamond-Square") {

    Terreno t(3, 0.0f);

 // O valor central deve ser EXATAMENTE a média dos cantos

    int a = t.obterAltitude(0,0);
    int b = t.obterAltitude(0,8);
    int c = t.obterAltitude(8,0);
    int d = t.obterAltitude(8,8);

    int mediaEsperada = (a + b + c + d) / 4.0f;

    CHECK(t.obterAltitude(4,4) ==doctest::Approx(mediaEsperada));
}

TEST_CASE("Rugosidade zero: todas as médias Diamond devem ser exatas") {

    Terreno t(3, 0.0f); // 9x9

    int N = t.obterLargura();

    REQUIRE(N == 9);

    int tamanho = N - 1; // começa em 8

 // Para cada nível do algoritmo Diamond-Square

    while (tamanho > 1) {

        int meio = tamanho / 2;

        for (int x = 0; x < N - 1; x += tamanho) {

            for (int y = 0; y < N - 1; y += tamanho) {

                int a = t.obterAltitude(x, y);
                int b = t.obterAltitude(x, y + tamanho);
                int c = t.obterAltitude(x + tamanho, y);
                int d = t.obterAltitude(x + tamanho, y + tamanho);

                int media = (a + b + c + d) / 4.0f;

                CHECK(t.obterAltitude(x + meio, y + meio) ==doctest::Approx(media));

            }

        }

    tamanho /= 2;
 }
}

// --- 3) Testar salvar arquivo ---
TEST_CASE("Salvar terreno em arquivo") {
    Terreno t(2, 0.0f);  // matriz 5x5

    // Para garantir valores previsíveis
    float v = 7.0f;
    for (int i = 0; i < t.obterProfundidade(); i++)
        for (int j = 0; j < t.obterLargura(); j++)
            t.at(i, j) = v++;

    std::string nome = "saida_terreno.txt";
    t.salvarTerreno(nome);

    std::ifstream arq(nome);
    REQUIRE(arq.is_open());

    int l, c;
    arq >> l >> c;
    CHECK(l == 5);
    CHECK(c == 5);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            float valor;
            arq >> valor;

            // O valor esperado depende de como deveria ser salvo
            CHECK(valor == doctest::Approx(7.0f + i * 5 + j));
        }
}


// --- 4) Ler terreno de um arquivo 3x3 ---
TEST_CASE("Carregar terreno de arquivo") {
    std::ofstream out("entrada_3x3.txt");
    out << "3 3\n";
    out << "1 2 3\n";
    out << "4 5 6\n";
    out << "7 8 9\n";
    out.close();

    Terreno t(1); // tamanho qualquer, vai ser sobrescrito
    t.lerTerreno("entrada_3x3.txt");

    CHECK(t.obterAltitude(0, 0) == doctest::Approx(1));
    CHECK(t.obterAltitude(0, 1) == doctest::Approx(2));
    CHECK(t.obterAltitude(0, 2) == doctest::Approx(3));

    CHECK(t.obterAltitude(1, 0) == doctest::Approx(4));
    CHECK(t.obterAltitude(1, 1) == doctest::Approx(5));
    CHECK(t.obterAltitude(1, 2) == doctest::Approx(6));

    CHECK(t.obterAltitude(2, 0) == doctest::Approx(7));
    CHECK(t.obterAltitude(2, 1) == doctest::Approx(8));
    CHECK(t.obterAltitude(2, 2) == doctest::Approx(9));
}

TEST_CASE("") {
    Paleta p;
    p.adicionarCor({0, 0, 0});
    p.adicionarCor({255,0, 0});
    p.adicionarCor({255,255, 0});

    Terreno t(3);
    t.lerTerreno("entrada_3x3.txt");

    t.criarImagem(p);

}
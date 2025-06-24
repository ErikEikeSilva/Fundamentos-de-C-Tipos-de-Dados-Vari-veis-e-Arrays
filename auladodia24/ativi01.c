#include <stdio.h> // Biblioteca para entrada/saída (printf, scanf)

int main() {
    // Declaração de um array de inteiros chamado 'pontuacoes_clientes' com 5 elementos
    int pontuacoes_clientes[5];

    // Atribuindo valores aos elementos do array
    // O primeiro cliente (índice 0) tem 90 pontos
    pontuacoes_clientes[0] = 90;
    pontuacoes_clientes[1] = 75;
    pontuacoes_clientes[2] = 100;
    pontuacoes_clientes[3] = 80;
    pontuacoes_clientes[4] = 95;

    // Acessando e imprimindo os valores dos elementos
    printf("Pontuações dos Clientes:\n");
    printf("Cliente 1 (índice 0): %d\n", pontuacoes_clientes[0]);
    printf("Cliente 2 (índice 1): %d\n", pontuacoes_clientes[1]);
    printf("Cliente 3 (índice 2): %d\n", pontuacoes_clientes[2]);
    printf("Cliente 4 (índice 3): %d\n", pontuacoes_clientes[3]);
    printf("Cliente 5 (índice 4): %d\n", pontuacoes_clientes[4]);

    // Exemplo: Calcular a pontuação média
    int soma_pontuacoes = 0;
    soma_pontuacoes = pontuacoes_clientes[0] + pontuacoes_clientes[1] +
                      pontuacoes_clientes[2] + pontuacoes_clientes[3] +
                      pontuacoes_clientes[4];

    double media_pontuacoes = (double)soma_pontuacoes / 5;
    printf("\nMédia das pontuações: %.2f\n", media_pontuacoes);

    return 0;
}
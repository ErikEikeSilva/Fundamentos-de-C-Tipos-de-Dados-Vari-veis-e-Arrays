#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída

int main() {
    printf("--- Numeros de 10 a 20 ---\n");

    // O loop 'for' é ideal quando sabemos quantas vezes queremos repetir
    // 1. Inicializa 'i' com 10
    // 2. Continua enquanto 'i' for menor ou igual a 20
    // 3. Incrementa 'i' em 1 a cada iteração
    for (int i = 10; i <= 20; i++) {
        printf("%d ", i); // Imprime o valor de 'i' seguido de um espaço
    }

    printf("\n"); // Imprime uma nova linha no final para melhor formatação

    return 0; // Retorna 0 para indicar sucesso
}
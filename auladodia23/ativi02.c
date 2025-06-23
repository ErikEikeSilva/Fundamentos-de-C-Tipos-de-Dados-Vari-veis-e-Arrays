#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída

int main() {
    int numero; // Declara uma variável inteira para armazenar o número digitado

    printf("--- Leitura de Numeros Ate Negativo ---\n");
    printf("Digite numeros inteiros. Para parar, digite um numero negativo.\n");

    // O loop 'do-while' garante que o bloco de código seja executado pelo menos uma vez
    do {
        printf("Digite um numero: ");
        scanf("%d", &numero); // Lê o número digitado pelo usuário e armazena na variável 'numero'

        // Verifica se o número digitado não é negativo
        if (numero >= 0) {
            printf("Voce digitou: %d\n", numero); // Imprime o número digitado
        }

    } while (numero >= 0); // A condição para continuar o loop é que 'numero' seja maior ou igual a zero

    printf("Um numero negativo foi digitado. Programa encerrado.\n"); // Mensagem de encerramento

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
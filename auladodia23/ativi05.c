#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída

int main() {
    int numero; // Variável para armazenar o número que o usuário deseja a tabuada

    printf("--- Gerador de Tabuada ---\n");
    printf("Digite um numero inteiro de 1 a 10 para ver sua tabuada: ");
    scanf("%d", &numero); // Lê o número digitado pelo usuário

    // Verifica se o número está dentro do intervalo válido (1 a 10)
    if (numero >= 1 && numero <= 10) {
        printf("Tabuada de multiplicacao do %d:\n", numero);
        // O loop 'for' vai de 1 a 10 para gerar todas as multiplicações
        for (int i = 1; i <= 10; i++) {
            printf("%d x %d = %d\n", numero, i, numero * i); // Imprime a operação e o resultado
        }
    } else {
        printf("Numero invalido. Por favor, digite um numero entre 1 e 10.\n"); // Mensagem de erro para número fora do intervalo
    }

    return 0; // Retorna 0 para indicar sucesso
}
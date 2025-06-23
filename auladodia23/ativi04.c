#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída

int main() {
    float valorCompra;  // Variável para armazenar o valor de cada compra
    float somaTotal = 0.0; // Variável para acumular a soma das compras, inicializada em zero

    printf("--- Soma de Valores de Compras ---\n");
    printf("Digite os valores das compras (digite 0 para finalizar e ver o total).\n");

    // O loop 'do-while' garante que o usuário digite pelo menos um valor
    do {
        printf("Digite o valor da compra: ");
        scanf("%f", &valorCompra); // Lê o valor da compra

        // Verifica se o valor é válido (não negativo)
        if (valorCompra < 0) {
            printf("Valor invalido. Por favor, digite um valor nao negativo.\n");
        } else {
            somaTotal += valorCompra; // Adiciona o valor da compra à soma total
        }

    } while (valorCompra != 0); // Continua o loop enquanto o valor digitado não for zero

    printf("A soma total das compras e: R$ %.2f\n", somaTotal); // Exibe a soma total formatada com 2 casas decimais

    return 0; // Retorna 0 para indicar sucesso
}
#include <stdio.h>

int main() {
    float valor, valorFinal;
    int tipo;

    printf("Digite o valor da compra: "); // Já está em português
    scanf("%f", &valor);

    printf("Digite o tipo do produto (1 para tipo A, ou outro número para tipo B): "); // Pequena clarificação para o usuário
    scanf("%d", &tipo);

    if (tipo == 1)
        valorFinal = valor * 1.10; // Mais direto que valor + (valor * 0.10)
    else
        valorFinal = valor * 1.20; // Mais direto que valor + (valor * 0.20)

    printf("Valor total a ser pago: R$ %.2f\n", valorFinal); // Já está em português

    return 0;
}
#include <stdio.h>

#define PI 3.14159 // Uma precisão maior para PI é uma boa prática, mas 3.14 funciona.

int main() {
    int opcao;
    float area; // Declarar area aqui é bom, se fosse usada fora dos ifs

    printf("Escolha a figura (1 - Círculo, 2 - Retângulo): "); // Já está em português
    scanf("%d", &opcao);

    if (opcao == 1) {
        float raio;
        printf("Digite o raio do círculo: "); // Já está em português
        scanf("%f", &raio);
        area = PI * raio * raio;
        printf("Área do círculo: %.2f\n", area); // Já está em português
    } else if (opcao == 2) {
        float base, altura;
        printf("Digite a base e a altura do retângulo: "); // Já está em português
        scanf("%f %f", &base, &altura);
        area = base * altura;
        printf("Área do retângulo: %.2f\n", area); // Já está em português
    } else {
        printf("Opção inválida.\n"); // Já está em português
    }

    return 0;
}
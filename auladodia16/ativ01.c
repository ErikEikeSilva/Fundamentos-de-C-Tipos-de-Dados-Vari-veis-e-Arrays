#include<stdio.h> // Inclui a biblioteca padrão de entrada e saída, necessária para usar printf

// Declaração da função 'soma'
// Esta linha informa ao compilador que existe uma função chamada 'soma'
// que receberá dois números inteiros (int a, int b) e retornará um número inteiro (int).
int soma(int a, int b);

// Função principal do programa
// Todo programa em C começa a execução pela função 'main'.
int main() {
    // Declaração e inicialização de variáveis
    int x = 5; // Declara uma variável inteira 'x' e atribui o valor 5 a ela.
    int y = 3; // Declara uma variável inteira 'y' e atribui o valor 3 a ela.

    // Chamada da função 'soma'
    // A função 'soma' é chamada com os valores de 'x' e 'y'.
    // O valor retornado pela função 'soma' (que é a soma de x e y)
    // é armazenado na variável 'resultado'.
    int resultado = soma(x, y);

    // Imprime o resultado na tela
    // 'printf' é uma função da biblioteca <stdio.h> usada para exibir texto e valores.
    // %d são "placeholders" que serão substituídos pelos valores das variáveis x, y e resultado.
    printf("A soma de %d e %d é: %d\n", x, y, resultado);

    return 0; // Indica que o programa foi executado com sucesso.
              // O valor 0 é um código de sucesso padrão.
}

// Definição da função 'soma'
// Esta é a implementação real da função 'soma' que foi declarada acima.
// Ela recebe dois parâmetros inteiros, 'a' e 'b'.
int soma(int a, int b) {
    // Retorna a soma dos valores de 'a' e 'b'.
    return a + b;
}
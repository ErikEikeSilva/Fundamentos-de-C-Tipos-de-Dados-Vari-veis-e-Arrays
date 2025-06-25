#include <stdio.h>

int main() {
    int matriz[3][3];
    int maior;

    printf("Digite os elementos da matriz 3x3:\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    maior = matriz[0][0];
    printf("Matriz:\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d\t", matriz[i][j]);
            if(matriz[i][j] > maior) {
                maior = matriz[i][j];
            }
        }
        printf("\n");
    }

    printf("Maior elemento: %d\n", maior);

    return 0;
}

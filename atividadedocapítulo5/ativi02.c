#include <stdio.h>

int main() {
    int vetor[5] = {10, 20, 30, 40, 50};

    for(int i = 0; i < 5; i++) {
        if(i % 2 == 0) {
            vetor[i] *= 2;
        }
    }

    printf("Vetor com índices pares multiplicados por 2:\n");
    for(int i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}

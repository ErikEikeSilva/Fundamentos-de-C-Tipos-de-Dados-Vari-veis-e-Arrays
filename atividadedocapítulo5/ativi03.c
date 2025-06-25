#include <stdio.h>

int main() {
    int vetor1[5] = {1, 2, 3, 4, 5};
    int vetor2[5] = {5, 4, 3, 2, 1};
    int soma[5];

    for(int i = 0; i < 5; i++) {
        soma[i] = vetor1[i] + vetor2[i];
    }

    printf("Vetor resultante da soma:\n");
    for(int i = 0; i < 5; i++) {
        printf("%d ", soma[i]);
    }

    return 0;
}

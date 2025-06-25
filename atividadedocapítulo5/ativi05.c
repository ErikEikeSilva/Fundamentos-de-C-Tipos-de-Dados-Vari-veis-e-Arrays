#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int usuario[6], sorteados[6];
    int acertos = 0;

    printf("Digite 6 números entre 1 e 60:\n");
    for(int i = 0; i < 6; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &usuario[i]);
    }

    srand(time(NULL));
    printf("Números sorteados: ");
    for(int i = 0; i < 6; i++) {
        sorteados[i] = rand() % 60 + 1;
        printf("%d ", sorteados[i]);
    }
    printf("\n");

    // Verifica acertos
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(usuario[i] == sorteados[j]) {
                acertos++;
                break;
            }
        }
    }

    printf("Você acertou %d número(s).\n", acertos);

    return 0;
}

#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cargo[50];
    char area[50];
    char frequencia[30];
    char metodo[30];
    char criterio1[30];
    char criterio2[30];
    char criterio3[30];
    float nota1, nota2, nota3;
    float media;
} Avaliacao;

float calcularMedia(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3;
}

void classificarDesempenho(float media) {
    printf("Média Final: %.2f\n", media);
    if (media >= 9) {
        printf("Desempenho: Excelente - Elegível para Reconhecimento e Promoção\n");
    } else if (media >= 7) {
        printf("Desempenho: Bom - Feedback Positivo e Possível Treinamento\n");
    } else {
        printf("Desempenho: Regular - Necessita Melhorias e Acompanhamento\n");
    }
} 
int main() {
    Avaliacao a;

    printf("=== Sistema de Avaliação de Desempenho ===\n");

    // Dados do funcionário
    printf("Nome do funcionário: ");
    scanf(" %[^\n]", a.nome);
    printf("Cargo: ");
    scanf(" %[^\n]", a.cargo);
    printf("Área de atuação: ");
    scanf(" %[^\n]", a.area);

    // Frequência da avaliação
    strcpy(a.frequencia, "Trimestral");

    // Método de avaliação
    strcpy(a.metodo, "Avaliação 360 graus");
//função c - tipos de Retorno e portu







// Funções em C - Tipos de Retorno e Parâmetros

#include <stdio.h>

// Função sem parâmetros e sem retorno
void saudacao() {
    printf("Olá! Bem-vindo à nossa aplicação.\n");
}

// Função com parâmetros e sem retorno
void exibirMensagem(char mensagem[]) {
    printf("Mensagem Recebida: %s\n", mensagem);
}

// Função com parâmetros e com retorno
int soma(int a, int b) {
    return a + b;
}

int main() {
    saudacao();

    exibirMensagem("Isso é um exemplo");

    return 0;
}
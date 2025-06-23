#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída

int main() {
    int idade;          // Idade do morador
    char sexo;          // Sexo do morador ('m' ou 'f')
    float salario;      // Salário do morador

    // Variáveis para armazenar os resultados da pesquisa
    int maiorIdade = 0; // Inicializa com 0, pois a idade sempre será maior ou igual a 0
    float somaSalarios = 0.0; // Acumulador da soma dos salários
    int contadorMoradores = 0; // Contador de quantos moradores foram registrados
    int quantidadeMulheres = 0; // Contador de mulheres
    // Usamos um int como booleano: 0 para falso, 1 para verdadeiro.
    // Inicializamos como falso (0)
    int existeSalarioAbaixo500 = 0;

    printf("--- Pesquisa de Moradores do Bairro ---\n");
    printf("Preencha as informacoes de cada morador.\n");
    printf("Para finalizar a pesquisa, digite 0 para a idade.\n");

    // O loop 'do-while' permite coletar dados de múltiplos moradores
    do {
        printf("\n--- Morador #%d ---\n", contadorMoradores + 1); // Indica o número do morador atual
        printf("Idade (0 para finalizar): ");
        scanf("%d", &idade); // Lê a idade

        if (idade == 0) {
            break; // Se a idade for 0, sai do loop imediatamente (finaliza a pesquisa)
        }

        if (idade < 0) {
            printf("ERRO: Idade invalida. Por favor, digite uma idade nao negativa.\n");
            // 'continue' faz o loop pular para a próxima iteração, ignorando o restante do código abaixo
            continue;
        }

        // Limpa o buffer de entrada para evitar problemas com 'scanf %c'
        // Isso é crucial depois de um scanf de número/float e antes de um scanf de caractere
        while (getchar() != '\n'); 

        printf("Sexo (m/f): ");
        scanf("%c", &sexo); // Lê o sexo
        // Loop de validação para o sexo
        while (sexo != 'm' && sexo != 'f' && sexo != 'M' && sexo != 'F') {
            printf("ERRO: Sexo invalido. Digite 'm' ou 'f': ");
            while (getchar() != '\n'); // Limpa o buffer novamente
            scanf("%c", &sexo);
        }

        printf("Salario: R$ ");
        scanf("%f", &salario); // Lê o salário

        if (salario < 0) {
            printf("ERRO: Salario invalido. Por favor, digite um salario nao negativo.\n");
            continue; // Pula para a próxima iteração se o salário for inválido
        }

        // Processamento dos dados coletados
        contadorMoradores++; // Incrementa o contador de moradores

        if (idade > maiorIdade) {
            maiorIdade = idade; // Atualiza a maior idade se a idade atual for maior
        }

        somaSalarios += salario; // Adiciona o salário à soma total

        // Converte para minúsculo para facilitar a comparação
        if (sexo == 'f' || sexo == 'F') {
            quantidadeMulheres++; // Incrementa o contador de mulheres
        }

        if (salario < 500.0) {
            existeSalarioAbaixo500 = 1; // Marca como verdadeiro se encontrar um salário abaixo de 500
        }

    } while (1); // Loop infinito que só é quebrado pela condição 'if (idade == 0) break;'

    // Exibição dos resultados finais
    printf("\n--- Resultados da Pesquisa ---\n");
    if (contadorMoradores == 0) {
        printf("Nenhum morador foi registrado na pesquisa.\n");
    } else {
        printf("a. A maior idade registrada: %d anos\n", maiorIdade);
        printf("b. A media salarial: R$ %.2f\n", somaSalarios / contadorMoradores);
        printf("c. A quantidade de mulheres: %d\n", quantidadeMulheres);
        if (existeSalarioAbaixo500) {
            printf("d. Existe salario abaixo de R$ 500: Sim\n");
        } else {
            printf("d. Existe salario abaixo de R$ 500: Nao\n");
        }
    }

    return 0; // Retorna 0 para indicar sucesso
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para isdigit

#define MAX_ITENS_PEDIDO 5 // Capacidade máxima de itens diferentes no pedido

// Estrutura para um item no pedido
typedef struct {
    char nome[50];
    double preco;
    int quantidade;
} ItemPedido;

// --- Funções de Utilidade e Validação ---

// Limpa o buffer de entrada para evitar problemas com fgets/scanf
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lê um inteiro com validação de entrada
int lerInteiroValido(const char *mensagem) {
    int valor;
    char buffer[100];
    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Tenta converter para int e verifica se a leitura foi bem-sucedida e o valor é não-negativo
            if (sscanf(buffer, "%d", &valor) == 1 && valor >= 0) {
                return valor;
            }
        }
        printf("Entrada inválida. Por favor, digite um número inteiro não negativo.\n");
    }
}

// Lê um double com validação de entrada
double lerDoubleValido(const char *mensagem) {
    double valor;
    char buffer[100];
    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Tenta converter para double e verifica se a leitura foi bem-sucedida e o valor é não-negativo
            if (sscanf(buffer, "%lf", &valor) == 1 && valor >= 0) {
                return valor;
            }
        }
        printf("Entrada inválida. Por favor, digite um número válido não negativo.\n");
    }
}

// --- Funções de Pedido ---

// Exibe o menu principal de opções
void exibirMenuPrincipal() {
    printf("\n--- MENU DE PEDIDOS ---\n");
    printf("1. Pedir Lanche Simples\n");
    printf("2. Pedir Trio Promocional (Lanche+Batata+Refrigerante)\n");
    printf("3. Ver Detalhes do Pedido e Finalizar\n");
    printf("4. Sair\n");
    printf("------------------------\n");
}

// Adiciona um item ao array de pedido
void adicionarItem(ItemPedido pedido[], int *numItens, const char *nome, double preco, int quantidade) {
    if (quantidade <= 0) {
        printf("Quantidade inválida para adicionar o item.\n");
        return;
    }

    // Procura se o item já existe para apenas atualizar a quantidade
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(pedido[i].nome, nome) == 0) {
            pedido[i].quantidade += quantidade;
            printf("Quantidade de '%s' atualizada para %d.\n", nome, pedido[i].quantidade);
            return;
        }
    }

    // Se não existe, adiciona como novo item, se houver espaço
    if (*numItens < MAX_ITENS_PEDIDO) {
        strcpy(pedido[*numItens].nome, nome);
        pedido[*numItens].preco = preco;
        pedido[*numItens].quantidade = quantidade;
        (*numItens)++;
        printf("'%s' adicionado ao pedido.\n", nome);
    } else {
        printf("Limite máximo de itens diferentes no pedido atingido (%d itens).\n", MAX_ITENS_PEDIDO);
    }
}

// Exibe os detalhes do pedido e calcula o total
void exibirEFinalizarPedido(ItemPedido pedido[], int numItens, double impostoPercentual, double taxaServicoPercentual) {
    if (numItens == 0) {
        printf("\nSeu pedido está vazio. Adicione itens antes de finalizar.\n");
        return;
    }

    printf("\n--- DETALHES DO PEDIDO ---\n");
    double subtotal = 0.0;
    for (int i = 0; i < numItens; i++) {
        double valorItem = pedido[i].preco * pedido[i].quantidade;
        printf("%d. %s (R$ %.2f) x %d = R$ %.2f\n", i + 1, pedido[i].nome, pedido[i].preco, pedido[i].quantidade, valorItem);
        subtotal += valorItem;
    }
    printf("--------------------------\n");
    printf("Subtotal: R$ %.2f\n", subtotal);

    // Cálculo do Imposto
    double valorImposto = subtotal * (impostoPercentual / 100.0);
    printf("Imposto (%.2f%%): R$ %.2f\n", impostoPercentual, valorImposto);
    double totalComImposto = subtotal + valorImposto;

    // Cálculo da Taxa de Serviço
    double valorTaxaServico = totalComImposto * (taxaServicoPercentual / 100.0);
    printf("Taxa de Serviço (%.2f%%): R$ %.2f\n", taxaServicoPercentual, valorTaxaServico);
    double totalProvisorio = totalComImposto + valorTaxaServico;

    printf("Total Provisório: R$ %.2f\n", totalProvisorio);

    // --- Aplicação de Desconto Simples ---
    int aplicarDesc = lerInteiroValido("Deseja aplicar um desconto de 10%% para Estudante? (1-Sim, 0-Não): ");
    double valorDesconto = 0.0;
    if (aplicarDesc == 1) {
        valorDesconto = totalProvisorio * 0.10; // 10% de desconto
        printf("Desconto de Estudante (10%%) aplicado: -R$ %.2f\n", valorDesconto);
    } else {
        printf("Nenhum desconto aplicado.\n");
    }

    double totalFinal = totalProvisorio - valorDesconto;

    printf("--------------------------\n");
    printf("TOTAL A PAGAR: R$ %.2f\n", totalFinal);
    printf("Obrigado pelo seu pedido!\n");
}

// --- Função Principal ---

int main() {
    ItemPedido pedidoCliente[MAX_ITENS_PEDIDO]; // Array estático para o pedido
    int numItensAtuais = 0;
    int opcao;

    // Valores fixos de imposto e taxa para simplificar, ou pode pedir ao usuário no início
    double impostoFixo = 8.0;   // 8% de imposto
    double taxaServicoFixo = 10.0; // 10% de taxa de serviço

    printf("Bem-vindo ao Sistema de Pedidos Simplificado!\n");

    do {
        exibirMenuPrincipal();
        opcao = lerInteiroValido("Escolha uma opção: ");

        switch (opcao) {
            case 1: { // Pedir Lanche Simples
                int quantidade;
                printf("\n--- Lanche Simples ---\n");
                printf("Opções:\n");
                printf("1. Hambúrguer (R$ 20.00)\n");
                printf("2. Cheeseburger (R$ 22.00)\n");
                int escolhaLanche = lerInteiroValido("Escolha o lanche: ");
                quantidade = lerInteiroValido("Quantidade: ");

                if (escolhaLanche == 1) {
                    adicionarItem(pedidoCliente, &numItensAtuais, "Hambúrguer", 20.00, quantidade);
                } else if (escolhaLanche == 2) {
                    adicionarItem(pedidoCliente, &numItensAtuais, "Cheeseburger", 22.00, quantidade);
                } else {
                    printf("Opção de lanche inválida.\n");
                }
                break;
            }
            case 2: { // Pedir Trio Promocional
                int quantidade;
                printf("\n--- Trio Promocional ---\n");
                printf("Um trio inclui: Hambúrguer Clássico + Batata Média + Refrigerante\n");
                printf("Preço do Trio: R$ 35.00\n");
                quantidade = lerInteiroValido("Quantidade de Trios: ");
                
                // Adiciona o trio como um único item para simplificar o controle
                adicionarItem(pedidoCliente, &numItensAtuais, "Trio Promocional", 35.00, quantidade);
                break;
            }
            case 3: // Ver Detalhes e Finalizar
                exibirEFinalizarPedido(pedidoCliente, numItensAtuais, impostoFixo, taxaServicoFixo);
                opcao = 4; // Sai do loop após finalizar
                break;
            case 4: // Sair
                printf("Saindo do sistema. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}
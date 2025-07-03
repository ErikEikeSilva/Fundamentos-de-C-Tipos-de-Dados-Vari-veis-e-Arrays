#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição de constantes
#define MAX_CLIENTES 100
#define ARQUIVO_CLIENTES "clientes_cnh.txt"
#define LOGIN_AD "admin"
#define SENHA_AD 1234

// Estrutura para um cliente
typedef struct {
    char nome[100];
    char cpf[15];
    int idade;
    char tipo_servico[30];
    char categoria[5];
    char status[30];
} Cliente;

// Array global de clientes e contador
Cliente clientes[MAX_CLIENTES];
int total_clientes = 0;

// --- PROTÓTIPOS DE FUNÇÕES ---
void limparTela();
void limparBufferEntrada();
int validarCPF(const char *cpf);
void salvarDados();
void carregarDados();
void cadastrarCliente();
void listarClientes();
void buscarPorCPF();
void atualizarStatus();
void exibirMenuPrincipal();

// --- DEFINIÇÕES DAS FUNÇÕES ---

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) {
        printf("CPF deve ter 11 digitos.\n");
        return 0;
    }
    
    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') {
            printf("CPF deve conter apenas numeros.\n");
            return 0;
        }
    }
    return 1;
}

void salvarDados() {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    for (int i = 0; i < total_clientes; i++) {
        fprintf(arquivo, "%s|%s|%d|%s|%s|%s\n",
                clientes[i].nome,
                clientes[i].cpf,
                clientes[i].idade,
                clientes[i].tipo_servico,
                clientes[i].categoria,
                clientes[i].status);
    }

    fclose(arquivo);
}

void carregarDados() {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "r");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com lista vazia.\n");
        return;
    }

    total_clientes = 0;
    while (fscanf(arquivo, " %99[^|]|%14[^|]|%d|%29[^|]|%4[^|]|%29[^\n]\n",
                 clientes[total_clientes].nome,
                 clientes[total_clientes].cpf,
                 &clientes[total_clientes].idade,
                 clientes[total_clientes].tipo_servico,
                 clientes[total_clientes].categoria,
                 clientes[total_clientes].status) == 6) {
        total_clientes++;
        if (total_clientes >= MAX_CLIENTES) break;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso. Total de clientes: %d\n", total_clientes);
}

void cadastrarCliente() {
    if (total_clientes >= MAX_CLIENTES) {
        printf("Limite maximo de clientes atingido (%d).\n", MAX_CLIENTES);
        printf("Pressione ENTER para continuar...");
        limparBufferEntrada();
        return;
    }

    Cliente novo;
    
    printf("\n--- CADASTRO DE CLIENTE ---\n");
    
    // Nome
    printf("Nome completo: ");
    limparBufferEntrada();
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    // CPF
    do {
        printf("CPF (apenas numeros, 11 digitos): ");
        scanf("%14s", novo.cpf);
    } while (!validarCPF(novo.cpf));

    // Idade
    printf("Idade: ");
    while (scanf("%d", &novo.idade) != 1 || novo.idade < 18) {
        printf("Idade invalida. Deve ser maior ou igual a 18 anos: ");
        limparBufferEntrada();
    }

    // Tipo de serviço
    int opcao_servico;
    printf("\nTipo de servico:\n");
    printf("1 - Primeira habilitacao\n");
    printf("2 - Renovacao\n");
    printf("3 - Mudanca de categoria\n");
    printf("Escolha: ");
    
    while (scanf("%d", &opcao_servico) != 1 || opcao_servico < 1 || opcao_servico > 3) {
        printf("Opcao invalida. Escolha 1, 2 ou 3: ");
        limparBufferEntrada();
    }
    
    switch(opcao_servico) {
        case 1: strcpy(novo.tipo_servico, "Primeira habilitacao"); break;
        case 2: strcpy(novo.tipo_servico, "Renovacao"); break;
        case 3: strcpy(novo.tipo_servico, "Mudanca de categoria"); break;
    }

    // Categoria
    printf("\nCategorias disponiveis:\n");
    printf("A - Motocicletas\n");
    printf("B - Carros\n");
    printf("AB - Carros e Motocicletas\n");
    printf("C - Veiculos pesados\n");
    printf("D - Onibus\n");
    printf("E - Carretas\n");
    printf("Digite a categoria desejada: ");
    
    scanf("%4s", novo.categoria);
    limparBufferEntrada();
    
    // Status inicial
    strcpy(novo.status, "Cadastro inicial");

    // Adiciona ao array
    clientes[total_clientes++] = novo;
    salvarDados();
    
    printf("\nCliente cadastrado com sucesso!\n");
    printf("Pressione ENTER para continuar...");
    limparBufferEntrada();
}

void listarClientes() {
    limparTela();
    printf("\n============================================================================================================\n");
    printf("|                                         RELATORIO DE ATENDIMENTOS                                          |\n");
    printf("=============================================================================================================\n");
    
    if (total_clientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        printf("=============================================================================================\n");
        printf("Pressione ENTER para continuar...");
        limparBufferEntrada();
        return;
    }

    printf("| %-30s | %-11s | %-5s | %-20s | %-4s | %-20s |\n", 
           "Nome", "CPF", "Idade", "Servico", "Cat.", "Status");
    printf("------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < total_clientes; i++) {
        printf("| %-30s | %s | %-5d | %-20s | %-4s | %-20s |\n",
               clientes[i].nome,
               clientes[i].cpf,
               clientes[i].idade,
               clientes[i].tipo_servico,
               clientes[i].categoria,
               clientes[i].status);
    }
    
    printf("=============================================================================================================\n");
    printf("\nTotal de clientes: %d\n", total_clientes);
    printf("Pressione ENTER para continuar...");
    limparBufferEntrada();
}

void buscarPorCPF() {
    char cpf_busca[15];
    int encontrado = 0;
    
    printf("\nDigite o CPF para buscar (apenas numeros): ");
    scanf("%14s", cpf_busca);
    limparBufferEntrada();
    
    if (!validarCPF(cpf_busca)) {
        printf("CPF invalido.\n");
        printf("Pressione ENTER para continuar...");
        limparBufferEntrada();
        return;
    }
    
    limparTela();
    printf("\n=== RESULTADO DA BUSCA ===\n");
    
    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_busca) == 0) {
            printf("\nNome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Idade: %d\n", clientes[i].idade);
            printf("Tipo de servico: %s\n", clientes[i].tipo_servico);
            printf("Categoria: %s\n", clientes[i].categoria);
            printf("Status atual: %s\n", clientes[i].status);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nCliente com CPF %s nao encontrado.\n", cpf_busca);
    }
    
    printf("\nPressione ENTER para continuar...");
    limparBufferEntrada();
}

void atualizarStatus() {
    char cpf_busca[15];
    int encontrado = 0;
    
    printf("\nDigite o CPF do cliente para atualizar status: ");
    scanf("%14s", cpf_busca);
    limparBufferEntrada();
    
    if (!validarCPF(cpf_busca)) {
        printf("CPF invalido.\n");
        printf("Pressione ENTER para continuar...");
        limparBufferEntrada();
        return;
    }
    
    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_busca) == 0) {
            printf("\nCliente encontrado:\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("Status atual: %s\n", clientes[i].status);
            
            printf("\nNovo status: ");
            char novo_status[30];
            fgets(novo_status, sizeof(novo_status), stdin);
            novo_status[strcspn(novo_status, "\n")] = '\0';
            
            strcpy(clientes[i].status, novo_status);
            salvarDados();
            
            printf("\nStatus atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nCliente com CPF %s nao encontrado.\n", cpf_busca);
    }
    
    printf("Pressione ENTER para continuar...");
    limparBufferEntrada();
}

void exibirMenuPrincipal() {
    int opcao;
    
    do {
        printf("\n=====================================================================\n");
        printf("|          SISTEMA DE GERENCIAMENTO - CLINICA HABILITAR             |\n");
        printf("=====================================================================\n");
        printf("| 1 - Abertura de processo - Renach                                 |\n");
        printf("| 2 - Relatorio de atendimentos                                     |\n");
        printf("| 3 - Consultar processo                                            |\n");
        printf("| 4 - Atualizar status do processo                                  |\n");
        printf("| 0 - Sair do sistema                                               |\n");
        printf("=====================================================================\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }
        
        switch(opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                buscarPorCPF();
                break;
            case 4:
                atualizarStatus();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                limparBufferEntrada();
        }
    } while (opcao != 0);
}

int main() {
    // Tela de login
    char login[20];
    int senha;
    
    printf("\n===================================================================\n");
    printf("|              SISTEMA DE GERENCIAMENTO - CLINICA HABILITAR         |\n");
    printf("=====================================================================\n");
    printf("\nLogin de acesso: ");
    scanf("%19s", login);
    
    printf("Senha: ");
    scanf("%d", &senha);
    limparBufferEntrada();
    
    // Verificação de credenciais
    if (strcmp(login, LOGIN_AD) == 0 && senha == SENHA_AD) {
        printf("\nACESSO PERMITIDO!\n");
        printf("Pressione ENTER para continuar...");
        limparBufferEntrada();
        
        // Carrega os dados e exibe o menu
        carregarDados();
        exibirMenuPrincipal();
        
        printf("\n===================================================================\n");
        printf("|               SESSAO ENCERRADA COM SUCESSO!                     |\n");
        printf("===================================================================\n");
    } else {
        printf("\nACESSO NEGADO - Credenciais invalidas.\n");
    }
    
    return 0;
}
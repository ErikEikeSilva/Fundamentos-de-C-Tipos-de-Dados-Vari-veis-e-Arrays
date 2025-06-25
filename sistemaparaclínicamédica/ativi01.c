#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Definições de constantes
#define MAX_CLIENTES 500
#define MAX_INSTRUTORES 50
#define ARQUIVO_CLIENTES "clientes_cnh.dat"
#define ARQUIVO_INSTRUTORES "instrutores.dat"
#define LOGIN_ADMIN "admin"
#define SENHA_ADMIN 1234
#define LOGIN_INSTRUTOR "instrutor"
#define SENHA_INSTRUTOR 5678

// Estruturas de dados
typedef struct {
    char nome[100];
    char cpf[15];
    char rg[15];
    char endereco[100];
    char telefone[15];
    char email[50];
    int idade;
    char tipo_servico[30]; // Primeira habilitação, Renovação, Mudança de categoria
    char categoria[5];     // A, B, AB, C, D, E
    char status[50];
    int aulas_teoricas_completas;
    int aulas_praticas_completas;
    char data_exame_teorico[11];
    char data_exame_pratico[11];
    char medico_responsavel[50];
    char instrutor[50];
    float valor_total;
    float valor_pago;
    char data_matricula[11];
    char data_vencimento[11];
    int reprovacoes_teorico;
    int reprovacoes_pratico;
} Cliente;

typedef struct {
    char nome[100];
    char cpf[15];
    char registro[20];
    char categorias[20]; // Categorias que pode ministrar (ex: "ABDE")
    int ativo;
} Instrutor;

// Variáveis globais
Cliente clientes[MAX_CLIENTES];
Instrutor instrutores[MAX_INSTRUTORES];
int total_clientes = 0;
int total_instrutores = 0;
int usuario_logado = 0; // 0 = não logado, 1 = admin, 2 = instrutor

// Protótipos de funções
void limparTela();
void limparBufferEntrada();
int validarCPF(const char *cpf);
int validarData(const char *data);
int validarEmail(const char *email);
int validarTelefone(const char *telefone);
void salvarDados();
void carregarDados();
void salvarInstrutores();
void carregarInstrutores();
void cadastrarCliente();
void editarCliente();
void listarClientes();
void buscarCliente();
void registrarAula();
void agendarExame();
void registrarPagamento();
void cadastrarInstrutor();
void listarInstrutores();
void gerarRelatorios();
void menuAdmin();
void menuInstrutor();
void login();
void configurarSistema();

// Implementação das funções

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
        return 0;
    }
    
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    
    // Validar dígitos verificadores (opcional)
    return 1;
}

int validarData(const char *data) {
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;
    
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    
    if (dia < 1 || dia > 31) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (ano < 1900 || ano > 2100) return 0;
    
    return 1;
}

int validarEmail(const char *email) {
    int tem_arroba = 0, tem_ponto = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') tem_arroba = 1;
        if (email[i] == '.' && tem_arroba) tem_ponto = 1;
    }
    return tem_arroba && tem_ponto;
}

int validarTelefone(const char *telefone) {
    if (strlen(telefone) < 10 || strlen(telefone) > 11) return 0;
    
    for (int i = 0; telefone[i] != '\0'; i++) {
        if (!isdigit(telefone[i])) return 0;
    }
    
    return 1;
}

void salvarDados() {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de clientes para escrita.\n");
        return;
    }
    
    fwrite(&total_clientes, sizeof(int), 1, arquivo);
    fwrite(clientes, sizeof(Cliente), total_clientes, arquivo);
    
    fclose(arquivo);
}

void carregarDados() {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "rb");
    if (arquivo == NULL) {
        printf("Arquivo de clientes não encontrado. Iniciando com lista vazia.\n");
        return;
    }
    
    fread(&total_clientes, sizeof(int), 1, arquivo);
    fread(clientes, sizeof(Cliente), total_clientes, arquivo);
    
    fclose(arquivo);
    printf("Dados de clientes carregados. Total: %d\n", total_clientes);
}

void salvarInstrutores() {
    FILE *arquivo = fopen(ARQUIVO_INSTRUTORES, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de instrutores para escrita.\n");
        return;
    }
    
    fwrite(&total_instrutores, sizeof(int), 1, arquivo);
    fwrite(instrutores, sizeof(Instrutor), total_instrutores, arquivo);
    
    fclose(arquivo);
}

void carregarInstrutores() {
    FILE *arquivo = fopen(ARQUIVO_INSTRUTORES, "rb");
    if (arquivo == NULL) {
        printf("Arquivo de instrutores não encontrado. Iniciando com lista vazia.\n");
        return;
    }
    
    fread(&total_instrutores, sizeof(int), 1, arquivo);
    fread(instrutores, sizeof(Instrutor), total_instrutores, arquivo);
    
    fclose(arquivo);
    printf("Dados de instrutores carregados. Total: %d\n", total_instrutores);
}

void cadastrarCliente() {
    if (total_clientes >= MAX_CLIENTES) {
        printf("Limite máximo de clientes atingido.\n");
        return;
    }
    
    Cliente novo;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    printf("\n--- CADASTRO DE NOVO ALUNO ---\n");
    
    // Dados pessoais
    printf("Nome completo: ");
    limparBufferEntrada();
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    
    do {
        printf("CPF (apenas números): ");
        scanf("%14s", novo.cpf);
    } while (!validarCPF(novo.cpf));
    
    printf("RG: ");
    scanf("%14s", novo.rg);
    
    printf("Idade: ");
    scanf("%d", &novo.idade);
    
    limparBufferEntrada();
    printf("Endereço: ");
    fgets(novo.endereco, sizeof(novo.endereco), stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = '\0';
    
    do {
        printf("Telefone: ");
        scanf("%14s", novo.telefone);
    } while (!validarTelefone(novo.telefone));
    
    do {
        printf("E-mail: ");
        scanf("%49s", novo.email);
    } while (!validarEmail(novo.email));
    
    // Tipo de serviço
    int opcao;
    printf("\nTipo de serviço:\n");
    printf("1 - Primeira habilitação\n");
    printf("2 - Renovação\n");
    printf("3 - Mudança de categoria\n");
    printf("4 - Adição de categoria\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    
    switch(opcao) {
        case 1: strcpy(novo.tipo_servico, "Primeira habilitação"); break;
        case 2: strcpy(novo.tipo_servico, "Renovação"); break;
        case 3: strcpy(novo.tipo_servico, "Mudança de categoria"); break;
        case 4: strcpy(novo.tipo_servico, "Adição de categoria"); break;
        default: strcpy(novo.tipo_servico, "Primeira habilitação");
    }
    
    // Categoria
    printf("\nCategorias disponíveis:\n");
    printf("A - Motocicletas\n");
    printf("B - Carros de passeio\n");
    printf("AB - Carros e Motocicletas\n");
    printf("C - Veículos pesados\n");
    printf("D - Ônibus\n");
    printf("E - Carretas\n");
    
    do {
        printf("Digite a categoria desejada: ");
        scanf("%4s", novo.categoria);
    } while (strcmp(novo.categoria, "A") != 0 &&
             strcmp(novo.categoria, "B") != 0 &&
             strcmp(novo.categoria, "AB") != 0 &&
             strcmp(novo.categoria, "C") != 0 &&
             strcmp(novo.categoria, "D") != 0 &&
             strcmp(novo.categoria, "E") != 0);
    
    // Instrutor
    if (total_instrutores > 0) {
        printf("\nInstrutores disponíveis:\n");
        for (int i = 0; i < total_instrutores; i++) {
            if (instrutores[i].ativo) {
                printf("%d - %s (%s)\n", i+1, instrutores[i].nome, instrutores[i].categorias);
            }
        }
        printf("Escolha o instrutor (0 para nenhum): ");
        int instrutor_escolhido;
        scanf("%d", &instrutor_escolhido);
        
        if (instrutor_escolhido > 0 && instrutor_escolhido <= total_instrutores) {
            strcpy(novo.instrutor, instrutores[instrutor_escolhido-1].nome);
        } else {
            strcpy(novo.instrutor, "Não atribuído");
        }
    } else {
        strcpy(novo.instrutor, "Não atribuído");
    }
    
    // Valores
    if (strcmp(novo.tipo_servico, "Primeira habilitação") == 0) {
        novo.valor_total = 1500.00;
    } else {
        novo.valor_total = 800.00;
    }
    novo.valor_pago = 0.00;
    
    // Datas
    sprintf(novo.data_matricula, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    sprintf(novo.data_vencimento, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1901);
    
    // Status inicial
    strcpy(novo.status, "Matriculado");
    novo.aulas_teoricas_completas = 0;
    novo.aulas_praticas_completas = 0;
    strcpy(novo.data_exame_teorico, "00/00/0000");
    strcpy(novo.data_exame_pratico, "00/00/0000");
    strcpy(novo.medico_responsavel, "A definir");
    novo.reprovacoes_teorico = 0;
    novo.reprovacoes_pratico = 0;
    
    // Adiciona ao array
    clientes[total_clientes++] = novo;
    salvarDados();
    
    printf("\nAluno cadastrado com sucesso!\n");
    printf("Valor total: R$ %.2f\n", novo.valor_total);
    printf("Pressione ENTER para continuar...");
    limparBufferEntrada();
}

// [Continuação com as outras funções...]

void login() {
    limparTela();
    char login[50];
    int senha;
    
    printf("\n===================================================================\n");
    printf("|                  SISTEMA DE GERENCIAMENTO - AUTOESCOLA           |\n");
    printf("===================================================================\n");
    printf("\nLogin: ");
    scanf("%49s", login);
    printf("Senha: ");
    scanf("%d", &senha);
    limparBufferEntrada();
    
    if (strcmp(login, LOGIN_ADMIN) == 0 && senha == SENHA_ADMIN) {
        usuario_logado = 1;
        printf("\nBem-vindo, Administrador!\n");
        menuAdmin();
    } else if (strcmp(login, LOGIN_INSTRUTOR) == 0 && senha == SENHA_INSTRUTOR) {
        usuario_logado = 2;
        printf("\nBem-vindo, Instrutor!\n");
        menuInstrutor();
    } else {
        printf("\nACESSO NEGADO. Credenciais inválidas.\n");
    }
}

int main() {
    carregarDados();
    carregarInstrutores();
    login();
    return 0;
}
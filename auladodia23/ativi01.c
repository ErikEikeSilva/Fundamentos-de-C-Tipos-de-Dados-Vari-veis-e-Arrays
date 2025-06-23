#include <stdio.h> // For input/output functions like printf and scanf
#include <stdlib.h> // For functions like system("cls") or system("clear") for clearing screen (optional)
#include <string.h> // For string manipulation, like strcpy (if needed for product names)

int main() {
    // Variable declarations
    // You'll need variables for:
    // - Number of different products sold in a day
    // - Product name (char array or pointer)
    // - Quantity sold (int)
    // - Unit price (float or double)
    // - Total for each product (float or double)
    // - Daily total (float or double)
    // - A character to control the multi-day loop (e.g., 's' or 'n')

    char continue_sales = 's'; // Initialize to 's' to start the loop

    // --- Outer loop for multiple days ---
    while (continue_sales == 's' || continue_sales == 'S') {
        // Clear screen (optional, depends on OS)
        // #ifdef _WIN32
        //     system("cls");
        // #else
        //     system("clear");
        // #endif

        printf("--- Controle de Vendas Diárias ---\n");

        int num_products;
        // --- Input for number of products with validation ---
        do {
            printf("Quantos produtos diferentes foram vendidos hoje? ");
            scanf("%d", &num_products);
            while (getchar() != '\n'); // Clear input buffer

            if (num_products <= 0) {
                printf("O número de produtos deve ser maior que zero. Tente novamente.\n");
            }
        } while (num_products <= 0);

        float daily_total_sales = 0.0; // Initialize daily total for each new day

        // --- Inner loop for each product ---
        for (int i = 1; i <= num_products; i++) {
            printf("\n--- Produto %d ---\n", i);
            char product_name[50]; // Assuming product name won't exceed 49 characters
            int quantity;
            float unit_price;

            printf("Nome do produto: ");
            // Use fgets to read product name, it's safer than scanf for strings
            fgets(product_name, sizeof(product_name), stdin);
            product_name[strcspn(product_name, "\n")] = 0; // Remove trailing newline from fgets

            // --- Input for quantity with validation ---
            do {
                printf("Quantidade vendida: ");
                scanf("%d", &quantity);
                while (getchar() != '\n'); // Clear input buffer

                if (quantity < 0) {
                    printf("A quantidade não pode ser negativa. Tente novamente.\n");
                }
            } while (quantity < 0);

            // --- Input for unit price with validation ---
            do {
                printf("Preço unitário: R$ ");
                scanf("%f", &unit_price);
                while (getchar() != '\n'); // Clear input buffer

                if (unit_price < 0) {
                    printf("O preço unitário não pode ser negativo. Tente novamente.\n");
                }
            } while (unit_price < 0);

            float product_total = quantity * unit_price;
            printf("Total para %s: R$ %.2f\n", product_name, product_total);

            daily_total_sales += product_total; // Accumulate to daily total
        }

        // --- Display daily total ---
        printf("\n--- Resumo do Dia ---\n");
        printf("Total geral das vendas do dia: R$ %.2f\n", daily_total_sales);

        // --- Ask to continue or exit ---
        printf("\nDeseja registrar vendas para outro dia? (S/N): ");
        scanf(" %c", &continue_sales); // Notice the space before %c to consume leftover newline
        while (getchar() != '\n'); // Clear input buffer
    }

    printf("\nObrigado por usar o sistema de controle de vendas!\n");

    return 0;
}
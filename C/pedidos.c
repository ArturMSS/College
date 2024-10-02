#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_ITENS 100 // numero máximo de itens, não limita unidades por item

// Estrutura para armazenar os dados dos pedidos
typedef struct {
    int codigo;     // Código do item pedido
    int quantidade; // Quantidade do item pedido
} ItemPedido;

// Estrutura para armazenar um pedido completo
typedef struct {
    ItemPedido itens[MAX_ITENS]; // Lista de itens no pedido
    int num_itens;               // Número de itens no pedido
} Pedido;

// Função para exibir o cardápio
void exibir_cardapio() {
    printf("Cardápio:\n");
    printf("Cachorro-quente (Código 100) - R$ 5.20\n");
    printf("Bauru simples (Código 101) - R$ 6.30\n");
    printf("Bauru com ovo (Código 102) - R$ 6.50\n");
    printf("Hambúrguer (Código 103) - R$ 7.20\n");
    printf("Cheeseburguer (Código 104) - R$ 8.30\n");
    printf("Refrigerante (Código 105) - R$ 5.00\n");
}

// Função para obter o preço do item com base no código
double obter_preco(int codigo) {
    switch (codigo) {
        case 100: return 5.20;  // Cachorro-quente
        case 101: return 6.30;  // Bauru simples
        case 102: return 6.50;  // Bauru com ovo
        case 103: return 7.20;  // Hambúrguer
        case 104: return 8.30;  // Cheeseburguer
        case 105: return 5.00;  // Refrigerante
        default: return 0.0;    // Código inválido
    }
}

// Função para obter entrada válida de caractere único ('s' ou 'n')
char obter_entrada_valida() {
    char entrada[10]; // Buffer para armazenar entrada do usuário

    while (1) {
        fgets(entrada, sizeof(entrada), stdin); // Lê entrada do usuário

        // Verifica se é um caractere único ('s' ou 'n')
        if (strlen(entrada) == 2 && (entrada[0] == 's' || entrada[0] == 'n') && entrada[1] == '\n') {
            return entrada[0]; // Retorna o caractere válido
        } else {
            printf("Entrada inválida. Digite 's' para Sim ou 'n' para Não: ");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // permite usar caracteres especiais e acentuação
    
    Pedido* pedidos = NULL;  // Ponteiro para armazenar os pedidos
    int num_pedidos = 0;     // Contador para o número de pedidos
    double faturamento_total = 0.0; // Inicialização do faturamento total
    
    char continuar_registro = 's'; // Controle para continuar registrando pedidos

    // Loop para registrar pedidos até que o usuário decida parar
    while (continuar_registro == 's') {
        // Aloca memória para um novo pedido
        pedidos = realloc(pedidos, (num_pedidos + 1) * sizeof(Pedido));
        if (pedidos == NULL) {
            fprintf(stderr, "Erro ao alocar memória.\n");
            return 1;
        }

        pedidos[num_pedidos].num_itens = 0; // Inicializa o número de itens do pedido atual
        char continuar_pedido = 's'; // Controle para continuar adicionando itens ao pedido

        printf("Pedido %d:\n", num_pedidos + 1);

        // Loop para permitir que o cliente adicione vários itens em um pedido
        while (continuar_pedido == 's') {
            exibir_cardapio(); // Exibe o cardápio para o cliente

            // Entrada do código do item
            printf("Digite o código do item: ");
            while (scanf("%d", &pedidos[num_pedidos].itens[pedidos[num_pedidos].num_itens].codigo) != 1 ||
                   (pedidos[num_pedidos].itens[pedidos[num_pedidos].num_itens].codigo < 100 || pedidos[num_pedidos].itens[pedidos[num_pedidos].num_itens].codigo > 105)) {
                printf("Código inválido. Insira um código entre 100 e 105: ");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            }

            // Entrada da quantidade do item
            printf("Digite a quantidade: ");
            while (scanf("%d", &pedidos[num_pedidos].itens[pedidos[num_pedidos].num_itens].quantidade) != 1 ||
                   pedidos[num_pedidos].itens[pedidos[num_pedidos].num_itens].quantidade <= 0) {
                printf("Quantidade inválida. Insira um valor positivo: ");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            }

            pedidos[num_pedidos].num_itens++; // Incrementa o número de itens no pedido

            // Limpa o buffer de entrada após leitura de números
            while (getchar() != '\n');

            // Pergunta ao cliente se ele deseja adicionar mais itens ao pedido
            printf("Deseja adicionar mais um item? (s - Sim, n - Não): ");
            continuar_pedido = obter_entrada_valida();
        }

        // Cálculo do valor total do pedido
        double valor_pedido = 0.0;
        for (int j = 0; j < pedidos[num_pedidos].num_itens; j++) {
            double preco_unitario = obter_preco(pedidos[num_pedidos].itens[j].codigo);
            valor_pedido += preco_unitario * pedidos[num_pedidos].itens[j].quantidade;
        }
        faturamento_total += valor_pedido; // Acumula o valor no faturamento total

        printf("Valor do pedido: R$ %.2f\n\n", valor_pedido);

        num_pedidos++; // Incrementa o contador de pedidos

        // Pergunta ao usuário se ele deseja registrar mais pedidos
        printf("Deseja registrar outro pedido? (s - Sim, n - Não): ");
        continuar_registro = obter_entrada_valida();
    }

    // Exibe o faturamento total do dia
    printf("Faturamento total do dia: R$ %.2f\n", faturamento_total);

    // Libera a memória alocada
    free(pedidos);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //necessário para usar setlocale

#define NUM_CLIENTES 10
#define MAX_NOME 100
#define PERCENTUAL_MAXIMO 0.2

// Definição da estrutura para armazenar dados de solicitações de empréstimo
typedef struct {
    char nome[MAX_NOME];   // Nome do cliente
    double salario;        // Salário do cliente
    double valor_emprestimo; // Valor do empréstimo solicitado
    int num_meses;         // Número de meses para quitação
    double parcela;        // Valor da parcela mensal calculada
    int aprovado;          // Indicador de aprovação do empréstimo (1 = aprovado, 0 = reprovado)
} SolicitacaoEmprestimo;

// Função para calcular o valor da parcela do empréstimo
double calcular_parcela(double valor_emprestimo, int num_meses) {
    return valor_emprestimo / num_meses;
}

// Função para verificar se o empréstimo é aprovado ou reprovado
int verificar_aprovacao(double salario, double parcela) {
    // O empréstimo é aprovado se a parcela for menor ou igual a 20% do salário
    return (parcela <= salario * PERCENTUAL_MAXIMO) ? 1 : 0;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    SolicitacaoEmprestimo clientes[NUM_CLIENTES]; // Array para armazenar dados dos clientes
    int emprestimos_aprovados = 0;
    int emprestimos_reprovados = 0;

    // Loop para registrar as solicitações de empréstimo de 10 clientes
    for (int i = 0; i < NUM_CLIENTES; i++) {
        printf("Cliente %d:\n", i + 1);

        // Leitura dos dados do cliente
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", clientes[i].nome); // Leitura de string com espaços

        printf("Digite o salário do cliente: ");
        while (scanf("%lf", &clientes[i].salario) != 1 || clientes[i].salario <= 0) {
            printf("Entrada inválida. Insira um salário válido: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }

        printf("Digite o valor do empréstimo: ");
        while (scanf("%lf", &clientes[i].valor_emprestimo) != 1 || clientes[i].valor_emprestimo <= 0) {
            printf("Entrada inválida. Insira um valor de empréstimo válido: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }

        printf("Digite o número de meses para quitação: ");
        while (scanf("%d", &clientes[i].num_meses) != 1 || clientes[i].num_meses <= 0) {
            printf("Entrada inválida. Insira um número de meses válido: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }

        // Calcula o valor da parcela
        clientes[i].parcela = calcular_parcela(clientes[i].valor_emprestimo, clientes[i].num_meses);

        // Verifica se o empréstimo é aprovado
        clientes[i].aprovado = verificar_aprovacao(clientes[i].salario, clientes[i].parcela);

        // Contabiliza o empréstimo como aprovado ou reprovado
        if (clientes[i].aprovado) {
            emprestimos_aprovados++;
            printf("Empréstimo aprovado para %s.\n", clientes[i].nome);
        } else {
            emprestimos_reprovados++;
            printf("Empréstimo reprovado para %s. Parcela mensal (%.2f) maior que 20%% do salário.\n", clientes[i].nome, clientes[i].parcela);
        }

        printf("\n");
    }

    // Exibe o resultado final
    printf("Quantidade de empréstimos concedidos: %d\n", emprestimos_aprovados);
    printf("Quantidade de empréstimos não concedidos: %d\n", emprestimos_reprovados);

    return 0;
}

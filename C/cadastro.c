#include <stdio.h>
#include <stdlib.h>

#define NUM_ALUNOS 10

// Definição da estrutura para armazenar as notas de cada aluno
typedef struct {
    double ap1, ap2, ap3, ap4; // Notas das atividades práticas
    double np;                 // Nota da prova
    double nota_final;         // Nota final calculada
} Aluno;

// Função para calcular a média das quatro notas práticas
double calcular_media_atividades(Aluno *aluno) {
    return (aluno->ap1 + aluno->ap2 + aluno->ap3 + aluno->ap4) / 10;
}

// Função para calcular a nota final (AV1)
double calcular_nota_final(Aluno *aluno) {
    double media_atividades = calcular_media_atividades(aluno);
    return media_atividades + (aluno->np * 0.6);
}

// Função para limpar o buffer de entrada, removendo caracteres restantes após uma entrada inválida
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler uma nota e validar se está entre 0 e 10
double ler_nota(char *prompt) {

    double nota;
    int resultado;

    while (1) {
        printf("%s", prompt);
        
        // Lê a entrada do usuário e verifica se é um número válido
        resultado = scanf("%lf", &nota);

        // Se scanf não leu um número ou o número não está entre 0 e 10
        if (resultado != 1 || nota < 0 || nota > 10) {
            printf("Entrada inválida. Insira um valor numérico entre 0 e 10.\n");
            limpar_buffer(); // Limpa o buffer de entrada para evitar loops infinitos com entradas inválidas
        } else {
            limpar_buffer(); // Limpa o buffer de entrada após uma entrada válida
            break;
        }
    }
    return nota;
}

int main() {

    Aluno *alunos = (Aluno *)malloc(NUM_ALUNOS * sizeof(Aluno)); // Alocação dinâmica de memória para 10 alunos

    if (alunos == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1; // Retorna 1 para indicar um erro
    }

    // Loop para registrar as notas de 10 alunos
    for (int i = 0; i < NUM_ALUNOS; i++) {
        printf("Aluno %d:\n", i + 1);

        // Leitura e validação das notas
        alunos[i].ap1 = ler_nota("Digite a nota da atividade prática 1 (ap1): ");
        alunos[i].ap2 = ler_nota("Digite a nota da atividade prática 2 (ap2): ");
        alunos[i].ap3 = ler_nota("Digite a nota da atividade prática 3 (ap3): ");
        alunos[i].ap4 = ler_nota("Digite a nota da atividade prática 4 (ap4): ");
        alunos[i].np  = ler_nota("Digite a nota da prova (np): ");

        // Calcula a nota final do aluno usando ponteiro para a estrutura
        alunos[i].nota_final = calcular_nota_final(&alunos[i]);

        // Exibe a nota final do aluno
        printf("Nota final do Aluno %d: %.2f\n\n", i + 1, alunos[i].nota_final);
    }

    free(alunos); // Liberação da memória alocada dinamicamente

    return 0; // Retorna 0 para indicar sucesso
}


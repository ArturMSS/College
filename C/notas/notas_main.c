#include <stdio.h>
#include <stdlib.h>
#include "lista_notas.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL," ");
    Lista* li = cria_lista();  // Cria a lista como ponteiro
    int opcao;

    do {
        exibir_menu();  // Chama o menu
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
    
        switch (opcao) {
            case 1:
                inserir_elemento(li);  // Inserir elemento
                break;
            case 2:
                remover_primeiro(li) ? printf("Primeiro elemento removido.\n") : printf("Lista vazia.\n");
                break;
            case 3:
                remover_ultimo(li) ? printf("Último elemento removido.\n") : printf("Lista vazia.\n");
                break;
            case 4: {
                int codigo;
                printf("Digite a matrícula do aluno a ser removido: ");
                scanf("%d", &codigo);
                remover_por_codigo(li, codigo) ? printf("Aluno removido.\n") : printf("Aluno não encontrado.\n");
                break;
            }
            case 5:
                consultar_elemento(li);  // Consultar aluno
                break;
            case 6:
                consultar_lista(li);  // Consultar lista de alunos
                break;
            case 7: {
                int codigo;
                printf("Digite a matrícula do aluno a ser alterado: ");
                scanf("%d", &codigo);
                alterar_dados_aluno(li, codigo);  // Alterar dados de um aluno
                break;
            }
            case 8:
                printf("Saindo...\n");
                break;  // Não chama libera_lista aqui
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 8);

    libera_lista(li);  // Libera a lista antes de sair
    return 0;
}

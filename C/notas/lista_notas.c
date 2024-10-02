#include <stdio.h>
#include <stdlib.h>
#include "lista_notas.h"

// Definição do tipo de lista
typedef struct elemento {
    Aluno dados;
    struct elemento *prox;
} Elem;

// Função para calcular a média do aluno
void calcular_media(Aluno* al) {
    al->media = al-> np*0.6 + ((al->n1 + al->n2 + al->n3 + al->n4) / 10);
}

// Função para validar notas
int validar_notas(float n1, float n2, float n3, float n4, float np) {
    // Verifica se as notas estão entre 0 e 10
    return (n1 >= 0 && n1 <= 10) && (n2 >= 0 && n2 <= 10) &&
           (n3 >= 0 && n3 <= 10) && (n4 >= 0 && n4 <= 10) &&
           (np >= 0 && np <= 10);
}

// Função para criar uma lista
Lista* cria_lista() {
    Lista* li = (Lista*)malloc(sizeof(Lista));  // Alocando espaço para um ponteiro
    if (li != NULL) {
        *li = NULL;  // Inicializa a lista com NULL (vazia)
    }
    return li;
}

// Função para liberar a lista
void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while (*li != NULL) {  
            no = *li;  // Pega o primeiro nó
            *li = (*li)->prox;  // Avança para o próximo nó
            free(no);  // Libera o nó atual
        }
        free(li);  // Libera o ponteiro da lista
    }
}

// Função para receber o tamanho da lista
int tamanho_lista(Lista* li) {
    if (li == NULL || *li == NULL) return 0;  // Verifica se a lista está vazia
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

// Função para checar se a lista está cheia
int lista_cheia(Lista* li) {
    return 0;  // Lista encadeada não pode estar cheia (além da limitação de memória)
}

// Função para checar se a lista está vazia
int lista_vazia(Lista* li) {
    return (li == NULL || *li == NULL);
}

// Inserir aluno no começo
int insere_lista_inicio(Lista* li, Aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*)malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = *li;  // Recebe endereço do 1º nó
    *li = no;  // Atualiza a lista para o novo nó
    return 1;
}

// Inserir aluno no final
int insere_lista_final(Lista* li, Aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*)malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;

    if (*li == NULL) {
        *li = no;  // Se a lista está vazia, o novo nó se torna o primeiro
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;  // Adiciona o novo nó ao final da lista
    }
    return 1;
}

// Inserir aluno de forma ordenada
int insere_lista_ordenada(Lista* li, Aluno al) {
    if (li == NULL) return 0;

    calcular_media(&al);  // Calcula a média antes da inserção

    Elem* no = (Elem*)malloc(sizeof(Elem));
    if (no == NULL) return 0;

    no->dados = al;

    if (*li == NULL) { // Caso a lista esteja vazia
        no->prox = NULL;
        *li = no;  // O novo nó se torna o primeiro
        return 1;
    } else {
        Elem* ant = NULL, *atual = *li;

        // Percorre a lista para ordenar pela média
        while (atual != NULL && atual->dados.media > al.media) {
            ant = atual;
            atual = atual->prox;
        }

        if (ant == NULL) { // Insere no início
            no->prox = *li;
            *li = no;
        } else { // Insere no meio ou no final
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

// Remover primeiro elemento
int remover_primeiro(Lista* li) {
    if (li == NULL || *li == NULL) return 0;  // Verifica se a lista está vazia

    Elem* no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

// Remover último elemento
int remover_ultimo(Lista* li) {
    if (li == NULL || *li == NULL) return 0;  // Verifica se a lista está vazia

    Elem* ant = NULL;
    Elem* atual = *li;

    // Percorre até o último elemento
    while (atual->prox != NULL) {
        ant = atual;
        atual = atual->prox;
    }

    // Se a lista tiver apenas um elemento
    if (ant == NULL) {
        *li = NULL;  // A lista agora está vazia
    } else {
        ant->prox = NULL;  // Desconecta o último nó
    }

    free(atual);  // Libera a memória do último nó
    return 1;  
}

// Função para remover um aluno por código (matrícula)
int remover_por_codigo(Lista* li, int codigo) {
    if (li == NULL || *li == NULL) return 0;

    Elem *ant = NULL, *atual = *li;
    while (atual != NULL && atual->dados.matricula != codigo) {
        ant = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return 0;  // Aluno não encontrado

    if (ant == NULL)  // Remove o primeiro
        *li = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual);
    return 1;
}

// Função para consultar um aluno por código (matrícula)
int consultar_por_codigo(Lista *li, int codigo, Aluno *elemento) {
    if (li == NULL || *li == NULL) return 0;

    Elem *no = *li;
    while (no != NULL && no->dados.matricula != codigo) {
        no = no->prox;
    }
    if (no == NULL) return 0;  // Aluno não encontrado

    *elemento = no->dados;
    return 1;
}

// Função para alterar os dados de um aluno
int alterar_dados_aluno(Lista *li, int codigo) {
    if (li == NULL) return 0;  // Verifica se a lista está vazia
    Elem *no = *li;  
    while (no != NULL && no->dados.matricula != codigo) {
        no = no->prox;  // Percorre a lista até encontrar o aluno
    }
    if (no == NULL) return 0;  // Aluno não encontrado

    printf("Digite as novas notas do aluno %s:\n", no->dados.nome);
    
    // Verificação da Nota 1
    do {
        printf("Nota 1 (0 a 10): ");
        scanf("%f", &no->dados.n1);
        if (no->dados.n1 < 0 || no->dados.n1 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (no->dados.n1 < 0 || no->dados.n1 > 10);

    // Verificação da Nota 2
    do {
        printf("Nota 2 (0 a 10): ");
        scanf("%f", &no->dados.n2);
        if (no->dados.n2 < 0 || no->dados.n2 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (no->dados.n2 < 0 || no->dados.n2 > 10);

    // Verificação da Nota 3
    do {
        printf("Nota 3 (0 a 10): ");
        scanf("%f", &no->dados.n3);
        if (no->dados.n3 < 0 || no->dados.n3 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (no->dados.n3 < 0 || no->dados.n3 > 10);

    // Verificação da Nota 4
    do {
        printf("Nota 4 (0 a 10): ");
        scanf("%f", &no->dados.n4);
        if (no->dados.n4 < 0 || no->dados.n4 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (no->dados.n4 < 0 || no->dados.n4 > 10);

    // Verificação da nota da prova
    do {
        printf("Nota Prova (0 a 10): ");
        scanf("%f", &no->dados.np);
        if (no->dados.np < 0 || no->dados.np > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (no->dados.np < 0 || no->dados.np > 10);

    // Recalcula a média
    calcular_media(&no->dados);

    printf("Dados alterados com sucesso! Nova média: %.2f\n", no->dados.media);
    return 1;  // Retorna 1 se a alteração for bem-sucedida
}

// Função para exibir o menu
void exibir_menu() {
    printf("\n----- MENU -----\n");
    printf("1. Inserir aluno\n");
    printf("2. Remover primeiro aluno\n");
    printf("3. Remover último aluno\n");
    printf("4. Remover aluno por código\n");
    printf("5. Consultar aluno por código\n");
    printf("6. Consultar lista de alunos\n");
    printf("7. Alterar dados de um aluno\n");
    printf("8. Sair\n");
}

// Função para consultar a lista de alunos
void consultar_lista(Lista *li) {
    if (li == NULL || *li == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    Elem *no = *li;
    printf("Lista de alunos:\n");
    while (no != NULL) {
        printf("Matrícula: %d, Nome: %s, Média: %.2f\n", no->dados.matricula, no->dados.nome, no->dados.media);
        no = no->prox;
    }
}

void consultar_elemento(Lista *li) {
    int codigo;
    Aluno al;
    printf("Digite a matrícula do aluno para consulta: ");
    scanf("%d", &codigo);

    if (consultar_por_codigo(li, codigo, &al))
        printf("Aluno encontrado: %s, Matrícula: %d, Média: %.2f\n", al.nome, al.matricula, al.media);
    else
        printf("Aluno não encontrado!\n");
}

void inserir_elemento(Lista *li) {
    Aluno al;
    printf("Digite o nome do aluno: ");
    scanf("%s", al.nome);
    
    // Verificação da Matrícula
    do {
        printf("Digite a matrícula do aluno (8 dígitos): ");
        scanf("%d", &al.matricula);
        if (al.matricula < 10000000 || al.matricula > 99999999) {
            printf("Matrícula inválida! Deve ter 8 dígitos.\n");
        }
    } while (al.matricula < 10000000 || al.matricula > 99999999);

    // Verificação da Nota 1
    do {
        printf("Digite a nota 1 (0 a 10): ");
        scanf("%f", &al.n1);
        if (al.n1 < 0 || al.n1 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (al.n1 < 0 || al.n1 > 10);

    // Verificação da Nota 2
    do {
        printf("Digite a nota 2 (0 a 10): ");
        scanf("%f", &al.n2);
        if (al.n2 < 0 || al.n2 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (al.n2 < 0 || al.n2 > 10);

    // Verificação da Nota 3
    do {
        printf("Digite a nota 3 (0 a 10): ");
        scanf("%f", &al.n3);
        if (al.n3 < 0 || al.n3 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (al.n3 < 0 || al.n3 > 10);

    // Verificação da Nota 4
    do {
        printf("Digite a nota 4 (0 a 10): ");
        scanf("%f", &al.n4);
        if (al.n4 < 0 || al.n4 > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (al.n4 < 0 || al.n4 > 10);

    // Verificação da Nota NP
    do {
        printf("Digite a nota Prova (0 a 10): ");
        scanf("%f", &al.np);
        if (al.np < 0 || al.np > 10) {
            printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
        }
    } while (al.np < 0 || al.np > 10);

    // Calcula e insere o aluno ordenado pela média
    if (insere_lista_ordenada(li, al))
        printf("Aluno inserido com sucesso!\n");
    else
        printf("Erro ao inserir o aluno!\n");
}

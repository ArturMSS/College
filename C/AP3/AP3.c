#include <stdio.h>
#include <stdlib.h>
#include "AP3.h"


// Definição do tipo de lista
typedef struct elemento {
    struct aluno dados;
    struct elemento *prox;
} Elem;

// Função para criar uma lista
Lista* cria_lista() {
    Lista* li = (Lista*)malloc(sizeof(Elem*));  // Alocando espaço para um ponteiro
    if (li != NULL) {
        *li = NULL;  // Inicializa a lista com NULL (vazia)
    }
    return li;
}
// Função para calcular a média do  aluno
float calcular_nota_final(struct aluno al) {
return al.np * 0.6 + ((al.ap1 + al.ap2 + al.ap3 + al.ap4) / 4) * 0.4;  
}

// Inserir aluno de forma ordenada
int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;



    Elem* no = (Elem*)malloc(sizeof(Elem));
    if (no == NULL) return 0;

    no->dados = al;
    float nota_aluno = calcular_nota_final(al);  // Calcula a média antes da inserção
    if (*li == NULL) { // Caso a lista esteja vazia
        no->prox = NULL;
        *li = no;  // O novo nó se torna o primeiro
        return 1;
    } else {
        Elem* ant = NULL, *atual = *li;

        // Percorre a lista para ordenar pela nota final
        while (atual != NULL && calcular_nota_final(atual->dados) > nota_aluno) {
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

void consultar_lista(Lista* li) {
    if (li == NULL || *li == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    Elem* no = *li;
    while (no != NULL) {
        printf("Matrícula: %d, Nome: %s, Nota Final: %.2f\n", 
               no->dados.matricula, no->dados.nome, calcular_nota_final(no->dados));
        no = no->prox;
    }
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

void combinar_listas(Lista* lista1, Lista* lista2, Lista* lista_combinada){
    Elem* no = *lista1;
    while (no != NULL){
        insere_lista_ordenada(lista_combinada, no ->dados);
        no = no->prox;
    }
    no = *lista2;
    while(no != NULL){
        insere_lista_ordenada(lista_combinada, no->dados);
        no = no->prox;
    }
}
// inserir os elementos das listas combinadas na lista das melhores notas
void inserir_melhores_notas(Lista* lista_combinada, Lista* melhores){
    Elem* no = *lista_combinada;
    int cont = 0;
    while (no!=NULL && cont<10){//para inserir 10 elementos numa lista
        insere_lista_ordenada(melhores, no->dados);
        no = no ->prox;
        cont ++;//conta ate 10
    }
}

// inserir os elementos das listas combinadas na lista das piores notas
void inserir_piores_notas(Lista* lista_combinada, Lista* piores){
    Elem* no = *lista_combinada;
    int total = 0;

    while(no != NULL){ //conta o numero de elementos
        total++;
        no = no->prox;
    }

    no = *lista_combinada;
    int cont = 0;
    while(no != NULL && cont<total-10){//pula os 10 primeiros
        no = no->prox;
        cont++;
    }

    while(no != NULL){
        insere_lista_ordenada(piores, no->dados);
        no = no->prox;
    }
}

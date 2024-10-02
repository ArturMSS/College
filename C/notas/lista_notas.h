#ifndef LISTADIN_H
#define LISTADIN_H

// Estrutura Aluno
typedef struct {
    int matricula;
    char nome[30];
    float n1, n2, n3, n4, np, media;
} Aluno;

// Definição da lista
typedef struct elemento* Lista;

// Funções de manipulação da lista

// Criação e liberação da lista
Lista* cria_lista();
void libera_lista(Lista* li);

// Consultas sobre a lista
int lista_vazia(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);

// Inserção de elementos
int insere_lista_inicio(Lista* li, Aluno al);
int insere_lista_final(Lista* li, Aluno al);
int insere_lista_ordenada(Lista* li, Aluno al);

// Remoção de elementos
int remover_primeiro(Lista* li);
int remover_ultimo(Lista* li);
int remover_por_codigo(Lista* li, int codigo);

// Consulta de elementos
int consultar_por_indice(Lista* li, int indice, Aluno* elemento);
int consultar_por_codigo(Lista* li, int codigo, Aluno* elemento);

// Atualização de dados
int alterar_dados_aluno(Lista* li, int codigo);

// Funções auxiliares
void exibir_menu();
void inserir_elemento(Lista* li);
void remover_elemento(Lista* li);
void consultar_elemento(Lista* li);
void consultar_lista(Lista* li);

#endif // LISTADIN_H

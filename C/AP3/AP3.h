#ifndef AP3_H
#define AP3_H

struct aluno {
    int matricula;
    char nome[30];
    float ap1, ap2, ap3, ap4, np, av;
};

typedef struct elemento* Lista;

//funções
Lista* cria_lista();

void libera_lista(Lista* li);
int insere_lista_ordenada(Lista* li, struct aluno al);
float calcular_nota_final(struct aluno al);
void libera_lista(Lista* li);
void combinar_listas(Lista* lista1, Lista* lista2, Lista* lista_combinada);
void inserir_piores_notas(Lista* lista_combinada, Lista* piores);
void inserir_melhores_notas(Lista* lista_combinada, Lista* melhores);
// Exibir a lista de alunos
void consultar_lista(Lista* li) ;

#endif // AP3_H

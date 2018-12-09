/*
    Codigo feito por:
        Pedro Victor Rodrigues de Carvalho (17/0113043)
        Victor Eduardo Fernandes Castor (17/0115127)
    Universidade de Brasília, Segundo semestre de 2018
    Curso: Engenharia de Computacao
    Materia: Organizacao de Arquivos
    Professor: Camilo Dorea
    Projeto 2: Registros em Arvore B
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

// Funcionamento garantido para ORDEM >= 4
#define ORDEM 4
#define TAM_CHAVE 9

typedef struct No{
   int qtd_chaves; //Quantidades de chaves contida no nó
   int prr[ORDEM];
   int identidade;
   char chaves[ORDEM][TAM_CHAVE]; //Chaves armazenadas no nó
   struct No *filhos[ORDEM+1]; //Ponteiro para os filhos
   struct No *pai;
}no;

typedef struct No_leitura{
    char chaves[ORDEM-1][TAM_CHAVE];
    int filhos[ORDEM];
    int prr[ORDEM-1];
}no_leitura;

int insere_chave (no **raiz, char* chave, int *prr, int *ID);
void promove (no **raiz, no *pNo, char lista[ORDEM][TAM_CHAVE], int qtd_lista, int prr_lista[ORDEM], int *ID);
no* busca_no (no *no_recebido, char* chave);
int compara_string(char* string1, char* string2);
void insertionSort(char array[ORDEM][TAM_CHAVE], int n, int* prr_lista);
void ordena_ponteiros(no* pNoPai, int n);
void atualiza_dados(FILE* arq_base);
void mostraArvore(no* NoAtual, int espaco_inicial);
void imprimeNo(char *nome, int espacos, int prr);
void escreveArq(FILE *ptrArq, no *pNo);
void mostra_arq_ind();
int busca_registro(char chave[TAM_CHAVE], FILE *arq, int ID_atual);
no_leitura *cria_no(FILE *arq);
int verifica_chave(char chave[TAM_CHAVE], no_leitura *no_criado);
int direciona(char chave[TAM_CHAVE], no_leitura *no_criado);
void liberaNo(no* pNo);

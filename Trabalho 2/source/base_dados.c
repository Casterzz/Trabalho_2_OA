# include "arvoreB.h"

#define TAM_REG 60
#define CAMPO_1 41

no* atualiza_dados(FILE* arq_base) {
	no* raiz = (no*)malloc(sizeof(no)); 
    raiz->qtd_chaves = 0;
    int prr = -1;
    for (int i = 0; i < ORDEM; i++) {
        raiz->filhos[i] = NULL;
    }
    raiz->pai = NULL;

    char linha_atual[TAM_REG];
    char registro[TAM_CHAVE];

    while (fgets(linha_atual, TAM_REG, arq_base) != NULL) {
    	for (int i = 0; i < 3; i++) {
    		registro[i] = linha_atual[i];
    	}
    	for (int i = 0; i < 5; i++) {
    		registro[i + 3] = linha_atual[CAMPO_1 + i];
    	}
    	registro[8] = '\0';
    	//printf("%s\n", registro);

        printf("<Incluindo registro %s, PRR = %d>\n\n", registro, prr+1);

    	insere_chave(&raiz, registro, &prr);
        mostraArvore(raiz, 0);
        printf("\n\n\n");
    }
    return raiz;
}

void imprimeNo(char *nome, int espacos, int prr) {
    int i;
    for (i = 0; i < espacos; i++) {
        printf("\t");
    }
    printf("%s %d\n", nome, prr);
}

void mostraArvore(no* NoAtual, int espaco_inicial) {
    int i;
    if (NoAtual == NULL) {
        //imprimeNo("*", espaco_inicial+1);
        return;
    }
    for (i = 0; i < NoAtual->qtd_chaves; i++) {
        mostraArvore(NoAtual->filhos[i], espaco_inicial+1);
        imprimeNo(NoAtual->chaves[i], espaco_inicial, NoAtual->prr[i]);
    }
    mostraArvore(NoAtual->filhos[i], espaco_inicial+1);
}

# include "arvoreB.h"

#define TAM_REG 60
#define CAMPO_1 41

no* atualiza_dados(FILE* arq_base) {
	no* raiz = (no*)malloc(sizeof(no)); 
    raiz->qtd_chaves = 0;
    int prr = -1;
    int ID = 0;
    raiz->identidade = ID;
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

        printf("<Incluindo registro %s, PRR = %d>\n", registro, prr+1);

    	insere_chave(&raiz, registro, &prr, &ID);
    }
    printf("\n");
    mostraArvore(raiz, 0);
    FILE *arquivo = fopen("indicelista.bt", "w");
    escreveArq(arquivo, raiz);
    fclose(arquivo);

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

void escreveArq(FILE *ptrArq, no *pNo) {
    // se no for NULL
    if (pNo == NULL) {
        return;
    }

    if (pNo->pai == NULL) {
        fprintf(ptrArq, "%d\n\n", pNo->identidade);
    }
 
// percorre todos os filhos recursivamente
//  for (todos os filhos) {
    for (int i = 0; i < ORDEM; i++) {
        escreveArq(ptrArq, pNo->filhos[i]);
    }

// escreve dados do no atual
    fprintf(ptrArq, "#\n%d\n", pNo->identidade);    // cabecalho
    for (int i = 0; i < ORDEM-1; i++) {    // escreve chaves
        if (i < pNo->qtd_chaves) {
            fprintf(ptrArq, "%s %d\n", pNo->chaves[i], pNo->prr[i]);
        } else {
            fprintf(ptrArq, "*        -1\n");
        }
    }
    for (int i = 0; i < ORDEM; i++) {    // escreve filhos
        if (pNo->filhos[i] != NULL) {
            fprintf(ptrArq, "%d ", pNo->filhos[i]->identidade);
        } else {
            fprintf(ptrArq, "-1 ");
        }
    }
    fprintf(ptrArq, "\n\n");
}

void mostra_arq_ind() {
    char linha_atual[20]; 
    FILE *arq = fopen("indicelista.bt", "r");
    printf("<ARQUIVO INDICELISTA.BT>\n\n");
    while (fgets(linha_atual, 20, arq) != NULL) {
        printf("%s", linha_atual);   
    }
    printf("\n");
}

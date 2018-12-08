#include "arvoreB.h"

int insere_chave (no **raiz, char* chave, int *prr, int *ID) {
    no* pNo = busca_no (*raiz, chave);
    char lista[ORDEM][TAM_CHAVE];
    int prr_lista[ORDEM];
    *prr = *prr + 1;

    if (pNo == NULL) {
        printf("falha ao inserir\n");
        return -1;
    }

    if (pNo->qtd_chaves < ORDEM-1) {
        for (int i = 0; i < TAM_CHAVE; i++) {
            pNo->chaves[pNo->qtd_chaves][i] = chave[i];
        }
        pNo->prr[pNo->qtd_chaves] = *prr;
        pNo->qtd_chaves++;

        insertionSort(pNo->chaves, pNo->qtd_chaves, pNo->prr);
        //ordena_ponteiros(pNo, pNo->qtd_chaves, changes);
    } else {
        for (int i = 0; i < pNo->qtd_chaves; i++) {
            for (int j = 0; j < TAM_CHAVE; j++) {    
                lista[i][j] = pNo->chaves[i][j];
            }
            prr_lista[i] = pNo->prr[i];
        }
        for (int i = 0; i < TAM_CHAVE; i++) {    
            lista[pNo->qtd_chaves][i] = chave[i];
            pNo->chaves[pNo->qtd_chaves][i] = chave[i];
        }
        prr_lista[pNo->qtd_chaves] = *prr; 
        pNo->prr[pNo->qtd_chaves] = *prr;
        pNo->filhos[pNo->qtd_chaves+1] = NULL;
        insertionSort(lista, pNo->qtd_chaves+1, prr_lista); 
        //ordena_ponteiros(pNo, pNo->qtd_chaves, changes);
        promove(raiz, pNo, lista, pNo->qtd_chaves+1, prr_lista, ID);
    }
}

void promove (no **raiz, no *pNo, char lista[ORDEM][TAM_CHAVE], int qtd_lista, int prr_lista[ORDEM], int *ID) {

    // Acha meio
    int meio = ceil(qtd_lista/2);
    if (qtd_lista%2 == 0) {
        meio++;
    }

    // Cria e preenche elemento divisor
    char elemento_div[TAM_CHAVE];
    int prr_div;

    for (int i = 0; i < TAM_CHAVE; i++) {
        elemento_div[i] = lista[meio-1][i];    
    }
    prr_div = prr_lista[meio-1];

    // Cria no irmao e atualiza chaves
    no *pNovo = (no*)malloc(sizeof(no));
    *ID = *ID + 1;
    pNovo->identidade = *ID;

    for(int i = 0; i < meio-1; i++) { 
        for (int j = 0; j < TAM_CHAVE; j++) {
            pNo->chaves[i][j] = lista[i][j];
        }
        pNo->prr[i] = prr_lista[i];
    }

    for (int i = meio; i < qtd_lista; i++) {
        for (int j = 0; j < TAM_CHAVE; j++) {
            pNovo->chaves[i-meio][j] = lista[i][j];
        }        
        pNovo->prr[i-meio] = prr_lista[i];
    }

    // "Carrega" ponteiros de filhos
    int cont = 0;
    for (int i = 0; i <= qtd_lista; i++) {
        if (meio+i <= qtd_lista) {
            pNovo->filhos[i] = pNo->filhos[meio + i];
            if (pNo->filhos[meio + i] != NULL) {
                if (pNo->filhos[meio + i]->pai != NULL) {
                    pNo->filhos[meio + i]->pai = pNovo;
                }
            }
        } else {
            pNovo->filhos[i] = NULL;
        }
    }
    for (int i = 0; (meio+i) <= ORDEM; i++) {
        pNo->filhos[meio + i] = NULL;
        cont++;
    }

    // Atualiza quantidades
    pNo->qtd_chaves = ORDEM-cont;
    pNovo->qtd_chaves = cont-1;

    // Cria novo pai caso nao exista ainda
    if (pNo->pai == NULL) {
        no *pPai = (no*)malloc(sizeof(no));
        *raiz = pPai;
        *ID = *ID + 1;
        pPai->pai = NULL;
        pPai->identidade = *ID;
        for (int i = 0; i < TAM_CHAVE; i++) {
            pPai->chaves[0][i] = elemento_div[i];    
        }
        pPai->prr[0] = prr_div;
        for (int i = 0; i < ORDEM; i++) {
            pPai->filhos[i] = NULL;    
        }
        pPai->filhos[0] = pNo;
        pPai->filhos[1] = pNovo;
        pNovo->pai = pPai;
        pNo->pai = pPai;
        pPai->qtd_chaves = 1;
    } else {
    	pNovo->pai = pNo->pai;
        // Se tiver espaco, simplesmente insere
        if (pNo->pai->qtd_chaves < ORDEM-1) {
            
            for (int i = 0; i < TAM_CHAVE; i++) {
                pNo->pai->chaves[pNo->pai->qtd_chaves][i] = elemento_div[i];
            }
            pNo->pai->prr[pNo->pai->qtd_chaves] = prr_div;

            char no_original[TAM_CHAVE];
            char no_novo[TAM_CHAVE];
            strcpy(no_original, pNo->pai->filhos[pNo->pai->qtd_chaves]->chaves[0]);
            strcpy(no_novo, pNovo->chaves[0]);

            no* maior;
            no* menor;

            int situacao = strcmp(no_original, no_novo);

            if (situacao > 0) {
                maior = pNo->pai->filhos[pNo->pai->qtd_chaves];
                menor = pNovo;
            } else {
                maior = pNovo;
                menor = pNo->pai->filhos[pNo->pai->qtd_chaves];
            }

            pNo->pai->filhos[pNo->pai->qtd_chaves+1] = maior;
            pNo->pai->filhos[pNo->pai->qtd_chaves] = menor;

            pNo->pai->qtd_chaves++;

            // inserir pNovo no array filhos do pai
            pNo->pai->filhos[pNo->pai->qtd_chaves+1] = pNovo;
            ordena_ponteiros(pNo->pai, pNo->pai->qtd_chaves+1);

            insertionSort(pNo->pai->chaves, pNo->pai->qtd_chaves, pNo->pai->prr);
            //ordena_ponteiros(pNo->pai, pNo->pai->qtd_chaves, changes);

        // Se nao tiver espaco, passa elemento divisor para cima e promove    
        } else {
            for (int i = 0; i < pNo->pai->qtd_chaves; i++) {
                for (int j = 0; j < TAM_CHAVE; j++) {
                    lista[i][j] = pNo->pai->chaves[i][j];    
                }
                prr_lista[i] = pNo->pai->prr[i];
            }
            for (int i = 0; i < TAM_CHAVE; i++) {
                lista[pNo->pai->qtd_chaves][i] = elemento_div[i];
            }
            prr_lista[pNo->pai->qtd_chaves] = prr_div;
            insertionSort(lista, pNo->pai->qtd_chaves+1, prr_lista);
            //ordena_ponteiros(pNo->pai, pNo->pai->qtd_chaves, changes);

            // inserir pNovo no array filhos do pai
            pNo->pai->filhos[pNo->pai->qtd_chaves+1] = pNovo;
            ordena_ponteiros(pNo->pai, ORDEM+1);

            promove(raiz, pNo->pai, lista, pNo->pai->qtd_chaves+1, prr_lista, ID);
        }
    }
}

no* busca_no (no *no_recebido, char* chave) {
    no* aux = no_recebido;
    int situacao;
    int i;

    for (i = 0; i < aux->qtd_chaves; i++) {
        situacao = strcmp(aux->chaves[i], chave);
        if (situacao < 0) {
            continue;
        } else if (situacao == 0) {
            printf("elemento ja existe\n");
            return NULL;
        } else if (situacao > 0) {
            if (aux->filhos[i] == NULL) {
                return aux;
            }
            return busca_no (aux->filhos[i], chave);
        }
    }
    if (aux->filhos[i] == NULL) {
        return aux;
    }
    return busca_no (aux->filhos[i], chave);
}

void insertionSort(char array[ORDEM][TAM_CHAVE], int n, int* prr_lista) { 
    int i, j; 
    char chave[TAM_CHAVE];
    int prr;
    for (i = 1; i < n; i++) {
        for (int j = 0; j < TAM_CHAVE; j++) { 
            chave[j] = array[i][j];
        }
        prr = prr_lista[i];
        j = i-1; 

        while (j >= 0 && strcmp(array[j], chave) > 0) { 
            for (int k = 0; k < TAM_CHAVE; k++) {
                array[j+1][k] = array[j][k]; 
            }
            prr_lista[j+1] = prr_lista[j];
            j = j-1; 
        }
        for (int k = 0; k < TAM_CHAVE; k++) {
            array[j+1][k] = chave[k]; 
        }
        prr_lista[j+1] = prr;
    }
}

void ordena_ponteiros(no* pNoPai, int n) { 
    int i, j;
    no* aux;
    for (i = 1; i < n; i++) {
        j = i-1; 
        aux = pNoPai->filhos[i];

        while (j >= 0 && strcmp(pNoPai->filhos[j]->chaves[0], aux->chaves[0]) > 0) { 
            pNoPai->filhos[j+1] = pNoPai->filhos[j];
            j = j-1; 
        }
        pNoPai->filhos[j+1] = aux;
    }
}

int busca_registro(char chave[TAM_CHAVE], FILE *arq, int ID_atual) {
	rewind(arq);
	//converter string p chave

	//encontrar e carregar no raiz
	char linha_atual[20];
	char inicio;
	int ID_lido;
	no_leitura *no_criado;
	int prr;

    while (fgets(linha_atual, 20, arq) != NULL) {
        if (linha_atual[0] == '#') {
        	fscanf(arq, "%d\n", &ID_lido);
        	if (ID_lido == ID_atual) {
        		no_criado = cria_no(arq);
        		prr = verifica_chave(chave, no_criado);
        		if (prr != -1) {
        			printf("Registro encontrado!\n");
        			free(no_criado);
        			return prr;
        		} else {
        			ID_atual = direciona(chave, no_criado);
        			free(no_criado);
        			if (ID_atual == -1) {
        				return -1;
        			}
        			return busca_registro(chave, arq, ID_atual);
        		}
        	}
        }
    }
    return -1;
}

no_leitura *cria_no(FILE *arq){
	char lixo[5];

	no_leitura *no_virtual = (no_leitura*)malloc(sizeof(no_leitura));
	for (int i = 0; i < ORDEM-1; i++) {
		fgets(no_virtual->chaves[i], TAM_CHAVE, arq);
		fgets(lixo, 1, arq);
		fscanf(arq, "%d", &no_virtual->prr[i]);
        fgets(lixo, 5, arq);
	}
	for (int i = 0; i < ORDEM; i++) {
		fscanf(arq, "%d", &no_virtual->filhos[i]);
        fgets(lixo, 5, arq);
	}
	return no_virtual;
}

int verifica_chave(char chave[TAM_CHAVE], no_leitura *no_criado) {
	for (int i = 0; i < ORDEM; i++) {
		if (strcmp(chave, no_criado->chaves[i]) == 0) {
			return no_criado->prr[i];
		}
	}
	return -1;
}

int direciona(char chave[TAM_CHAVE], no_leitura *no_criado) {
    for (int i = 0; i < ORDEM; i++) {
		if (strcmp(chave, no_criado->chaves[i]) < 0) {
			return no_criado->filhos[i];
		}
	}
	return no_criado->filhos[ORDEM-1];
}
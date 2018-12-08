#include "arvoreB.h"

void dados_arq() {
    FILE* arq_base = fopen("registros.txt", "r");
    no* raiz = atualiza_dados(arq_base);
    fclose(arq_base);
    return;
}

void limpa_buffer(){
    int n;
    while((n = getchar()) != EOF && n != '\n');
}

int main() {
    int opcao = 5;
    char nome[45];
    char matricula[20];
    char chave[TAM_CHAVE];
    int ID_raiz;
    int prr;
    dados_arq();

    do {
        printf("\n\tOrganização de registros em B-Tree\n\n");
        printf ("O que deseja fazer?\n\n");
        printf("1 - Mostrar 'indicelista.bt'\n");
        printf("2 - Buscar registros\n");
        printf("3 - Fechar\n");

        while (opcao == 5) {
            scanf("%d", &opcao);
            limpa_buffer();
            if (opcao == 5) {
                printf("Entrada invalida.\n");
            }
            printf("\n\n");
        }

        switch(opcao) {
            case 1:
                mostra_arq_ind();
                opcao = -1;
                break;

            case 2:
                printf("Entre com o nome:\n");
                scanf("%s", nome);
                printf("Entre com a matricula:\n");
                scanf("%s", matricula);
                for (int i = 0; i < TAM_CHAVE-3; i++) {
                    if (i < 3) {
                        chave[i] = nome[i];
                    }
                    chave[i+3] = matricula[i];
                }
                FILE *arq = fopen("indicelista.bt", "r");
                fscanf(arq, "%d", &ID_raiz);
                printf("%s\n", chave);
                prr = busca_registro(chave, arq, ID_raiz);
                if (prr == -1) {
                    printf("registro nao encontrado!\n");
                }
                fclose(arq);
                opcao = -1;
                break;

            case 3:     // Sair
                opcao = -1;
                break;

            default:
                printf("Entrada invalida\n");
                opcao = 5;
        }
    } while (opcao > 0);
    return 0;
}

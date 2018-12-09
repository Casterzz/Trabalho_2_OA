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

#include "arvoreB.h"

void dados_arq() {
    FILE* arq_base = fopen("registros.txt", "r");
    atualiza_dados(arq_base);
    fclose(arq_base);
    return;
}

void limpa_buffer(){
    int n;
    while((n = getchar()) != EOF && n != '\n');
}

int main() {
    FILE *arq, *registros;
    int opcao = 6;
    char espacos[41];
    char nome[45];
    char matricula[20];
    char curso[3];
    char turma;
    char linha[60];
    char chave[TAM_CHAVE];
    int ID_raiz;
    int prr;
    dados_arq();

    for (int i = 0; i < 40; i++) {
        espacos[i] = ' ';
    }
    espacos[40] = '\0';

    do {
        printf("\n\tOrganização de registros em B-Tree\n\n");
        printf ("O que deseja fazer?\n\n");
        printf("1 - Mostrar 'indicelista.bt'\n");
        printf("2 - Buscar registros\n");
        printf("3 - Inserir novo registro\n");
        printf("4 - Excluir registro\n");
        printf("5 - Fechar\n");

        while (opcao == 6) {
            scanf("%d", &opcao);
            limpa_buffer();
            if (opcao == 6) {
                printf("Entrada invalida.\n");
            }
            printf("\n\n");
        }

        switch(opcao) {
            case 1:     // Mostra arquivo indice
                mostra_arq_ind();
                opcao = 6;
                break;

            case 2:     // Busca registro
                printf("Entre com o nome:\n");
                scanf("%[^\n]", nome);
                printf("\n");

                printf("Entre com a matricula:\n");
                scanf("%s", matricula);
                printf("\n");

                for (int i = 0; i < TAM_CHAVE-3; i++) {
                    if (i < 3) {
                        chave[i] = nome[i];
                    }
                    chave[i+3] = matricula[i];
                }
                arq = fopen("indicelista.bt", "r");
                fscanf(arq, "%d", &ID_raiz);
                printf("Chave de busca: %s\n", chave);
                prr = busca_registro(chave, arq, ID_raiz);
                if (prr == -1) {
                    printf("Registro nao encontrado!\n");
                } else {
                    registros = fopen("registros.txt", "r");
                    for(int i = 0; i <= prr; i++) {
                        fgets(linha, 60, registros);
                    }
                    printf("%s", linha);
                    fclose(registros);
                }
                fclose(arq);
                printf("Sera mostrado o arquivo de indices a seguir. (5s)\n");
                sleep(5);
                printf("\n\n");
                mostra_arq_ind();
                opcao = 6;
                break;

            case 3:     // Insercao de registro novo
                printf("Insira o nome completo:\n");
                for (int i = 0; i < 45; i++) {
                    nome[i] = '\0';
                }
                scanf("%[^\n]", nome);
                printf("\n");
                strcat(nome, espacos);
                nome[40] = '\0';
                limpa_buffer();

                printf("Insira a matricula:\n");
                scanf("%s", matricula);
                limpa_buffer();
                printf("\n");

                printf("Insira o curso:\n");
                scanf("%s", curso);
                limpa_buffer();
                printf("\n");

                printf("Insira a turma:\n");
                scanf("%c", &turma);
                limpa_buffer();
                printf("\n");

                FILE* registros = fopen("registros.txt", "a");
                fprintf(registros, "%s %s  %s  %c\n", nome, matricula, curso, turma);
                fclose(registros);
                dados_arq();
                printf("Sera mostrado o arquivo de indices a seguir. (5s)\n");
                sleep(5);
                printf("\n\n");
                mostra_arq_ind();
                opcao = 6;
                break;

            case 4:     // Remocao de registro
                printf("Entre com o nome:\n");
                scanf("%[^\n]", nome);
                printf("\n");

                printf("Entre com a matricula:\n");
                scanf("%s", matricula);
                printf("\n");

                for (int i = 0; i < TAM_CHAVE-3; i++) {
                    if (i < 3) {
                        chave[i] = nome[i];
                    }
                    chave[i+3] = matricula[i];
                }
                arq = fopen("indicelista.bt", "r");
                fscanf(arq, "%d", &ID_raiz);
                printf("Chave de busca: %s\n", chave);
                prr = busca_registro(chave, arq, ID_raiz);
                if (prr == -1) {
                    printf("registro nao encontrado!\n");
                } else {
                    registros = fopen("registros.txt", "r+");
                    for(int i = 0; i < prr; i++) {
                        fgets(linha, 60, registros);
                    }
                    fprintf(registros, "***");
                    fclose(registros);
                }
                printf("Registro removido.\n");
                fclose(arq);
                dados_arq();
                printf("Sera mostrado o arquivo de indices a seguir. (5s)\n");
                sleep(5);
                printf("\n\n");
                mostra_arq_ind();
                opcao = 6;
                break;

            case 5:     // Sair
                opcao = -1;
                break;

            default:
                printf("Entrada invalida\n");
                opcao = 6;
        }
    } while (opcao > 0);
    return 0;
}

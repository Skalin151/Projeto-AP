#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"
#include "funcoes.h"

char tecla;
int opcao;
int ano_referencia;

int main() {

    struct Pessoa pessoas[MAX_PESSOAS];
    int num_pessoas = 0;

    ler_pessoas(pessoas, &num_pessoas);
    ler_info_academica(pessoas, &num_pessoas);

    while (1) {
    printf("\nPressione 'M' para exibir o menu: ");
    tecla = getchar();
    getchar();
    if (tecla == 'M' || tecla == 'm') {
            do {
                printf(" ________________________________________________________\n");
                printf("|                   Gestao de Estudantes                 |\n");
                printf("|                                                        |\n");
                printf("| 1. Gerenciar Estudantes                                |\n");
                printf("| 2. Numero Medio de Matriculas                          |\n");
                printf("| 3. Numero de Estudantes Finalistas                     |\n");
                printf("| 4. Media das Idades por Nacionalidade                  |\n");
                printf("| 5. Estudantes em Risco de Prescrever                   |\n");
                printf("| 6. Estudantes que Nasceram num Domingo                 |\n");
                printf("| 7. Estudantes cujo Aniversario e na Quaresma           |\n"); //Fix
                printf("| 8. Sair                                                |\n");
                printf("|________________________________________________________|\n");

                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("\nA Entrar No Submenu Estudantes...\n");
                        printf(" ________________________________________________________\n");
                        printf("|                      SubMenu Estudantes                |\n");
                        printf("|                                                        |\n");
                        printf("| 1. Adicionar Estudante                                 |\n"); //Fix
                        printf("| 2. Remover Estudante                                   |\n"); //Fix
                        printf("| 3. Pesquisar Estudante                                 |\n");
                        printf("| 4. Listar todos os Estudantes                          |\n");
                        printf("| 5. Listar Estudantes Ordem Alfabetica Apelido          |\n"); //Fix
                        printf("| 6. Listar Estudantes de uma Nacionalidade              |\n");
                        printf("| 7. Listar Estudantes numa Faixa Etária                 |\n");
                        printf("| 8. Retornar                                            |\n");
                        printf("|________________________________________________________|\n");
                        int r;
                        scanf("%d", &r);
                        switch (r) {
                            case 1:
                                adicionar_estudante(pessoas, &num_pessoas);

                                break;
                            case 2:
                                eliminar_estudante(pessoas, &num_pessoas);
                                break;
                            case 3:
                                pesquisar_estudante(pessoas, num_pessoas);
                                break;
                            case 4:
                                listar_estudantes(pessoas, num_pessoas);

                                break;
                            case 5:
                                listar_estudantes_por_apelido(pessoas, num_pessoas);
                                break;
                            case 6:
                                listar_por_nacionalidade(pessoas, num_pessoas);
                                break;
                            case 7:
                                listar_por_faixa_etaria(pessoas, num_pessoas);
                                break;
                            case 8:
                                break;
                            default:
                                printf("\nOpcao invalida.\n");
                                break;
                    }
                        break;
                    case 2:
                            media_matriculas(pessoas, num_pessoas);
                            break;
                    case 3:
                            contar_finalistas( pessoas, num_pessoas);
                            break;
                    case 4:
                            media_idade_por_nacionalidade(pessoas, num_pessoas);
                            break;
                    case 5:
                            estudantes_em_risco(pessoas, num_pessoas);
                            break;
                    case 6:
                            listar_estudantes_domingo(pessoas, num_pessoas, &ano_referencia);
                            break;
                    case 7:
                            aniversarios_na_quaresma(pessoas, num_pessoas, &ano_referencia);
                            break;

                    case 8:
                            atualizar_dados_pessoais(pessoas, &num_pessoas);
                            atualizar_dados_academicos(pessoas, &num_pessoas);
                            printf("\nSaindo do programa.\n");
                            return;
                    default:
                        printf("\nOpcao invalida.\n");
                        break;
                }
            } while (opcao != 8);
        }
    }
    return 0;
}

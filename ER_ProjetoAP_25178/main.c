#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

char tecla;
int opcao;

int main()
{
    Pessoa pessoas[MAX_PESSOAS];
    int num_pessoas = 0;

    ler_pessoas(pessoas, &num_pessoas);
    ler_info_academica(pessoas, &num_pessoas);

    while (1)
    {
        do
        {
            printf(" ___________________________________________________________\n");
            printf("|                   Gestao de Estudantes                    |\n");
            printf("|                                                           |\n");
            printf("| 1. Gerir Estudantes                                       |\n");
            printf("| 2. Numero Medio de Matriculas                             |\n");
            printf("| 3. Numero de Estudantes Finalistas                        |\n");
            printf("| 4. Media das Idades por Nacionalidade                     |\n");
            printf("| 5. Estudantes em Risco de Prescrever                      |\n");
            printf("| 6. Estudantes que nasceram num determinado dia da semana  |\n");
            printf("| 7. Estudantes com aniversario num Domingo                 |\n");
            printf("| 8. Gerar consulta do tipo Infra                           |\n");
            printf("| 9. Sair                                                   |\n");
            printf("|___________________________________________________________|\n");

            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                printf("\nA Entrar No Submenu Estudantes...\n");
                printf(" ________________________________________________________\n");
                printf("|                      SubMenu Estudantes                |\n");
                printf("|                                                        |\n");
                printf("| 1. Adicionar Estudante                                 |\n");
                printf("| 2. Remover Estudante                                   |\n");
                printf("| 3. Atualizar Estudante                                 |\n");
                printf("| 4. Pesquisar Estudante                                 |\n");
                printf("| 5. Listar todos os Estudantes                          |\n");
                printf("| 6. Listar Estudantes Ordem Alfabetica Apelido          |\n");
                printf("| 7. Listar Estudantes de uma Nacionalidade              |\n");
                printf("| 8. Listar Estudantes numa Faixa Etaria                 |\n");
                printf("| 9. Retornar                                            |\n");
                printf("|________________________________________________________|\n");
                int r;
                scanf("%d", &r);
                switch (r)
                {
                case 1:
                    adicionar_estudante(pessoas, &num_pessoas);
                    break;
                case 2:
                    eliminar_estudante(pessoas, &num_pessoas);
                    break;
                case 3:
                    alterar_estudante(pessoas, num_pessoas);
                    break;
                case 4:
                    pesquisar_estudante(pessoas, num_pessoas);
                    break;
                case 5:
                    listar_estudantes(pessoas, num_pessoas);
                    break;
                case 6:
                    listar_estudantes_por_apelido(pessoas, num_pessoas);
                    break;
                case 7:
                    listar_por_nacionalidade(pessoas, num_pessoas);
                    break;
                case 8:
                    listar_por_faixa_etaria(pessoas, num_pessoas);
                    break;
                case 9:
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
                contar_finalistas(pessoas, num_pessoas);
                break;
            case 4:
                media_idade_por_nacionalidade(pessoas, num_pessoas);
                break;
            case 5:
                listar_estudantes_em_risco(pessoas, num_pessoas);
                break;
            case 6:
                listar_estudantes_dia_semana(pessoas, num_pessoas);
                break;
            case 7:
                listar_estudantes_domingo(pessoas, num_pessoas);
                break;
            case 8:
                listar_estudantes_media_ano(pessoas, num_pessoas);
                break;
            case 9:
                escrever_estudantes(pessoas, num_pessoas);
                escrever_info_academica(pessoas, num_pessoas);
                exportar_csv(pessoas, num_pessoas);
                printf("\nA sair do programa.\n");
                return 0;
            default:
                printf("\nOpcao invalida.\n");
                break;
            }
        } while (opcao != 8);
    }
    return 0;
}

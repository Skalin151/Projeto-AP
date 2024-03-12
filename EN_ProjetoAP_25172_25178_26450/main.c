#include <stdio.h>
#include "Funcoes.h"
#include "Estruturas.h"

#define MAX_LUGARES 1500
#define BUFFER_SIZE 255

int main() {

    srand(time(NULL));

    struct Cliente clientes[MAX_ENTRIES];
    struct Entradas dadosent[MAX_ENTRIES];
    struct LugarEstacionamento dadosest[MAX_ENTRIES];
    struct EntradaseSaidas saida [MAX_ENTRIES];

    int num_dadosent = 0;
    int num_dadosest = 0;
    int num_clientes = 0;
    int num_entradas = 0;
    int num_saidas = 0;
    int num_EntradaseSaidas = 0;
    int lugaresLivres = 0;
    int lugaresOcupados = 0;
    char tecla;
    int opcao;

    carregarClientes(clientes, &num_clientes);

    lerentradas(dadosent, &num_dadosent, dadosest, &num_dadosest);
    lerEntradaseSaidas(saida, &num_EntradaseSaidas);

    while (1) {
        printf("\nPressione 'M' para exibir o menu: ");
        tecla = getchar();
        getchar();

        if (tecla == 'M' || tecla == 'm') {
            do {
                printf(" ________________________________________________________\n");
                printf("|                     Estacionamento                     |\n");
                printf("|                                                        |\n");
                printf("| 1. Gerenciar Clientes e Veiculos                       |\n"); //----FEITO----
                printf("| 2. Entrada e saida de Veiculos                         |\n"); //Pereira
                printf("| 3. Informacoes de Ocupacao                             |\n"); //----FEITO----
                printf("| 4. Mapa de Ocupacao                                    |\n"); //----FEITO----
                printf("| 5. Listar Saidas e Valor Pago por Dia                  |\n"); //Pereira
                printf("| 6. Listar Clientes com Subscricao (Ordem Alfabetica)   |\n"); // ----FEITO----
                printf("| 7. Sair                                                |\n");
                printf("|________________________________________________________|\n");

                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("\nA Entrar No Submenu de Gerenciar Clientes e Veiculos...\n");
                        printf(" ________________________________________________________\n");
                        printf("|                      Menu clientes                     |\n");
                        printf("|                                                        |\n");
                        printf("| 1. Adicionar cliente                                   |\n");
                        printf("| 2. Retirar cliente                                     |\n");
                        printf("| 3. Alterar os dados de um cliente                      |\n");
                        printf("| 4. Mostrar todos os clientes                           |\n");
                        printf("| 5. Atualizar Clientes                                  |\n");
                        printf("| 6. Data final de subscricao de cada cliente            |\n");
                        printf("| 7. Retornar                                            |\n");
                        printf("|________________________________________________________|\n");
                        int r;
                        scanf("%d", &r);
                        switch (r) {
                            case 1:
                                addCliente(clientes, &num_clientes);
                                break;
                            case 2:
                                removerCliente(clientes, &num_clientes);
                                break;
                            case 3:
                                alterarCliente(clientes, &num_clientes);
                                break;
                            case 4:
                                mostrarClientes(clientes, num_clientes);
                                break;
                            case 5:
                                atualizarClientes(clientes, num_clientes);
                                break;
                            case 6:
                                mostrarDataFinalSubscricao(clientes, num_clientes);
                                break;
                            case 7:
                                // Retorna para o menu principal
                                break;
                            default:
                                printf("\nOpcao invalida.\n");
                                break;
                        }
                        break;
                    case 2:
                        printf("\nA Entrar No Submenu De Entrada e Saida De Veiculos...\n");
                        printf(" ________________________________________________________\n");
                        printf("|                      Menu Veiculos                     |\n");
                        printf("|                                                        |\n");
                        printf("| 1. Registas entradas                                   |\n");
                        printf("| 2. Registar saidas                                     |\n");
                        printf("| 3. Mostrar entradas                                    |\n");
                        printf("| 4. Mostrar saidas                                      |\n");
                        printf("| 5. Retornar                                            |\n");
                        printf("|________________________________________________________|\n");
                        int t;
                        scanf("%d", &t);
                        switch (t) {
                            case 1:
                                adicionarEntrada(dadosent, &num_dadosent, dadosest, &num_dadosest);
                                //atualizarEntradas(dadosent, num_dadosent, dadosest, num_dadosest);
                                break;
                            case 2:
                                registrarSaida(dadosent, &num_dadosent, saida, &num_saidas);
                                //atualizarEntradasSaidas(dadosent, num_dadosent, saida, num_saidas);
                                break;
                            case 3:
                                printf("Deseja atualizar as entradas? (1 - Sim / 0 - Nao): ");
                                int resposta;
                                scanf("%d", &resposta);

                                if (resposta == 1) {
                                    printf("=======ENTRADAS ATUALIZADAS=======\n\n\n");
                                    atualizarEntradas(dadosent, num_dadosent, dadosest, num_dadosest);
                                    mostrarEntradas(dadosent, num_dadosent, dadosest, num_dadosest);
                                    printf("==================================\n\n\n");
                                } else {
                                    printf("=======ENTRADAS NAO ATUALIZADAS=======\n\n\n");
                                    mostrarEntradas(dadosent, num_dadosent, dadosest, num_dadosest);
                                    printf("======================================\n\n\n");
                                }
                                break;
                            case 4:
                                printf("Deseja atualizar as entradas e saidas? (1 - Sim / 0 - Nao): ");
                                int resposta1;
                                scanf("%d", &resposta1);

                                if (resposta1 == 1) {
                                    printf("=======SAIDAS ATUALIZADAS=======\n\n\n");
                                    atualizarEntradasSaidas(dadosent, num_dadosent, saida, num_saidas);
                                    mostrarSaidas(saida, num_saidas);
                                    printf("================================\n\n\n");
                                } else {
                                    printf("=======SAIDAS NAO ATUALIZADAS=======\n\n\n");
                                    mostrarSaidas(saida, num_saidas);
                                    printf("====================================\n\n\n");
                                }
                                break;

                            case 5:
                                return;
                            default:
                                printf("\nOpcao invalida.\n");
                                break;
                        }
                        break;
                    case 3:
                            lugaresLivres = MAX_LUGARES - num_dadosest;
                            printf("Lugares livres: %d\n", lugaresLivres);

                            for (int i = 0; i < num_dadosest; i++) {
                                printf("Matricula: %s - Lugar: Piso %d, Linha %c, Coluna %d\n",
                                       dadosent[i].matriculas,
                                       dadosest[i].piso,
                                       dadosest[i].linha,
                                       dadosest[i].coluna);
                            }
                            break;
                    case 4:
                            desenharMapa(dadosest, &num_dadosest);
                            break;
                    case 5:
                            calculo_final(saida, &num_EntradaseSaidas,clientes, num_clientes);
                            printf("\nAcima estao os pagamentos todos\n\n");
                            consulta_pagamento(saida, &num_EntradaseSaidas);
                            break;
                    case 6:
                            mostrarClientesOrdenados(clientes, num_clientes);
                            break;
                    case 7:
                            printf("\nSaindo do programa.\n");
                            atualizarClientes(clientes, num_clientes);
                            atualizarEntradas(dadosent, num_dadosent, dadosest, num_dadosest);
                            atualizarEntradasSaidas(dadosent, num_dadosent, saida, num_saidas);
                            return;
                    default:
                        printf("\nOpcao invalida.\n");
                        break;
                }
            } while (opcao != 7);//Continua o loop enquanto a opção não for 7
        }
    }

    return 0;
}

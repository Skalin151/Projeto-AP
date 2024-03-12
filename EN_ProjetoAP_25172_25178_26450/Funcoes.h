#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Estruturas.h"

#define BUFFER_SIZE2 255

#define MAX_CHAR 100
#define MAX_CLIENTES 100
#define MAX_ENTRIES 1500

#define T1 0.6  // Tarifa por 15 minutos das 8h00 às 22h00
#define T2 0.2  // Tarifa por 15 minutos das 22h00 às 8h00
#define T3 8.0   // Tarifa para o dia completo
#define T4 75.0 // Subscrição

void mostrarClientesOrdenados(struct Cliente clientes[], int num_clientes);
//void desenharMapa(struct EntradasESaidas entradas,*num_entradas);

void lerentradas(struct Entradas entradas[], int *num_entradas, struct LugarEstacionamento lugares[], int *totalLugares) {
    FILE *file = fopen("entradas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    *num_entradas = 0;
    *totalLugares = 0;

    while (*num_entradas < MAX_ENTRIES &&
           fscanf(file, "%s %d %d %d %d %d %1d%1[A-T]%2d ",
                  &entradas[*num_entradas].matriculas,
                  &entradas[*num_entradas].data_entrada.ano,
                  &entradas[*num_entradas].data_entrada.mes,
                  &entradas[*num_entradas].data_entrada.dia,
                  &entradas[*num_entradas].hora,
                  &entradas[*num_entradas].min,
                  &lugares[*totalLugares].piso,
                  &lugares[*totalLugares].linha,
                  &lugares[*totalLugares].coluna) == 9) {
        (*num_entradas)++;
        (*totalLugares)++;
    }
    fclose(file);
}

void lerEntradaseSaidas(struct EntradaseSaidas entsaida[], int *num_EntradaseSaidas){
    FILE *file = fopen("entradas_e_saidas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    *num_EntradaseSaidas = 0;

    while(*num_EntradaseSaidas < MAX_ENTRIES &&
          fscanf(file,"%s   %d %d %d %d %d %d %d %d %d %d ",
                 &entsaida[*num_EntradaseSaidas].matriculas,
                 &entsaida[*num_EntradaseSaidas].data_entrada.ano,
                 &entsaida[*num_EntradaseSaidas].data_entrada.mes,
                 &entsaida[*num_EntradaseSaidas].data_entrada.dia,
                 &entsaida[*num_EntradaseSaidas].horaent,
                 &entsaida[*num_EntradaseSaidas].minent,
                 &entsaida[*num_EntradaseSaidas].data_saida.ano,
                 &entsaida[*num_EntradaseSaidas].data_saida.mes,
                 &entsaida[*num_EntradaseSaidas].data_saida.dia,
                 &entsaida[*num_EntradaseSaidas].horasaida,
                 &entsaida[*num_EntradaseSaidas].minsaida) ==11) {
        (*num_EntradaseSaidas)++;
    }
    fclose(file);
}

void carregarClientes(struct Cliente clientes[], int *num_clientes) {
    FILE *file;
    file = fopen("clientes.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo clientes.txt\n");
        return;
    }

    while (*num_clientes < MAX_CLIENTES &&
           fscanf(file, "%s %49[^\t] %s %d %d %d %d",
                  clientes[*num_clientes].matricula,
                  clientes[*num_clientes].nome,
                  clientes[*num_clientes].cod_postal,
                  &clientes[*num_clientes].NIF,
                  &clientes[*num_clientes].data_inscricao.ano,
                  &clientes[*num_clientes].data_inscricao.mes,
                  &clientes[*num_clientes].data_inscricao.dia) == 7) {
        clientes[*num_clientes].id_cliente = *num_clientes + 1;
        (*num_clientes)++;
    }

    fclose(file);
}

void mostrarClientes(struct Cliente clientes[], int num_clientes) {
    if (num_clientes == 0) {
        printf("Nao existem clientes para mostrar.\n");
        return;
    }

    printf("\nCLIENTES\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < num_clientes; i++) {
            if (clientes[i].id_cliente != 0) {
                printf("ID Cliente: %d\nMatricula: %s\nNome: %s\nCodigo Postal: %s\nNIF: %d\nData Inscricao: %d/%d/%d\n",
                clientes[i].id_cliente,
                clientes[i].matricula,
                clientes[i].nome,
                clientes[i].cod_postal,
                clientes[i].NIF,
                clientes[i].data_inscricao.ano,
                clientes[i].data_inscricao.mes,
                clientes[i].data_inscricao.dia);
        printf("-------------------------------------------------------------\n");
        }
    }
}

int compararClientes(const void *a, const void *b) {
    struct Cliente *clienteA = (struct Cliente *)a;
    struct Cliente *clienteB = (struct Cliente *)b;
    return strcmp(clienteA->nome, clienteB->nome);
}

void mostrarClientesOrdenados(struct Cliente clientes[], int num_clientes) {
    // Criar uma cópia de clientes e ordená-la
    struct Cliente *clientes_ordenados = malloc(num_clientes * sizeof(struct Cliente));
    memcpy(clientes_ordenados, clientes, num_clientes * sizeof(struct Cliente));

    // Ordenar a cópia da estrutura
    qsort(clientes_ordenados, num_clientes, sizeof(struct Cliente), compararClientes);

    printf("\nCLIENTES\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < num_clientes; i++) {
        printf("ID Cliente: %d\nNome: %s\n",
               clientes_ordenados[i].id_cliente,
               clientes_ordenados[i].nome);
        printf("-------------------------------------------------------------\n");
    }

    // Liberar a memória alocada para a cópia
    free(clientes_ordenados);
}

void adicionarUmAno(struct Cliente *cliente) {
    cliente->data_inscricao.ano += 1;
}

void mostrarDataFinalSubscricao(struct Cliente *clientes, int num_clientes) {
    printf("\nCLIENTES\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_cliente != 0) {
            // Adiciona 1 ao ano de inscrição (validade de 1 ano)
            adicionarUmAno(&clientes[i]);

            // mostra os detalhes do cliente com a nova data (+1 ano)
            printf("ID Cliente: %d\nNome: %s\nData final de subscricao: %d/%d/%d\n",
                   clientes[i].id_cliente,
                   clientes[i].nome,
                   clientes[i].data_inscricao.ano,
                   clientes[i].data_inscricao.mes,
                   clientes[i].data_inscricao.dia);
            printf("-------------------------------------------------------------\n");
        }
    }
}

void addCliente(struct Cliente clientes[], int *num_clientes) {
    if (*num_clientes >= MAX_CLIENTES) {
        printf("Limite maximo de clientes atingido.\n");
        return;
    }

    printf("Digite os dados do cliente:\n");

    // Pede ao utilizador os dados do cliente
    printf("Matricula: ");
    scanf("%s", clientes[*num_clientes].matricula);
    getchar();

    printf("Nome: ");
    scanf(" %49[^\n]", clientes[*num_clientes].nome);

    printf("Codigo Postal: ");
    scanf("%s", clientes[*num_clientes].cod_postal);

    printf("NIF: ");
    scanf("%d", &clientes[*num_clientes].NIF);

    printf("Data de inscricao (ano mes dia): ");
    scanf("%d %d %d", &clientes[*num_clientes].data_inscricao.ano,
          &clientes[*num_clientes].data_inscricao.mes,
          &clientes[*num_clientes].data_inscricao.dia);

    // Incrementa o ID do cliente
    clientes[*num_clientes].id_cliente = *num_clientes + 1;

    // Incrementa o número de clientes
    (*num_clientes)++;
    printf("Cliente adicionado na memoria com sucesso.\n");
}

void removerCliente(struct Cliente clientes[], int *num_clientes) {
    if (*num_clientes == 0) {
        printf("Não existem clientes para remover.\n");
        return;
    }

    printf("Clientes existentes:\n");
    for (int i = 0; i < *num_clientes; i++) {
        printf("ID: %d\tNome: %s\n", clientes[i].id_cliente, clientes[i].nome);
    }

    printf("Existem %d clientes. Escolha o ID do cliente para remover (de 1 a %d): ", *num_clientes, *num_clientes);

    int id_cliente;

    // Verifica se a leitura do ID do cliente correu bem e está dentro do intervalo válido
    while (scanf("%d", &id_cliente) != 1 || id_cliente < 1 || id_cliente > *num_clientes) {
        printf("Insira um numero válido (de 1 a %d): ", *num_clientes);

        // Limpa o buffer de entrada para evitar loops infinitos
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    int indice = -1;

    // Procura o cliente pelo id_cliente
    for (int i = 0; i < *num_clientes; i++) {
        if (clientes[i].id_cliente == id_cliente) {
            indice = i;
            break;
        }
    }

    // Se o cliente for encontrado, remove-o da memória
    if (indice != -1) {
        // Move os clientes à fremte uma posição para trás na memória
        for (int i = indice; i < *num_clientes - 1; i++) {
            clientes[i] = clientes[i + 1];
        }

        // Decrementa o número de clientes
        (*num_clientes)--;
        printf("Cliente removido da memoria com sucesso.\n");
    } else {
        printf("Cliente com ID %d nao encontrado.\n", id_cliente);
    }
}

void alterarCliente(struct Cliente clientes[], int *num_clientes) {
    if (*num_clientes == 0) {
        printf("Nao existem clientes para alterar.\n");
        return;
    }

    printf("Clientes existentes:\n");
    for (int i = 0; i < *num_clientes; i++) {
        printf("ID: %d\tNome: %s\n", clientes[i].id_cliente, clientes[i].nome);
    }

    printf("Existem %d clientes. Escolha o ID do cliente para alterar (de 1 a %d): ", *num_clientes, *num_clientes);

    int id_cliente;

    // Verifica se a leitura do ID do cliente correu bem e está dentro do intervalo válido
    while (scanf("%d", &id_cliente) != 1 || id_cliente < 1 || id_cliente > *num_clientes) {
        printf("Insira um numero valido (de 1 a %d): ", *num_clientes);

        // Limpa o buffer de entrada para evitar loops infinitos
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Encontrar o índice do cliente com base no ID fornecido
    int indice = -1;
    for (int i = 0; i < *num_clientes; i++) {
        if (clientes[i].id_cliente == id_cliente) {
            indice = i;
            break;
        }
    }

    // Verificar se o cliente foi encontrado
    if (indice != -1) {
        // mostrar os dados do cliente selecionado
        printf("\nDados do Cliente ID %d:\n", id_cliente);
        printf("Nome: %s\n", clientes[indice].nome);

        // alterar os dados do cliente
        printf("\nDigite os novos dados do cliente:\n");

        printf("Novo Nome: ");
        scanf(" %49[^\n]", clientes[indice].nome);

        printf("Novo Codigo Postal: ");
        scanf("%s", clientes[indice].cod_postal);

        printf("Novo NIF: ");
        scanf("%d", &clientes[indice].NIF);

        printf("Novo ano de inscricao: ");
        scanf("%d", &clientes[indice].data_inscricao.ano);

        printf("Cliente alterado na memoria com sucesso.\n");
    } else {
        printf("Cliente com ID %d nao encontrado.\n", id_cliente);
    }
}

//Atualiza o Bloco de notas clientes.txt
void atualizarClientes(struct Cliente clientes[], int num_clientes) {
    // Abre o arquivo em modo de escrita (apaga tudo e escreve desde o inicio)
    FILE *file;
    file = fopen("clientes.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo clientes.txt\n");
        return;
    }

    // Escreve os dados dos clientes no arquivo
    for (int i = 0; i < num_clientes; i++) {
        fprintf(file, "%s\t%s\t%s\t%d\t%d\t%d\t%d\n",
                clientes[i].matricula,
                clientes[i].nome,
                clientes[i].cod_postal,
                clientes[i].NIF,
                clientes[i].data_inscricao.ano,
                clientes[i].data_inscricao.mes,
                clientes[i].data_inscricao.dia);
    }

    // Fecha o arquivo
    fclose(file);
    printf("Clientes atualizados no arquivo clientes.txt.\n");
}

void gerarSequenciaAleatoria(char *sequencia) {
    do {
        // número aleatório de 1 a 3
        int num1 = rand() % 3 + 1;

        // letra aleatória de A a T
        char letra = 'A' + rand() % 20;

        // número aleatório de 1 a 25
        int num2 = rand() % 25 + 1;

        // Formata a sequência
        sprintf(sequencia, "%d%c%02d", num1, letra, num2);
    } while (sequenciaJaExistente(sequencia));
}

int sequenciaJaExistente(const char *sequencia) {
    FILE *arquivo = fopen("entradas.txt", "r");
    char linha[20];

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Verifica se a sequência já existe
        if (strstr(linha, sequencia) != NULL) {
            fclose(arquivo);
            return 1; // Sequência já existe
        }
    }

    fclose(arquivo);
    return 0; // Sequência não existe
}

void adicionarEntrada(struct Entradas entradas[], int *num_entradas, struct LugarEstacionamento lugares[], int *totalLugares) {
    // Lê entradas existentes do arquivo para a memória
    lerentradas(entradas, num_entradas, lugares, totalLugares);

    char matricula[MAX_MATRICULA_LENGTH];
    int ano, mes, dia, hora, min;

    printf("Insira a matricula do carro que entrou: ");
    scanf("%s", matricula);

    // Gera a sequência aleatória (sem repetições)
    char sequencia[5];
    gerarSequenciaAleatoria(sequencia);

    // Pede ao usuário inserir o ano, mês, dia, hora e minutos
    printf("Insira o ano, mes, dia, hora e minutos (formato AAAA MM DD HH MM): ");
    scanf("%d %d %d %d %d", &ano, &mes, &dia, &hora, &min);

    // Adiciona a nova entrada a entradas
    strcpy(entradas[*num_entradas].matriculas, matricula);
    entradas[*num_entradas].data_entrada.ano = ano;
    entradas[*num_entradas].data_entrada.mes = mes;
    entradas[*num_entradas].data_entrada.dia = dia;
    entradas[*num_entradas].hora = hora;
    entradas[*num_entradas].min = min;

    // Adiciona o lugar de estacionamento a lugares
    lugares[*totalLugares].piso = rand() % 3 + 1; // exemplo: gera um número aleatório entre 1 e 3 para o piso
    lugares[*totalLugares].linha = 'A' + rand() % 5; // exemplo: gera uma letra aleatória de A a E para a linha
    lugares[*totalLugares].coluna = rand() % 10 + 1; // exemplo: gera um número aleatório entre 1 e 10 para a coluna

    (*num_entradas)++;
    (*totalLugares)++;

    // Atualiza o arquivo com todas as entradas
    printf("Foi adicionada a entrada com sucesso.\n");
}

void atualizarEntradas(struct Entradas entradas[], int num_entradas, struct LugarEstacionamento lugares[], int totalLugares) {
    // Abre o arquivo em modo de escrita (apaga tudo e escreve desde o início)
    FILE *file;
    file = fopen("entradas.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo entradas.txt\n");
        return;
    }

    // Escreve os dados de entradas e lugares no arquivo
    for (int i = 0; i < num_entradas; i++) {
        fprintf(file, "%s %d %d %d %d %d %d%c%d\n",
                entradas[i].matriculas,
                entradas[i].data_entrada.ano,
                entradas[i].data_entrada.mes,
                entradas[i].data_entrada.dia,
                entradas[i].hora,
                entradas[i].min,
                lugares[i].piso,
                lugares[i].linha,
                lugares[i].coluna);
    }

    fclose(file);
    printf("Entradas atualizadas no arquivo entradas.txt.\n");
}

void registrarSaida(struct Entradas entradas[], int *num_entradas, struct EntradaseSaidas saidas[], int *num_saidas) {
    char matricula[MAX_MATRICULA_LENGTH];
    int ano, mes, dia, hora, min;

    printf("Insira a matricula do carro que saiu: ");
    scanf("%s", matricula);

    // Procura a entrada na estrutura de entradas
    int indice_entrada = -1;
    for (int i = 0; i < *num_entradas; i++) {
        if (strcmp(entradas[i].matriculas, matricula) == 0) {
            indice_entrada = i;
            break;
        }
    }

    if (indice_entrada == -1) {
        printf("Veículo não encontrado na lista de entradas.\n");
        return;
    }

    printf("Insira o ano, mes, dia, hora e minutos (formato AAAA MM DD HH MM): ");
    scanf("%d %d %d %d %d", &ano, &mes, &dia, &hora, &min);

    // Adiciona a nova saída ao array de saídas
    strcpy(saidas[*num_saidas].matriculas, matricula);
    saidas[*num_saidas].data_entrada = entradas[indice_entrada].data_entrada;
    saidas[*num_saidas].horaent = entradas[indice_entrada].hora;
    saidas[*num_saidas].minent = entradas[indice_entrada].min;
    saidas[*num_saidas].data_saida.ano = ano;
    saidas[*num_saidas].data_saida.mes = mes;
    saidas[*num_saidas].data_saida.dia = dia;
    saidas[*num_saidas].horasaida = hora;
    saidas[*num_saidas].minsaida = min;

    // Remove a linha correspondente ao carro que saiu do arquivo "entradas.txt"
    removerLinha("entradas.txt", matricula);

    (*num_saidas)++;
    printf("Saída registrada com sucesso.\n");
}

void atualizarEntradasSaidas(struct Entradas entradas[], int num_entradas, struct EntradaseSaidas saidas[], int num_saidas) {
    FILE *file;
    file = fopen("entradas_e_saidas.txt", "a"); //Continua a escrever com o "a"

    if (file == NULL) {
        printf("Erro ao abrir o arquivo entradas_e_saidas.txt\n");
        return;
    }

    for (int j = 0; j < num_saidas; j++) {
        int indice_entrada = -1;
        for (int i = 0; i < num_entradas; i++) {
            if (strcmp(entradas[i].matriculas, saidas[j].matriculas) == 0) {
                indice_entrada = i;
                break;
            }
        }

        if (indice_entrada != -1) {
            fprintf(file, "%s %d %d %d %d %d %d %d %d %d %d\n",
                    saidas[j].matriculas,
                    entradas[indice_entrada].data_entrada.ano,
                    entradas[indice_entrada].data_entrada.mes,
                    entradas[indice_entrada].data_entrada.dia,
                    entradas[indice_entrada].hora,
                    entradas[indice_entrada].min,
                    saidas[j].data_saida.ano,
                    saidas[j].data_saida.mes,
                    saidas[j].data_saida.dia,
                    saidas[j].horasaida,
                    saidas[j].minsaida);

            // REMOVER LINHA DO ENTRADAS.TXT
        }
    }

    fclose(file);
    printf("Entradas e saídas atualizadas no arquivo entradas_e_saidas.txt.\n");
}

void mostrarEntradas(struct Entradas entradas[], int num_entradas, struct LugarEstacionamento lugares[], int totalLugares) {
    printf("===== ENTRADAS =====\n");
    for (int i = 0; i < num_entradas; i++) {
        printf("Matricula: %s\n", entradas[i].matriculas);
        printf("Data de Entrada: %d/%d/%d %02d:%02d\n",
               entradas[i].data_entrada.dia, entradas[i].data_entrada.mes, entradas[i].data_entrada.ano,
               entradas[i].hora, entradas[i].min);
        printf("Lugar de Estacionamento: Piso %d, Linha %c, Coluna %d\n",
               lugares[i].piso, lugares[i].linha, lugares[i].coluna);
        printf("---------------------\n");
    }
    printf("Total de Entradas: %d\n", num_entradas);
}

void mostrarSaidas(struct EntradaseSaidas saidas[], int num_saidas) {
    printf("===== SAIDAS =====\n");
    for (int i = 0; i < num_saidas; i++) {
        printf("Matricula: %s\n", saidas[i].matriculas);
        printf("Data de Entrada: %d/%d/%d %02d:%02d\n",
               saidas[i].data_entrada.dia, saidas[i].data_entrada.mes, saidas[i].data_entrada.ano,
               saidas[i].horaent, saidas[i].minent);
        printf("Data de Saida: %d/%d/%d %02d:%02d\n",
               saidas[i].data_saida.dia, saidas[i].data_saida.mes, saidas[i].data_saida.ano,
               saidas[i].horasaida, saidas[i].minsaida);
        printf("---------------------\n");
        printf("\n");
    }
    printf("Total de Saidas: %d\n", num_saidas);
}

void removerLinha(const char *arquivo, const char *matricula) {
    FILE *tempFile;
    FILE *file;
    char buffer[1000];

    tempFile = fopen("temp.txt", "w");
    file = fopen(arquivo, "r");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, matricula) == NULL) {
            fputs(buffer, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(arquivo);
    rename("temp.txt", arquivo);
}

// Função para desenhar o mapa do piso e ler os dados do arquivo
void desenharMapa(struct LugarEstacionamento lugares[], int *totalLugares) {
    int i, j, piso;

    // A desenhar o mapa para cada piso
    for (piso = 1; piso <= 3; piso++) {
        printf("Mapa do Piso %d:\n", piso);

        // Inicializa a matriz do mapa com espaços vazios
        char mapa[20][25];
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 25; j++) {
                mapa[i][j] = '|';
            }
        }

        // Preencher o mapa com as informações dos lugares de estacionamento
        for (int k = 0; k < *totalLugares; k++) {
            struct LugarEstacionamento lugar = lugares[k];

            // Verificar se o piso é o mesmo
            if (lugar.piso == piso) {
                int linha = lugar.linha - 'A';
                int coluna = lugar.coluna - 1;
                mapa[linha][coluna] = 'X';
            }
        }

        // mostrar mapa
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 25; j++) {
                printf("%c ", mapa[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


void calculo_final(struct EntradaseSaidas entsaida[], int *num_EntradaseSaidas, struct Cliente clientes[], int num_clientes) {
    FILE *pagamentos = fopen("Pagamentos.txt", "w");
    if (pagamentos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < *num_EntradaseSaidas; i++) {
        // Verifica se a matricula esta na lista de clientes
        int matricula_encontrada = 0;
        for (int j = 0; j < num_clientes; j++) {
            if (strcmp(entsaida[i].matriculas, clientes[j].matricula) == 0) {
                matricula_encontrada = 1;
                break;
            }
        }

        if (matricula_encontrada) {
            // Se a matricula for encontrada o custo deverá ser igual a 0
            printf("Matricula: %s Custo total: 0.0 (O cliente esta exento)\n", entsaida[i].matriculas);
            fprintf(pagamentos, "Matricula: %s Custo total: 0.0 (O cliente esta exento)\n", entsaida[i].matriculas);
        } else {
            // Arredonda para cima o tempo de entrada para o próximo intervalo de 15 minutos
            if (fmod(entsaida[i].minent, 15.0) > 0) {
                entsaida[i].minent = ((int) (entsaida[i].minent / 15) + 1) * 15;
                if (entsaida[i].minent >= 60.0) {
                    entsaida[i].minent -= 60.0;
                    entsaida[i].horaent++;
                }
            }

            // Arredonda para cima o tempo de saída para o próximo intervalo de 15 minutos
            if (fmod(entsaida[i].minsaida, 15.0) > 0) {
                entsaida[i].minsaida = ((int) (entsaida[i].minsaida / 15) + 1) * 15;
                if (entsaida[i].minsaida >= 60.0) {
                    entsaida[i].minsaida -= 60.0;
                    entsaida[i].horasaida++;
                }
            }

            // Cálculo do custo total para o estacionamento
            float custo_total = 0.0;

            // Cálculo para minutos de entrada até minutos de saída
            while (entsaida[i].horaent != entsaida[i].horasaida || entsaida[i].minent != entsaida[i].minsaida) {
                if (entsaida[i].horaent >= 8.0 && entsaida[i].horaent < 22.0) {
                    custo_total += T1 / 4.0;
                } else {
                    custo_total += T2 / 4.0;
                }

                entsaida[i].minent += 15.0;

                if (entsaida[i].minent >= 60.0) {
                    entsaida[i].minent -= 60.0;
                    entsaida[i].horaent += 1.0;
                }

                if (entsaida[i].horaent >= 24.0) {
                    entsaida[i].horaent -= 24.0;
                }
            }

            // Limita o custo total a T3 se ultrapassar
            if (custo_total > T3) {
                custo_total = T3;
            }

            float dias_estacionado = entsaida[i].data_saida.dia - entsaida[i].data_entrada.dia;

            // Imprime e escreve no arquivo de pagamentos
            printf("Matricula: %s Custo total: %.2f\n", entsaida[i].matriculas, custo_total + (8.0 * dias_estacionado));
            fprintf(pagamentos, "Matricula: %s Custo total: %.2f\n", entsaida[i].matriculas,
                    custo_total + (8.0 * dias_estacionado));
        }
    }

    // Fecha os arquivos
    fclose(pagamentos);
}
void consulta_pagamento(struct EntradaseSaidas entsaida[], int *num_EntradaseSaidas) {

    int ano_consulta, mes_consulta, dia_consulta;
    printf("Digite a data de consulta (AAAA MM DD): ");
    scanf("%d %d %d", &ano_consulta, &mes_consulta, &dia_consulta);

    float custo_total;

    printf("Carros que saíram na data %d-%02d-%02d e valor pago:\n", ano_consulta, mes_consulta, dia_consulta);

    for(int i; i < *num_EntradaseSaidas; i++) {

        if (entsaida[i].data_saida.ano && entsaida[i].data_saida.mes && entsaida[i].data_saida.dia == dia_consulta) {
            custo_total = 0.0;
            float total_horas = 0.0;

            while (entsaida[i].horaent != entsaida[i].horasaida || entsaida[i].minent != entsaida[i].minsaida) {
            if (entsaida[i].horaent >= 8.0 && entsaida[i].horaent < 22.0) {
                custo_total += T1 / 4.0;
            } else {
                custo_total += T2 / 4.0;
            }

            entsaida[i].minent += 15.0;

            if (entsaida[i].minent >= 60.0) {
                entsaida[i].minent -= 60.0;
                entsaida[i].horaent += 1.0;
            }

            if (entsaida[i].horaent >= 24.0) {
                entsaida[i].horaent -= 24.0;
            }
        }

        // Limita o custo total a T3 se ultrapassar
        if (custo_total > T3) {
            custo_total = T3;
        }

            printf("Matricula: %s Custo total: %.2f\n", entsaida[i].matriculas, entsaida[i].custo_total);
        }
    }

}

#endif // FUNCOES_H_INCLUDED

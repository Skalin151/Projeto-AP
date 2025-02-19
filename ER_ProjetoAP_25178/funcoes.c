#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "funcoes.h"

// Ler dados e carregar para estruturas
// Funciona
void ler_pessoas(Pessoa pessoas[], int *num_pessoas)
{
    FILE *file = fopen("Estudantes.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o ficheiro Estudantes.txt.\n");
        return;
    }

    int id, dia, mes, ano;
    char nome[MAX_NOME];
    char nacionalidade[MAX_NACIONALIDADE];

    *num_pessoas = 0;

    while (fscanf(file, "%d\t%49[^\t]\t%d-%d-%d\t%19s",
                  &id, nome, &dia, &mes, &ano, nacionalidade) == 6)
    {
        if (*num_pessoas >= MAX_PESSOAS)
        {
            printf("Numero maximo de pessoas atingido.\n");
            break;
        }

        pessoas[*num_pessoas].id = id;
        strcpy(pessoas[*num_pessoas].nome, nome);
        pessoas[*num_pessoas].data_nascimento.dia = dia;
        pessoas[*num_pessoas].data_nascimento.mes = mes;
        pessoas[*num_pessoas].data_nascimento.ano = ano;
        strcpy(pessoas[*num_pessoas].nacionalidade, nacionalidade);

        (*num_pessoas)++;
    }

    fclose(file);
}

// Funciona
void ler_info_academica(Pessoa pessoas[], int *num_pessoas)
{
    FILE *file = fopen("Situacao_Escolar_Estudante.txt", "r");
    if (!file)
    {
        printf("ERRO: Falha ao abrir Situacao_Escolar_Estudante.txt.\n");
        return;
    }

    int id, num_matriculas, ects, ano_curricular;
    float media_atual;

    while (fscanf(file, "%d%d%d%d%f", &id, &num_matriculas, &ects, &ano_curricular, &media_atual) == 5)
    {
        for (int i = 0; i < *num_pessoas; i++)
        {
            if (pessoas[i].id == id)
            {
                pessoas[i].num_matriculas = num_matriculas;
                pessoas[i].ects = ects;
                pessoas[i].ano_curricular = ano_curricular;
                pessoas[i].media_atual = media_atual;
                break;
            }
        }
    }

    fclose(file);
}

// Funcao principal para adicionar um novo estudante
// Funciona
void adicionar_estudante(Pessoa pessoas[], int *num_pessoas)
{
    if (*num_pessoas >= MAX_PESSOAS)
    {
        printf("Numero maximo de estudantes atingido. Nao e possivel adicionar mais.\n");
        return;
    }

    Pessoa novo_estudante;

    // Atribuir automaticamente o ID
    if (*num_pessoas == 0)
    {
        novo_estudante.id = 1;
    }
    else
    {
        // Encontra o maior ID atual e incrementa 1
        int maior_id = 0;
        for (int i = 0; i < *num_pessoas; i++)
        {
            if (pessoas[i].id > maior_id)
            {
                maior_id = pessoas[i].id;
            }
        }
        novo_estudante.id = maior_id + 1;
    }

    printf("Digite o nome do novo estudante: ");
    scanf(" %[^\n]", novo_estudante.nome);

    printf("Digite a data de nascimento (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &novo_estudante.data_nascimento.dia,
          &novo_estudante.data_nascimento.mes,
          &novo_estudante.data_nascimento.ano);

    printf("Digite a nacionalidade: ");
    scanf(" %[^\n]", novo_estudante.nacionalidade);

    printf("Digite o numero de matriculas: ");
    scanf("%d", &novo_estudante.num_matriculas);

    printf("Digite o numero de ECTS: ");
    scanf("%d", &novo_estudante.ects);

    // Adiciona os novos parâmetros: Ano do Curso e Média Atual
    printf("Digite o ano curricular: ");
    scanf("%d", &novo_estudante.ano_curricular);

    printf("Digite a media atual: ");
    scanf("%f", &novo_estudante.media_atual);

    // Adiciona o novo estudante ao array
    pessoas[*num_pessoas] = novo_estudante;
    (*num_pessoas)++;

    printf("\nFoi adicionado o seguinte aluno: \n");
    imprimir_estudante(novo_estudante);

    escrever_estudantes(pessoas, *num_pessoas);
    escrever_info_academica(pessoas, *num_pessoas);
    exportar_csv(pessoas, *num_pessoas);
}

// Funciona
void eliminar_estudante(Pessoa pessoas[], int *num_pessoas)
{
    int id;
    printf("Insira o ID do estudante a eliminar: ");
    scanf("%d", &id);

    for (int i = 0; i < *num_pessoas; i++)
    {
        if (pessoas[i].id == id)
        {

            printf("\nEstudante encontrado:\n");
            printf("ID: %d\n", pessoas[i].id);
            printf("Nome: %s\n", pessoas[i].nome);
            pessoas[i].data_nascimento.dia,
                pessoas[i].data_nascimento.mes,
                pessoas[i].data_nascimento.ano,
                printf("Nacionalidade: %s\n", pessoas[i].nacionalidade);

            char confirmacao;
            printf("\nDeseja realmente eliminar este estudante? (s/n): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 's' || confirmacao == 'S')
            {
                for (int j = i; j < *num_pessoas - 1; j++)
                {
                    pessoas[j] = pessoas[j + 1];
                }
                (*num_pessoas)--;
                printf("Estudante eliminado com sucesso.\n");

                escrever_estudantes(pessoas, *num_pessoas);
                escrever_info_academica(pessoas, *num_pessoas);
                exportar_csv(pessoas, *num_pessoas);
            }
            else
            {
                printf("Eliminacao cancelada.\n");
            }
            return;
        }
    }
    printf("Estudante nao encontrado.\n");
}

void alterar_estudante(Pessoa pessoas[], int num_pessoas)
{
    int id;
    printf("Insira o ID do estudante a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < num_pessoas; i++)
    {
        if (pessoas[i].id == id)
        {
            // Exibe os dados atuais do estudante
            printf("\n=== Dados Atuais do Estudante ===\n");
            printf("ID: %d\n", pessoas[i].id);
            printf("Nome: %s\n", pessoas[i].nome);
            printf("Data de Nascimento: %02d-%02d-%04d\n", pessoas[i].data_nascimento.dia,
                   pessoas[i].data_nascimento.mes, pessoas[i].data_nascimento.ano);
            printf("Nacionalidade: %s\n", pessoas[i].nacionalidade);
            printf("Numero de Matriculas: %d\n", pessoas[i].num_matriculas);
            printf("ECTS: %d\n", pessoas[i].ects);
            printf("Ano do Curso: %d\n", pessoas[i].ano_curricular);
            printf("Media Atual: %.2f\n", pessoas[i].media_atual);
            printf("===============================\n");

            char confirmacao;
            printf("\nDeseja alterar os dados deste estudante? (s/n): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 's' || confirmacao == 'S')
            {
                printf("\nDigite o novo nome do estudante: ");
                scanf(" %[^\n]", pessoas[i].nome);

                printf("Digite a nova data de nascimento (dd-mm-aaaa): ");
                scanf("%d-%d-%d", &pessoas[i].data_nascimento.dia,
                      &pessoas[i].data_nascimento.mes,
                      &pessoas[i].data_nascimento.ano);

                printf("Digite a nova nacionalidade: ");
                scanf(" %[^\n]", pessoas[i].nacionalidade);

                printf("Digite o novo numero de matriculas: ");
                scanf("%d", &pessoas[i].num_matriculas);

                printf("Digite o novo numero de ECTS: ");
                scanf("%d", &pessoas[i].ects);

                printf("Digite o novo ano do curso: ");
                scanf("%d", &pessoas[i].ano_curricular);

                printf("Digite a nova media atual: ");
                scanf("%f", &pessoas[i].media_atual);

                printf("\nDados do seguinte estudante alterados com sucesso.\n");
                imprimir_estudante(pessoas[i]);

                escrever_estudantes(pessoas, num_pessoas);
                escrever_info_academica(pessoas, num_pessoas);
                exportar_csv(pessoas, num_pessoas);
            }
            else
            {
                printf("\nAlteracao cancelada.\n");
            }
            return;
        }
    }
    printf("\nEstudante nao encontrado.\n");
}

void imprimir_estudante(Pessoa estudante)
{
    printf("-------------------------\n");
    printf("ID: %d | Nome: %s | Data de Nascimento: %d/%d/%d | Nacionalidade: %s\n",
           estudante.id, estudante.nome, estudante.data_nascimento.dia, estudante.data_nascimento.mes, estudante.data_nascimento.ano, estudante.nacionalidade);

    // Verifica se os dados acadêmicos foram inicializados
    if (estudante.num_matriculas == 0 && estudante.ects == 0)
    {
        printf("  Matriculas: Dados não disponíveis | ECTS: Dados não disponíveis\n");
    }
    else
    {
        printf("  Matriculas: %d | ECTS: %d\n", estudante.num_matriculas, estudante.ects);
    }

    printf("  Ano do Curso: %d | Media Atual: %.2f\n\n", estudante.ano_curricular, estudante.media_atual);
}

// Funciona
void pesquisar_estudante(Pessoa pessoas[], int num_pessoas)
{
    char nome_parcial[MAX_NOME];
    printf("Insira parte do nome a pesquisar: ");
    getchar();
    fgets(nome_parcial, MAX_NOME, stdin);
    nome_parcial[strcspn(nome_parcial, "\n")] = 0;

    int encontrados = 0;
    for (int i = 0; i < num_pessoas; i++)
    {
        if (strstr(pessoas[i].nome, nome_parcial) != NULL)
        {
            printf("ID: %d, Nome: %s, Nacionalidade: %s\n",
                   pessoas[i].id, pessoas[i].nome, pessoas[i].nacionalidade);
            encontrados++;
        }
    }
    printf("Total de estudantes encontrados: %d\n", encontrados);
}

// Listar todos os estudantes
// Funciona
void listar_estudantes(Pessoa pessoas[], int num_pessoas)
{
    if (num_pessoas == 0)
    {
        printf("Nenhum estudante inscrito.\n");
        return;
    }

    int pagina = 1;

    printf("Total de estudantes: %d\n", num_pessoas);
    printf("=== Lista de Estudantes ===\n");
    printf("\nA mostrar pagina: %d\n", pagina);
    for (int i = 0; i < num_pessoas; i++)
    {
        if (i >= MAX_PER_PAGE && (i % MAX_PER_PAGE == 0))
        {
            printf("Para seguir para a proxima pagina, selecione p. Para sair pressione q.\n");
            char input;
            scanf(" %c", &input);
            if (input == 'q')
                break;
            pagina++;
            printf("\nA mostrar pagina: %d\n", pagina);
        }
        imprimir_estudante(pessoas[i]);
    }

    printf("Total de estudantes: %d\n", num_pessoas);
}

// Listar estudantes de uma determinada nacionalidade
// Funciona
void listar_por_nacionalidade(Pessoa pessoas[], int num_pessoas)
{
    char *nacionalidades[] = {
        "Angolana",
        "Brasileira",
        "Espanhola",
        "Francesa",
        "Guineense",
        "Italiana",
        "Mocambicana",
        "Portuguesa",
        "Timorense"};
    int num_nacionalidades = sizeof(nacionalidades) / sizeof(nacionalidades[0]);

    printf("Escolha uma nacionalidade pelo numero:\n");
    for (int i = 0; i < num_nacionalidades; i++)
    {
        printf("%d. %s\n", i + 1, nacionalidades[i]);
    }

    int escolha;
    printf("Insira o numero da nacionalidade: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > num_nacionalidades)
    {
        printf("Escolha invalida.\n");
        return;
    }

    char *nacionalidade_escolhida = nacionalidades[escolha - 1];

    int count = 0;
    Pessoa estudantes[num_pessoas];
    for (int i = 0; i < num_pessoas; i++)
    {
        if (strcmp(pessoas[i].nacionalidade, nacionalidade_escolhida) == 0)
        {
            estudantes[count] = pessoas[i];
            count++;
        }
    }

    listar_estudantes(estudantes, count);
}

// Listar estudantes numa determinada faixa etaria
// Funciona
void listar_por_faixa_etaria(Pessoa pessoas[], int num_pessoas)
{
    int idade_min, idade_max;
    printf("Insira a idade minima: ");
    scanf("%d", &idade_min);
    printf("Insira a idade maxima: ");
    scanf("%d", &idade_max);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;

    Pessoa pessoas_novo[num_pessoas];
    int count = 0;
    for (int i = 0; i < num_pessoas; i++)
    {
        int idade = ano_atual - pessoas[i].data_nascimento.ano;
        if (idade >= idade_min && idade <= idade_max)
        {
            pessoas_novo[count] = pessoas[i];
            count++;
        }
    }
    listar_estudantes(pessoas_novo, count);
}

// Determinar o numero medio de matriculas dos estudantes
// Funciona
void media_matriculas(Pessoa pessoas[], int num_pessoas)
{
    if (num_pessoas == 0)
    {
        printf("Nenhum estudante cadastrado.\n");
        return;
    }

    // Variáveis para a média geral
    float soma_geral = 0.0;

    // Variáveis para a média por nacionalidade
    char nacionalidades[MAX_PESSOAS][MAX_NACIONALIDADE]; // Armazena nacionalidades únicas
    float soma_matriculas[MAX_PESSOAS] = {0.0};              // Soma de matrículas por nacionalidade
    int contagem_nacionalidades[MAX_PESSOAS] = {0};      // Contagem de estudantes por nacionalidade
    int num_nacionalidades = 0;                          // Número de nacionalidades únicas

    // Calcula a média geral e agrupa por nacionalidade
    for (int i = 0; i < num_pessoas; i++)
    {
        soma_geral += pessoas[i].num_matriculas;

        // Verifica se a nacionalidade já foi registrada
        bool encontrada = false;
        for (int j = 0; j < num_nacionalidades; j++)
        {
            if (strcmp(pessoas[i].nacionalidade, nacionalidades[j]) == 0)
            {
                soma_matriculas[j] += pessoas[i].num_matriculas;
                contagem_nacionalidades[j]++;
                encontrada = true;
                break;
            }
        }

        // Se a nacionalidade não foi encontrada, adiciona ao array
        if (!encontrada)
        {
            strcpy(nacionalidades[num_nacionalidades], pessoas[i].nacionalidade);
            soma_matriculas[num_nacionalidades] = pessoas[i].num_matriculas;
            contagem_nacionalidades[num_nacionalidades] = 1;
            num_nacionalidades++;
        }
    }

    // Exibe a média geral
    printf("Media geral de matriculas: %.2f\n", (float)soma_geral / num_pessoas);

    // Exibe a média por nacionalidade
    printf("\nMedia de matriculas por nacionalidade:\n");
    for (int i = 0; i < num_nacionalidades; i++)
    {
        float media = (float)soma_matriculas[i] / contagem_nacionalidades[i];
        printf("Nacionalidade: %s | Media de matriculas: %.2f\n", nacionalidades[i], media);
    }
}

// Listar estudantes por ordem alfabetica do apelido
// Funciona

const char *obter_apelido(const char *nome)
{
    const char *apelido = nome;
    const char *p = nome;
    while (*p)
    {
        if (*p == ' ')
        {
            apelido = p + 1;
        }
        p++;
    }
    return apelido;
}

int comparar_apelidos(const void *a, const void *b)
{
    const Pessoa *pa = (const Pessoa *)a;
    const Pessoa *pb = (const Pessoa *)b;
    return strcmp(obter_apelido(pa->nome), obter_apelido(pb->nome));
}

void listar_estudantes_por_apelido(Pessoa pessoas[], int num_pessoas)
{
    qsort(pessoas, num_pessoas, sizeof(Pessoa), comparar_apelidos);
    printf("Lista de estudantes ordenada por apelido:\n");

    listar_estudantes(pessoas, num_pessoas);
}

// Determinar o numero de estudantes finalistas
// Funciona
void contar_finalistas(Pessoa pessoas[], int num_pessoas)
{
    int count = 0;
    printf("Estudantes finalistas:\n");
    for (int i = 0; i < num_pessoas; i++)
    {
        if (pessoas[i].ects >= 154)
        {
            printf("ID: %d, Nome: %s, ECTS: %d\n", pessoas[i].id, pessoas[i].nome, pessoas[i].ects);
            count++;
        }
    }
    printf("Numero total de estudantes finalistas: %d\n", count);
}

// Determinar a media de idades dos estudantes de uma nacionalidade
// Funciona
void media_idade_por_nacionalidade(Pessoa pessoas[], int num_pessoas)
{
    char *nacionalidades[] = {
        "Angolana",
        "Brasileira",
        "Espanhola",
        "Francesa",
        "Guineense",
        "Italiana",
        "Mocambicana",
        "Portuguesa",
        "Timorense"};
    int num_nacionalidades = sizeof(nacionalidades) / sizeof(nacionalidades[0]);

    printf("Escolha uma nacionalidade pelo numero:\n");
    for (int i = 0; i < num_nacionalidades; i++)
    {
        printf("%d. %s\n", i + 1, nacionalidades[i]);
    }

    int escolha;
    printf("Insira o numero da nacionalidade: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > num_nacionalidades)
    {
        printf("Escolha invalida.\n");
        return;
    }

    char *nacionalidade_escolhida = nacionalidades[escolha - 1];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;

    int soma_idades = 0;
    int count = 0;

    for (int i = 0; i < num_pessoas; i++)
    {
        if (strcmp(pessoas[i].nacionalidade, nacionalidade_escolhida) == 0)
        {
            int idade = ano_atual - pessoas[i].data_nascimento.ano;
            soma_idades += idade;
            count++;
        }
    }

    if (count > 0)
    {
        printf("Media de idade dos estudantes de nacionalidade %s: %.2f\n",
               nacionalidade_escolhida, (float)soma_idades / count);
    }
    else
    {
        printf("Nenhum estudante encontrado com a nacionalidade %s\n", nacionalidade_escolhida);
    }
}

// Determinar o numero de estudantes em risco de prescrever
// Funciona
void listar_estudantes_em_risco(Pessoa pessoas[], int num_pessoas)
{
    int count = 0; //count serve para contar o numero de estudantes que correspondem ao filtro
    int razao1 = 0, razao2 = 0, razao3 = 0;
    int pagina = 1;
    bool estudante_discriminado = false;

    printf("Estudantes em risco de prescrever:\n");
    printf("\nA mostrar pagina: %d\n\n", pagina);

    for (int i = 0; i < num_pessoas; i++)
    {
        if (count >= MAX_PER_PAGE && (count % MAX_PER_PAGE == 0) && estudante_discriminado == true)
        {
            printf("Para seguir para a proxima pagina, selecione p. Para sair pressione q.\n");
            char input;
            scanf(" %c", &input);
            if (input == 'q')
                break;
            pagina++;
            printf("\nA mostrar pagina: %d\n", pagina);
        }

        if ((pessoas[i].num_matriculas == 3 && pessoas[i].ects < 60) ||
            (pessoas[i].num_matriculas == 4 && pessoas[i].ects < 120) ||
            (pessoas[i].num_matriculas > 5 && pessoas[i].ects < 154))
        {
            count++;
            estudante_discriminado = true;

            imprimir_estudante(pessoas[i]);

            if (pessoas[i].num_matriculas == 3 && pessoas[i].ects < 60)
            {
                printf("Risco de prescricao: 3 matriculas e menos de 60 ECTS\n\n");
                razao1++;
            }
            else if (pessoas[i].num_matriculas == 4 && pessoas[i].ects < 120)
            {
                printf("Risco de prescricao: 4 matriculas e menos de 120 ECTS\n\n");
                razao2++;
            }
            else if (pessoas[i].num_matriculas > 5 && pessoas[i].ects < 154)
            {
                printf("Risco de prescricao: Mais de 5 matriculas e menos de 154 ECTS\n\n");
                razao3++;
            }
        }
        else estudante_discriminado = false;
    }

    printf("-------------------------\n");
    printf("Total de estudantes em risco de prescrever com 3 matriculas e menos de 60 ECTS: %d\n", razao1);
    printf("Total de estudantes em risco de prescrever com 4 matriculas e menos de 120: %d\n", razao2);
    printf("Total de estudantes em risco de prescrever com mais de 5 matriculas e menos de 154 ECTS: %d\n", razao3);
    printf("Total de estudantes em risco de prescrever: %d\n", count);
}

void escrever_estudantes(Pessoa pessoas[], int num_pessoas)
{
    FILE *file = fopen("Estudantes.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o ficheiro Estudantes.txt para escrita.\n");
        return;
    }

    for (int i = 0; i < num_pessoas; i++)
    {
        fprintf(file, "%d\t%s\t%02d-%02d-%04d\t%s\n",
                pessoas[i].id,
                pessoas[i].nome,
                pessoas[i].data_nascimento.dia,
                pessoas[i].data_nascimento.mes,
                pessoas[i].data_nascimento.ano,
                pessoas[i].nacionalidade);
    }

    fclose(file);
    printf("Dados dos estudantes escritos no ficheiro Estudantes.txt com sucesso.\n");
}

void escrever_info_academica(Pessoa pessoas[], int num_pessoas)
{
    if (num_pessoas == 0)
    {
        printf("Nenhum estudante disponivel para escrever no ficheiro.\n");
        return;
    }

    FILE *file = fopen("Situacao_Escolar_Estudante.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o ficheiro Situacao_Escolar_Estudante.txt para escrita.\n");
        return;
    }

    for (int i = 0; i < num_pessoas; i++)
    {
        // Verifica se os dados foram carregados corretamente antes de escrever
        if (pessoas[i].num_matriculas == 0 && pessoas[i].ects == 0 && pessoas[i].ano_curricular == 0 && pessoas[i].media_atual == 0.0)
        {
            printf("Aviso: Estudante ID %d parece não ter dados academicos.\n", pessoas[i].id);
        }

        fprintf(file, "%d\t%d\t%d\t%d\t%.2f\n",
                pessoas[i].id,
                pessoas[i].num_matriculas,
                pessoas[i].ects,
                pessoas[i].ano_curricular,
                pessoas[i].media_atual);
    }

    fclose(file);
    printf("Dados academicos foram escritos no ficheiro com sucesso.\n");
}

void exportar_csv(Pessoa pessoas[], int num_pessoas)
{
    FILE *file = fopen("estudantes.csv", "w");
    if (!file)
    {
        printf("ERRO: Falha ao abrir estudantes.csv para escrita.\n");
        return;
    }

    // Escreve o cabeçalho do CSV
    fprintf(file, "ID,Nome,Data de Nascimento,Nacionalidade,Matriculas,ECTS,Ano do Curso,Media Atual\n");

    // Escreve os dados dos estudantes
    for (int i = 0; i < num_pessoas; i++)
    {
        fprintf(file, "%d,%s,%02d-%02d-%04d,%s,%d,%d,%d,%.2f\n",
                pessoas[i].id,
                pessoas[i].nome,
                pessoas[i].data_nascimento.dia,
                pessoas[i].data_nascimento.mes,
                pessoas[i].data_nascimento.ano,
                pessoas[i].nacionalidade,
                pessoas[i].num_matriculas,
                pessoas[i].ects,
                pessoas[i].ano_curricular,
                pessoas[i].media_atual);
    }

    fclose(file);
    printf("✅ Dados exportados com sucesso para estudantes.csv\n");
}

int dia_da_semana(int d, int m, int y)
{
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

// E1: Listar estudantes que nasceram num Domingo ou cujo aniversario num determinado ano e ao Domingo
// Funciona
void listar_estudantes_domingo(Pessoa pessoas[], int num_pessoas)
{
    int ano_referencia;
    int pagina = 1, count = 0; //count serve para contar o numero de estudantes que correspondem ao filtro
    bool estudante_discriminado = false;

    printf("Insira o ano de referencia: ");
    scanf("%d", &ano_referencia);
    printf("Estudantes que tem aniversario num domingo no ano %d:\n", ano_referencia);

    printf("\nA mostrar pagina: %d\n", pagina);
    for (int i = 0; i < num_pessoas; i++)
    {
        if (count >= MAX_PER_PAGE && (count % MAX_PER_PAGE == 0) && estudante_discriminado == true)
        {
            printf("Para seguir para a proxima pagina, selecione p. Para sair pressione q.\n");
            char input;
            scanf(" %c", &input);

            if (input == 'q')
                break;

            pagina++;
            printf("\nA mostrar pagina: %d\n", pagina);
        }

        int dia_nasc = pessoas[i].data_nascimento.dia;
        int mes_nasc = pessoas[i].data_nascimento.mes;

        if (dia_da_semana(dia_nasc, mes_nasc, ano_referencia) == 0)
        {
            count++;
            estudante_discriminado = true;

            imprimir_estudante(pessoas[i]);
            printf("Tem aniversario a %02d-%02d-%02d. E um Domingo\n", dia_nasc, mes_nasc, ano_referencia);
        }
        // TODO: explicar estudante_discriminado no relatorio
        else
            estudante_discriminado = false;
    }

    printf("-------------------------\n");
}

void listar_estudantes_dia_semana(Pessoa pessoas[], int num_pessoas)
{
    int pagina = 1, count = 0; //count serve para contar o numero de estudantes que correspondem ao filtro
    bool estudante_discriminado = false;

    char *dias_semana[] = {
        "Domingo",
        "Segunda",
        "Terca",
        "Quarta",
        "Quinta",
        "Sexta",
        "Sabado"};
    int num_dias_semana = sizeof(dias_semana) / sizeof(dias_semana[0]);

    printf("Escolha um dia da semana pelo numero:\n");
    for (int i = 0; i < num_dias_semana; i++)
    {
        printf("%d. %s\n", i + 1, dias_semana[i]);
    }

    int escolha;
    printf("Insira o numero do dia da semana: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > num_dias_semana)
    {
        printf("Escolha invalida.\n");
        return;
    }

    int dia_semana_escolhido = escolha - 1;

    printf("\nA mostrar pagina: %d\n", pagina);
    for (int i = 0; i < num_pessoas; i++)
    {
        if (count >= MAX_PER_PAGE && (count % MAX_PER_PAGE == 0) && estudante_discriminado == true)
        {
            printf("Para seguir para a proxima pagina, selecione p. Para sair pressione q.\n");
            char input;
            scanf(" %c", &input);
            if (input == 'q')
            {
                break;
            }
            pagina++;
            printf("\nA mostrar pagina: %d\n", pagina);
        }

        int dia_nasc = pessoas[i].data_nascimento.dia;
        int mes_nasc = pessoas[i].data_nascimento.mes;
        int ano_nasc = pessoas[i].data_nascimento.ano;

        if (dia_da_semana(dia_nasc, mes_nasc, ano_nasc) == dia_semana_escolhido)
        {
            count++;
            estudante_discriminado = true;

            imprimir_estudante(pessoas[i]);
            printf("Nasceu a %02d-%02d-%d. Dia da semana: %s\n", dia_nasc, mes_nasc, ano_nasc, dias_semana[escolha - 1]);
        }
        // TODO: explicar estudante_discriminado no relatorio
        else
            estudante_discriminado = false;
    }

    printf("-------------------------\n");
}

// Teste
void listar_estudantes_media_ano(Pessoa pessoas[], int num_pessoas)
{
    int sem_class[4] = {0};
    int media_10_12[4] = {0};
    int media_12_14[4] = {0};
    int media_14_16[4] = {0};
    int media_16_18[4] = {0};
    int media_18_20[4] = {0};

    for (int i = 0; i < num_pessoas; i++)
    {
        int ano = pessoas[i].ano_curricular - 1;
        if (ano >= 0 && ano < 3)
        {
            float media = pessoas[i].media_atual;

            if (media == 0)
            {
                sem_class[ano]++;
                sem_class[3]++;
            }
            else if (media >= 10 && media < 12)
            {
                media_10_12[ano]++;
                media_10_12[3]++;
            }
            else if (media >= 12 && media < 14)
            {
                media_12_14[ano]++;
                media_12_14[3]++;
            }
            else if (media >= 14 && media < 16)
            {
                media_14_16[ano]++;
                media_14_16[3]++;
            }
            else if (media >= 16 && media < 18)
            {
                media_16_18[ano]++;
                media_16_18[3]++;
            }
            else if (media >= 18 && media <= 20)
            {
                media_18_20[ano]++;
                media_18_20[3]++;
            }
        }
    }

    printf("\n+--------------------------------+-------------------------+------------------+\n");
    printf("|      Numero de estudantes por Intervalos de Classificacao Media e Ano     |\n");
    printf("+------------------------+---------------------------------+------------------+\n");
    printf("|                       |         Ano de Inscricao        |                 |\n");
    printf("| Intervalo Media Atual |    1.        2.        3.      | Todos os anos   |\n");
    printf("+------------------------+---------------------------------+------------------+\n");
    printf("| Sem Classificacao     |    %3d       %3d       %3d     |      %3d        |\n",
           sem_class[0], sem_class[1], sem_class[2], sem_class[3]);
    printf("+------------------------+---------------------------------+------------------+\n");
    printf("| [10 , 12[            |    %3d       %3d       %3d     |      %3d        |\n",
           media_10_12[0], media_10_12[1], media_10_12[2], media_10_12[3]);
    printf("+------------------------+---------------------------------+------------------+\n");
    printf("| [12 , 14[            |    %3d       %3d       %3d     |      %3d        |\n",
           media_12_14[0], media_12_14[1], media_12_14[2], media_12_14[3]);
    printf("+------------------------+---------------------------------+------------------+\n");
    printf("| [14 , 16[            |    %3d       %3d       %3d     |      %3d        |\n",
           media_14_16[0], media_14_16[1], media_14_16[2], media_14_16[3]);
    printf("+------------------------+---------------------------------+------------------+\n");
    printf("| [16 , 18[            |    %3d       %3d       %3d     |      %3d        |\n",
           media_16_18[0], media_16_18[1], media_16_18[2], media_16_18[3]);
    printf("+------------------------+---------------------------------+------------------+\n");
    printf("| [18 , 20]            |    %3d       %3d       %3d     |      %3d        |\n",
           media_18_20[0], media_18_20[1], media_18_20[2], media_18_20[3]);
    printf("+------------------------+---------------------------------+------------------+\n");

    int total_1 = sem_class[0] + media_10_12[0] + media_12_14[0] +
                  media_14_16[0] + media_16_18[0] + media_18_20[0];
    int total_2 = sem_class[1] + media_10_12[1] + media_12_14[1] +
                  media_14_16[1] + media_16_18[1] + media_18_20[1];
    int total_3 = sem_class[2] + media_10_12[2] + media_12_14[2] +
                  media_14_16[2] + media_16_18[2] + media_18_20[2];
    int total_geral = total_1 + total_2 + total_3;

    printf("| Todos os Intervalos   |    %3d       %3d       %3d     |      %3d        |\n",
           total_1, total_2, total_3, total_geral);
    printf("+------------------------+---------------------------------+------------------+\n");
}

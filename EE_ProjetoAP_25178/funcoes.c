#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "estruturas.h"
#include "funcoes.h"

#define MAX_PESSOAS 5000
#define MAX_NOME 50
#define MAX_NACIONALIDADE 10


// 1. Ler dados e carregar para estruturas
//Funciona
void ler_pessoas(struct Pessoa pessoas[], int *num_pessoas) {
    FILE *file = fopen("dados2.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo dados2.txt.\n");
        return;
    }

    *num_pessoas = 0;
    char linha[256];

    while (*num_pessoas < MAX_PESSOAS && fgets(linha, sizeof(linha), file)) {
        struct Pessoa *p = &pessoas[*num_pessoas];
        char nome_temp[MAX_NOME];
        int dia, mes, ano;

        if (sscanf(linha, "%d\t%[^\t]\t%d-%d-%d\t%s",
                   &p->id, nome_temp, &dia, &mes, &ano, p->nacionalidade) == 6) {

            strncpy(p->nome, nome_temp, MAX_NOME - 1);
            p->nome[MAX_NOME - 1] = '\0';

            p->data_nascimento.dia = dia;
            p->data_nascimento.mes = mes;
            p->data_nascimento.ano = ano;

            p->num_materias = 0;
            p->ects = 0;

            (*num_pessoas)++;
        }
    }

    fclose(file);
}

//Funciona
void ler_info_academica(struct Pessoa pessoas[], int num_pessoas) {
    FILE *file = fopen("cod_nMat_ECTS.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo cod_nMat_ECTS.txt.\n");
        return;
    }

    int id, num_materias, ects;
    while (fscanf(file, "%d\t%d\t%d", &id, &num_materias, &ects) == 3) {
        for (int i = 0; i < num_pessoas; i++) {
            if (pessoas[i].id == id) {
                pessoas[i].num_materias = num_materias;
                pessoas[i].ects = ects;
                break;
            }
        }
    }

    fclose(file);
}




// 2. Gerir estudantes
//Funciona
void ler_entrada(char *prompt, void *valor, int e_inteiro) {
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro na leitura. Tente novamente.\n");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = 0;

        if (e_inteiro) {
            if (sscanf(buffer, "%d", (int*)valor) == 1) {
                break;
            }
            printf("Entrada invalida. Por favor, insira um namero inteiro.\n");
        } else {
            strcpy((char*)valor, buffer);
            break;
        }
    }
}

// Função principal para adicionar um novo estudante
//Funciona
void adicionar_estudante(struct Pessoa pessoas[], int *num_pessoas) {


    struct Pessoa novo_estudante;

    printf("Digite o ID do novo estudante: ");
    scanf("%d", &novo_estudante.id);

    printf("Digite o nome do novo estudante: ");
    scanf(" %[^\n]", novo_estudante.nome);

    printf("Digite a data de nascimento (dd-mm-aaaa): ");
    scanf("%d-%d-%d", &novo_estudante.data_nascimento.dia,
          &novo_estudante.data_nascimento.mes,
          &novo_estudante.data_nascimento.ano);

    printf("Digite a nacionalidade: ");
    scanf(" %[^\n]", novo_estudante.nacionalidade);

    printf("Digite o numero de matérias: ");
    scanf("%d", &novo_estudante.num_materias);

    printf("Digite o numero de ECTS: ");
    scanf("%d", &novo_estudante.ects);

    pessoas[*num_pessoas] = novo_estudante;
    (*num_pessoas)++;

    printf("Estudante adicionado com sucesso.\n");
}

//Funciona
void eliminar_estudante(struct Pessoa pessoas[], int *num_pessoas) {
    int id;
    printf("Insira o ID do estudante a eliminar: ");
    scanf("%d", &id);

    for (int i = 0; i < *num_pessoas; i++) {
        if (pessoas[i].id == id) {

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

            if (confirmacao == 's' || confirmacao == 'S') {
                for (int j = i; j < *num_pessoas - 1; j++) {
                    pessoas[j] = pessoas[j + 1];
                }
                (*num_pessoas)--;
                printf("Estudante eliminado com sucesso.\n");
            } else {
                printf("Eliminaçao cancelada.\n");
            }
            return;
        }
    }
    printf("Estudante nao encontrado.\n");
}


//Funciona
void pesquisar_estudante(struct Pessoa pessoas[], int num_pessoas) {
    char nome_parcial[MAX_NOME];
    printf("Insira parte do nome a pesquisar: ");
    getchar();
    fgets(nome_parcial, MAX_NOME, stdin);
    nome_parcial[strcspn(nome_parcial, "\n")] = 0;

    int encontrados = 0;
    for (int i = 0; i < num_pessoas; i++) {
        if (strstr(pessoas[i].nome, nome_parcial) != NULL) {
            printf("ID: %d, Nome: %s, Nacionalidade: %s\n",
                   pessoas[i].id, pessoas[i].nome, pessoas[i].nacionalidade);
            encontrados++;
        }
    }
    printf("Total de estudantes encontrados: %d\n", encontrados);
}

// 3. Listar todos os estudantes
//Funciona
void listar_estudantes(struct Pessoa pessoas[], int num_pessoas) {
    for (int i = 0; i < num_pessoas; i++) {
        printf("ID: %d, Nome: %s, Nacionalidade: %s, Matriculas: %d, ECTS: %d\n",
               pessoas[i].id, pessoas[i].nome, pessoas[i].nacionalidade,
               pessoas[i].num_materias, pessoas[i].ects);
    }
    printf("Total de estudantes: %d\n", num_pessoas);
}

// 4. Listar estudantes de uma determinada nacionalidade
//Funciona
void listar_por_nacionalidade(struct Pessoa pessoas[], int num_pessoas) {
    char* nacionalidades[] = {
        "Angolana",
        "Brasileira",
        "Espanhola",
        "Francesa",
        "Guineense",
        "Italiana",
        "Mocambicana",
        "Portuguesa",
        "Timorense"
    };
    int num_nacionalidades = sizeof(nacionalidades) / sizeof(nacionalidades[0]);

    printf("Escolha uma nacionalidade pelo numero:\n");
    for (int i = 0; i < num_nacionalidades; i++) {
        printf("%d. %s\n", i + 1, nacionalidades[i]);
    }

    int escolha;
    printf("Insira o número da nacionalidade: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > num_nacionalidades) {
        printf("Escolha invalida.\n");
        return;
    }

    char* nacionalidade_escolhida = nacionalidades[escolha - 1];

    int count = 0;
    for (int i = 0; i < num_pessoas; i++) {
        if (strcmp(pessoas[i].nacionalidade, nacionalidade_escolhida) == 0) {
            printf("ID: %d, Nome: %s\n", pessoas[i].id, pessoas[i].nome);
            count++;
        }
    }
    printf("Total de estudantes da nacionalidade %s: %d\n", nacionalidade_escolhida, count);
}

// 5. Listar estudantes numa determinada faixa etária
//Funciona
void listar_por_faixa_etaria(struct Pessoa pessoas[], int num_pessoas) {
    int idade_min, idade_max;
    printf("Insira a idade minima: ");
    scanf("%d", &idade_min);
    printf("Insira a idade maxima: ");
    scanf("%d", &idade_max);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;

    int count = 0;
    for (int i = 0; i < num_pessoas; i++) {
        int idade = ano_atual - pessoas[i].data_nascimento.ano;
        if (idade >= idade_min && idade <= idade_max) {
            printf("ID: %d, Nome: %s, Idade: %d\n", pessoas[i].id, pessoas[i].nome, idade);
            count++;
        }
    }
    printf("Total de estudantes na faixa etaria %d-%d: %d\n", idade_min, idade_max, count);
}

// 6. Determinar o número médio de matrículas dos estudantes
//Funciona
void media_matriculas(struct Pessoa pessoas[], int num_pessoas) {
    int soma_geral = 0;
    for (int i = 0; i < num_pessoas; i++) {
        soma_geral += pessoas[i].num_materias;
    }
    printf("Media geral de matriculas: %.2f\n", (float)soma_geral / num_pessoas);

}

// 7. Listar estudantes por ordem alfabética do apelido
//Funciona

const char* obter_apelido(const char* nome) {
    const char* apelido = nome;
    const char* p = nome;
    while (*p) {
        if (*p == ' ') {
            apelido = p + 1;
        }
        p++;
    }
    return apelido;
}

int comparar_apelidos(const void* a, const void* b) {
    const struct Pessoa* pa = (const struct Pessoa*)a;
    const struct Pessoa* pb = (const struct Pessoa*)b;
    return strcmp(obter_apelido(pa->nome), obter_apelido(pb->nome));
}

void listar_estudantes_por_apelido(struct Pessoa pessoas[], int num_pessoas) {
    qsort(pessoas, num_pessoas, sizeof(struct Pessoa), comparar_apelidos);
    printf("Lista de estudantes ordenada por apelido:\n");
    for (int i = 0; i < num_pessoas; i++) {
        printf("%d\t%s\t%d-%d-%d\t%s\n",
               pessoas[i].id,
               pessoas[i].nome,
               pessoas[i].data_nascimento.dia,
               pessoas[i].data_nascimento.mes,
               pessoas[i].data_nascimento.ano,
               pessoas[i].nacionalidade);
    }
}

// 8. Determinar o número de estudantes finalistas
//Funciona
void contar_finalistas(struct Pessoa pessoas[], int num_pessoas) {
    int count = 0;
    printf("Estudantes finalistas:\n");
    for (int i = 0; i < num_pessoas; i++) {
        if (pessoas[i].ects >= 154) {
            printf("ID: %d, Nome: %s, ECTS: %d\n", pessoas[i].id, pessoas[i].nome, pessoas[i].ects);
            count++;
        }
    }
    printf("Numero total de estudantes finalistas: %d\n", count);
}

// 9. Determinar a média de idades dos estudantes de uma nacionalidade
//Funciona
void media_idade_por_nacionalidade(struct Pessoa pessoas[], int num_pessoas) {
    char* nacionalidades[] = {
        "Angolana",
        "Brasileira",
        "Espanhola",
        "Francesa",
        "Guineense",
        "Italiana",
        "Mocambicana",
        "Portuguesa",
        "Timorense"
    };
    int num_nacionalidades = sizeof(nacionalidades) / sizeof(nacionalidades[0]);

    printf("Escolha uma nacionalidade pelo número:\n");
    for (int i = 0; i < num_nacionalidades; i++) {
        printf("%d. %s\n", i + 1, nacionalidades[i]);
    }

    int escolha;
    printf("Insira o número da nacionalidade: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > num_nacionalidades) {
        printf("Escolha inválida.\n");
        return;
    }

    char* nacionalidade_escolhida = nacionalidades[escolha - 1];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;

    int soma_idades = 0;
    int count = 0;

    for (int i = 0; i < num_pessoas; i++) {
        if (strcmp(pessoas[i].nacionalidade, nacionalidade_escolhida) == 0) {
            int idade = ano_atual - pessoas[i].data_nascimento.ano;
            soma_idades += idade;
            count++;
        }
    }

    if (count > 0) {
        printf("Media de idade dos estudantes de nacionalidade %s: %.2f\n",
               nacionalidade_escolhida, (float)soma_idades / count);
    } else {
        printf("Nenhum estudante encontrado com a nacionalidade %s\n", nacionalidade_escolhida);
    }
}

// 10. Determinar o número de estudantes em risco de prescrever
//Funciona
void estudantes_em_risco(struct Pessoa pessoas[], int num_pessoas) {
    int count = 0;
    printf("Estudantes em risco de prescrever:\n");
    for (int i = 0; i < num_pessoas; i++) {
        if ((pessoas[i].num_materias == 3 && pessoas[i].ects < 60) ||
            (pessoas[i].num_materias == 4 && pessoas[i].ects < 120) ||
            (pessoas[i].num_materias > 5 && pessoas[i].ects < 154)) {
            count++;
            printf("ID: %d, Nome: %s, Razao: ", pessoas[i].id, pessoas[i].nome);
            if (pessoas[i].num_materias == 3 && pessoas[i].ects < 60) {
                printf("3 matriculas e menos de 60 ECTS\n");
            } else if (pessoas[i].num_materias == 4 && pessoas[i].ects < 120) {
                printf("4 matriculas e menos de 120 ECTS\n");
            } else if (pessoas[i].num_materias > 5 && pessoas[i].ects < 154) {
                printf("Mais de 5 matriculas e menos de 154 ECTS\n");
            }
        }
    }
    printf("Total de estudantes em risco de prescrever: %d\n", count);
}

// Função para atualizar o arquivo dados2.txt
//Não funciona
void atualizar_dados_pessoais(struct Pessoa pessoas[], int num_pessoas) {
    FILE *file = fopen("dados2.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo dados2.txt para escrita.\n");
        return;
    }

    for (int i = 0; i < num_pessoas; i++) {
        fprintf(file, "%d\t%s\t%d-%d-%d\t%s\n",
                pessoas[i].id,
                pessoas[i].nome,
                pessoas[i].data_nascimento.dia,
                pessoas[i].data_nascimento.mes,
                pessoas[i].data_nascimento.ano,
                pessoas[i].nacionalidade);
    }

    fclose(file);
    printf("Arquivo dados2.txt atualizado com sucesso.\n");
}

// Função para atualizar o arquivo cod_nMat_ECTS.txt
void atualizar_dados_academicos(struct Pessoa pessoas[], int num_pessoas) {
    FILE *file = fopen("cod_nMat_ECTS.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo cod_nMat_ECTS.txt para escrita.\n");
        return;
    }

    for (int i = 0; i < num_pessoas; i++) {
        fprintf(file, "%d\t%d\t%d\n",
                pessoas[i].id,
                pessoas[i].num_materias,
                pessoas[i].ects);
    }

    fclose(file);
    printf("Arquivo cod_nMat_ECTS.txt atualizado com sucesso.\n");
}

int dia_da_semana(int d, int m, int y) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}


// E1: Listar estudantes que nasceram num Domingo ou cujo aniversário num determinado ano é ao Domingo
//Funciona
void listar_estudantes_domingo(struct Pessoa pessoas[], int num_pessoas, int ano_referencia) {
    printf("Estudantes que nasceram num Domingo ou cujo aniversario em %d e num Domingo:\n", ano_referencia);
    for (int i = 0; i < num_pessoas; i++) {
        int dia_nasc = pessoas[i].data_nascimento.dia;
        int mes_nasc = pessoas[i].data_nascimento.mes;
        int ano_nasc = pessoas[i].data_nascimento.ano;

        if (dia_da_semana(dia_nasc, mes_nasc, ano_nasc) == 0) {
            printf("%s (nascido em %d-%02d-%02d, que foi um Domingo)\n",
                   pessoas[i].nome, ano_nasc, mes_nasc, dia_nasc);
        }

        else if (dia_da_semana(dia_nasc, mes_nasc, ano_referencia) == 0) {
            printf("%s (aniversario em %d-%02d-%02d sera um Domingo)\n",
                   pessoas[i].nome, ano_referencia, mes_nasc, dia_nasc);
        }
    }
}

// E2: Listar estudantes cujo aniversário, num determinado ano, é na quaresma
//Funciona
void calcular_pascoa(int ano, int *mes, int *dia) {
    int a = ano % 19;
    int b = ano / 100;
    int c = ano % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    *mes = (h + l - 7 * m + 114) / 31;
    *dia = ((h + l - 7 * m + 114) % 31) + 1;
}

// Função para verificar se uma data está dentro da Quaresma
bool esta_na_quaresma(int dia, int mes, int ano_pascoa, int mes_pascoa, int dia_pascoa) {

    //46 dias antes da Páscoa
    int dias_antes_pascoa = 46;

    //Quarta-feira de Cinzas
    int dia_inicio = dia_pascoa;
    int mes_inicio = mes_pascoa;

    while (dias_antes_pascoa > 0) {
        dia_inicio--;
        if (dia_inicio == 0) {
            mes_inicio--;
            if (mes_inicio == 2) {
                dia_inicio = 28;
            } else if (mes_inicio == 4 || mes_inicio == 6 || mes_inicio == 9 || mes_inicio == 11) {
                dia_inicio = 30;
            } else {
                dia_inicio = 31;
            }
        }
        dias_antes_pascoa--;
    }

    if (mes > mes_inicio && mes < mes_pascoa) {
        return true;
    } else if (mes == mes_inicio && dia >= dia_inicio) {
        return true;
    } else if (mes == mes_pascoa && dia < dia_pascoa) {
        return true;
    }

    return false;
}

// Função para determinar os estudantes com aniversário na Quaresma
//Funciona
void aniversarios_na_quaresma(struct Pessoa pessoas[], int num_pessoas, int ano) {
    int mes_pascoa, dia_pascoa;
    calcular_pascoa(ano, &mes_pascoa, &dia_pascoa);

    printf("Estudantes com aniversario na Quaresma de %d:\n", ano);

    for (int i = 0; i < num_pessoas; i++) {
        struct Pessoa p = pessoas[i];
        if (esta_na_quaresma(p.data_nascimento.dia, p.data_nascimento.mes, ano, mes_pascoa, dia_pascoa)) {
            printf("ID: %d, Nome: %s, Data de Nascimento: %02d-%02d\n",
                   p.id, p.nome, p.data_nascimento.dia, p.data_nascimento.mes);
        }
    }
}

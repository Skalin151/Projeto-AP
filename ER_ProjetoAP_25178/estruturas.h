#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PESSOAS 5000
#define MAX_NOME 50
#define MAX_NACIONALIDADE 20

typedef struct Data {
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Pessoa {
    int id;
    char nome[MAX_NOME];
    Data data_nascimento;
    char nacionalidade[MAX_NACIONALIDADE];
    int num_matriculas;
    int ects;
    int ano_curricular;
    float media_atual;
}Pessoa;

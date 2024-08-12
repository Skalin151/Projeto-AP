#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PESSOAS 5000
#define MAX_NOME 50
#define MAX_NACIONALIDADE 20

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Pessoa {
    int id;
    char nome[MAX_NOME];
    struct Data data_nascimento;
    char nacionalidade[MAX_NACIONALIDADE];
    int num_materias;
    int ects;
};

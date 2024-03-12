#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_ENTRIES 1500
#define MAX_MATRICULA_LENGTH 10
#define TAMANHO_MAX_REGISTRO 255

#include "Funcoes.h"

// Estrutura para representar a data
struct Data {
    int ano;
    int mes;
    int dia;
};

struct Cliente {
    int id_cliente;
    char matricula[MAX_MATRICULA_LENGTH];
    char nome[50];
    char cod_postal[9];
    int NIF;
    struct Data data_inscricao;
    struct Data fim_inscricao;
};

struct Entradas {
    char matriculas[MAX_MATRICULA_LENGTH];
    struct Data data_entrada;
    int hora;
    int min;

};

struct EntradaseSaidas {
    char matriculas[MAX_MATRICULA_LENGTH];
    struct Data data_entrada;
    int horaent;
    int minent;
    struct Data data_saida;
    int horasaida;
    int minsaida;
    float custo_total;
};

struct LugarEstacionamento {
    int piso;
    char linha;
    int coluna;
};


#endif // ESTRUTURAS_H

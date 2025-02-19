#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#define MAX_PER_PAGE 5

#include "estruturas.h"

//Funções de leitura
void ler_pessoas(Pessoa pessoas[], int *num_pessoas);
void ler_info_academica(Pessoa pessoas[], int *num_pessoas);

// Funções para gerir estudantes
void adicionar_estudante(Pessoa pessoas[], int *num_pessoas);
void eliminar_estudante(Pessoa pessoas[], int *num_pessoas);
void alterar_estudante(Pessoa pessoas[], int num_pessoas);
void pesquisar_estudante(Pessoa pessoas[], int num_pessoas);

// Funções para listar estudantes
void listar_estudantes(Pessoa pessoas[], int num_pessoas);
void listar_por_nacionalidade(Pessoa pessoas[], int num_pessoas);
void listar_por_faixa_etaria(Pessoa pessoas[], int num_pessoas);
void listar_estudantes_por_apelido(Pessoa pessoas[], int num_pessoas);

// Funções para cálculos e estatísticas
void media_matriculas(Pessoa pessoas[], int num_pessoas);
void contar_finalistas(Pessoa pessoas[], int num_pessoas);
void media_idade_por_nacionalidade(Pessoa pessoas[], int num_pessoas);
void listar_estudantes_em_risco(Pessoa pessoas[], int num_pessoas);

// Funções para atualizar arquivos
void escrever_estudantes(Pessoa pessoas[], int num_pessoas);
void escrever_info_academica(Pessoa pessoas[], int num_pessoas);
void exportar_csv(Pessoa pessoas[], int num_pessoas);

// Funções auxiliares
int dia_da_semana(int d, int m, int y);
void imprimir_estudante(Pessoa estudante);

// Funções extras
void listar_estudantes_domingo(Pessoa pessoas[], int num_pessoas);
void listar_estudantes_dia_semana(Pessoa pessoas[], int num_pessoas);

// Teste
void listar_estudantes_media_ano(Pessoa pessoas[], int num_pessoas);


#endif // FUNCOES_H_INCLUDED

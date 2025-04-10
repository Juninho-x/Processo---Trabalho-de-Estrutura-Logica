// processo.h

#ifndef PROCESSO_H
#define PROCESSO_H

#include <time.h>

// Aqui estão as constantes
#define MAX_ASSUNTOS 10         // Significa: máximo de assuntos por processo
#define MAX_PROCESSOS 1000      // Significa: máximo de processos suportados

// Essa é a definição da estrutura do Processo
typedef struct {
    long id;                           // Esse é o identificador único
    char numero[30];                   // Esse é o número do processo
    struct tm data_ajuizamento;        // Essa é a data de ajuizamento (formato de data)
    long id_classe;                    // Esse é o ID da classe do processo
    long id_assunto[MAX_ASSUNTOS];     // Essa é a lista de assuntos vinculados
    int num_assuntos;                  // Essa é a quantidade de assuntos
    int ano_eleicao;                   // Esse é o ano da eleição relacionada (ou 0)
} Processo;

// Esses são os protótipos das funções
void ordenar_por_id(Processo *processos, int n);
void ordenar_por_data(Processo *processos, int n);
int contar_processos_por_classe(Processo *processos, int n, long id_classe);
int contar_assuntos_distintos(Processo *processos, int n);
void listar_processos_multiplos_assuntos(Processo *processos, int n);
int dias_tramitacao(Processo *p);
int carregar_processos(const char *nome_arquivo, Processo *processos);

#endif

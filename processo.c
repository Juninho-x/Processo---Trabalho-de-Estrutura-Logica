// processo.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

// Essa é a função para ordenar os processos por ID na ordem crescente
void ordenar_por_id(Processo *processos, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processos[i].id > processos[j].id) {
                Processo temp = processos[i];
                processos[i] = processos[j];
                processos[j] = temp;
            }
        }
    }
}

// Essa ordena por data de ajuizamento na ordem decrescente
void ordenar_por_data(Processo *processos, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // mktime transforma struct tm em time_t para comparar datas
            if (difftime(mktime(&processos[i].data_ajuizamento), mktime(&processos[j].data_ajuizamento)) < 0) {
                Processo temp = processos[i];
                processos[i] = processos[j];
                processos[j] = temp;
            }
        }
    }
}

// Aqui conta quantos processos vão possuir um determinado id_classe
int contar_processos_por_classe(Processo *processos, int n, long id_classe) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (processos[i].id_classe == id_classe) count++;
    }
    return count;
}

// Aqui conta quantos assuntos distintos vão existir em todos os processos
int contar_assuntos_distintos(Processo *processos, int n) {
    long encontrados[MAX_PROCESSOS * MAX_ASSUNTOS];
    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processos[i].num_assuntos; j++) {
            int existe = 0;
            for (int k = 0; k < total; k++) {
                if (encontrados[k] == processos[i].id_assunto[j]) {
                    existe = 1;
                    break;
                }
            }
            if (!existe) encontrados[total++] = processos[i].id_assunto[j];
        }
    }

    return total;
}

// Isso vai listar processos com mais de um assunto
void listar_processos_multiplos_assuntos(Processo *processos, int n) {
    for (int i = 0; i < n; i++) {
        if (processos[i].num_assuntos > 1) {
            printf("ID: %ld, Número: %s\n", processos[i].id, processos[i].numero);
        }
    }
}

// Isso vai calcular a quantidade de dias desde o ajuizamento até hoje
int dias_tramitacao(Processo *p) {
    time_t agora;
    time(&agora);
    return (int)(difftime(agora, mktime(&p->data_ajuizamento)) / (60 * 60 * 24));
}

// Isso cai ler os dados do arquivo CSV e armazenar em vetor de Processos
int carregar_processos(const char *nome_arquivo, Processo *processos) {
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) return -1;

    char linha[512];
    fgets(linha, sizeof(linha), fp); // Isso ignora o cabeçalho

    int i = 0;
    while (fgets(linha, sizeof(linha), fp) && i < MAX_PROCESSOS) {
        char *token = strtok(linha, ",");
        processos[i].id = atol(token); // Isso é o id

        token = strtok(NULL, ",");
        strcpy(processos[i].numero, token); // Isso é o numero

        token = strtok(NULL, ",");
        strptime(token, "%Y-%m-%d %H:%M:%S.000", &processos[i].data_ajuizamento); // data

        token = strtok(NULL, ",{}"); // Isso remove as chaves
        processos[i].id_classe = atol(token); // Isso é a classe

        processos[i].num_assuntos = 0;
        while ((token = strtok(NULL, ",{}")) != NULL && strlen(token) > 0) {
            processos[i].id_assunto[processos[i].num_assuntos++] = atol(token);
        }

        token = strtok(NULL, "\n");
        processos[i].ano_eleicao = token ? atoi(token) : 0;

        i++;
    }

    fclose(fp);
    return i;
}

// main.c

#include <stdio.h>
#include "processo.h"

int main() {
    Processo processos[MAX_PROCESSOS];

    // Aqui carrega os dados do arquivo CSV
    int total = carregar_processos("processo_043_202409032338.csv", processos);
    if (total < 0) {
        printf("Eita! Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Total de processos lidos: %d\n", total);

    // Ordenação por ID
    ordenar_por_id(processos, total);
    printf("Ordenado por ID com sucesso!\n");

    // Ordenação por data na ordem decrescente
    ordenar_por_data(processos, total);
    printf("Ordenado por data de ajuizamento (descendente)!\n");

    // Vai contar por id_classe
    long classe = 12554;
    int qtd_classe = contar_processos_por_classe(processos, total, classe);
    printf("Processos com classe %ld: %d\n", classe, qtd_classe);

    // Vai contar assuntos distintos
    printf("Quantidade de assuntos distintos: %d\n", contar_assuntos_distintos(processos, total));

    // Vai listar processos com múltiplos assuntos
    printf("Processos com múltiplos assuntos:\n");
    listar_processos_multiplos_assuntos(processos, total);

    // Vai mostrar dias de tramitação do primeiro processo
    printf("Dias em tramitação (1º processo): %d dias\n", dias_tramitacao(&processos[0]));

    return 0;
}


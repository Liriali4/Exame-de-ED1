#include <stdio.h>
#include "./tadFabrica.h"


void gerarRelatorio(
    Fila *filaInicial,
    Maquina *maquinaDeEnchimento,
    FilaDeEmbalagens *filaPA,
    FilaDeEmbalagens *filaPB,
    Maquina *maquinaDeEmbalar,
    Fila *filaDescartados,
    FilaDeCaixas *filaDeCaixasPA,
    FilaDeCaixas *filaDeCaixasPB,
    Maquina *maquinaEmpilhadora
) {
    FILE *arquivo = fopen("relatorio_simulacao.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Imprimir Lucro
    fprintf(arquivo, "Lucro = Venda - (Custo e Prejuizo) se Lucro < 0\n\n");

    // Imprimir Tabela de Custo de Produção e Preço de Venda
    fprintf(arquivo, "Produto\tCusto de Produção (KZ)\tPreço de Venda (KZ)\n");
    fprintf(arquivo, "PA\t%.2f\t%.2f\n", 250.0, 1100.0);
    fprintf(arquivo, "PB\t%.2f\t%.2f\n\n", 220.0, 1700.0);

    // Iniciar 1ª fase (Relatório da Simulação)
    fprintf(arquivo, "-----------------------------1ª Fase---------------------------------\n");
    fprintf(arquivo, "Nº de pacotes inseridos: %d\n", filaInicial->tamanho);
    fprintf(arquivo, "Nº de pacotes enchidos: %d\n\n", maquinaDeEnchimento->qtdd_por_dia);

    // Continuar com a 2ª fase, 3ª fase, etc...
    // Exemplo:
    fprintf(arquivo, "-----------------------------2ª Fase---------------------------------\n");
    fprintf(arquivo, "Nº de pacotes validados: (nº E.pa x nº pa)(nº E.pa x nº pb)\n");
    fprintf(arquivo, "Nº de pacotes descartados: %d\n", filaDescartados->tamanho);

    fclose(arquivo);
}


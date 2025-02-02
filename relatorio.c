#include <stdio.h>
#include <stdlib.h>
#include "tadFabrica.h"

// Função para contar os elementos de uma fila, retorna 0 se a fila for inválida
int contarElementosFila(Fila *fila) {
    if (fila == NULL || fila->inicio == NULL) return 0; 
    int contador = 0;
    Lista *atual = fila->inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}
// Função para contar os elementos de uma fila, retorna 0 se a fila for inválida
int contarElementosFilaDeEmbalagens(FilaDeEmbalagens *fila) {
    if (fila == NULL || fila->inicio == NULL) return 0; 
    int contador = 0;
    listaDeEmbalagens *atual = fila->inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}
// Função para contar os elementos de uma fila de caixas, retorna 0 se a fila for inválida
int contarElementosFilaDeCaixas(FilaDeCaixas *fila) {
    if (fila == NULL || fila->inicio == NULL) return 0; 
    int contador = 0;
    ListaDeCaixas *atual = fila->inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

void gerarRelatorio(
    Fila *filaInicial,
    Maquina *maquinaDeEnchimento,
    Maquina *maquinaDeEmbalar,
    Fila *filaDescartados,
    FilaDeEmbalagens *filaPA,
    FilaDeEmbalagens *filaPB,
    FilaDeCaixas *filaDeCaixasPA,
    FilaDeCaixas *filaDeCaixasPB,
    Maquina *maquinaEmpilhadora
) {
    // Verifica se todas as estruturas foram inicializadas corretamente

	printf("\nGerando relatório...\n\n");


    // Verifica se as máquinas possuem valores válidos
    if (!maquinaDeEnchimento || !maquinaDeEmbalar || !maquinaEmpilhadora) {
        printf("Erro: Algumas máquinas não foram inicializadas corretamente.\n");
        return;
    }

    // Obtendo os totais
    int totalDeInseridos = contarElementosFila(filaInicial);
    int totalDeEmbaladosPA = contarElementosFilaDeEmbalagens(filaPA);
    int totalDeEmbaladosPB = contarElementosFilaDeEmbalagens(filaPB);
    int totalDeCaixasPA = contarElementosFilaDeCaixas(filaDeCaixasPA);
    int totalDeCaixasPB = contarElementosFilaDeCaixas(filaDeCaixasPB);
    int totalDeDescartados = contarElementosFila(filaDescartados);

    FILE *arquivo = fopen("relatorio_simulacao.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Arquivo de relatório aberto com sucesso.\n");

    // Escrevendo no arquivo
    fprintf(arquivo, "Lucro = Venda - (Custo e Prejuízo)\n\n");
    fprintf(arquivo, "Produto\tCusto de Produção (KZ)\tPreço de Venda (KZ)\tLucro\n");
    fprintf(arquivo, "PA\t   \t   250\t   \t   1100\t   \t   \t 850\n");
    fprintf(arquivo, "PB\t   \t   220\t   \t   1700\t   \t   \t 1480\n\n");

    fprintf(arquivo, "-----------------------------1ª Fase---------------------------------\n");
    fprintf(arquivo, "Nº de pacotes inseridos: %d\n", 
            (maquinaDeEnchimento ? maquinaDeEnchimento->qtdd_por_dia : 0));
    fprintf(arquivo, "Nº de pacotes enchidos: %d\n\n", 
            (maquinaDeEnchimento ? maquinaDeEnchimento->qtdd_por_dia : 0));
	fprintf(arquivo, "Tempo de processamento: %d segundos\n\n", 
            (maquinaDeEnchimento ? maquinaDeEnchimento->tempo_de_processamento : 0));

    fprintf(arquivo, "-----------------------------2ª Fase---------------------------------\n");
    fprintf(arquivo, "Nº de pacotes validados: %d (PA: %d, PB: %d)\n", 
            totalDeEmbaladosPA + totalDeEmbaladosPB);
    fprintf(arquivo, "Nº de pacotes descartados: %d\n", totalDeDescartados);
    fprintf(arquivo, "Nº de embalagens PA: %d\n", totalDeCaixasPA*4);
    fprintf(arquivo, "Nº de embalagens PB: %d\n\n", totalDeCaixasPB*3);
	fprintf(arquivo, "Tempo de processamento: %d segundos\n\n", 
            (maquinaDeEmbalar ? maquinaDeEmbalar->tempo_de_processamento : 0));
            
    fprintf(arquivo, "-----------------------------3ª Fase---------------------------------\n");
    fprintf(arquivo, "Nº de caixas PA: %d\n", totalDeCaixasPA);
    fprintf(arquivo, "Nº de caixas PB: %d\n", totalDeCaixasPB);
	fprintf(arquivo, "Tempo de processamento: %d segundos\n\n", 
            (maquinaEmpilhadora ? maquinaEmpilhadora->tempo_de_processamento : 0));

    fprintf(arquivo, "-----------------------------4ª Fase Custo de Produção (KZ) ---------------------------------\n");

    fprintf(arquivo, "Total gerado PA: %d\n", totalDeCaixasPA*4*6 * 1100);
    fprintf(arquivo, "Total gerado PB: %d\n", totalDeCaixasPB*3*4 * 1700);
    
	fprintf(arquivo, "-----------------------------4ª Fase Custo de Produção (KZ) ---------------------------------\n");
    
    fprintf(arquivo, "Total de Desperdício: %d pacotes\n\n", totalDeInseridos);

    fprintf(arquivo, "-----------------------------5ª Fase Preço de Venda (KZ) ----------------------------------------\n");
    
    fprintf(arquivo, "Possibilidade de Lucro para PA: %d\n", (1100 - 250) *totalDeCaixasPA*4*6);
    fprintf(arquivo, "Possibilidade de Lucro para PB: %d\n", (1700 - 220)* totalDeCaixasPB*3*4);

    fclose(arquivo);
    printf("Relatório gerado com sucesso!\n");
}


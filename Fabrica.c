#include <string.h>
#include "./tadFabrica.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//----------------------------   Função para iniciar uma fila  ----------------------------------------
Fila *iniciarFila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f == NULL) {
        printf("Erro de alocação de memória para a fila.\n");
        exit(1);
    }
    f->inicio = f->fim = NULL;
    return f;
}


//----------------------------   Função para iniciar uma fila de embalagens  -----------------------------
FilaDeEmbalagens *iniciarFilaDeEmbalagens() {
    FilaDeEmbalagens *fila = (FilaDeEmbalagens *)malloc(sizeof(FilaDeEmbalagens));
    if (fila == NULL) {
        printf("Erro ao alocar memória para a fila de embalagens.\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}


//----------------------------   Função para iniciar uma Máquina  --------------------------------------
Maquina *iniciarMaquina(const char *nome, int tipo) {
    Maquina *m = (Maquina *)malloc(sizeof(Maquina));
    if (m == NULL) {
        printf("Erro de alocação de memória para a máquina.\n");
        exit(1);
    }
    
    strcpy(m->nome, nome);  
    m->tipo_de_maquina = tipo;
    m->qtdd_por_dia = 0;
    m->tempo_de_processamento = 0;
    m->fila_do_produto = NULL;

    return m;
}


//----------------------------   Função para criar uma embalagem  --------------------------------------
Lista *criarEmbalagem(Pacote pacote) {
    Lista *novaLista = (Lista *)malloc(sizeof(Lista));
    if (novaLista == NULL) {
        printf("Erro ao alocar memória para a embalagem.\n");
        exit(1);
    }
    novaLista->valor = pacote;  // Agora atribui corretamente
    novaLista->proximo = NULL;
    printf("Embalagem criada com sucesso.\n");
    return novaLista;
}


//----------------------------   Inserção manual de pacotes na fila inicial  ----------------------------  
void inserirPacoteNaFilaInicialManualmente(	Fila *fila, Pacote pacote) {
    if(fila != NULL){
	    Lista *novoPacote = (Lista *)malloc(sizeof(Lista));
	    
	    if (novoPacote != NULL) {
	    	novoPacote->valor = pacote;
		    novoPacote->proximo = NULL;
		
		    if (fila->fim == NULL) {
		        fila->inicio = novoPacote;
		        fila->fim = novoPacote;
		    } else {
		        fila->fim->proximo = novoPacote;
		    }
		    fila->fim = novoPacote;
		    
		    printf("Pacote inserido com sucesso.\n");
	
	    }else{
	        printf("Erro ao alocar memória para o pacote.\n");
	        exit(1);
		}
	}else{
		printf("Erro: Fila não inicializada.\n");
	}
}


//---------------  Função para inserir pacotes automaticamente (simulação de leitura de arquivo)  --------
void inserirPacoteNaFilaInicialAutomaticamente(Fila *fila, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de pacotes");
        return;
    }

    float peso;
    char estado[10];
    int valido;

    while (fscanf(arquivo, "%f %s %d", &peso, estado, &valido) == 3) {
        Pacote pacote;
        pacote.peso = peso;
        strcpy(pacote.estado, estado);
        pacote.valido = valido;

        inserirPacoteNaFilaInicialManualmente(fila, pacote);
    }

    fclose(arquivo);
    printf("\nPacotes inseridos automaticamente com sucesso.\n");
}

/*
if (contador == 0) {
        printf("Nenhum pacote foi carregado do arquivo.\n\n");
    } else {
        printf("Pacotes inseridos automaticamente: %d\n\n", contador);
    }
*/

//----------------------------   Inserção  de embalagens na fila de embalagens  ----------------------------  
void inserirEmbalagemNaFilaDeEmbalagens(FilaDeEmbalagens *fila, Lista *embalagem) {
    if (fila != NULL) {
        listaDeEmbalagens *novaEmbalagem = (listaDeEmbalagens *)malloc(sizeof(listaDeEmbalagens));

        if (novaEmbalagem != NULL) {
            novaEmbalagem->embalagem = embalagem;
            novaEmbalagem->proximo = NULL;

            if (fila->fim == NULL) {
                fila->inicio = novaEmbalagem;
            } else {
                fila->fim->proximo = novaEmbalagem;
            }
            fila->fim = novaEmbalagem;  // Atualiza o fim da fila
            printf("Embalagem adicionada na fila de embalagens.\n\n");
        } else {
            printf("Erro ao alocar memória para embalagem.\n");
            exit(1);
        }
    } else {
        printf("Erro: Fila de embalagens não inicializada.\n");
    }
}


//------------------------------  Encher pacotes da fila  ------------------------------------------------  
void encherPacotes(Fila *fila, Maquina *maquinaDeEnchimento) {
    if (fila->inicio == NULL) {
        printf("Nenhum pacote na fila para encher.\n");
        return;
    }
	maquinaDeEnchimento->fila_do_produto = fila;
		
    int qtdEnchidos = 0;
    Lista *atual = fila->inicio;
    while (atual != NULL) {
        if (strcmp(atual->valor.estado, "vazio") == 0) {
            strcpy(atual->valor.estado, "cheio");
            qtdEnchidos++;
            maquinaDeEnchimento->qtdd_por_dia++; // Incrementa a quantidade processada na máquina
            
            printf("Nº%d  Peso: %.2f  |  Estado: %s  \n",qtdEnchidos, atual->valor.peso, atual->valor.estado);
        }
        
        atual = atual->proximo;
    }
    printf("\n\n");
    printf("Pacotes enchidos: %d\nTotal processado pela máquina: %d\n", qtdEnchidos, maquinaDeEnchimento->qtdd_por_dia);
    printf("\n\n");
}


//----------------------------   Imprimir fila  -----------------------------------------------------------
void imprimirFila(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n \n");
        return;
    }

    Lista *atual = fila->inicio;
    printf("\n \n------------------  Conteúdo da Fila ------------------ \n \n");
    while (atual != NULL) {
        printf("Peso: %.2f  |  Estado: %s  |  Válido: %s\n", 
               atual->valor.peso, atual->valor.estado, 
               atual->valor.valido ? "Sim" : "Não");
        atual = atual->proximo;
    }
}


//----------------------------   Imprimir fila de embalagens  -------------------------------------------
void imprimirFilaDeEmbalagens(FilaDeEmbalagens *fila) {
    if (fila->inicio == NULL) {
        printf("Fila de embalagens vazia.\n");
        return;
    }

    listaDeEmbalagens *atual = fila->inicio;
    int count = 1;

    printf("\n------------------  Conteúdo da Fila de Embalagens ------------------\n");
    while (atual != NULL) {
        printf("Embalagem %d:\n", count++);
        Lista *pacoteAtual = atual->embalagem;
        while (pacoteAtual != NULL) {
            printf("  - Peso: %.2f | Estado: %s | Válido: %s\n", 
                   pacoteAtual->valor.peso, 
                   pacoteAtual->valor.estado, 
                   pacoteAtual->valor.valido ? "Sim" : "Não");
            pacoteAtual = pacoteAtual->proximo;
        }
        atual = atual->proximo;
    }
}


//----------------------------   Validar pacote  ----------------------------------------------------------
void validarPacote(Pacote *pacote){
	// PA-200  e  PB-1000
	if (pacote->peso == 200 || pacote->peso == 1000) {
        pacote->valido = 1;
    } else {
        pacote->valido = 0;
    }
}


//-------------------------------   Embalar Pacotes  ---------------------------------------------------------
void embalarPacotes(
	int modo,
	Maquina *maquinaDeEmbalar,
	Fila *filaInicial,
	FilaDeEmbalagens *filaDeEmbalagensPA, 
	FilaDeEmbalagens *filaDeEmbalagensPB,
	Fila *filaDescartados
){
   
   //Peca o primeiro da fila
    Lista *atual = filaInicial->inicio;
    Lista *anterior = NULL;
   
    Lista *embalagemPA = NULL;
	Lista *embalagemPB = NULL;
	int countPA = 0;
	int countPB = 0;
	
	while (atual != NULL) {
	    validarPacote(&atual->valor);
	
	    if (atual->valor.valido) {
	        if (atual->valor.peso == 200 && (modo == 1 || modo == 3)) {
	            // Criar embalagem de PA
	            Lista *novoPacote = criarEmbalagem(atual->valor);
	            novoPacote->proximo = embalagemPA;
	            embalagemPA = novoPacote;
	            countPA++;
	
	            if (countPA == 6) { // Se completou 6 pacotes, adiciona na fila
	                inserirEmbalagemNaFilaDeEmbalagens(filaDeEmbalagensPA, embalagemPA);
	                embalagemPA = NULL; // Reseta para nova embalagem
	                countPA = 0;
	            }
	        } else if (atual->valor.peso == 1000 && (modo == 2 || modo == 3)) {
	            // Criar embalagem de PB
	            Lista *novoPacote = criarEmbalagem(atual->valor);
	            novoPacote->proximo = embalagemPB;
	            embalagemPB = novoPacote;
	            countPB++;
	
	            if (countPB == 4) { // Se completou 4 pacotes, adiciona na fila
	                inserirEmbalagemNaFilaDeEmbalagens(filaDeEmbalagensPB, embalagemPB);
	                embalagemPB = NULL; // Reseta para nova embalagem
	                countPB = 0;
	            }
	        }
	    } else {
	        inserirPacoteNaFilaInicialManualmente(filaDescartados, atual->valor);
	    }
	
	    maquinaDeEmbalar->qtdd_por_dia++;
	
	    anterior = atual;
	    atual = atual->proximo;
	    free(anterior);
	}

    filaInicial->inicio = NULL;
    filaInicial->fim = NULL;
    printf("\n\n	Pacotes embalados com sucesso!\n\n");
    
}


//----------------------------   Iniciar uma fila de caixas  --------------------------------------------------- 
FilaDeCaixas *iniciarFilaDeCaixas() {
    FilaDeCaixas *fila = (FilaDeCaixas *)malloc(sizeof(FilaDeCaixas));
    if (!fila) {
        printf("Erro ao alocar memória para a fila de caixas.\n");
        exit(1);
    }
    fila->inicio = fila->fim = NULL;
    return fila;
}


//----------------------------   Criar uma pilha  --------------------------------------------------- 
Pilha *criarCaixa() {
    Pilha *novaCaixa = (Pilha *)malloc(sizeof(Pilha));
    if (!novaCaixa) {
        printf("Erro ao alocar memória para a caixa.\n");
        exit(1);
    }
    novaCaixa->topo = NULL;
    novaCaixa->quantidade = 0;
    return novaCaixa;
}


//---------------------------- Empilhar embalagens ------------------------------------------------------
void empilharEmbalagem(Pilha *caixa, listaDeEmbalagens *embalagem) {
    if (!caixa || !embalagem) {
        printf("Erro: Caixa ou Embalagem inválida.\n");
        return;
    }

    embalagem->proximo = caixa->topo; // Adiciona a embalagem no topo da caixa
    caixa->topo = embalagem;
    caixa->quantidade++;
    printf("Caixa criada!\n");
}


//----------------------------  Inserir caixa na Fila de Caixas  -------------------------------------------------
void inserirCaixaNaFila(FilaDeCaixas *fila, Pilha *caixa) {
    if (!fila || !caixa) {
        printf("Erro: Fila ou Caixa inválida.\n");
        return;
    }

    ListaDeCaixas *novaCaixa = (ListaDeCaixas *)malloc(sizeof(ListaDeCaixas));
    if (!novaCaixa) {
        printf("Erro ao alocar memória para a lista de caixas.\n");
        exit(1);
    }

    novaCaixa->caixa = caixa;
    novaCaixa->proximo = NULL;

    if (fila->fim == NULL) {  // A fila está vazia
        fila->inicio = fila->fim = novaCaixa;
    } else {  // A fila não está vazia
        fila->fim->proximo = novaCaixa;
        fila->fim = novaCaixa;
    }

    printf("Caixa inserida na fila de caixas.\n");
}


//----------------------------  Empilhar caicas de embalagens  --------------------------------------------------------
void empilharCaixas(FilaDeEmbalagens *filaPA, FilaDeEmbalagens *filaPB, 
                     FilaDeCaixas *filaDeCaixasPA, FilaDeCaixas *filaDeCaixasPB, Maquina *MaquinaDeEmpilhamento) {
    
    Pilha *caixaAtualPA = criarCaixa();
    Pilha *caixaAtualPB = criarCaixa();
    
    listaDeEmbalagens *atualPA = filaPA->inicio;
    listaDeEmbalagens *atualPB = filaPB->inicio;
    listaDeEmbalagens *tempPA, *tempPB;
    
    int countPA = 0, countPB = 0;

    printf("Iniciando empilhamento...\n\n");

    // Empilhando PA (4 embalagens por caixa)
    while (atualPA) {
        printf("Empilhando embalagem PA...\n");
        tempPA = atualPA;
        atualPA = atualPA->proximo;

        empilharEmbalagem(caixaAtualPA, tempPA);
        countPA++;
		MaquinaDeEmpilhamento->qtdd_por_dia++;
		
        // Se a caixa estiver cheia, adiciona na fila de caixas
        if (countPA == 4) {
            printf("Caixa de PA cheia, inserindo na fila...\n\n");
            inserirCaixaNaFila(filaDeCaixasPA, caixaAtualPA);
            caixaAtualPA = criarCaixa();
            countPA = 0;
        }
		printf("\n");
        // Remover a embalagem da fila original
        //free(tempPA);
    }

    // Empilhando PB (3 embalagens por caixa)
    while (atualPB) {
        printf("Empilhando embalagem PB...\n");
        tempPB = atualPB;
        atualPB = atualPB->proximo;

        empilharEmbalagem(caixaAtualPB, tempPB);
        countPB++;
		MaquinaDeEmpilhamento->qtdd_por_dia++;
		
        // Se a caixa estiver cheia, adiciona na fila de caixas
        if (countPB == 4) {
            printf("Caixa de PB cheia, inserindo na fila...\n\n");
            inserirCaixaNaFila(filaDeCaixasPB, caixaAtualPB);
            caixaAtualPB = criarCaixa();
            countPA = 0;
        }
		printf("\n");
        // Remover a embalagem da fila original
        //free(tempPB);
    }

	// Se restarem embalagens incompletas, elas não são empilhadas
	    if (countPA > 0) {
	        printf("\nRestaram %d embalagens PA sem empilhar.\n", countPA);
	        //a caixa tem embalagens mas não chegou no limite desejado
	        free(caixaAtualPA);
	    }
	    if (countPB > 0) {
	        printf("\nRestaram %d embalagens PB sem empilhar.\n", countPB);
	        //a caixa tem embalagens mas não chegou no limite desejado
	        free(caixaAtualPB);
	    }

    printf("\nEmpilhamento concluído!\n");
}



//-----------------------------------  Imprimir fila de caixas  ----------------------------------------------
void imprimirFilaDeCaixas(FilaDeCaixas *fila) {
    if (fila->inicio == NULL) {
        printf("\nFila de caixas vazia.\n");
        return;
    }

    ListaDeCaixas *atualCaixa = fila->inicio;
    if (!atualCaixa) {
            printf("Erro: atualCaixa inválida encontrada!\n");
            return;
        }
    
    int numeroCaixa = 1;

    printf("\n------------------  Conteúdo da Fila de Caixas ------------------\n");

    while (atualCaixa != NULL) {
        printf("\nCaixa %d:\n", numeroCaixa++);
        
      Pilha *caixa = atualCaixa->caixa;
        if (!caixa) {
            printf("Erro: Caixa inválida encontrada!\n");
            return;
        }

        listaDeEmbalagens *atualEmbalagem = caixa->topo;
        if (!atualEmbalagem) {
            printf("Erro: atualEmbalagem inválida encontrada!\n");
            return;
        }
        
        int numeroEmbalagem = 1;

        while (atualEmbalagem != NULL) {
        //	printf("  Endereço da embalagem %d: %p\n\n", numeroEmbalagem, (void*)atualEmbalagem);

            printf("  Embalagem %d\n", numeroEmbalagem++);
            
              Lista *pacoteAtual = atualEmbalagem->embalagem;
           while (pacoteAtual != NULL) {
           	//printf("    - Endereço do pacote: %p\n\n", (void*)pacoteAtual);

                if (pacoteAtual->valor.peso > 0) { // Evita pacotes corrompidos
                    printf("    - Peso: %.2f | Estado: %s\n", pacoteAtual->valor.peso, pacoteAtual->valor.estado);
                }
                pacoteAtual = pacoteAtual->proximo;
            }
        
           
            atualEmbalagem = atualEmbalagem->proximo;
        }
        atualCaixa = atualCaixa->proximo;
    }

    printf("\n---------------------------------------------------------------\n");
}


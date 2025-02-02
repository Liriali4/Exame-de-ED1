#ifndef TAD_FABRICA_H
#define TAD_FABRICA_H
#include <stdbool.h>
#include <stdio.h>

//----------------------------  Estruturas da fila  ---------------------------------------------------------

typedef struct pacote {
    float peso;		// 200ml(PA) ou 1L(PB)
    char estado[8]; 	// vazio ou cheio
    bool valido; 	//pacote válido ou inválido
} Pacote;

typedef struct no {
    Pacote valor;	// o pacote
    struct no *proximo;	// ponteiro do próximo pacote
} Lista;

typedef struct fila {
    Lista *inicio;	// ponteiro do inicio da fila
    Lista *fim;		// ponteiro do final da fila
} Fila;


//----------------------------  Estruturas da Máquina  ---------------------------------------------------------

typedef struct maquina{
	char nome[20];		// nome atribuída a máquina
	int tipo_de_maquina;	// de (1)enchimento, (2)embalamento ou (3)empilhamento
	int qtdd_por_dia;		// quantidade de pacotes processados por dia
	float tempo_de_processamento; //tempo de processamento
	Fila * fila_do_produto; // fila associada a máquina
}Maquina;


typedef struct listadeembalagens {
    Lista *embalagem;  // Garda o ponteiro da lista (embalagem)
    struct  listadeembalagens * proximo; // Ponteiro da proxima embalagem
} listaDeEmbalagens;

typedef struct filadeembalagens {
    listaDeEmbalagens *inicio;	// ponteiro do inicio da fila de embalagens
    listaDeEmbalagens *fim;		// ponteiro do final da fila de embalagens
} FilaDeEmbalagens;

typedef struct pilha {  // Caixa de Embalagens
    listaDeEmbalagens *topo;  // Cada caixa contém embalagens 4-PA ou 3-PB
    int quantidade;  // Número de embalagens na caixa
} Pilha;

typedef struct listadecaixas {
    Pilha *caixa;  // Ponteiro para a pilha (caixa de embalagens)
    struct listadecaixas *proximo; // Ponteiro para a próxima caixa
} ListaDeCaixas;

typedef struct filaDeCaixas {
    ListaDeCaixas *inicio;  // Ponteiro para o início da lista de caixas
    ListaDeCaixas *fim;  // Ponteiro para o final da lista de caixas
} FilaDeCaixas;


//----------------------------  Funções da Fila e listas ---------------------------------------------------------

Fila * iniciarFila();// inicializar lista normal
FilaDeEmbalagens *iniciarFilaDeEmbalagens();// inicializar lista de embalaos

void inserirPacoteNaFilaInicialManualmente(Fila *fila, Pacote pacote); //pedir os dados ao utilizador
void inserirPacoteNaFilaInicialAutomaticamente(Fila *fila, const char *nomeArquivo);//receber ficheiro com os pacotes a inserir na fila
void imprimirFila(Fila *fila);//imprime a lista normal
void imprimirFilaDeEmbalagens(FilaDeEmbalagens *fila);// imprime a lista de embalados
Lista * criarEmbalagem(Pacote pacote); //será usada num loop para criar embalagem


//----------------------------  Funções da Máquina  ---------------------------------------------------------

Maquina * iniciarMaquina(const char *nome, int tipo);

void encherPacotes(Fila *fila, Maquina *maquinaDeEnchimento);//enche todos pacotes independentemente do tipo ou se é valido

void validarPacote(Pacote *pacote);//verificar se nada está fora do padrão (Validar um de cada vez);

void embalarPacotes(
	int modo,
	Maquina *maquinaDeEmbalar,
	Fila *filaInicial,
	FilaDeEmbalagens *filaDeEmbaladosPA, 
	FilaDeEmbalagens *filaDeEmbaladosPB,
	Fila *filaDescartados
	);//por numa fila de acordo com o tipo, 6 para PA e 4 para PB

Pilha *criarCaixa(); //criar uma caixa

void empilharEmbalagem(Pilha *caixa, listaDeEmbalagens *embalagem);//preenche a pilha com embalagen

void empilharCaixas(FilaDeEmbalagens *filaPA, FilaDeEmbalagens *filaPB, FilaDeCaixas *filaDeCaixasPA, FilaDeCaixas *filaDeCaixasPB, Maquina *maquinaEmpilhadora);

FilaDeCaixas *iniciarFilaDeCaixas(); //Iniciar a fila de caixas

void inserirCaixaNaFila(FilaDeCaixas *fila, Pilha *caixa);//leva para a fila de caixas

void imprimirFilaDeCaixas(FilaDeCaixas *fila);

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
);


#endif // TAD_FABRICA_H


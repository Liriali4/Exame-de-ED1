#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "./Fabrica.c"
#include "./relatorio.c"

int menuModoDeInsercao() {
    int x;
    printf("1- Automático\n");
    printf("2- Manual\n");
    printf("R: ");
    scanf("%d", &x);
    return x;
}

int menuContinuar() {
    int x;
    printf("\n\n");
    printf("2- Continuar inserção\n");
    printf("3- Ir para máquina de enchimento\n");
    printf("0- Encerrar o programa\n");
    printf("R: ");
    scanf("%d", &x);
    return x;
}

int menuIrParaEmbalamento() {
    int x;
    printf("\n\n");
    printf("4- Ir para máquina de embalamento\n");
    printf("0- Encerrar o programa\n");
    printf("R: ");
    scanf("%d", &x);
    return x;
}

int menuEscolherQualEmbalar(){
    int x;
    printf("1- Embalar pacotes do tipo PA\n");
    printf("2- Embalar pacotes do tipo PB\n");
    printf("3- Embalar PA e PB simultaneamente\n");
    printf("0- Encerrar o programa\n");
    printf("R: ");
    scanf("%d", &x);
    return x;
}

int menuAposEmbalamento() {
    int x;
    printf("\n\n");
    printf("5- Imprimir listas de embalagens\n");
    printf("6- Ir para a máquina de empilhamento\n");
    printf("0- Encerrar o programa\n");
    printf("R: ");
    scanf("%d", &x);
    return x;
}

int menuAposEmpilhamento() {
    int x;
    printf("\n\n");
    printf("7- Imprimir caixas empilhadas\n");
    printf("8- Gerar relatório\n");
    printf("0- Encerrar o programa\n");
    printf("R: ");
    scanf("%d", &x);
    return x;
}

int main() {
    setlocale(LC_ALL, "portuguese");

    int opc;
    Pacote pacote;

    // Inicializar Filas
    Fila *filaInicial = iniciarFila();
    FilaDeEmbalagens *filaDeEmbalagensPA = iniciarFilaDeEmbalagens();
    FilaDeEmbalagens *filaDeEmbalagensPB = iniciarFilaDeEmbalagens();
    Fila *filaDescartados = iniciarFila(); 
    
    FilaDeCaixas *filaDeCaixasPA = iniciarFilaDeCaixas();
    FilaDeCaixas *filaDeCaixasPB = iniciarFilaDeCaixas();

    // Inicializar Máquinas
    Maquina *MaquinaDeEnchimento = iniciarMaquina("Enchedora", 1);
    Maquina *MaquinaDeEmbalamento = iniciarMaquina("Embaladora", 2);
    Maquina *MaquinaDeEmpilhamento = iniciarMaquina("Empilhadora", 3);

    printf("Inserção de pacote, escolha o modo:\n\n");
    opc = menuModoDeInsercao();

    while (1) {
        switch (opc) {
            case 1: { // Inserção Automática
                inserirPacoteNaFilaInicialAutomaticamente(filaInicial, "pacotes.txt");

                opc = menuContinuar();
                continue;
            }

            case 2: { // Inserção Manual
                do {
                    printf("Digite o peso do pacote: ");
                    scanf("%f", &pacote.peso);
                    strcpy(pacote.estado, "vazio");
                    pacote.valido = 1;
                    inserirPacoteNaFilaInicialManualmente(filaInicial, pacote);
                    opc = menuContinuar();
                } while (opc == 2);
                continue;
            }

            case 3: { // Máquina de Enchimento
                printf("------------------------------------ Máquina de Enchimento ------------------------------\n\n");
                encherPacotes(filaInicial, MaquinaDeEnchimento);
                opc = menuIrParaEmbalamento();
                continue;
            }

            case 4: { // Máquina de Embalamento
                printf("------------------------------------ Máquina de Embalamento ------------------------------\n\n");
                int modoDeEmbalar = menuEscolherQualEmbalar();
                if (modoDeEmbalar == 0) {
                    opc = modoDeEmbalar;
                    break;
                }
                embalarPacotes(modoDeEmbalar, MaquinaDeEmbalamento, filaInicial, filaDeEmbalagensPA, filaDeEmbalagensPB, filaDescartados);

                // Novo menu após a embalagem
                while (1) {
                    int escolha = menuAposEmbalamento();
                    switch (escolha) {
                        case 5: // Imprimir listas de embalagens
                            printf("\n\n_________________________________ Embalagens PA _________________________________\n\n");
                            imprimirFilaDeEmbalagens(filaDeEmbalagensPA);
                            printf("\n\n_________________________________ Embalagens PB _________________________________\n\n");
                            imprimirFilaDeEmbalagens(filaDeEmbalagensPB);
                            break;

                        case 6: // Ir para a máquina de empilhamento
                            printf("------------------------------------ Máquina de Empilhamento ------------------------------\n\n");
                            empilharCaixas(filaDeEmbalagensPA, filaDeEmbalagensPB, filaDeCaixasPA, filaDeCaixasPB, MaquinaDeEmpilhamento);
                            opc = 7; // Ir direto para a opção de exibir caixas
                            break;

                        case 0: // Encerrar o programa
                            printf("Encerrando o programa...\n");
                            exit(0);

                        default:
                            printf("Escolha uma opção válida.\n");
                    }

                    if (escolha == 6 || escolha == 0) {
                        break; // Sai do loop após empilhar ou encerrar
                    }
                }
                break;
            }

            case 7: { // Exibir caixas empilhadas
                while (1) {
                    int escolha = menuAposEmpilhamento();
                    switch (escolha) {
                        case 7:
                            printf("\n\n			Caixas do tipo PA \n\n");
							imprimirFilaDeCaixas(filaDeCaixasPA);
							
							printf("\n\n			Caixas do tipo PB \n\n");
							imprimirFilaDeCaixas(filaDeCaixasPB);

                            break;
						case 8:// gerar rellatório
						
							gerarRelatorio(
							    filaInicial,
							    MaquinaDeEnchimento,
							    filaDeEmbalagensPA,
							    filaDeEmbalagensPB,
								MaquinaDeEmbalamento,
							    filaDescartados,
							    filaDeCaixasPA,
							    filaDeCaixasPB,
							    MaquinaDeEmpilhamento
							);

                        break;
                        case 0:
                            printf("Encerrando o programa...\n");
                            exit(0);

                        default:
                            printf("Escolha uma opção válida.\n");
                    }
                }
                break;
            }

            case 0:
                printf("Encerrando o programa...\n");
                exit(0);

            default:
                printf("Escolha uma opção válida\n\n");
                opc = menuContinuar();
                continue;
        }
    }
}


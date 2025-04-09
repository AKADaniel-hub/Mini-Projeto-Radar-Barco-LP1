#include <stdio.h>
#include <stdlib.h>

void lerTabelaDeFicheiro(char tabela[20][80], const char *ficheiro);

void consultarCoordenadasBarco(char tabela[20][80]);

void consultarCoordenadas(char tabelaAntes[20][80], char tabelaDepois[20][80]);

void imprimirTabela(char tabela[20][80]);

void movimentoDepois(int linha, int coluna, char tabela[20][80], char barcoEscolhido);

void listarMovimentos(char tabelaAntes[20][80], char tabelaDepois[20][80]);

int main(void) {
    int opcaoMenu;
    char tabelaAntes[20][80];
    char tabelaDepois[20][80];

    lerTabelaDeFicheiro(tabelaAntes, "tabela_antes.txt");
    lerTabelaDeFicheiro(tabelaDepois, "tabela_depois.txt");


    while (opcaoMenu != 5) {
        opcaoMenu = 0;

        printf("\nMenu:\n");

        printf("1 - Imprimir tabela \"antes\"\n");

        printf("2 - Imprimir tabela \"depois\"\n");

        printf("3 - Consultar as coordenadas de um barco\n");

        printf("4 - Listar barcos que se moveram\n");

        printf("5 - Sair\n");

        printf("Escolha uma opcao: ");


        scanf(" %d", &opcaoMenu);


        switch (opcaoMenu) {
            case 1:
                printf("\nTabela Antes: \n");
                imprimirTabela(tabelaAntes);
                break;
            case 2:
                printf("\nTabela Depois:\n");
                imprimirTabela(tabelaDepois);
                break;
            case 3:

                consultarCoordenadas(tabelaAntes, tabelaDepois);
                break;
            case 4:

                listarMovimentos(tabelaAntes, tabelaDepois);
                break;
            case 5:
                printf("A sair do programa...");
                return 0;
            default:


                printf("Opcao invalida. Tente novamente.\n");

            //limpa o buffer de entrada
                while (getchar() != '\n');
                break;
        }
    }

    return 0;
}

struct Barco {
    char id; // 'A', 'B', 'C', 'D' ou 'E'
    int linha;
    int coluna;
};


/*
 * Função para ler uma tabela de um ficheiro e armazená-la numa matriz bidimensional.
 *
 * @param tabela      Matriz de caracteres com 20 linhas e 80 colunas,
 *                    onde os dados do ficheiro serão armazenados.
 * @param nomeFicheiro Nome do ficheiro a ser lido.
 */

void lerTabelaDeFicheiro(char tabela[20][80], const char *nomeFicheiro) {
    // Abre o ficheiro para leitura
    FILE *ficheiro = fopen(nomeFicheiro, "r");

    // Verifica se o ficheiro foi aberto corretamente
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro %s\n", nomeFicheiro);
        return; // Se não for possível abrir o ficheiro, a função termina imediatamente
    }

    // Percorre a matriz para preencher os 20x80 caracteres com dados do ficheiro
    for (int i = 0; i < 20; i++) {
        // Loop externo para as 20 linhas
        for (int j = 0; j < 80; j++) {
            // Loop interno para as 80 colunas
            char c = fgetc(ficheiro); // Lê um único carácter do ficheiro

            // Se o carácter for uma nova linha, ignora-o e lê o próximo carácter
            if (c == '\n') {
                c = fgetc(ficheiro);
            }

            // Armazena o carácter lido na matriz
            tabela[i][j] = c;
        }
    }

    // Fecha o ficheiro após a leitura
    fclose(ficheiro);
}

void consultarCoordenadas(char tabelaAntes[20][80], char tabelaDepois[20][80]) {
    int tabelaEscolhida;

    printf("Qual a tabela que quer consultar? Tabela antes - 1 Tabela depois - 2\n");
    scanf(" %d", &tabelaEscolhida);

    if (tabelaEscolhida == 1) {
        consultarCoordenadasBarco(tabelaAntes);
    } else if (tabelaEscolhida == 2) {
        consultarCoordenadasBarco(tabelaDepois);
    } else {
        printf("Opcao invalida. Tente novamente.\n");
    }
}

void imprimirTabela(char tabela[20][80]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 80; j++) {
            printf("%c", tabela[i][j]);
        }
        printf("\n");
    }
}

void consultarCoordenadasBarco(char tabela[20][80]) {
    char barcoEscolhido;

    printf("Escolha o barco que quer encontrar:\n");
    scanf(" %c", &barcoEscolhido);


    struct Barco barcos[5]; // os 5 barcos (A, B, C, D, E)
    int barcoCount = 0;

    //preenchemos a estrutura de barcos
    for (int linha = 0; linha < 20; linha++) {
        for (int coluna = 0; coluna < 80; coluna++) {
            if (tabela[linha][coluna] != '.' && tabela[linha][coluna] != ' ') {
                int existe = 0;
                for (int k = 0; k < barcoCount; k++) {
                    if (barcos[k].id == tabela[linha][coluna]) {
                        existe = 1;
                        break;
                    }
                }
                if (!existe) {
                    barcos[barcoCount].id = tabela[linha][coluna];
                    barcos[barcoCount].linha = linha + 1;
                    barcos[barcoCount].coluna = coluna + 1;
                    barcoCount++;
                }
            }
        }
    }

    // procuramo o barco escolhido
    int encontrado = 0;
    for (int i = 0; i < barcoCount; i++) {
        // se nao tiver isto vai imprimir todas as cordenadas
        if (barcos[i].id == barcoEscolhido) {
            printf("O barco %c encontra-se na linha %d e na coluna %d\n", barcoEscolhido, barcos[i].linha,
                   barcos[i].coluna);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Barco nao encontrado!\n");
    }
}


void listarMovimentos(char tabelaAntes[20][80], char tabelaDepois[20][80]) {
    char barcoEscolhido;

    int linha = 0, coluna = 0;

    printf("Escolha qual o barco que quer listar o movimento:\n");
    scanf(" %c", &barcoEscolhido);

    for (linha = 0; linha < 20; linha++) {
        for (coluna = 0; coluna < 80; coluna++) {
            if (tabelaAntes[linha][coluna] != '.' && tabelaAntes[linha][coluna] == barcoEscolhido) {
                movimentoDepois(linha, coluna, tabelaDepois, barcoEscolhido);
                return;
            }
        }
    }
}


void movimentoDepois(int linhaPosAntes, int colunaPosAntes, char tabelaDepois[20][80], char barcoEscolhido) {

    int linhaPosDepois = 0, colunaPosDepois = 0;

    for (int linha = 0; linha < 20; linha++) {
        for (int coluna = 0; coluna < 80; coluna++) {
            if (tabelaDepois[linha][coluna] != '.' && tabelaDepois[linha][coluna] == barcoEscolhido) {
                linhaPosDepois = linha;
                colunaPosDepois = coluna;
                break;
            }
        }
    }


    if (linhaPosDepois > linhaPosAntes) {
        printf("Movimento: O barco moveu-se para baixo.\n");
        return;
    }
    if (linhaPosDepois < linhaPosAntes) {
        printf("Movimento: O barco moveu-se para cima.\n");
        return;
    }

    if (colunaPosDepois > colunaPosAntes) {
        printf("Movimento: O barco moveu-se para a direita.\n");
        return;
    }
    if (colunaPosDepois < colunaPosAntes) {
        printf("Movimento: O barco moveu-se para a esquerda.\n");
        return;
    }
    printf("Movimento: O barco nao se moveu.\n");

}

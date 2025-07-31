#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define NAVIO 3 // Constante representando o navio no tabuleiro

// Função recursiva para validar se o navio (horizontal/vertical) cabe no tabuleiro
// Parameters:
//   linha, coluna: coordenadas iniciais do navio
//   tamanho: tamanho do navio
//   horizontal: 1 se horizontal, 0 se vertical
//   pos: índice da parte do navio atual a validar
// Retorna 1 se válido, 0 se inválido
int valida_posicao(int linha, int coluna, int tamanho, int horizontal, int pos) {
    if (pos == tamanho) {
        return 1; // todas as posições validadas
    }
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        return 0; // fora do tabuleiro
    }
    if (horizontal) {
        return valida_posicao(linha, coluna + 1, tamanho, horizontal, pos + 1);
    } else {
        return valida_posicao(linha + 1, coluna, tamanho, horizontal, pos + 1);
    }
}

/* 
// Alternativa iterativa para validar posição linear:
// int valida_posicao_iterativa(int linha, int coluna, int tamanho, int horizontal) {
//     if (horizontal) {
//         return (coluna >= 0 && coluna + tamanho - 1 < TAM_TABULEIRO && linha >= 0 && linha < TAM_TABULEIRO);
//     } else {
//         return (linha >= 0 && linha + tamanho - 1 < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO);
//     }
// }
*/

// Função recursiva para validar se um navio diagonal cabe no tabuleiro
// diagonalPrincipal: 1 para diagonal principal (baixo-direita), 0 para diagonal secundária (baixo-esquerda)
int valida_posicao_diagonal(int linha, int coluna, int tamanho, int diagonalPrincipal, int pos) {
    if (pos == tamanho)
        return 1;
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO)
        return 0;
    if (diagonalPrincipal)
        return valida_posicao_diagonal(linha + 1, coluna + 1, tamanho, diagonalPrincipal, pos + 1);
    else
        return valida_posicao_diagonal(linha + 1, coluna - 1, tamanho, diagonalPrincipal, pos + 1);
}

// Função que verifica se as posições do navio (horizontal ou vertical) estão livres (sem sobreposição)
int verifica_sobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        if (tabuleiro[l][c] == NAVIO) {
            return 0; // posição já ocupada
        }
    }
    return 1; // sem sobreposição
}

// Função que verifica sobreposição para navios diagonais
int verifica_sobreposicao_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = diagonalPrincipal ? (coluna + i) : (coluna - i);
        if (tabuleiro[l][c] == NAVIO) {
            return 0; // posição já ocupada
        }
    }
    return 1; // sem sobreposição
}

// Função para posicionar navio horizontal ou vertical
void posiciona_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }
}

// Função para posicionar navio diagonal
void posiciona_navio_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = diagonalPrincipal ? (coluna + i) : (coluna - i);
        tabuleiro[l][c] = NAVIO;
    }
}

// Função para imprimir o tabuleiro no console
void imprime_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("  ");
    for (int c = 0; c < TAM_TABULEIRO; c++) {
        printf("%d ", c);
    }
    printf("\n");
    for (int linha = 0; linha < TAM_TABULEIRO; linha++) {
        printf("%d ", linha);
        for (int coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {{0}};

    // Coordenadas iniciais para os quatro navios (definidas no código)
    int linha_navio_horizontal = 2;
    int coluna_navio_horizontal = 3;

    int linha_navio_vertical = 5;
    int coluna_navio_vertical = 7;

    int linha_navio_diag_principal = 0;
    int coluna_navio_diag_principal = 0;

    int linha_navio_diag_secundaria = 0;
    int coluna_navio_diag_secundaria = TAM_TABULEIRO - 1; // coluna 9

    // Validação dos navios linearmente orientados
    if (!valida_posicao(linha_navio_horizontal, coluna_navio_horizontal, TAM_NAVIO, 1, 0)) {
        printf("Navio horizontal nao cabe no tabuleiro.\n");
        return 1;
    }

    if (!valida_posicao(linha_navio_vertical, coluna_navio_vertical, TAM_NAVIO, 0, 0)) {
        printf("Navio vertical nao cabe no tabuleiro.\n");
        return 1;
    }

    // Validação dos navios diagonais
    if (!valida_posicao_diagonal(linha_navio_diag_principal, coluna_navio_diag_principal, TAM_NAVIO, 1, 0)) {
        printf("Navio diagonal principal nao cabe no tabuleiro.\n");
        return 1;
    }

    if (!valida_posicao_diagonal(linha_navio_diag_secundaria, coluna_navio_diag_secundaria, TAM_NAVIO, 0, 0)) {
        printf("Navio diagonal secundaria nao cabe no tabuleiro.\n");
        return 1;
    }

    // Verificação de sobreposição --- Importante verificar na ordem certa

    // Horizontal
    if (!verifica_sobreposicao(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, TAM_NAVIO, 1)) {
        printf("Navio horizontal sobrepoe outro navio.\n");
        return 1;
    }
    posiciona_navio(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, TAM_NAVIO, 1);

    // Vertical
    if (!verifica_sobreposicao(tabuleiro, linha_navio_vertical, coluna_navio_vertical, TAM_NAVIO, 0)) {
        printf("Navio vertical sobrepoe outro navio.\n");
        return 1;
    }
    posiciona_navio(tabuleiro, linha_navio_vertical, coluna_navio_vertical, TAM_NAVIO, 0);

    // Diagonal principal
    if (!verifica_sobreposicao_diagonal(tabuleiro, linha_navio_diag_principal, coluna_navio_diag_principal, TAM_NAVIO, 1)) {
        printf("Navio diagonal principal sobrepoe outro navio.\n");
        return 1;
    }
    posiciona_navio_diagonal(tabuleiro, linha_navio_diag_principal, coluna_navio_diag_principal, TAM_NAVIO, 1);

    // Diagonal secundária
    if (!verifica_sobreposicao_diagonal(tabuleiro, linha_navio_diag_secundaria, coluna_navio_diag_secundaria, TAM_NAVIO, 0)) {
        printf("Navio diagonal secundaria sobrepoe outro navio.\n");
        return 1;
    }
    posiciona_navio_diagonal(tabuleiro, linha_navio_diag_secundaria, coluna_navio_diag_secundaria, TAM_NAVIO, 0);

    // Imprime o tabuleiro com os 4 navios posicionados
    imprime_tabuleiro(tabuleiro);

    return 0;
}

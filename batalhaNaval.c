#include <stdio.h>

// Constantes para configuração do tabuleiro e navios
#define TAM_TABULEIRO 10     // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3          // Tamanho fixo dos navios (todos de tamanho 3)
#define NAVIO 3              // Valor para representar o navio no tabuleiro

/******************************************************************************/
/* Função para verificar se um navio reto (horizontal ou vertical) cabe       */
/* dentro dos limites do tabuleiro                                            */
/* horizontal = 1 para navio horizontal; horizontal = 0 para navio vertical   */
/******************************************************************************/
int valida_posicao_reta(int linha, int coluna, int tamanho, int horizontal) {
    if (horizontal)
        return (coluna >= 0 && coluna + tamanho - 1 < TAM_TABULEIRO && linha >= 0 && linha < TAM_TABULEIRO);
    else
        return (linha >= 0 && linha + tamanho - 1 < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO);
}

/******************************************************************************/
/* Função para verificar se um navio diagonal cabe dentro do tabuleiro        */
/* diagonalPrincipal = 1: diagonal ↘ (principal), diagonalPrincipal = 0: ↙    */
/******************************************************************************/
int valida_posicao_diagonal(int linha, int coluna, int tamanho, int diagonalPrincipal) {
    if (diagonalPrincipal)
        return (linha >= 0 && linha + tamanho - 1 < TAM_TABULEIRO &&
                coluna >= 0 && coluna + tamanho - 1 < TAM_TABULEIRO);
    else
        return (linha >= 0 && linha + tamanho - 1 < TAM_TABULEIRO &&
                coluna - (tamanho - 1) >= 0 && coluna < TAM_TABULEIRO);
}

/******************************************************************************/
/* Função para verificar sobreposição em navio reto (horizontal/vertical)     */
/* Retorna 1 se NÃO houver sobreposição, 0 caso contrário                     */
/******************************************************************************/
int verifica_sobreposicao_reta(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        if (tabuleiro[l][c] == NAVIO)
            return 0;
    }
    return 1; // livre
}

/******************************************************************************/
/* Função para verificar sobreposição em navio diagonal                       */
/******************************************************************************/
int verifica_sobreposicao_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = diagonalPrincipal ? (coluna + i) : (coluna - i);
        if (tabuleiro[l][c] == NAVIO)
            return 0;
    }
    return 1; // livre
}

/******************************************************************************/
/* Função para posicionar navio reto (horizontal/vertical)                    */
/******************************************************************************/
void posiciona_navio_reta(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }
}

/******************************************************************************/
/* Função para posicionar navio diagonal                                      */
/******************************************************************************/
void posiciona_navio_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = diagonalPrincipal ? (coluna + i) : (coluna - i);
        tabuleiro[l][c] = NAVIO;
    }
}

/******************************************************************************/
/* Função para imprimir o tabuleiro no console, com alinhamento               */
/******************************************************************************/
void imprime_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("    "); // Espaço para alinhamento dos números de coluna
    for (int c = 0; c < TAM_TABULEIRO; c++)
        printf("%2d ", c);
    printf("\n");
    for (int l = 0; l < TAM_TABULEIRO; l++) {
        printf("%2d |", l);
        for (int c = 0; c < TAM_TABULEIRO; c++) {
            printf(" %d ", tabuleiro[l][c]);
        }
        printf("\n");
    }
}

int main() {
    // 1. Inicializa o tabuleiro com água (0 em todas as posições)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {{0}};

    // 2. Coordenadas iniciais dos navios definidas no código
    // (Escolha posições que não causem sobreposição!)
    int linha_h = 2, coluna_h = 3;                // Navio horizontal inicia em (2,3)
    int linha_v = 5, coluna_v = 7;                // Navio vertical inicia em (5,7)
    int linha_diag_principal = 0, coluna_diag_principal = 0;       // Diagonal ↘ começa em (0,0)
    int linha_diag_secundaria = 0, coluna_diag_secundaria = 9;     // Diagonal ↙ começa em (0,9)

    // 3. Validação dos navios antes de posicionar
    if (!valida_posicao_reta(linha_h, coluna_h, TAM_NAVIO, 1)) {
        printf("ERRO: Navio horizontal inválido.\n");
        return 1;
    }
    if (!valida_posicao_reta(linha_v, coluna_v, TAM_NAVIO, 0)) {
        printf("ERRO: Navio vertical inválido.\n");
        return 1;
    }
    if (!valida_posicao_diagonal(linha_diag_principal, coluna_diag_principal, TAM_NAVIO, 1)) {
        printf("ERRO: Navio diagonal principal inválido.\n");
        return 1;
    }
    if (!valida_posicao_diagonal(linha_diag_secundaria, coluna_diag_secundaria, TAM_NAVIO, 0)) {
        printf("ERRO: Navio diagonal secundária inválido.\n");
        return 1;
    }

    // 4. Verificação de sobreposição e posicionamento dos navios (ordem importa!)
    if (!verifica_sobreposicao_reta(tabuleiro, linha_h, coluna_h, TAM_NAVIO, 1)) {
        printf("ERRO: Sobreposição no navio horizontal.\n");
        return 1;
    }
    posiciona_navio_reta(tabuleiro, linha_h, coluna_h, TAM_NAVIO, 1);

    if (!verifica_sobreposicao_reta(tabuleiro, linha_v, coluna_v, TAM_NAVIO, 0)) {
        printf("ERRO: Sobreposição no navio vertical.\n");
        return 1;
    }
    posiciona_navio_reta(tabuleiro, linha_v, coluna_v, TAM_NAVIO, 0);

    if (!verifica_sobreposicao_diagonal(tabuleiro, linha_diag_principal, coluna_diag_principal, TAM_NAVIO, 1)) {
        printf("ERRO: Sobreposição no navio diagonal principal.\n");
        return 1;
    }
    posiciona_navio_diagonal(tabuleiro, linha_diag_principal, coluna_diag_principal, TAM_NAVIO, 1);

    if (!verifica_sobreposicao_diagonal(tabuleiro, linha_diag_secundaria, coluna_diag_secundaria, TAM_NAVIO, 0)) {
        printf("ERRO: Sobreposição no navio diagonal secundária.\n");
        return 1;
    }
    posiciona_navio_diagonal(tabuleiro, linha_diag_secundaria, coluna_diag_secundaria, TAM_NAVIO, 0);

    // 5. Imprimir o tabuleiro final, mostrando água (0) e navios (3)
    printf("\nTabuleiro final:\n\n");
    imprime_tabuleiro(tabuleiro);

    return 0;
}

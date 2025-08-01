#include <stdio.h>

// -------------------- Constantes ----------------------
#define TAM_TABULEIRO 10    // Tabuleiro 10x10
#define TAM_NAVIO 3         // Navios sempre tamanho 3
#define NAVIO 3             // Valor de navio
#define HABILIDADE 5        // Valor para área de efeito
#define TAM_HABILIDADE 5    // Matrizes de habilidade 5x5

// ----------------- Protótipos das Funções -----------------
int valida_posicao_reta(int linha, int coluna, int tamanho, int horizontal);
int valida_posicao_diagonal(int linha, int coluna, int tamanho, int diagonalPrincipal);
int verifica_sobreposicao_reta(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal);
int verifica_sobreposicao_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal);
void posiciona_navio_reta(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal);
void posiciona_navio_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal);
void imprime_tabuleiro_visual(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
void cria_habilidade_cone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void cria_habilidade_cruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void cria_habilidade_octaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void sobrepoe_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna);

// ---------------- Implementação das Funções ----------------

// Valida posicionamento de navio reto
int valida_posicao_reta(int linha, int coluna, int tamanho, int horizontal) {
    if (horizontal)
        return (coluna >= 0 && coluna + tamanho - 1 < TAM_TABULEIRO && linha >= 0 && linha < TAM_TABULEIRO);
    else
        return (linha >= 0 && linha + tamanho - 1 < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO);
}

// Valida posicionamento de navio diagonal
int valida_posicao_diagonal(int linha, int coluna, int tamanho, int diagonalPrincipal) {
    if (diagonalPrincipal)
        return (linha >= 0 && linha + tamanho - 1 < TAM_TABULEIRO &&
                coluna >= 0 && coluna + tamanho - 1 < TAM_TABULEIRO);
    else
        return (linha >= 0 && linha + tamanho - 1 < TAM_TABULEIRO &&
                coluna - (tamanho - 1) >= 0 && coluna < TAM_TABULEIRO);
}

// Verifica sobreposição de navio reto
int verifica_sobreposicao_reta(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        if (tabuleiro[l][c] == NAVIO)
            return 0;
    }
    return 1;
}

// Verifica sobreposição de navio diagonal
int verifica_sobreposicao_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = diagonalPrincipal ? (coluna + i) : (coluna - i);
        if (tabuleiro[l][c] == NAVIO)
            return 0;
    }
    return 1;
}

// Posiciona navio reto
void posiciona_navio_reta(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }
}

// Posiciona navio diagonal
void posiciona_navio_diagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int diagonalPrincipal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = diagonalPrincipal ? (coluna + i) : (coluna - i);
        tabuleiro[l][c] = NAVIO;
    }
}

// Cria matriz cone (cone apontando para baixo)
void cria_habilidade_cone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++) {
            habilidade[linha][coluna] = 0;
            int minimo = centro - linha;
            int maximo = centro + linha;
            if (linha >= 0 && minimo <= coluna && coluna <= maximo && coluna >= 0 && coluna < TAM_HABILIDADE)
                habilidade[linha][coluna] = 1;
        }
    }
}

// Cria matriz cruz
void cria_habilidade_cruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int linha = 0; linha < TAM_HABILIDADE; linha++)
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++)
            habilidade[linha][coluna] = (linha == centro || coluna == centro) ? 1 : 0;
}

// Cria matriz octaedro (losango)
void cria_habilidade_octaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++) {
            int dist = (linha > centro ? linha - centro : centro - linha) + (coluna > centro ? coluna - centro : centro - coluna);
            habilidade[linha][coluna] = (dist <= 2) ? 1 : 0;
        }
    }
}

// Sobrepõe uma matriz de habilidade ao tabuleiro
void sobrepoe_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha_tab = origemLinha - meio + i;
                int col_tab = origemColuna - meio + j;
                if (linha_tab >= 0 && linha_tab < TAM_TABULEIRO && col_tab >= 0 && col_tab < TAM_TABULEIRO) {
                    if (tabuleiro[linha_tab][col_tab] != NAVIO) // Não sobrescreve navio
                        tabuleiro[linha_tab][col_tab] = HABILIDADE;
                }
            }
        }
    }
}

// Imprime tabuleiro visualmente
void imprime_tabuleiro_visual(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("    ");
    for (int c = 0; c < TAM_TABULEIRO; c++)
        printf("%2d ", c);
    printf("\n");
    for (int l = 0; l < TAM_TABULEIRO; l++) {
        printf("%2d |", l);
        for (int c = 0; c < TAM_TABULEIRO; c++) {
            if (tabuleiro[l][c] == 0)
                printf(" ~ "); // água
            else if (tabuleiro[l][c] == NAVIO)
                printf(" N "); // navio
            else if (tabuleiro[l][c] == HABILIDADE)
                printf(" * "); // área habilidade
            else
                printf(" ? "); // valor inesperado
        }
        printf("\n");
    }
}

// ---------------- Função principal -----------------
int main() {
    // Inicializa tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    for (int i = 0; i < TAM_TABULEIRO; i++)
        for (int j = 0; j < TAM_TABULEIRO; j++)
            tabuleiro[i][j] = 0;

    // Posiciona navios
    int linha_h = 2, coluna_h = 3;
    int linha_v = 5, coluna_v = 7;
    int linha_diag_principal = 0, coluna_diag_principal = 0;
    int linha_diag_secundaria = 0, coluna_diag_secundaria = 9;

    if (!valida_posicao_reta(linha_h, coluna_h, TAM_NAVIO, 1) ||
        !verifica_sobreposicao_reta(tabuleiro, linha_h, coluna_h, TAM_NAVIO, 1)) {
        printf("Erro navio horizontal\n");
        return 1;
    }
    posiciona_navio_reta(tabuleiro, linha_h, coluna_h, TAM_NAVIO, 1);

    if (!valida_posicao_reta(linha_v, coluna_v, TAM_NAVIO, 0) ||
        !verifica_sobreposicao_reta(tabuleiro, linha_v, coluna_v, TAM_NAVIO, 0)) {
        printf("Erro navio vertical\n");
        return 1;
    }
    posiciona_navio_reta(tabuleiro, linha_v, coluna_v, TAM_NAVIO, 0);

    if (!valida_posicao_diagonal(linha_diag_principal, coluna_diag_principal, TAM_NAVIO, 1) ||
        !verifica_sobreposicao_diagonal(tabuleiro, linha_diag_principal, coluna_diag_principal, TAM_NAVIO, 1)) {
        printf("Erro navio diagonal principal\n");
        return 1;
    }
    posiciona_navio_diagonal(tabuleiro, linha_diag_principal, coluna_diag_principal, TAM_NAVIO, 1);

    if (!valida_posicao_diagonal(linha_diag_secundaria, coluna_diag_secundaria, TAM_NAVIO, 0) ||
        !verifica_sobreposicao_diagonal(tabuleiro, linha_diag_secundaria, coluna_diag_secundaria, TAM_NAVIO, 0)) {
        printf("Erro navio diagonal secundária\n");
        return 1;
    }
    posiciona_navio_diagonal(tabuleiro, linha_diag_secundaria, coluna_diag_secundaria, TAM_NAVIO, 0);

    // Criação das matrizes de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    cria_habilidade_cone(cone);
    cria_habilidade_cruz(cruz);
    cria_habilidade_octaedro(octaedro);

    // Pontos de origem escolhidos
    int origem_cone_l = 1, origem_cone_c = 1;         // canto superior-esquerdo
    int origem_cruz_l = 7, origem_cruz_c = 7;         // canto inferior-direito
    int origem_octaedro_l = 4, origem_octaedro_c = 4; // centro do tabuleiro

    // Sobrepõe habilidades
    sobrepoe_habilidade(tabuleiro, cone, origem_cone_l, origem_cone_c);
    sobrepoe_habilidade(tabuleiro, cruz, origem_cruz_l, origem_cruz_c);
    sobrepoe_habilidade(tabuleiro, octaedro, origem_octaedro_l, origem_octaedro_c);

    // Exibe tabuleiro final
    printf("\nTabuleiro final com navios e áreas das habilidades:\n\n");
    imprime_tabuleiro_visual(tabuleiro);
    return 0;
}
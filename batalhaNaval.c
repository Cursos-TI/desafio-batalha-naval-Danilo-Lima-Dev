#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função recursiva para validar se o navio cabe no tabuleiro
// sem sair dos limites.
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

// Função para verificar se o navio vai sobrepor outro navio já posicionado
// Parameters:
//   tabuleiro: matriz do jogo
//   linha, coluna: coordenadas iniciais do navio
//   tamanho: tamanho do navio
//   horizontal: 1 se horizontal, 0 se vertical
// Retorna 1 se não há sobreposição, 0 se houver
int verifica_sobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    int i;
    for (i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        if (tabuleiro[l][c] == 3) {
            return 0; // posição já ocupada
        }
    }
    return 1; // sem sobreposição
}

// Função para posicionar o navio no tabuleiro
// Parameters:
//   tabuleiro: matriz do jogo
//   linha, coluna: coordenadas iniciais do navio
//   tamanho: tamanho do navio
//   horizontal: 1 se horizontal, 0 se vertical
void posiciona_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    int i;
    for (i = 0; i < tamanho; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        tabuleiro[l][c] = 3;
    }
}

// Função para imprimir o tabuleiro no console
void imprime_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("  ");
    for (int c = 0; c < TAM_TABULEIRO; c++) {
        printf("%d ", c); // Indica as colunas no topo
    }
    printf("\n");
    for (int linha = 0; linha < TAM_TABULEIRO; linha++) {
        printf("%d ", linha); // Indica as linhas na lateral
        for (int coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com zeros (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {{0}};

    // Define as coordenadas iniciais dos navios diretamente no código
    int linha_navio_horizontal = 2;
    int coluna_navio_horizontal = 3;

    int linha_navio_vertical = 5;
    int coluna_navio_vertical = 7;

    // Valida posição do navio horizontal
    if (!valida_posicao(linha_navio_horizontal, coluna_navio_horizontal, TAM_NAVIO, 1, 0)) {
        printf("Navio horizontal nao cabe no tabuleiro.\n");
        return 1;
    }

    // Valida posição do navio vertical
    if (!valida_posicao(linha_navio_vertical, coluna_navio_vertical, TAM_NAVIO, 0, 0)) {
        printf("Navio vertical nao cabe no tabuleiro.\n");
        return 1;
    }

    // Verifica sobreposição dos navios
    if (!verifica_sobreposicao(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, TAM_NAVIO, 1)) {
        printf("Navio horizontal sobrepoe outro navio.\n");
        return 1;
    }

    // Posiciona navio horizontal (orientação 1 = horizontal)
    posiciona_navio(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, TAM_NAVIO, 1);

    // Verifica sobreposição com o navio vertical após posicionar o horizontal
    if (!verifica_sobreposicao(tabuleiro, linha_navio_vertical, coluna_navio_vertical, TAM_NAVIO, 0)) {
        printf("Navio vertical sobrepoe outro navio.\n");
        return 1;
    }

    // Posiciona navio vertical (orientação 0 = vertical)
    posiciona_navio(tabuleiro, linha_navio_vertical, coluna_navio_vertical, TAM_NAVIO, 0);

    // Imprime o tabuleiro no console
    imprime_tabuleiro(tabuleiro);

    return 0;
}

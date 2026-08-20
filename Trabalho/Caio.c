#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Definição de valores constantes e caracteres representativos;
 */
#define MAXIMO_LINHAS 40
#define MAXIMO_COLUNAS 100

#define ESPACO ' '
#define PAREDE '#'
#define COMIDA '*'
#define TUNEL '@'

#define PACMAN '>'

#define MAXIMO_FANTASMAS 4

#define FANTASMA_B 'B'
#define FANTASMA_P 'P'
#define FANTASMA_I 'I'
#define FANTASMA_C 'C'

#define MOVIMENTO_PARA_ESQUERDO 'a'
#define MOVIMENTO_PARA_DIREITA 'd'
#define MOVIMENTO_PARA_CIMA 'w'
#define MOVIMENTO_PARA_BAIXO 's'

#define MOVIMENTO_HORIZONTAL 1
#define MOVIMENTO_VERITICAL 2
#define MOVIMENTO_SENTIDO_ESQUERDA 1
#define MOVIMENTO_SENTIDO_DIREITA 2


/**
 * @brief Definição de estruturas de dados dos componentes do código;
 */

 typedef struct{
    int x, y;
 }Posicao;

typedef struct{
    Posicao posicao;
}Pacman;

typedef struct{
    Posicao posicao;
    int direcaoMovimento, sentidoMovimento;
}Fantasma;

typedef struct{
    Posicao posicao;
}Portal;

typedef struct{
    int linhas, colunas;
    char posicoes[MAXIMO_LINHAS][MAXIMO_COLUNAS]; // Posições controladas porrrr uma matriz comum, por ser mais "fácil" que a estrutura posição;
    Portal entrada, saida;
}Mapa;

typedef struct{
    char tipo;
    int numero;
    // Variáveis lógicas que verificao se houve pontuação ou não e/ou colisão ou não;
    int pontuado, colisao;
}Movimento;

typedef struct {
    int movimentos, movimentosSemPontuar, colisoes,
        movimentosParaBaixo, movimentosParaCima,
        movimentosParaEsquerda, movimentosParaDireita;
}Estatisticas;

typedef struct{
    Mapa mapa;
    int indice;
}Trilha;

typedef struct{
    Mapa mapa;
    Pacman pacman;
    Fantasma fantasmas[MAXIMO_FANTASMAS];
    Estatisticas estatisticas;
}Jogo;


/**
 * @brief Funções principais que ditarão o andamento do jogo;
 *  
 * @OBS: A função de tratar o túnel será inserida junto a funções auxiliares;
 */
Jogo inicializarJogo();
Jogo realizarJogo(Jogo jogo);
Jogo gerarResumo(Jogo jogo);
Jogo gerarRanking(Jogo jogo);
Jogo gerarEstatisticas(Jogo jogo);
Jogo gerarTrilha(Jogo jogo);

Pacman criarPacman(Mapa mapa) {
    Pacman pacman;
    unsigned short int l, c;

    /*
    // A implementar;
    for (l = 0; l < mapa.linhas; l++) {
        for(c = 0; mapa.colunas; c++) {
            
        }
    }
    */

    return pacman;
}

Estatisticas criarEstatisticas(){
    Estatisticas estatisticas;

    estatisticas.movimentos = 0;
    estatisticas.movimentosSemPontuar = 0;
    estatisticas.colisoes = 0;
    estatisticas.movimentosParaBaixo = 0;
    estatisticas.movimentosParaCima = 0;
    estatisticas.movimentosParaEsquerda = 0;
    estatisticas.movimentosParaDireita = 0;

    return estatisticas;
}

/**
 * @author Caio Costa Lopes
 * @date 13/08/2026
 * 
 * @brief Programa que roda uma simulação do jogo do Pacman no terminal;
 * 
 * @return int Programa principal
 */
int main() {
    Jogo jogo;

    jogo = inicializarJogo();
    jogo = realizarJogo(jogo);
    jogo = gerarResumo(jogo);
    jogo = gerarRanking(jogo);
    jogo = gerarEstatisticas(jogo);

    return 0;
}

Jogo inicializarJogo() {
    Jogo jogo;

    jogo.mapa = criarMapa();
    jogo.pacman = criarPacman(jogo.mapa);
    criarFantasmas(jogo.fantasmas, jogo.mapa);
    jogo.estatisticas = criarEstatisticas();

    return jogo;
}
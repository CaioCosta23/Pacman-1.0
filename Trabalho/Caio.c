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
    Fantasma fantasma;
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
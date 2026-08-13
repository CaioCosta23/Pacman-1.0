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

 typedef struct {
    int x, y;
 }Posicao;

typedef struct{
    Posicao posicao;
}Pacman;

typedef struct{
    Posicao posicao;
    int direcaoMovimento, sentidoMovimento;
}Fantasma;

typedef struct {
    Posicao posicao;
}Portal;

typedef struct{
    int linhas, colunas;
    Portal entrada, saida;
}Mapa;



int main() {

    return 0;
}
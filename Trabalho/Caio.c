#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Definição de valores constantes e caracteres representativos;
 */
#define MAXIMO_LINHAS 40
#define MAXIMO_COLUNAS 100

#define INICIALIZACAO_DADOS -1

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

 // Estrutura de dados que representa uma posição no mapa (Faz referência a uma localização exata no mapa);
 typedef struct{
    int x, y;
 }Posicao;

// Estrutura de dados que representa o Pacman;
typedef struct{
    Posicao posicao;
}Pacman;


// Estrutura de dados que representa um fantasma;
typedef struct{
    Posicao posicao;
    int direcaoMovimento, sentidoMovimento;
}Fantasma;


// Estrutura de dados que representa um portal;
typedef struct{
    Posicao posicao;
}Portal;


//Estrutura de dados que representa o mapa do jogo;
typedef struct{
    int linhas, colunas;
    /*
     * Posições controladas por uma matriz comum (conjunto simples), por ser mais "fácil" que a
     * estrutura "Posicao" (que é uma estrutura mais "complexa" e mais difícil de se controlar e referênciar quando necessário
     * uma varredura no mapa por completo);
    */
    //char posicoes[MAXIMO_LINHAS][MAXIMO_COLUNAS]; 
    Posicao posicoes[MAXIMO_LINHAS * MAXIMO_COLUNAS]; // Possui todas as posiçoes possíveis de um mapa com dimensões máximas (determinadas nas regras do jogo);
    Portal entrada, saida;
}Mapa;


// Estrutura de dados que representa o registro de um movimento;
typedef struct{
    char tipo;
    int numero;
    // Variáveis lógicas que verificao se houve pontuação ou não e/ou colisão ou não;
    int pontuado, colisao;
}Movimento;


// Estrutura de dados que guarda as estatisticas do jogo;
typedef struct {
    int movimentos, movimentosSemPontuar, colisoes,
        movimentosParaBaixo, movimentosParaCima,
        movimentosParaEsquerda, movimentosParaDireita;
}Estatisticas;


// Estrutura de dados que guarda a trilha (estados do mapa em cada jogada);
typedef struct{
    Mapa mapa;
    int indice;
}Trilha;


// Estrutura de dados que guarda os dados/ entidades principais do jogo;
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


/**
 * @brief Obtém o número da linha de uma posição;
 * 
 * @param posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da posição a ser verificada;
 * @return int Numero da linha da posicao;
 */
int obtemLinhaPosicao(Posicao posicao) {
    return posicao.x;
}

/**
 * @brief Obtém o número da coluna de uma posição;
 * 
 * @param posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da posição a ser verificada;
 * @return int Numero da coluna da posicao;
 */
int obtemColunaPosicao(Posicao posicao) {
    return posicao.y;
}

/**
 * @brief Atualiza os dados de uma posição;
 * 
 * @param x Linha da posição/coordenada a ser atualizada;
 * @param y Coluna da posição/coordenada a ser atualizada;
 * @return Posicao Posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da posição atualizada;
 */
Posicao atualizaPosicao(int x, int y) {
    Posicao posicao;

    posicao.x = x;
    posicao.y = y;

    return posicao;
}

/**
 * @brief Cria/Inicializa uma posição com dados padrões ('setados');
 * 
 * @return Posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da posição inicializada com valores padrões;
 */
Posicao criaPosicao() {
    return atualizaPosicao(INICIALIZACAO_DADOS, INICIALIZACAO_DADOS);
}


Mapa criarMapa() {
    Mapa mapa;
    // Em desenvolvimento;
    return mapa;
}


int encontraPacman(char elemento) {
    return (elemento == PACMAN);
}


/**
 * @brief 
 * 
 * @param mapa 
 * @return Pacman 
 */
Pacman criarPacman(Mapa mapa) {
    Pacman pacman;
    
    pacman.posicao = criaPosicao();

    return pacman;
}

/**
 * @brief Atribui os dados (coordenadas de )
 * 
 * @param pacman Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da do Pacman que terá a posição atualizada;
 * @param x Número que representa a linha da posição/coordenada que será utilizada para atualizar a posição do pacman;
 * @param y Número que representa a coluna da posição/coordenada que será utilizada para atualizar a posição do pacman;
 * @return Pacman Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados do Pacman com sua posição atualizada;
 */
Pacman atribuiPosicaoPacman(Pacman pacman, Posicao posicao) {
    pacman.posicao = atualizaPosicao(posicao.x, posicao.y);

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
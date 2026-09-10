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
#define PORTAL '@'

#define MAXIMO_PORTAIS 2

#define PACMAN '>'

#define MAXIMO_FANTASMAS 4

#define FANTASMA_B 'B'
#define FANTASMA_P 'P'
#define FANTASMA_I 'I'
#define FANTASMA_C 'C'

#define MOVIMENTO_PARA_ESQUERDA 'a'
#define MOVIMENTO_PARA_DIREITA 'd'
#define MOVIMENTO_PARA_CIMA 'w'
#define MOVIMENTO_PARA_BAIXO 's'

//--------------------------------------------------------------------TIPOS-ABSTRATOS-DE-DADOS-----------------------------------------------------------------------------------------------
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
    char tipoMovimento, identificador;
}Fantasma;


// Estrutura de dados que representa um portal;
typedef struct{
    Posicao posicao;
    unsigned short int ativo; 
}Portal;


//Estrutura de dados que representa o mapa do jogo;
typedef struct{
    int linhas, colunas;
    /*
     * Posições controladas por uma matriz comum (conjunto simples), por ser mais "fácil" que a
     * estrutura "Posicao" (que é uma estrutura mais "complexa" e mais difícil de se controlar e referênciar quando necessário
     * uma varredura no mapa por completo), além de impressão e obtenção de dados;
    */
    char elemento[MAXIMO_LINHAS][MAXIMO_COLUNAS]; 
    Portal portais[MAXIMO_PORTAIS];
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

//------------------------------------------------------------------DECLARAÇÃO-DE-FUNÇÕES-PRINCIPAIS------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------FUNÇÕES AUXILIARES--------------------------------------------------------------------------------------------------

// -> Funções de Posicão

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
 * @return Posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da posição atualizada;
 */
Posicao atualizaPosicao(int x, int y) {
    Posicao posicao;

    posicao.x = x;
    posicao.y = y;

    return posicao;
}

/**
 * @brief Busca um por um elemento do jogo no mapa e retorna sua posição caso o mesmo seja achado;
 * 
 * @param mapa Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados do mapa (atual) do jogo;
 * @param elemento Elemento do jogo que será procurado dentro do mapa;
 * @return Posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da posição do elemento (cso o mesmo tenha sido achado,
 * caso contrário, retorna uma posição inicializada com valores padrões, indicando que o elemento não está no mapa);
 */
Posicao buscaPosicaoElemento(Mapa mapa, char elemento) {
    int l, c;
    Posicao posicao;
    
    posicao = criarPosicao();

    for(l = 0; l < mapa.linhas; l++) {
        for(c = 0; c < mapa.colunas; c++) {
            if (elemento == mapa.elemento[l][c]){
                posicao = atualizaPosicao(l, c);
                break;
            }
        }
    }
    return posicao;
}

/**
 * @brief Cria/Inicializa uma posição com dados padrões ('setados');
 * 
 * @return Posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da posição inicializada com valores padrões;
 */
Posicao criarPosicao() {
    return atualizaPosicao(INICIALIZACAO_DADOS, INICIALIZACAO_DADOS);
}

//..........................................................................................................................................................................................
// -> Funções de Pacman

/**
 * @brief Cria um Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da do Pacman com dados inicializados com valores padronizados;
 * 
 * @return Pacman Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da do Pacman com dados padrões em seus atributos;
 */
Pacman criarPacman() {
    Pacman pacman;
    
    pacman.posicao = criarPosicao();

    return pacman;
}

/**
 * @brief Inicializa os dados do pacman co as informações iniciais coletadas do mapa inicial do jogo (com seus dados já atribuidos);
 * 
 * @param pacman Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da do Pacman com informações padrões iniciais;
 * @param mapa Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados do mapa atualizados;
 * @return Pacman Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados da do Pacman com dados atualizados;
 */
Pacman inicializarPacman(Pacman pacman, Mapa mapa) {
    pacman.posicao = buscaPosicaoElemento(mapa, PACMAN);

    return pacman;
}

//..........................................................................................................................................................................................
// -> Funções de Fantasmas

/**
 * @brief Cria fantasmas com dados iniciais com valores padrões;
 * 
 * @param fantasmas Vetor/Lista de Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados dos fantasmas que seram inicializados
 * com dados padrões;
 */
void criarFantasmas(Fantasma fantasmas[]) {
    unsigned short int f;

    for (f = 0; f < MAXIMO_FANTASMAS; f++) {
        fantasmas[f].posicao = criarPosicao();
        fantasmas[f].tipoMovimento;
        fantasmas[f].identificador = '\0';
    }
}

/**
 * @brief Função que inicializa/atribui dados dos fantasmas do jogo;
 * 
 * @param fantasmas Vetor/Lista de Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados dos fantasmas atualizados com as
 * informações e características que os mesmos terão no jogo (caso exista(m));
 * @param mapa Mapa do jogo (atualizado) que será utilizado para buscar os fantasmas dentro do jogo;
 *
 */
void inicializarFantasmas(Fantasma fantasmas[], Mapa mapa) {
    fantasmas[0].posicao = buscaPosicaoElemento(mapa, FANTASMA_B);
    fantasmas[0].tipoMovimento = MOVIMENTO_PARA_ESQUERDA;
   
    fantasmas[1].posicao = buscaPosicaoElemento(mapa, FANTASMA_P);
    fantasmas[1].tipoMovimento = MOVIMENTO_PARA_CIMA;
    
    fantasmas[2].posicao = buscaPosicaoElemento(mapa, FANTASMA_I);
    fantasmas[2].tipoMovimento = MOVIMENTO_PARA_BAIXO;
    
    fantasmas[3].posicao = buscaPosicaoElemento(mapa, FANTASMA_C);
    fantasmas[3].tipoMovimento = MOVIMENTO_PARA_DIREITA;
}

Fantasma alteraMovimentoFantasma(Fantasma fantasma) {

    switch (fantasma.tipoMovimento) {
        case MOVIMENTO_PARA_BAIXO:
            fantasma.tipoMovimento = MOVIMENTO_PARA_CIMA;
            break;
        case MOVIMENTO_PARA_CIMA:
            fantasma.tipoMovimento = MOVIMENTO_PARA_BAIXO;
            break;
        case MOVIMENTO_PARA_DIREITA:
            fantasma.tipoMovimento = MOVIMENTO_PARA_ESQUERDA;
            break;
        case MOVIMENTO_PARA_ESQUERDA:
            fantasma.tipoMovimento = MOVIMENTO_PARA_DIREITA;
            break;
        default:
            printf("Movimento incorreto.");
            break;
    }

    return fantasma;
}

//..........................................................................................................................................................................................
// -> Funções de Portais

/**
 * @brief Cria os portais do jogo com dados inicializados com valores padrões;
 * 
 * @param portais Vetor/Lista de Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados dos portais do mapa,
 * que seram inicializados com dados padrões;
 */
void criarPortais(Portal portais[]) {
    unsigned short int p;

    for(p = 0; p < MAXIMO_PORTAIS; p++) {
        portais[p].posicao = criarPosicao();
        portais[p].ativo = 0;
    }
}

/**
 * @brief Atribui os dados necessários para o funcionamento dos portais;
 * 
 * @param portais Vetor/Lista de Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados dos portais do mapa atualizados,
 * com as informações e características que os mesmos terão no jogo (caso exista(m));
 * @param mapa Mapa do jogo (atualizado) que será utilizado para buscar os fantasmas dentro do jogo;
 */
void inicializaPortais(Portal portais[], Mapa mapa) {
    unsigned short int p;

    for(p = 0; p < MAXIMO_PORTAIS; p++) {
        if (portais[p].ativo == 0){
            portais[p].posicao = buscaPosicaoElemento(mapa, PORTAL);
            portais[p].ativo = 1;
        }
    }
}

//..........................................................................................................................................................................................
// -> Funções de Mapa

/**
 * @brief Cria um mapa com dados inicializados com valores padrões;
 * 
 * @return Mapa Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados do mapa que seram inicializados com dados padrões;
 */
Mapa criarMapa() {
    Mapa mapa;
    unsigned short int l, c;

    mapa.linhas = MAXIMO_LINHAS;
    mapa.colunas = MAXIMO_COLUNAS;
    criarPortais(mapa.portais);

    for(l = 0; l < mapa.linhas; l++) {
        for(c = 0; mapa.colunas; c++) {
            mapa.elemento[l][c] = '\0';
        }
    }
    return mapa;
}

/**
 * @brief Verifica se a posição está no limite do mapa;
 * 
 * @param mapa Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados (atualizados) do mapa;
 * @param posicao Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados de uma posição do mapa;
 * @return int 1 (verdadeiro) se a posição estiver no limite do mapa ou 0 (falso), caso contrário;
 */
int verificaLimiteMapa(Mapa mapa, Posicao posicao) {
    return ((obtemLinhaPosicao(posicao) == (mapa.linhas - 1)) || (obtemColunaPosicao(posicao) == (mapa.colunas - 1)));
}

Mapa movimentaFantasma(Mapa mapa, Fantasma fantasma) {
    if (verificaLimiteMapa(mapa, fantasma.posicao))
        fantasma = alteraMovimentoFantasma(fantasma);

    return mapa;
}

Mapa movimentaPacman(Mapa mapa, Pacman pacman) {
    return mapa;
}

/**
 * @brief Imprime o mapa do jogo na tela;
 * 
 * @param mapa Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados do mapa (atualizado);
 */
void imprimirMapa(Mapa mapa) {
    unsigned short int l, c;

    for(l = 0; l < mapa.linhas; l++) {
        for(c = 0; c < mapa.colunas; c++) {
            printf("%c", mapa.elemento[l][c]);
        }
        printf("\n");
    }
}

//..........................................................................................................................................................................................
// -> Funções de Estatisticas;

/**
 * @brief Cria as estatísticas do jogo com dados inicializados com dados em valores padrões;
 * 
 * @return Estatisticas Tipo Abstrato de Dados (T.A.D.) que representa a estrutura que guarda os dados das estatisticas que seram inicializados com dados padrões;
 */
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

//-----------------------------------------------------------------------PROGRAMA PRINCIPAL--------------------------------------------------------------------------------------------------

/**
 * @author Caio Costa Lopes
 * @date 13/08/2026
 * 
 * @brief Programa que roda uma simulação do jogo do Pacman no terminal;
 * 
 * @return int Programa principal
 */
int main() {
    // Manter esse trecho em vazio até a leitura de arquivos;

    return 0;
}

//-----------------------------------------------------------------------FUNÇÕES-PRINCIPAIS--------------------------------------------------------------------------------------------------

Jogo inicializarJogo() {
    Jogo jogo;

    jogo.mapa = criarMapa();
    //jogo.mapa = inicializarMapa();
    jogo.pacman = criarPacman();
    jogo.pacman = inicializarPacman(jogo.pacman, jogo.mapa);
    criarFantasmas(jogo.fantasmas);
    inicializarFantasmas(jogo.fantasmas, jogo.mapa);
    jogo.estatisticas = criarEstatisticas();

    return jogo;
}
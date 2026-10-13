#ifndef AGENTE_H
#define AGENTE_H

/**
 * @file agente.h
 * @brief Definição da estrutura do Agente de IA e operações do catálogo.
 * Atende aos requisitos RNF-01 (Estruturação dos Dados via Struct),
 * RNF-04 (Catálogo em memória para até 50 agentes) e RF-02.
 */

#define MAX_AGENTES 50
#define TAM_NOME 81       /* Até 80 caracteres + terminador nulo */
#define TAM_SCRIPT 1001   /* Até 1000 caracteres + terminador nulo */
#define NOTA_MIN 0.0f
#define NOTA_MAX 5.0f

/**
 * @struct Agente
 * @brief Representa um Agente de IA registrado no catálogo.
 */
typedef struct {
    int id;                     /* Identificador único (> 0) */
    char nome[TAM_NOME];        /* Nome do agente (até 80 caracteres) */
    char script[TAM_SCRIPT];    /* Instruções/prompt do agente (até 1000 caracteres) */
    float nota;                 /* Avaliação de 0.0 a 5.0 */
    int ativo;                  /* 1 = Ativo no catálogo, 0 = Posição livre/desativada */
} Agente;

/**
 * @struct Catalogo
 * @brief Gerencia o conjunto de agentes em memória.
 */
typedef struct {
    Agente agentes[MAX_AGENTES];
    int total_ativos;
} Catalogo;

/**
 * @brief Inicializa o catálogo em memória, zerando todos os campos e posições.
 * @param cat Ponteiro para a estrutura do catálogo.
 */
void inicializar_catalogo(Catalogo *cat);

/**
 * @brief Retorna a quantidade de vagas restantes no catálogo.
 * @param cat Ponteiro para o catálogo.
 * @return Quantidade de vagas disponíveis (0 a MAX_AGENTES).
 */
int obter_vagas_disponiveis(const Catalogo *cat);

/**
 * @brief Verifica se um ID já está em uso por algum agente ativo.
 * @param cat Ponteiro para o catálogo.
 * @param id Identificador a ser verificado.
 * @return 1 se já existir, 0 se estiver disponível.
 */
int id_ja_existe(const Catalogo *cat, int id);

/**
 * @brief Busca a posição (índice) do agente no vetor pelo seu ID.
 * @param cat Ponteiro para o catálogo.
 * @param id Identificador do agente.
 * @return Índice no array (0 a MAX_AGENTES-1) ou -1 se não encontrado.
 */
int buscar_posicao_por_id(const Catalogo *cat, int id);

/**
 * @brief Encontra o primeiro índice vago no array de agentes.
 * @param cat Ponteiro para o catálogo.
 * @return Índice livre (0 a MAX_AGENTES-1) ou -1 se o catálogo estiver cheio.
 */
int encontrar_posicao_livre(const Catalogo *cat);

#endif /* AGENTE_H */

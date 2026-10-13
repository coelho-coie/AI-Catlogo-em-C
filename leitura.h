#ifndef LEITURA_H
#define LEITURA_H

/**
 * @file leitura.h
 * @brief Rotinas de leitura segura no console e validação de entradas.
 * Atende aos requisitos RNF-01 (Validação e Robustez de Entradas) e RNF-05 (Portabilidade).
 */

/**
 * @brief Limpa caracteres residuais do buffer de entrada (stdin) até encontrar '\n' ou EOF.
 */
void limpar_buffer_entrada(void);

/**
 * @brief Lê uma linha de texto do teclado com proteção de overflow e descarte de excedente.
 * @param destino Buffer onde a string será armazenada.
 * @param tamanho_max Capacidade total do buffer destino (incluindo o terminador '\0').
 * @return 1 se a leitura foi bem-sucedida, 0 em caso de erro ou EOF.
 */
int ler_linha(char *destino, int tamanho_max);

/**
 * @brief Solicita e lê um texto do usuário, permitindo espaços e controlando obrigatoriedade.
 * @param prompt Mensagem exibida para o usuário.
 * @param destino Buffer de saída.
 * @param tamanho_max Tamanho máximo do buffer.
 * @param obrigatorio Se 1, rejeita texto vazio ou composto apenas de espaços.
 * @return 1 em sucesso.
 */
int ler_texto(const char *prompt, char *destino, int tamanho_max, int obrigatorio);

/**
 * @brief Lê um número inteiro com validação total contra caracteres não-numéricos.
 * @param prompt Mensagem exibida para o usuário.
 * @param valor_saida Ponteiro para armazenar o inteiro lido.
 * @return 1 em sucesso.
 */
int ler_inteiro(const char *prompt, int *valor_saida);

/**
 * @brief Lê um número inteiro garantindo que pertença a uma faixa inclusiva [min, max].
 * @param prompt Mensagem exibida para o usuário.
 * @param min Valor mínimo aceito.
 * @param max Valor máximo aceito.
 * @param valor_saida Ponteiro para armazenar o inteiro lido.
 * @return 1 em sucesso.
 */
int ler_inteiro_faixa(const char *prompt, int min, int max, int *valor_saida);

/**
 * @brief Lê um número em ponto flutuante dentro de uma faixa [min, max], aceitando ponto ou vírgula.
 * @param prompt Mensagem exibida para o usuário.
 * @param min Valor mínimo aceito.
 * @param max Valor máximo aceito.
 * @param valor_saida Ponteiro para armazenar o float lido.
 * @return 1 em sucesso.
 */
int ler_float_faixa(const char *prompt, float min, float max, float *valor_saida);

/**
 * @brief Pausa a execução de forma portável até o usuário pressionar [ENTER].
 */
void pausar_tela(void);

/**
 * @brief Limpa o console de forma compatível com Windows e Linux.
 */
void limpar_tela(void);

#endif /* LEITURA_H */

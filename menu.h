#ifndef MENU_H
#define MENU_H

#include "agente.h"

/**
 * @file menu.h
 * @brief Interface do Menu Principal e fluxo de navegação do sistema.
 * Atende ao requisito RF-01 (Menu Principal Interativo).
 */

/**
 * @brief Executa o loop principal de navegação do catálogo.
 * Mantém o sistema ativo até a escolha explícita de encerramento.
 * @param cat Ponteiro para a estrutura do catálogo de agentes.
 */
void executar_menu_principal(Catalogo *cat);

/**
 * @brief Exibe o layout visual do Menu Principal com opções do catálogo.
 * @param cat Ponteiro para o catálogo para visualização de métricas (ativos/vagas).
 */
void exibir_layout_menu(const Catalogo *cat);

#endif /* MENU_H */

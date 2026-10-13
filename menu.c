#include "menu.h"
#include "leitura.h"
#include <stdio.h>

void exibir_layout_menu(const Catalogo *cat) {
    int ativos = cat ? cat->total_ativos : 0;
    int vagas = cat ? obter_vagas_disponiveis(cat) : 0;

    printf("============================================================\n");
    printf("         CATALOGO DE AGENTES DE INTELIGENCIA ARTIFICIAL     \n");
    printf("============================================================\n");
    printf(" Status: [%d/%d] Agentes Ativos  |  Vagas Disponiveis: %d\n", ativos, MAX_AGENTES, vagas);
    printf("------------------------------------------------------------\n");
    printf("  [1] Cadastrar Novo Agente de IA       (RF-02)\n");
    printf("  [2] Listar Agentes Cadastrados        (RF-03)\n");
    printf("  [3] Buscar Agente por ID              (RF-04)\n");
    printf("  [4] Buscar Agente por Nome            (RF-05)\n");
    printf("  [5] Salvar Catalogo em Arquivo        (RF-08)\n");
    printf("  [6] Carregar Catalogo de Arquivo      (RF-09)\n");
    printf("  [0] Encerrar o Sistema\n");
    printf("============================================================\n");
}

static void handler_cadastrar_agente(Catalogo *cat) {
    limpar_tela();
    printf("============================================================\n");
    printf("            CADASTRO DE NOVO AGENTE DE IA (RF-02)           \n");
    printf("============================================================\n");
    if (obter_vagas_disponiveis(cat) == 0) {
        printf("Aviso: O catalogo atingiu o limite maximo de %d agentes.\n", MAX_AGENTES);
        printf("Nao ha vagas disponiveis no momento.\n");
    } else {
        printf("Modulo pronto para cadastro de novo agente.\n");
        printf("Capacidade restante: %d vagas.\n", obter_vagas_disponiveis(cat));
    }
    pausar_tela();
}

static void handler_listar_agentes(const Catalogo *cat) {
    limpar_tela();
    printf("============================================================\n");
    printf("           LISTAGEM DE AGENTES CADASTRADOS (RF-03)          \n");
    printf("============================================================\n");
    if (cat->total_ativos == 0) {
        printf("Nenhum agente cadastrado no momento.\n");
    } else {
        printf("Total de agentes ativos no catalogo: %d\n", cat->total_ativos);
    }
    pausar_tela();
}

static void handler_buscar_id(const Catalogo *cat) {
    limpar_tela();
    printf("============================================================\n");
    printf("               BUSCA DE AGENTE POR ID (RF-04)               \n");
    printf("============================================================\n");
    printf("Modulo de busca por ID e submenu de acoes (Editar / Excluir).\n");
    (void)cat;
    pausar_tela();
}

static void handler_buscar_nome(const Catalogo *cat) {
    limpar_tela();
    printf("============================================================\n");
    printf("              BUSCA DE AGENTE POR NOME (RF-05)              \n");
    printf("============================================================\n");
    printf("Modulo de busca por nome (parcial ou completo).\n");
    (void)cat;
    pausar_tela();
}

static void handler_salvar_arquivo(const Catalogo *cat) {
    limpar_tela();
    printf("============================================================\n");
    printf("           SALVAMENTO DO CATALOGO EM ARQUIVO (RF-08)        \n");
    printf("============================================================\n");
    printf("Modulo de persistencia em disco local.\n");
    printf("Total de registros para gravacao: %d agentes ativos.\n", cat->total_ativos);
    pausar_tela();
}

static void handler_carregar_arquivo(Catalogo *cat) {
    limpar_tela();
    printf("============================================================\n");
    printf("          CARREGAMENTO DO CATALOGO DE ARQUIVO (RF-09)       \n");
    printf("============================================================\n");
    printf("Modulo de restauracao de dados salvos em disco.\n");
    (void)cat;
    pausar_tela();
}

void executar_menu_principal(Catalogo *cat) {
    int opcao = -1;

    while (opcao != 0) {
        limpar_tela();
        exibir_layout_menu(cat);

        if (!ler_inteiro_faixa("\nDigite a opcao desejada (0-6): ", 0, 6, &opcao)) {
            continue;
        }

        switch (opcao) {
            case 1:
                handler_cadastrar_agente(cat);
                break;
            case 2:
                handler_listar_agentes(cat);
                break;
            case 3:
                handler_buscar_id(cat);
                break;
            case 4:
                handler_buscar_nome(cat);
                break;
            case 5:
                handler_salvar_arquivo(cat);
                break;
            case 6:
                handler_carregar_arquivo(cat);
                break;
            case 0:
                limpar_tela();
                printf("============================================================\n");
                printf(" Sistema encerrado com sucesso. Ate logo!\n");
                printf("============================================================\n\n");
                break;
            default:
                break;
        }
    }
}

#include "agente.h"
#include <string.h>

void inicializar_catalogo(Catalogo *cat) {
    if (!cat) return;

    cat->total_ativos = 0;
    for (int i = 0; i < MAX_AGENTES; i++) {
        cat->agentes[i].id = 0;
        cat->agentes[i].nome[0] = '\0';
        cat->agentes[i].script[0] = '\0';
        cat->agentes[i].nota = 0.0f;
        cat->agentes[i].ativo = 0;
    }
}

int obter_vagas_disponiveis(const Catalogo *cat) {
    if (!cat) return 0;
    return MAX_AGENTES - cat->total_ativos;
}

int id_ja_existe(const Catalogo *cat, int id) {
    if (!cat || id <= 0) return 0;

    for (int i = 0; i < MAX_AGENTES; i++) {
        if (cat->agentes[i].ativo && cat->agentes[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int buscar_posicao_por_id(const Catalogo *cat, int id) {
    if (!cat || id <= 0) return -1;

    for (int i = 0; i < MAX_AGENTES; i++) {
        if (cat->agentes[i].ativo && cat->agentes[i].id == id) {
            return i;
        }
    }
    return -1;
}

int encontrar_posicao_livre(const Catalogo *cat) {
    if (!cat) return -1;

    for (int i = 0; i < MAX_AGENTES; i++) {
        if (!cat->agentes[i].ativo) {
            return i;
        }
    }
    return -1;
}

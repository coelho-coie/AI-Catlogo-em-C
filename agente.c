#include <string.h>
#include <ctype.h>

#define MAX_AGENTES 50
#define TAM_NOME 81
#define TAM_SCRIPT 1001

// Autor: Vitor Hugo
typedef struct {
    int total;
    int ids[MAX_AGENTES];
    char nomes[MAX_AGENTES][TAM_NOME];
    char scripts[MAX_AGENTES][TAM_SCRIPT];
    float notas[MAX_AGENTES];
} Catalogo;

// Autor: Vitor Hugo
int buscar_posicao(Catalogo *cat, int id) {
    int i;
    for (i = 0; i < cat->total; i++) {
        if (cat->ids[i] == id) return i;
    }
    return -1;
}

// Autor: Vitor Hugo
int proximo_id(Catalogo *cat) {
    int i;
    int maior = 0;
    for (i = 0; i < cat->total; i++) {
        if (cat->ids[i] > maior) maior = cat->ids[i];
    }
    return maior + 1;
}

// Autor: Erick
int nome_valido(char *nome) {
    int i;
    int tem_letra = 0;
    for (i = 0; nome[i] != '\0'; i++) {
        if (isdigit((unsigned char)nome[i]) || nome[i] == ';') return 0;
        if (!isspace((unsigned char)nome[i])) tem_letra = 1;
    }
    return tem_letra;
}

// Autor: Erick
// O ID e gerado aqui, nao digitado. Retorna o ID criado, ou 0 se falhar.
int cadastrar_agente(Catalogo *cat, char *nome, char *script, float nota) {
    int pos = cat->total;
    if (pos >= MAX_AGENTES) return 0;
    if (!nome_valido(nome) || nota < 0.0f || nota > 5.0f) return 0;

    cat->ids[pos] = proximo_id(cat);
    strcpy(cat->nomes[pos], nome);
    strcpy(cat->scripts[pos], script);
    cat->notas[pos] = nota;
    cat->total++;
    return cat->ids[pos];
}

// Autor: Mateus
// Remove a posicao e puxa os seguintes uma casa para tras, em todos os vetores.
void excluir_posicao(Catalogo *cat, int pos) {
    int i;
    for (i = pos; i < cat->total - 1; i++) {
        cat->ids[i] = cat->ids[i + 1];
        strcpy(cat->nomes[i], cat->nomes[i + 1]);
        strcpy(cat->scripts[i], cat->scripts[i + 1]);
        cat->notas[i] = cat->notas[i + 1];
    }
    cat->total--;
}

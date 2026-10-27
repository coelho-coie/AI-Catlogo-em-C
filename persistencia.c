#include <stdio.h>
#include <string.h>

#define ARQUIVO "agentes.txt"

// Autor: Arthur
// Grava uma linha por agente: id;nota;nome;script
void salvar_dados(Catalogo *cat, const char *caminho) {
    FILE *arq;
    int i;

    arq = fopen(caminho, "w");
    if (arq == NULL) {
        printf("Erro: nao foi possivel gravar %s.\n", caminho);
        return;
    }
    for (i = 0; i < cat->total; i++) {
        fprintf(arq, "%d;%.2f;%s;%s\n", cat->ids[i], cat->notas[i],
                cat->nomes[i], cat->scripts[i]);
    }
    fclose(arq);
}

// Autor: Arthur
// Le o arquivo para o catalogo. Se o arquivo nao existir, o catalogo fica vazio.
void carregar_dados(Catalogo *cat, const char *caminho) {
    FILE *arq;
    char linha[1200];
    char nome[TAM_NOME];
    char script[TAM_SCRIPT];
    int id;
    float nota;
    int campos;
    int pos;

    arq = fopen(caminho, "r");
    if (arq == NULL) return;

    while (cat->total < MAX_AGENTES && fgets(linha, sizeof(linha), arq) != NULL) {
        script[0] = '\0';
        campos = sscanf(linha, "%d;%f;%80[^;];%1000[^\n]", &id, &nota, nome, script);
        if (campos >= 3) {
            pos = cat->total;
            cat->ids[pos] = id;
            cat->notas[pos] = nota;
            strcpy(cat->nomes[pos], nome);
            strcpy(cat->scripts[pos], script);
            cat->total++;
        }
    }
    fclose(arq);
}

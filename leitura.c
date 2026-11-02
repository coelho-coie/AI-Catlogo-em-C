#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Autor: Vitor Hugo (Tarefa 1.2)
// Le uma linha. Se a entrada acabar (EOF), encerra o programa.
void ler_linha(char *buffer, int tamanho) {
    int c;
    int len;

    if (fgets(buffer, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada.\n");
        exit(0);
    }
    len = (int)strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        /* linha maior que o buffer: descarta o resto */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

// Autor: Vitor Hugo (Tarefa 1.2)
int ler_inteiro(const char *mensagem) {
    char buffer[64];
    int valor;
    char resto;

    while (1) {
        printf("%s", mensagem);
        ler_linha(buffer, sizeof(buffer));
        if (sscanf(buffer, "%d %c", &valor, &resto) == 1) return valor;
        printf("Erro: digite um numero inteiro.\n");
    }
}
// Autor: Vitor Hugo (Tarefa 1.2)
int converter_nota(char *texto, float *nota) {
    float valor;
    char resto;
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') texto[i] = '.';
    }
    if (sscanf(texto, "%f %c", &valor, &resto) != 1 || valor < 0.0f || valor > 5.0f) return 0;
    *nota = valor;
    return 1;
}

// Autor: Vitor Hugo (Tarefa 1.2)
float ler_nota(const char *mensagem) {
    char buffer[64];
    float valor;

    while (1) {
        printf("%s", mensagem);
        ler_linha(buffer, sizeof(buffer));
        if (converter_nota(buffer, &valor)) return valor;
        printf("Erro: digite uma nota de 0 a 5.\n");
    }
}

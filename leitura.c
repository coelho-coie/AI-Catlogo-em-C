#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "leitura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpar_buffer_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Descarta caracteres residuais */
    }
}

int ler_linha(char *destino, int tamanho_max) {
    if (!destino || tamanho_max <= 1) return 0;

    if (fgets(destino, tamanho_max, stdin) == NULL) {
        destino[0] = '\0';
        return 0;
    }

    size_t len = strlen(destino);
    if (len > 0 && (destino[len - 1] == '\n' || destino[len - 1] == '\r')) {
        while (len > 0 && (destino[len - 1] == '\n' || destino[len - 1] == '\r')) {
            destino[len - 1] = '\0';
            len--;
        }
    } else if (len == (size_t)(tamanho_max - 1)) {
        /* Buffer encheu sem quebra de linha: descarta o excedente para evitar pulo de campos */
        limpar_buffer_entrada();
    }

    return 1;
}

static int string_somente_espacos(const char *str) {
    if (!str) return 1;
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int ler_texto(const char *prompt, char *destino, int tamanho_max, int obrigatorio) {
    while (1) {
        if (prompt && prompt[0] != '\0') {
            printf("%s", prompt);
            fflush(stdout);
        }

        if (!ler_linha(destino, tamanho_max)) {
            destino[0] = '\0';
            return 0;
        }

        if (obrigatorio) {
            if (strlen(destino) == 0 || string_somente_espacos(destino)) {
                printf("Erro: O campo nao pode ser vazio. Tente novamente.\n");
                continue;
            }
        }
        return 1;
    }
}

int ler_inteiro(const char *prompt, int *valor_saida) {
    char buffer[64];
    int valor;
    char lixo;

    while (1) {
        if (prompt && prompt[0] != '\0') {
            printf("%s", prompt);
            fflush(stdout);
        }

        if (!ler_linha(buffer, sizeof(buffer))) {
            return 0;
        }

        if (strlen(buffer) == 0 || string_somente_espacos(buffer)) {
            printf("Erro: Digite um valor numerico.\n");
            continue;
        }

        if (sscanf(buffer, "%d %c", &valor, &lixo) == 1) {
            if (valor_saida) *valor_saida = valor;
            return 1;
        }

        printf("Erro: Entrada invalida. Digite apenas numeros inteiros.\n");
    }
}

int ler_inteiro_faixa(const char *prompt, int min, int max, int *valor_saida) {
    int valor;
    while (1) {
        if (!ler_inteiro(prompt, &valor)) {
            return 0;
        }

        if (valor >= min && valor <= max) {
            if (valor_saida) *valor_saida = valor;
            return 1;
        }

        printf("Erro: O valor deve estar entre %d e %d. Tente novamente.\n", min, max);
    }
}

int ler_float_faixa(const char *prompt, float min, float max, float *valor_saida) {
    char buffer[64];
    float valor;
    char lixo;

    while (1) {
        if (prompt && prompt[0] != '\0') {
            printf("%s", prompt);
            fflush(stdout);
        }

        if (!ler_linha(buffer, sizeof(buffer))) {
            return 0;
        }

        if (strlen(buffer) == 0 || string_somente_espacos(buffer)) {
            printf("Erro: Digite uma nota valida (ex: 4.5 ou 4,5).\n");
            continue;
        }

        /* Aceita tanto ponto quanto virgula como separador decimal */
        for (size_t i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == ',') {
                buffer[i] = '.';
            }
        }

        if (sscanf(buffer, "%f %c", &valor, &lixo) == 1) {
            if (valor >= min && valor <= max) {
                if (valor_saida) *valor_saida = valor;
                return 1;
            }
            printf("Erro: O valor deve estar entre %.1f e %.1f. Tente novamente.\n", min, max);
        } else {
            printf("Erro: Nota invalida. Digite um numero decimal valido (ex: 4.5).\n");
        }
    }
}

void pausar_tela(void) {
    printf("\nPressione [ENTER] para continuar...");
    fflush(stdout);
    char temp[16];
    ler_linha(temp, sizeof(temp));
}

void limpar_tela(void) {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

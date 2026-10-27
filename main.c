#include <stdio.h>
#include "agente.c"
#include "leitura.c"
#include "persistencia.c"
#include "menu.c"

// Autor: Vitor Hugo
int main(void) {
    Catalogo catalogo;

    catalogo.total = 0;
    carregar_dados(&catalogo, ARQUIVO);
    printf("%d agente(s) carregado(s).\n", catalogo.total);

    executar_menu(&catalogo);
    return 0;
}

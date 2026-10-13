#include <stdio.h>
#include <stdlib.h>
#include "agente.h"
#include "menu.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

int main(void) {
#if defined(_WIN32) || defined(_WIN64)
    /* Configura o console do Windows para codificacao UTF-8 */
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Catalogo catalogo;
    inicializar_catalogo(&catalogo);

    executar_menu_principal(&catalogo);

    return 0;
}

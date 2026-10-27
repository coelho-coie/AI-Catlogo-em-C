#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Autor: Vitor Hugo (menu principal)
void mostrar_menu(Catalogo *cat) {
    printf("\n=== CATALOGO DE AGENTES DE IA ===\n");
    printf("Agentes: %d/%d\n", cat->total, MAX_AGENTES);
    printf("1 - Cadastrar agente\n");
    printf("2 - Listar agentes\n");
    printf("3 - Buscar por ID\n");
    printf("4 - Buscar por nome\n");
    printf("5 - Ranking por nota\n");
    printf("0 - Sair\n");
}

// Autor: Mateus
void mostrar_ficha(Catalogo *cat, int pos) {
    printf("\nID: %d\n", cat->ids[pos]);
    printf("Nome: %s\n", cat->nomes[pos]);
    printf("Nota: %.2f\n", cat->notas[pos]);
    printf("Instrucoes: %s\n", cat->scripts[pos]);
}

// Autor: Mateus
// Edicao: ENTER mantem o valor atual. O ID nao muda.
void editar(Catalogo *cat, int pos) {
    char buffer[TAM_SCRIPT];
    int i;
    float nota;

    printf("Novo nome (ENTER mantem): ");
    ler_linha(buffer, TAM_NOME);
    if (strlen(buffer) > 0) {
        if (nome_valido(buffer)) strcpy(cat->nomes[pos], buffer);
        else printf("Nome invalido. Mantido o atual.\n");
    }

    printf("Nova instrucao (ENTER mantem): ");
    ler_linha(buffer, TAM_SCRIPT);
    if (strlen(buffer) > 0) strcpy(cat->scripts[pos], buffer);

    printf("Nova nota de 0 a 5 (ENTER mantem): ");
    ler_linha(buffer, 64);
    if (strlen(buffer) > 0) {
        for (i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == ',') buffer[i] = '.';
        }
        if (sscanf(buffer, "%f", &nota) == 1 && nota >= 0.0f && nota <= 5.0f) {
            cat->notas[pos] = nota;
        } else {
            printf("Nota invalida. Mantida a atual.\n");
        }
    }
}

// Autor: Mateus
// Retorna 1 se excluiu.
int excluir(Catalogo *cat, int pos) {
    char resposta[8];

    printf("Confirma a exclusao de %s? (S/N): ", cat->nomes[pos]);
    ler_linha(resposta, sizeof(resposta));
    if (resposta[0] == 'S' || resposta[0] == 's') {
        excluir_posicao(cat, pos);
        printf("Agente excluido.\n");
        return 1;
    }
    printf("Exclusao cancelada.\n");
    return 0;
}

// Autor: Matheus
void submenu(Catalogo *cat, int pos) {
    int opcao;

    while (1) {
        mostrar_ficha(cat, pos);
        printf("1 - Editar   2 - Excluir   0 - Voltar\n");
        opcao = ler_inteiro("Opcao: ");

        if (opcao == 1) {
            editar(cat, pos);
            salvar_dados(cat, ARQUIVO);
        } else if (opcao == 2) {
            if (excluir(cat, pos)) {
                salvar_dados(cat, ARQUIVO);
                return;
            }
        } else if (opcao == 0) {
            return;
        } else {
            printf("Opcao invalida.\n");
        }
    }
}

// Autor: Erick
// Busca sem diferenciar maiusculas de minusculas.
int contem(char *texto, char *termo) {
    int i;
    int j;
    int k;

    for (i = 0; texto[i] != '\0'; i++) {
        j = 0;
        k = i;
        while (termo[j] != '\0' && texto[k] != '\0' &&
               tolower((unsigned char)texto[k]) == tolower((unsigned char)termo[j])) {
            j++;
            k++;
        }
        if (termo[j] == '\0') return 1;
    }
    return 0;
}

// Autor: Erick
void buscar_id(Catalogo *cat) {
    int id;
    int pos;

    id = ler_inteiro("ID procurado: ");
    pos = buscar_posicao(cat, id);
    if (pos < 0) {
        printf("Nenhum agente com o ID %d.\n", id);
        return;
    }
    submenu(cat, pos);
}

// Autor: Erick
void buscar_nome(Catalogo *cat) {
    char termo[TAM_NOME];
    int i;
    int qtd = 0;
    int id;
    int pos;

    printf("Nome ou parte dele: ");
    ler_linha(termo, sizeof(termo));

    for (i = 0; i < cat->total; i++) {
        if (contem(cat->nomes[i], termo)) {
            printf("ID %d - %s\n", cat->ids[i], cat->nomes[i]);
            qtd++;
        }
    }
    if (qtd == 0) {
        printf("Nenhum agente encontrado.\n");
        return;
    }

    id = ler_inteiro("Digite o ID para abrir (0 para voltar): ");
    pos = buscar_posicao(cat, id);
    if (pos >= 0) submenu(cat, pos);
}

// Autor: Erick
void cadastrar(Catalogo *cat) {
    char nome[TAM_NOME];
    char script[TAM_SCRIPT];
    float nota;
    int id;

    if (cat->total >= MAX_AGENTES) {
        printf("Catalogo cheio (%d agentes).\n", MAX_AGENTES);
        return;
    }

    printf("Nome (sem numeros): ");
    ler_linha(nome, TAM_NOME);
    while (!nome_valido(nome)) {
        printf("Nome invalido. Use letras e espacos: ");
        ler_linha(nome, TAM_NOME);
    }

    nota = ler_nota("Nota (0 a 5): ");

    printf("Instrucoes: ");
    ler_linha(script, TAM_SCRIPT);

    id = cadastrar_agente(cat, nome, script, nota);
    if (id == 0) {
        printf("Nao foi possivel cadastrar.\n");
        return;
    }
    printf("Agente cadastrado com o ID %d.\n", id);
    salvar_dados(cat, ARQUIVO);
}

// Autor: Mateus
void listar(Catalogo *cat) {
    int i;

    if (cat->total == 0) {
        printf("Nenhum agente cadastrado.\n");
        return;
    }
    printf("\nID    NOME                     NOTA  INSTRUCOES\n");
    for (i = 0; i < cat->total; i++) {
        printf("%-5d %-24.24s %-5.2f %.30s\n", cat->ids[i], cat->nomes[i],
               cat->notas[i], cat->scripts[i]);
    }
}

// Diferencial: ranking da maior nota para a menor (selecao)
void ranking(Catalogo *cat) {
    int ordem[MAX_AGENTES];
    int i;
    int j;
    int tmp;

    if (cat->total == 0) {
        printf("Nenhum agente cadastrado.\n");
        return;
    }
    for (i = 0; i < cat->total; i++) ordem[i] = i;
    for (i = 0; i < cat->total - 1; i++) {
        for (j = i + 1; j < cat->total; j++) {
            if (cat->notas[ordem[j]] > cat->notas[ordem[i]]) {
                tmp = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = tmp;
            }
        }
    }

    printf("\nPOS  ID    NOTA   NOME\n");
    for (i = 0; i < cat->total; i++) {
        printf("%-4d %-5d %-6.2f %s\n", i + 1, cat->ids[ordem[i]],
               cat->notas[ordem[i]], cat->nomes[ordem[i]]);
    }
}

// Autor: Vitor Hugo (menu principal)
void executar_menu(Catalogo *cat) {
    int opcao = -1;

    while (opcao != 0) {
        mostrar_menu(cat);
        opcao = ler_inteiro("Opcao: ");
        if (opcao == 1) cadastrar(cat);
        else if (opcao == 2) listar(cat);
        else if (opcao == 3) buscar_id(cat);
        else if (opcao == 4) buscar_nome(cat);
        else if (opcao == 5) ranking(cat);
        else if (opcao != 0) printf("Opcao invalida.\n");
    }
    printf("Ate logo!\n");
}

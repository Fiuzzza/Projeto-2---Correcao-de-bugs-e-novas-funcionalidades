#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade (entre 1 e 10): ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer();

    if(tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10) {
        printf("Prioridade deve estar entre 1 e 10.\n");
        return OK; 
    }

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, TAMANHO_CATEGORIA, stdin);
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0'; 

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, TAMANHO_DESCRICAO, stdin);
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0'; 

    *pos = *pos + 1;

    return OK;
}


ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    char categoria[100];
    printf("Entre com a categoria que deseja listar (deixe vazio para listar todas): ");
    fgets(categoria, 100, stdin);
    categoria[strcspn(categoria, "\n")] = '\0'; 

    int encontrou = 0; 

    for(int i=0; i<*pos; i++){
        if(categoria[0] == '\0' || strcmp(tarefas[i].categoria, categoria) == 0) {
            encontrou = 1;
            printf("Pos: %d\t", i+1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
    }

    if(!encontrou) {
        if(categoria[0] == '\0')
            printf("Nenhuma tarefa encontrada.\n");
        else
            printf("Nenhuma tarefa encontrada na categoria '%s'.\n", categoria);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}

ERROS exportar(Tarefa tarefas[], int *pos) {
    if (*pos == 0)
        return SEM_TAREFAS;

    char nome_arquivo[100];
    printf("Digite o nome do arquivo para exportar as tarefas: ");
    scanf("%s", nome_arquivo);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
        return ABRIR;

    for (int i = 0; i < *pos; i++) {
        fprintf(arquivo, "Prioridade: %d\tCategoria: %s\tDescricao: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
    }

    fclose(arquivo);

    return OK;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

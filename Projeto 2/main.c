#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos); 
    if(erro != OK) {
        printf("Erro ao carregar tarefas. Código de erro: %d\n", erro);
        return 1; 
    }

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        if(opcao < 0 || opcao > 3) {
            printf("Opcao invalida\n");
            continue;
        }

        if(opcao == 0) {
            break; 
        }

        erro = fs[opcao - 1](tarefas, &pos);
        if(erro != OK) {
            printf("Erro ao executar a operacao. Código de erro: %d\n", erro);
        }

    } while(opcao != 0);

    erro = fs[3](tarefas, &pos); 
    if(erro != OK) {
        printf("Erro ao salvar tarefas. Código de erro: %d\n", erro);
        return 1; 
    }

    return 0; 
}

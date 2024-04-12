#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, exportar, carregar}; 

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[5](tarefas, &pos); 
    if(erro != OK)
        pos = 0;

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas\n");
        printf("5 - Carregar tarefas do arquivo binario\n"); 
        printf("6 - Salvar tarefas no arquivo binario\n"); 
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        if(opcao < 0 || opcao > 6) {
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

    } while(opcao >= 0);

    if (opcao == 0 || opcao == 4 || opcao == 5 || opcao == 6) { 
        erro = fs[opcao](tarefas, &pos);
        if(erro != OK) {
            printf("Erro ao executar a operacao. Código de erro: %d\n", erro);
        }
    }

    return 0; 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da conta
struct Conta {
    int numero;
    int agencia;
    float saldo;
    char tipo[10];
    struct Conta* prox;
};

// Definição da estrutura da fila
struct Fila {
    struct Conta* frente;
    struct Conta* tras;
};

// Função para criar uma nova conta
struct Conta* criarConta(int numero, int agencia, float saldo, const char* tipo) {
    struct Conta* novaConta = (struct Conta*)malloc(sizeof(struct Conta));
    novaConta->numero = numero;
    novaConta->agencia = agencia;
    novaConta->saldo = saldo;
    strcpy(novaConta->tipo, tipo);
    novaConta->prox = NULL;
    return novaConta;
}

// Função para criar uma nova fila vazia
struct Fila* criarFila() {
    struct Fila* novaFila = (struct Fila*)malloc(sizeof(struct Fila));
    novaFila->frente = NULL;
    novaFila->tras = NULL;
    return novaFila;
}

// Função para verificar se a fila está vazia
int filaVazia(struct Fila* fila) {
    return (fila->frente == NULL);
}

// Função para inserir uma conta na fila (enqueue)
void inserirConta(struct Fila* fila, int numero, int agencia, float saldo, const char* tipo) {
    struct Conta* novaConta = criarConta(numero, agencia, saldo, tipo);
    
    if (filaVazia(fila)) {
        fila->frente = novaConta;
        fila->tras = novaConta;
    } else {
        fila->tras->prox = novaConta;
        fila->tras = novaConta;
    }
    
    printf("Conta inserida com sucesso!\n");
}

// Função para remover uma conta da fila (dequeue)
void removerConta(struct Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Nenhuma conta para remover.\n");
        return;
    }
    
    struct Conta* contaRemovida = fila->frente;
    fila->frente = fila->frente->prox;
    
    free(contaRemovida);
    
    printf("Conta removida com sucesso!\n");
}

// Função para exibir todas as contas da fila
void exibirContas(struct Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Nenhuma conta para exibir.\n");
        return;
    }
    
    struct Conta* contaAtual = fila->frente;
    
    printf("Contas na fila:\n");
    while (contaAtual != NULL) {
        printf("Numero: %d, Agencia: %d, Saldo: %.2f, Tipo: %s\n", contaAtual->numero, contaAtual->agencia, contaAtual->saldo, contaAtual->tipo);
        contaAtual = contaAtual->prox;
    }
}

// Função principal
int main() {
    struct Fila* filaContas = criarFila();
    int opcao;
    
    do {
        printf("\nEscolha a opcao:\n");
        printf("0. Sair\n");
        printf("1. Zerar FILA\n");
        printf("2. Exibir FILA\n");
        printf("3. Enqueue - Inserir Conta\n");
        printf("4. Dequeue - Excluir Conta\n");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 0:
                printf("Encerrando o programa...\n");
                break;
            case 1:
                // Zerar FILA
                while (!filaVazia(filaContas)) {
                    removerConta(filaContas);
                }
                printf("FILA zerada!\n");
                break;
            case 2:
                // Exibir FILA
                exibirContas(filaContas);
                break;
            case 3:
                // Enqueue - Inserir Conta
                int numero, agencia;
                float saldo;
                char tipo[10];
                
                printf("Digite o numero da conta: ");
                scanf("%d", &numero);
                printf("Digite a agencia: ");
                scanf("%d", &agencia);
                printf("Digite o saldo: ");
                scanf("%f", &saldo);
                printf("Digite o tipo (Corrente, Poupanca ou Salario): ");
                scanf("%s", tipo);
                
                inserirConta(filaContas, numero, agencia, saldo, tipo);
                break;
            case 4:
                // Dequeue - Excluir Conta
                removerConta(filaContas);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
    
    return 0;
}

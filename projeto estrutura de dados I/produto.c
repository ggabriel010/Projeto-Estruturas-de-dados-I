#include <stdio.h>
#include <string.h>
#include "produto.h"

void listarProdutos(struct Produto* produtos, int qtdProdutos) {
    printf("=== Lista de Produtos ===\n");
    for (int i = 0; i < qtdProdutos; i++) {
        printf("%d. %s - R$ %.2f - %s\n", i + 1, produtos[i].nome, produtos[i].preco, produtos[i].categoria);
    }
    printf("=========================\n");
}

void adicionarProduto(struct Produto* produtos, int* qtdProdutos) {
    if (*qtdProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    printf("Digite o nome do produto: ");
    scanf("%s", produtos[*qtdProdutos].nome);
    printf("Digite o preço do produto: ");
    scanf("%f", &produtos[*qtdProdutos].preco);
    printf("Digite a categoria do produto: ");
    scanf("%s", produtos[*qtdProdutos].categoria);

    (*qtdProdutos)++;
    printf("Produto adicionado com sucesso!\n");
}

void excluirProduto(struct Produto* produtos, int* qtdProdutos) {
    int escolha;
    listarProdutos(produtos, *qtdProdutos);
    printf("Digite o número do produto que deseja excluir: ");
    scanf("%d", &escolha);

    if (escolha > 0 && escolha <= *qtdProdutos) {
        for (int i = escolha - 1; i < *qtdProdutos - 1; i++) {
            produtos[i] = produtos[i + 1];
        }
        (*qtdProdutos)--;
        printf("Produto excluído com sucesso!\n");
    } else {
        printf("Número do produto inválido!\n");
    }
}

void editarProduto(struct Produto* produtos, int qtdProdutos) {
    int escolha;
    listarProdutos(produtos, qtdProdutos);
    printf("Digite o número do produto que deseja editar: ");
    scanf("%d", &escolha);

    if (escolha > 0 && escolha <= qtdProdutos) {
        printf("Digite o novo nome do produto: ");
        scanf("%s", produtos[escolha - 1].nome);
        printf("Digite o novo preço do produto: ");
        scanf("%f", &produtos[escolha - 1].preco);
        printf("Digite a nova categoria do produto: ");
        scanf("%s", produtos[escolha - 1].categoria);
        printf("Produto editado com sucesso!\n");
    } else {
        printf("Número do produto inválido!\n");
    }
}

void salvarProdutos(struct Produto* produtos, int qtdProdutos) {
    FILE* file = fopen("produtos.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < qtdProdutos; i++) {
        fprintf(file, "%s %.2f %s\n", produtos[i].nome, produtos[i].preco, produtos[i].categoria);
    }

    fclose(file);
    printf("Produtos salvos com sucesso!\n");
}

void carregarProdutos(struct Produto* produtos, int* qtdProdutos) {
    FILE* file = fopen("produtos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    *qtdProdutos = 0;
    while (fscanf(file, "%s %f %s", produtos[*qtdProdutos].nome, &produtos[*qtdProdutos].preco, produtos[*qtdProdutos].categoria) != EOF) {
        (*qtdProdutos)++;
    }

    fclose(file);
    printf("Produtos carregados com sucesso!\n");
}

int buscaBinaria(struct Produto* produtos, int qtdProdutos, char* nome) {
    int inicio = 0, fim = qtdProdutos - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(produtos[meio].nome, nome);

        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

void merge(struct Produto* produtos, int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    struct Produto L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = produtos[inicio + i];
    for (j = 0; j < n2; j++)
        R[j] = produtos[meio + 1 + j];

    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].nome, R[j].nome) <= 0) {
            produtos[k] = L[i];
            i++;
        } else {
            produtos[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        produtos[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        produtos[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Produto* produtos, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(produtos, inicio, meio);
        mergeSort(produtos, meio + 1, fim);

        merge(produtos, inicio, meio, fim);
    }
}

void ordenarProdutos(struct Produto* produtos, int qtdProdutos) {
    mergeSort(produtos, 0, qtdProdutos - 1);
    printf("Produtos ordenados com sucesso!\n");
}
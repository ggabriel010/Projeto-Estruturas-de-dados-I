#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 100

struct Produto {
    char nome[50];
    float preco;
    char categoria[50];
};

void listarProdutos(struct Produto* produtos, int qtdProdutos);
void adicionarProduto(struct Produto* produtos, int* qtdProdutos);
void excluirProduto(struct Produto* produtos, int* qtdProdutos);
void editarProduto(struct Produto* produtos, int qtdProdutos);
void salvarProdutos(struct Produto* produtos, int qtdProdutos);
void carregarProdutos(struct Produto* produtos, int* qtdProdutos);
int buscaBinaria(struct Produto* produtos, int qtdProdutos, char* nome);
void ordenarProdutos(struct Produto* produtos, int qtdProdutos);

#endif

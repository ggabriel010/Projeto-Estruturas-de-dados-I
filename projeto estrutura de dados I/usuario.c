#include <stdio.h>
#include "produto.h"
#include "usuario.h"

int main() {
    struct Produto produtos[MAX_PRODUTOS];
    struct Usuario usuarios[MAX_USUARIOS] = {{"admin", "admin123", "admin@sports.com"}};
    int qtdProdutos = 0;
    int qtdUsuarios = 1;

    if (!login(usuarios, qtdUsuarios)) {
        printf("Você foi bloqueado após 3 tentativas!\n");
        return 0;
    }

    int opcao;
    do {
        printf("\n======= Menu =======\n");
        printf("1. Listar Produtos\n");
        printf("2. Adicionar Produto\n");
        printf("3. Excluir Produto\n");
        printf("4. Editar Produto\n");
        printf("5. Salvar Produtos\n");
        printf("6. Carregar Produtos\n");
        printf("7. Buscar Produto\n");
        printf("8. Ordenar Produtos\n");
        printf("0. Sair\n");
        printf("====================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarProdutos(produtos, qtdProdutos);
                break;
            case 2:
                adicionarProduto(produtos, &qtdProdutos);
                break;
            case 3:
                excluirProduto(produtos, &qtdProdutos);
                break;
            case 4:
                editarProduto(produtos, qtdProdutos);
                break;
            case 5:
                salvarProdutos(produtos, qtdProdutos);
                break;
            case 6:
                carregarProdutos(produtos, &qtdProdutos);
                break;
            case 7: {
                char nome[50];
                printf("Digite o nome do produto: ");
                scanf("%s", nome);
                int index = buscaBinaria(produtos, qtdProdutos, nome);
                if (index != -1) {
                    printf("Produto encontrado: %s - R$ %.2f - %s\n", produtos[index].nome, produtos[index].preco, produtos[index].categoria);
                } else {
                    printf("Produto não encontrado!\n");
                }
                break;
            }
            case 8:
                ordenarProdutos(produtos, qtdProdutos);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

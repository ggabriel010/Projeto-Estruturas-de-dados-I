#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_USUARIOS 5

struct Produto {
    char nome[50];
    float preco;
    char categoria[50];
};

struct Usuario {
    char nome[50];
    char senha[50];
    char email[50];
};


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


int verificarEmailValido(char* email, struct Usuario* usuarios, int qtdUsuarios) {
    if (strchr(email, '@') == NULL || strlen(email) >= 80) {
        return 0;
    }

    for (int i = 0; i < qtdUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            return 0;
        }
    }

    return 1;
}

int login(struct Usuario* usuarios, int qtdUsuarios) {
    char nome[50];
    char senha[50];
    char email[50];
    int tentativas = 3;

    while (tentativas > 0) {
        printf("Digite o nome do usuário: ");
        scanf("%s", nome);
        printf("Digite a senha: ");
        scanf("%s", senha);
        printf("Digite o email: ");
        scanf("%s", email);

        for (int i = 0; i < qtdUsuarios; i++) {
            if (strcmp(usuarios[i].nome, nome) == 0 && strcmp(usuarios[i].senha, senha) == 0 && strcmp(usuarios[i].email, email) == 0) {
            printf("==================================\n");
            printf("Login bem sucedido!\n");
            printf("Bem-vindo à Loja Performance Sports!\n");
            printf("==================================\n");
              
                return 1;
            }
        }

        tentativas--;
        printf("Login incorreto! Tentativas restantes: %d\n", tentativas);
    }

    return 0;
}

void cadastrarUsuario(struct Usuario* usuarios, int* qtdUsuarios) {
    if (*qtdUsuarios >= MAX_USUARIOS) {
        printf("Limite de usuários atingido!\n");
        return;
    }

    printf("Digite o nome do novo usuário: ");
    scanf("%s", usuarios[*qtdUsuarios].nome);
    printf("Digite a senha: ");
    scanf("%s", usuarios[*qtdUsuarios].senha);
    printf("Digite o email: ");
    scanf("%s", usuarios[*qtdUsuarios].email);

    if (!verificarEmailValido(usuarios[*qtdUsuarios].email, usuarios, *qtdUsuarios)) {
        printf("Email inválido ou já registrado!\n");
        return;
    }

    (*qtdUsuarios)++;
    printf("Usuário cadastrado com sucesso!\n");
}

int main() {
    struct Usuario usuarios[MAX_USUARIOS] = {
        {"admin", "admin123", "admin@gmail.com"},
        {"kewim", "kewim123", "kewim@gmail.com"},
        {"reudismam", "santos", "santos2011@gmail.com"},
        {"gabriel", "mengao", "flamengo2022@gmail.com"},
        {"flamengo", "jesus", "jorgejesus2019@gmail.com"}
    };

    struct Produto produtos[MAX_PRODUTOS] = {
        {"Chuteira Futsal Umbro Pró 5", 261.89, "Chuteira"},
        {"Tênis Umbro Street Jogger", 159.90, "Chuteira"},
        {"Tênis Masculino Adidas Ultra Energy - Preto+Branco", 206.89, "Tênis"},
        {"Chuteira Futsal Adidas F50 Club Unissex", 261.99, "Chuteira"},
        {"Camisa Borussia Dortmund Home 23/24", 160.00, "Camisas"},
        {"Camisa Manchester United Home", 170.90, "Camisas"},
        {"Camisa Juventus Away 23/24", 180.00, "Camisas"},
        {"Camisa Santos I 24/25", 350.00, "Camisas"},
        {"Camisa Santos II 24/25", 360.90, "Camisas"},
        {"Camisa Flamengo I 24/25", 320.00, "Camisas"},
        {"Camisa Flamengo II 24/25", 300.90, "Camisas"},
        {"Camiseta Vasco Kappa Masculina", 100.90, "Camisas"},
        {"WHEY 100% PURE CONCENTRADO 900G - PROBIOTICA", 100.00, "Suplemento"},
        {"Tênis New Balance 327 V1 - Marinho+Laranjaa", 450.90, "Tênis"},
        {"Camisa Bayern de Munique Third 23/24", 390.00, "Camisas"},
        {"Camisa Puma Al-Hilal Home 2024", 399.90, "Camisas"},
        {"Camisa Retro Santos 2012/2013 Away Azul", 450.90, "Camisas"},
        {"Tênis Olympikus Cyber 3 Unissex", 250.00, "Tênis"},
        {"Tênis Under Armour Spawn 3 Preto - Preto", 299.90, "Tênis"},
        {"Tênis Nike E-Series AD Masculino - Branco", 379.90, "Tênis"}
    };

    int qtdUsuarios = 5; // Número inicial de usuários
    int qtdProdutos = 20; // Número inicial de produtos
    int escolha;

    if (login(usuarios, qtdUsuarios)) {
        do {
            printf("1. Listar produtos\n");
            printf("2. Adicionar produto\n");
            printf("3. Excluir produto\n");
            printf("4. Editar produto\n");
            printf("5. Salvar produtos\n");
            printf("6. Carregar produtos\n");
            printf("7. Buscar produto\n");
            printf("8. Ordenar produtos\n");
            printf("0. Sair\n");
            printf("Escolha: ");
            scanf("%d", &escolha);

            switch (escolha) {
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
                    printf("Digite o nome do produto que deseja buscar: ");
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
                    return 0;
                default:
                    printf("Opção inválida!\n");
            }
        } while (1);
    }

    return 0;
}

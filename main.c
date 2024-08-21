#include <stdio.h>
#include <string.h>

//Usuarios, senhas e e-mails foram definidos desde o inicio, segue os nomes a seguir;

// usuario: admin, senha:admin123, e-mail:admin@gmail.com
//usuario: kewim, senha: kewim123, e-mail:kewim@gmail.com
//usuario: reudismam, senha: santos, e-mail:santos2011@gmail.com
//usuario: gabriel, senha:mengao, e-mail:flamengo2022@gmail.com
//usuario: flamengo, senha:jesus, jorgejesus2019@gmail.com


#define MAX_PRODUTOS 100
#define MAX_USUARIOS 5
#define MAX_CARRINHO 50

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

struct Carrinho {
    struct Produto produtos[MAX_CARRINHO];
    int quantidade[MAX_CARRINHO];
    int totalProdutos;
};

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
            if (strcmp(usuarios[i].nome, nome) == 0 && 
                strcmp(usuarios[i].senha, senha) == 0 &&
                strcmp(usuarios[i].email, email) == 0) {
                printf("Login bem-sucedido!\n");
                return 1;
            }
        }

        tentativas--;
        printf("Usuário, senha ou email incorretos! Tentativas restantes: %d\n", tentativas);
    }

    return 0;
}

void mensagemBoasVindas() {
    printf("====================================\n");
    printf("Bem-vindo à Loja Performance Sports!\n");
    printf("====================================\n");
}

void listarProdutos(struct Produto* produtos, int qtdProdutos) {
    printf("=== Lista de Produtos ===\n");
    for (int i = 0; i < qtdProdutos; i++) {
        printf("%d. %s - R$ %.2f - %s\n", i + 1, produtos[i].nome, produtos[i].preco, produtos[i].categoria);
    }
    printf("=========================\n");
}

void adicionarAoCarrinho(struct Produto* produtos, int qtdProdutos, struct Carrinho* carrinho) {
    int escolha, quantidade;
    listarProdutos(produtos, qtdProdutos);
    printf("Digite o número do produto que deseja adicionar ao carrinho: ");
    scanf("%d", &escolha);

    if (escolha > 0 && escolha <= qtdProdutos) {
        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);
        carrinho->produtos[carrinho->totalProdutos] = produtos[escolha - 1];
        carrinho->quantidade[carrinho->totalProdutos] = quantidade;
        carrinho->totalProdutos++;
        printf("Produto adicionado ao carrinho!\n");
    } else {
        printf("Número do produto inválido!\n");
    }
}

void verCarrinho(struct Carrinho* carrinho) {
    if (carrinho->totalProdutos == 0) {
        printf("Carrinho vazio!\n");
        return;
    }

    printf("=== Carrinho de Compras ===\n");
    for (int i = 0; i < carrinho->totalProdutos; i++) {
        printf("%d. %s - R$ %.2f - Quantidade: %d\n", i + 1, carrinho->produtos[i].nome, carrinho->produtos[i].preco, carrinho->quantidade[i]);
    }
    printf("===========================\n");
}

void comprarCarrinho(struct Carrinho* carrinho) {
    float total = 0;
    printf("=== Finalizando a Compra ===\n");
    for (int i = 0; i < carrinho->totalProdutos; i++) {
        printf("%d. %s - R$ %.2f - Quantidade: %d\n", i + 1, carrinho->produtos[i].nome, carrinho->produtos[i].preco, carrinho->quantidade[i]);
        total += carrinho->produtos[i].preco * carrinho->quantidade[i];
    }
    printf("===========================\n");
    printf("Total da compra: R$ %.2f\n", total);
    printf("Compra realizada com sucesso!\n");
    carrinho->totalProdutos = 0; 
}

void menu() {
    printf("=== Escolha uma opção ===\n");
    printf("1 - Listar todos os produtos disponíveis\n");
    printf("2 - Adicionar produto ao carrinho\n");
    printf("3 - Ver carrinho\n");
    printf("4 - Comprar produtos do carrinho\n");
    printf("5 - Ver detalhes de um produto\n");
    printf("6 - Sair\n");
    printf("=========================\n");
}

void verDetalhesProduto(struct Produto* produtos, int qtdProdutos) {
    char nome[50];
    printf("Digite o nome do produto que deseja ver os detalhes: ");
    scanf("%s", nome);

    for (int i = 0; i < qtdProdutos; i++) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            printf("Detalhes do produto:\n");
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preço: R$ %.2f\n", produtos[i].preco);
            printf("Categoria: %s\n", produtos[i].categoria);
            return;
        }
    }

    printf("Produto não encontrado!\n");
}

int main() {
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
        {"WHEY PURE CONCENTRADO 900G - PROBIOTICA", 100.00, "Suplemento"},
        {"Tênis New Balance 327 V1 - Marinho+Laranjaa", 450.90, "Tênis"},
        {"Camisa Bayern de Munique Third 23/24", 390.00, "Camisas"},
        {"Camisa Puma Al-Hilal Home 2024", 399.90, "Camisas"},
        {"Camisa Retro Santos 2012/2013 Away Azul", 450.90, "Camisas"},
        {"Tênis Olympikus Cyber 3 Unissex", 250.00, "Tênis"},
        {"Tênis Under Armour Spawn 3 Preto - Preto", 299.90, "Tênis"},
        {"Tênis Nike E-Series AD Masculino - Branco", 379.90, "Tênis"}
    };
    struct Usuario usuarios[MAX_USUARIOS] = {
        {"admin", "admin123", "admin@gmail.com"},
        {"kewim", "kewim123", "kewim@gmail.com"},
        {"reudismam", "santos", "santos2011@gmail.com"},
        {"gabriel", "mengao", "flamengo2022@gmail.com"},
        {"flamengo", "jesus", "jorgejesus2019@gmail.com"}
    };
    struct Carrinho carrinho = {0}; 
    int qtdProdutos = 20;
    int qtdUsuarios = 5;

    if (!login(usuarios, qtdUsuarios)) {
        printf("Número de tentativas excedido. Programa encerrado.\n");
        return 1;
    }

    mensagemBoasVindas();

    int op;
    do {
        menu();
        scanf("%d", &op);
        switch (op) {
            case 1:
                listarProdutos(produtos, qtdProdutos);
                break;
            case 2:
                adicionarAoCarrinho(produtos, qtdProdutos, &carrinho);
                break;
            case 3:
                verCarrinho(&carrinho);
                break;
            case 4:
                comprarCarrinho(&carrinho);
                break;
            case 5:
                verDetalhesProduto(produtos, qtdProdutos);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (op != 6);

    return 0;
}

#ifndef USUARIO_H
#define USUARIO_H

#define MAX_USUARIOS 5

struct Usuario {
    char nome[50];
    char senha[50];
    char email[50];
};

int verificarEmailValido(char* email, struct Usuario* usuarios, int qtdUsuarios);
int login(struct Usuario* usuarios, int qtdUsuarios);
void cadastrarUsuario(struct Usuario* usuarios, int* qtdUsuarios);

#endif

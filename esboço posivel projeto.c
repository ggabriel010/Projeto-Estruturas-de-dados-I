#include <stdio.h>

struct Aluno {
  int mat;
  char nome[10];
  float media;
};

void cadastrar(struct Aluno* v, int* qtd) {
    printf("Informe os dados do aluno:\n");
    scanf("%d %s %f", &v[*qtd].mat, v[*qtd].nome, &v[*qtd].media);
    *qtd = *qtd + 1;
}

void listar(struct Aluno* v, int qtd) {
    int i;
    for (i = 0; i < qtd; i++) {
        printf("Aluno: %d %s %f\n", v[i].mat, v[i].nome, v[i].media);
    }
}

void atualizar (struct aluno *v, int qtd) {
int i;
int mat;
   printf("digite a matricúla do aluno:");
   scanf("%d", &mat );
   int atualizou=0;
for ( i = 0; i < qtd; i++){
    if(v[i].mat == mat){
        printf("informe a nova média:");
        int media;
        scanf("%f", &v[i].media);
        atualizou= 1;
    }
    if (atualizou==0){
        printf("Infelizmente o aluno não foi encontrado.\n");

    }
    
}
void excluir(struct aluno *v, int *qtd){
 int i;
 printf("informe a matricula do aluno") ;
 int mat;
 scanf("%d", &mat);
struct aluno temp(*qtd);
int j=0;
 int i=0;
 for ( i = 0; i < *qtd; i++){
if(v[i].mat != mat){
    temp[j]= v[i];
    j++;
}
 }
  for ( i = 0; i < j; i++){
    v[i]= temp[i];
  }
  if (j==*qtd){
    printf("aluno não encontrado!\n");
  }
  else{
    *qtd= *qtd -1
  }
  
};


};


void menu() {
    printf("=== escolha uma opcao ===\n");
    printf("1 - cadastrar\n");
    printf("2 - listar\n");
    printf("0 - sair\n");
      printf("3 - atualizar\n");            
    printf("==========================\n");
}



int main() {
    //!showMemory(start=65520)
    struct Aluno v[20];
    int qtd = 0;
    menu();
    int op;
    scanf("%d", &op);
    while (op != 0) {
        if (op == 1) {
            cadastrar(v, &qtd);
           
        }
        else if (op == 2) {
            listar(v, qtd);
        } 
         else if (op == 2) {
            listar(v, qtd);
        } 
        menu();
        scanf("%d", &op);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct aluno {
  int codigo;
  char nome[100];
  int cpf;
};

struct disciplina {
  int codigo;
  char nome[50];
  char professor[100];
  int creditos;
};

int main(){
  int menu;
  printf("MENU\n");
  printf("1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3.Consulta por Aluno\n4.Consulta por Disciplina\n5.Sair\n");
  while(1){  
    scanf("%d", &menu);
    switch (menu){
      case 1:
        printf("cadastro aluno.\n");
        //Cadastro do aluno
      break;
      case 2:
        printf("cadastro da disciplina\n");
        //cadastro da disciplina
      break;

      case 3:
        printf("consulta por aluno.\n");
        //consulta por aluno
      break;
      case 4:
        printf("consulta por disciplina.\n");
        //consulta por disciplina
      break;
      case 5:
        printf("Tchau\n");
        return 0;
      default:
        printf("Opção inválida! Tente novamente.");
      break;
    }
  }
  FILE* file;
  
  // struct disciplina *d;
  // d = (struct disciplina*)malloc(sizeof(struct disciplina));
  // printf("Digite o nome da disciplina: ");
  // fgets(d->nome,sizeof(d->nome),stdin);

  // printf("Digite o codigo da disciplina: ");
  // scanf("%d", &d->codigo);
  // fflush(stdin);

  // printf("Digite o nome do professor: ");
  // fgets(d->professor,sizeof(d->professor),stdin);

  // printf("Digite o número de creditos da disciplina: ");
  // scanf("%d", &d->creditos);

  // printf("%s %d \n %s %d", d->nome,d->codigo,d->professor,d->creditos);

}
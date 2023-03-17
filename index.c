#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno {
  int codigo;
  char nome[100];
  char cpf[15];
};

struct disciplina {
  int codigo;
  char nome[50];
  char professor[100];
  int creditos;
};

void consultaAluno(){
    FILE* fp = fopen("../students.csv", "r");
 
    if (!fp)
        printf("Can't open file\n");
    else {
        // Here we have taken size of array 1024 you can modify it
        char buffer[1024];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer, 1024, fp)) {
            column = 0;
            row++;
 
            // Splitting the data
            char* value = strtok(buffer, ",");
 
            while (value) {
                // Column 1
                if (column == 0) {
                    printf("Nome: ");
                }
 
                // Column 2
                if (column == 1) {
                    printf("\tCodigo: ");
                }
 
                // Column 3
                if (column == 2) {
                    printf("\tCPF: ");
                }
 
                printf("%s", value);
                value = strtok(NULL, ", ");
                column++;
            }
 
            printf("\n");
        }
 
        // Close the file
        fclose(fp);
    }
    return;
}

void cadastroAluno(){
  FILE* fp = fopen("../students.csv", "a+");
  if (!fp) {
        printf("Can't open file\n");
        return;
  }
  struct aluno *a;
  a = (struct aluno*)malloc(sizeof(struct aluno));

  printf("Digite o nome do aluno: ");
  fgets(a->nome,sizeof(a->nome),stdin);
  a->nome[strcspn(a->nome, "\n")] = '\0'; // substitui \n por \0

  printf("Digite o codigo do aluno: ");
  scanf("%d", &a->codigo);
  fflush(stdin);

  printf("Digite o CPF do aluno: ");
  fgets(a->cpf,sizeof(a->cpf),stdin);
  a->cpf[strcspn(a->cpf, "\n")] = '\0'; // substitui \n por \0

  printf("Deseja adicionar disciplina?\n1. Sim\n2. Nao\n ");
  int op;
  scanf("%d", &op);
  switch (op){
  case 1:
    /* code */
    break;
  case 2:
    /* code */
    break;
  
  default:
    printf("Opção Inválida\n");
    break;
  }

  // Saving data in file
  fprintf(fp, "%s, %d, %s\n", a->nome, a->codigo, a->cpf);
 
  printf("\nNovo aluno adicionado ao sistema.\n");
 
  fclose(fp);
  free(a);
  return;
}

void cadastroDisciplina(){
  FILE* fp = fopen("../disciplinas.csv", "a+");
  if (!fp) {
        printf("Can't open file\n");
        return;
  }
  
  struct disciplina *d;
  d = (struct disciplina*)malloc(sizeof(struct disciplina));
  printf("Digite o nome da disciplina: ");
  fgets(d->nome,sizeof(d->nome),stdin);
  d->nome[strcspn(d->nome, "\n")] = '\0'; // substitui \n por \0

  printf("Digite o codigo da disciplina: ");
  scanf("%d", &d->codigo);
  fflush(stdin);

  printf("Digite o nome do professor: ");
  fgets(d->professor,sizeof(d->professor),stdin);
  d->professor[strcspn(d->professor, "\n")] = '\0'; // substitui \n por \0

  printf("Digite o número de creditos da disciplina: ");
  scanf("%d", &d->creditos);
  fflush(stdin);

  // Saving data in file
  fprintf(fp, "%s, %d, %s, %d\n", d->nome, d->codigo, d->professor, d->creditos);
 
  printf("\nNova disciplina adicionada ao sistema.\n");
 
  fclose(fp);
  free(d);
  return;
}

int main(){
  int menu;
  printf("MENU\n");
  printf("1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Sair\n");
  while(1){  
    scanf("%d", &menu);
    fflush(stdin);
    switch (menu){
      case 1:
        printf("Cadastro aluno.\n");
        cadastroAluno();
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Sair\n");

      break;
      case 2:
        printf("Cadastro da disciplina\n");
        cadastroDisciplina();
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Sair\n");
        //cadastro da disciplina
      break;

      case 3:
        printf("Consulta por aluno.\n");
        consultaAluno();
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Sair\n");
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
        printf("Opção inválida! Tente novamente.\n");
      break;
    }
  }
  // FILE* file;
  
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
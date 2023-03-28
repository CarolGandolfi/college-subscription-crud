#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

char* existeDisciplina(char nome[50]){
  FILE* fp = fopen("../disciplinas.csv", "r");
  if (!fp){
    printf("Can't open file\n");
  }else{
    char buffer[1024];
    char lowerNome[50];
    strcpy(lowerNome, nome);

    for(unsigned int i=0; i< strlen(lowerNome); i++){
      lowerNome[i] = tolower(lowerNome[i]);
    } 
    // printf("a materia %s existe?\n", lowerNome);
    int row = 0;
    // int column = 0;
 
    while (fgets(buffer, 1024, fp)) {
      // column = 0;
      row++;
      // Splitting the data
      char* value = strtok(buffer, ",");
 
      if(strcmp(lowerNome, value)==0){
        //printf ("existe e o codigo eh %s\n", value);
        // column = 1;
        fclose(fp);
        return value;
      }
    }
    //printf("Nao existe\n");
    // Close the file
    fclose(fp);
  }
  return "\0";

}

void consultaAluno(char nome[100]){
  FILE* fp = fopen("../students.csv", "r");

  if (!fp){
    printf("Can't open file\n");
  }else{
    char buffer[1024];
    char lowerNome[50];
    strcpy(lowerNome, nome);
    for(unsigned int i=0; i< strlen(lowerNome); i++){
      lowerNome[i] = tolower(lowerNome[i]);
    } 

    int row = 0;
    int column = 0;
 
    while (fgets(buffer, 1024, fp)) {
      column = 0;
      row++;
      // Splitting the data
      char* value = strtok(buffer, ",{}-");
 
      if(strcmp(lowerNome, value)==0){
        while (strcmp(value,"\n")) {
          // Column 1
          if (column == 0) {
            value[0]=toupper(value[0]);
            printf("Nome: %s", value);
          }
 
          // Column 2
          if (column == 1) {
            printf("\tCodigo:%s", value);
          }
 
          // Column 3
          if (column == 2) {
            printf("\tCPF:%s\n", value);
          }

          if (column>2){
            printf("%s\n", value);
          }
          value = strtok(NULL, ",{}-");
          column++;
        } 
        fclose(fp);
        return;
      }else{
        printf("Aluno nao cadastrado.\n");
      }
    }
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
  for(unsigned int i=0; i<strlen(a->nome); i++){
    a->nome[i] = tolower(a->nome[i]);
  }

  printf("Digite o codigo do aluno: ");
  scanf("%d", &a->codigo);
  fflush(stdin);

  printf("Digite o CPF do aluno: ");
  fgets(a->cpf,sizeof(a->cpf),stdin);
  a->cpf[strcspn(a->cpf, "\n")] = '\0'; // substitui \n por \0

  fprintf(fp, "%s, %d, %s", a->nome, a->codigo, a->cpf);

  int op=0;
  do{
    printf("Deseja adicionar disciplinas a um período?\n1. Sim\n2. Nao\n");
    char per[10], str[50], disciplina[50];
    scanf("%d", &op);
    fflush(stdin);
    if (op==1){
      printf("Qual período a matéria foi/será cursada? (formato AAAA.S)\n");
      fgets(per,sizeof(per),stdin);
      per[strcspn(per, "\n")] = '\0';
      fprintf(fp, ", %s{", per);
      int oc=0;
      //materias do periodo
      do{
        printf("Qual a disciplina cursada?(digite 0 para sair)\n");
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")] = '\0';
        //
        if(strcmp(str,"0")==0){
          break;
        }
        strcpy(disciplina, existeDisciplina(str));

        if(strlen(disciplina)==0){
          printf("Essa disciplina nao esta cadastrada.\n");
        }else{
          printf("Disciplina adicionada ao periodo.\n");
          if(oc==0){
            oc++;
            fprintf(fp, "%s", disciplina);
          }else{
            fprintf(fp, "-%s", disciplina);
          }
        }
      } while (1);
      fprintf(fp, "}");

    } else if (op!=1 && op!=2){
      printf("Opcao invalida");
    }

  } while (op!=2);

  // Saving data in file
  fprintf(fp, "\n");
 
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
  for(unsigned int i=0; i<strlen(d->nome); i++){
    d->nome[i] = tolower(d->nome[i]);
  }

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
        printf("Digite o nome completo a ser consultado: ");
        char name[50];
        fgets(name,sizeof(name),stdin);
        name[strcspn(name, "\n")] = '\0'; // substitui \n por \0
        consultaAluno(name);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Sair\n");
        //consulta por aluno
      break;
      case 4:
        printf("consulta por disciplina.\n");
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Sair\n");
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
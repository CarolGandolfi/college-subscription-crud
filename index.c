#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  int codigo;
  char nome[100];
  char cpf[15];
  struct aluno* prox;
} aluno;

typedef struct {
  char periodo[7];
  int codAl;
  int codDis;
  struct periodo* prox;
} periodo;

typedef struct {
  int codigo;
  char nome[50];
  char professor[100];
  int creditos;
  struct disciplina* prox;
} disciplina;

void insereAluno (int cod, char cpf[15], char nome[100], aluno *p){
  aluno *nova;
  nova = malloc (sizeof (aluno));
  nova->codigo = cod;
  strcpy(nova->cpf, cpf);
  strcpy(nova->nome, nome);
  nova->prox = p->prox;
  p->prox = (struct aluno*)nova;
}

void insereDisciplina (int cod, char nome[50], char prof[100], int cred, disciplina *p){
  disciplina *nova;
  nova = malloc (sizeof (disciplina));
  nova->codigo = cod;
  strcpy(nova->nome, nome);
  strcpy(nova->professor, prof);
  nova->creditos = cred;
  nova->prox = p->prox;
  p->prox = (struct disciplina*)nova;
}

aluno* busca_codAl (int cod, aluno *le){
  if (le == NULL)  return NULL;
  if (le->codigo == cod)  return le;
  return busca_codAl (cod, (aluno *)le->prox);
}

aluno* busca_nomeAl (char nome[100], aluno *le){
  if (le == NULL)  return NULL;
  if (strcmp(le->nome, nome))  return le;
  return busca_nomeAl (nome, (aluno *)le->prox);
}

disciplina* busca_codDis (int cod, disciplina *le){
  if (le == NULL)  return NULL;
  if (le->codigo == cod)  return le;
  return busca_codDis (cod, (disciplina *)le->prox);
}

disciplina* busca_nomeDis (char nome[100], disciplina *le){
  if (le == NULL)  return NULL;
  if (strcmp(le->nome, nome) || strcmp(le->professor, nome))  return le;
  return busca_nomeDis (nome, (disciplina *)le->prox);
}

void imprimeA (aluno *le) {
   aluno *p;
   for (p = (aluno *)le->prox; p != NULL; p = (aluno *)p->prox)
      printf ("Nome: %s\tCodigo: %d\n", p->nome, p->codigo);
}

void imprimeD (disciplina *le) {
   disciplina *p;
   for (p = (disciplina *)le->prox; p != NULL; p = (disciplina *)p->prox)
      printf ("Disciplina: %s\tCodigo: %d\tProfessor: %s\t Creditos: %d\n", p->nome, p->codigo, p->professor, p->creditos);
}

void removeAluno (aluno *p){
   aluno *lixo;
   lixo = (aluno *)p->prox;
   p->prox = lixo->prox;
   free (lixo);
}

void removeDisciplina (disciplina *p){
  disciplina *lixo;
  lixo = (disciplina *)p->prox;
  p->prox = lixo->prox;
  free (lixo);
}

char* existeDisciplina(char nome[50]){
  //verifica se existe o nome ou numero da discilpina pesquisada
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
    //printf("o nome ou numero pesquisado eh %s\n", lowerNome);
    // printf("a materia %s existe?\n", lowerNome);
    int row = 0;
    // int column = 0;
 
    while (fgets(buffer, 1024, fp)) {
      // column = 0;
      row++;
      // Splitting the data
      char* value = strtok(buffer, ",");
      char* numero= strtok(NULL, ",");
      //printf("o numero da disciplina %s eh %s\n", value, numero);
 
      if(strcmp(lowerNome, value)==0 || strcmp(lowerNome, numero)==0){
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
    int cont = 0;
 
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
            printf("\tCodigo: %s", value);
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
        cont++;
        fclose(fp);
        return;
      }
    }
    if (cont==0){
      printf("Aluno nao cadastrado.\n");
    }

    fclose(fp);
  }
  return;
}

void cadastroAluno(aluno* a){
  FILE* fp = fopen("../students.csv", "a+");
  if (!fp) {
        printf("Can't open file\n");
        return;
  }
  // aluno *a;
  // a = (aluno*)malloc(sizeof(aluno));

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

  fprintf(fp, "%s,%d, %s", a->nome, a->codigo, a->cpf);

  // int op=0;
  // do{
  //   printf("Deseja adicionar disciplinas a um periodo?\n1. Sim\n2. Nao\n");
  //   char per[10], str[50], disciplina[50];
  //   scanf("%d", &op);
  //   fflush(stdin);
  //   if (op==1){
  //     printf("Qual período a materia foi/sera cursada? (formato AAAA.S)\n");
  //     fgets(per,sizeof(per),stdin);
  //     per[strcspn(per, "\n")] = '\0';
  //     fprintf(fp, ", %s{", per);
  //     int oc=0;
  //     //materias do periodo
  //     do{
  //       printf("Qual a disciplina cursada?(digite 0 para sair)\n");
  //       fgets(str,sizeof(str),stdin);
  //       str[strcspn(str, "\n")] = '\0';
  //       //
  //       if(strcmp(str,"0")==0){
  //         break;
  //       }
  //       strcpy(disciplina, existeDisciplina(str));

  //       if(strlen(disciplina)==0){
  //         printf("Essa disciplina nao esta cadastrada.\n");
  //       }else{
  //         printf("Disciplina adicionada ao periodo.\n");
  //         if(oc==0){
  //           oc++;
  //           fprintf(fp, "%s", disciplina);
  //         }else{
  //           fprintf(fp, "-%s", disciplina);
  //         }
  //       }
  //     } while (1);
  //     fprintf(fp, "}");

  //   } else if (op!=1 && op!=2){
  //     printf("Opcao invalida");
  //   }

  // } while (op!=2);

  // Saving data in file
  fprintf(fp, "aluno add\n");

  insereAluno(a->codigo, a->cpf, a->nome, a);
 
  printf("\nNovo aluno adicionado ao sistema.\n");
 
  fclose(fp);
  // free(a);
  return;
}

void discEmAl(char nome[100]){
  FILE* fp = fopen("../students.csv", "r+");
  int op=0;
  int row = 0;

  if (!fp){
    printf("Can't open file\n");
  }else{
    char buffer[1024];
    char lowerNome[100];
    strcpy(lowerNome, nome);

    for(unsigned int i=0; i< strlen(lowerNome); i++){
      lowerNome[i] = tolower(lowerNome[i]);
    } 

    while (fgets(buffer, 1024, fp)) {
      // column = 0;
      row++;
      fseek(fp, 30, SEEK_SET);
      // Splitting the data
      char* value = strtok(buffer, ",");
      char* numero= strtok(NULL, ",");
      // printf("o numero da disciplina %s eh %s\n", value, numero);
 
      if(strcmp(lowerNome, value)==0 || strcmp(lowerNome, numero)==0){
        do{
          printf("Deseja adicionar disciplinas a um periodo?\n1. Sim\n2. Nao\n");
          char per[10], str[50], disciplina[50];
          scanf("%d", &op);
          fflush(stdin);
          if (op==1){
            printf("Qual periodo a matéria foi/sera cursada? (formato AAAA.S)\n");
            fgets(per,sizeof(per),stdin);
            per[strcspn(per, "\n")] = '\0';
            fprintf(fp, ", %s{", per);
            int oc=0;
            //materias do periodo
            while (1){
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
            }
            fprintf(fp, "}");

          } else if (op!=1 && op!=2){
            printf("Opcao invalida");
          }

        } while (op!=2);
        fprintf(fp, "\n");
        //printf ("existe e o codigo eh %s\n", value);
        // column = 1;
      }
    }
  }

  // Saving data in file
  printf("\nNova disciplina cadastrada ao aluno.\n");
 
  fclose(fp);
  return;
}

void cadastroDisciplina(disciplina* ld){
  FILE* fp = fopen("../disciplinas.csv", "a+");
  if (!fp) {
        printf("Can't open file\n");
        return;
  }
  // disciplina *ld;
  // ld = (disciplina*)malloc(sizeof(disciplina));
  // ld->prox = NULL;
  printf("Digite o nome da disciplina: ");
  fgets(ld->nome,sizeof(ld->nome),stdin);
  ld->nome[strcspn(ld->nome, "\n")] = '\0'; // substitui \n por \0
  for(unsigned int i=0; i<strlen(ld->nome); i++){
    ld->nome[i] = tolower(ld->nome[i]);
  }

  printf("Digite o codigo da disciplina: ");
  scanf("%d", &ld->codigo);
  fflush(stdin);

  printf("Digite o nome do professor: ");
  fgets(ld->professor,sizeof(ld->professor),stdin);
  ld->professor[strcspn(ld->professor, "\n")] = '\0'; // substitui \n por \0

  printf("Digite o número de creditos da disciplina: ");
  scanf("%d", &ld->creditos);
  fflush(stdin);

  // Saving data in file
  insereDisciplina(ld->codigo, ld->nome, ld->professor, ld->creditos, ld);
  fprintf(fp, "%s,%d,%s,%d\n", ld->nome, ld->codigo, ld->professor, ld->creditos);
 
  printf("\nNova disciplina adicionada ao sistema.\n");
 
  fclose(fp);
  // free(ld);
  return;
}

int main(){
  int menu;
  disciplina *listaDis;
  listaDis = (disciplina*)malloc(sizeof(disciplina));
  listaDis->prox = NULL;

  aluno *listaAl;
  listaAl = (aluno*)malloc(sizeof(aluno));
  listaAl->prox = NULL;

  printf("MENU\n");
  printf("1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Add disciplina a aluno\n6. Sair\n");
  while(1){  
    scanf("%d", &menu);
    fflush(stdin);
    switch (menu){
      case 1:
        printf("Cadastro aluno.\n");
        cadastroAluno(listaAl);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Add disciplina a aluno\n6. Sair\n");

      break;
      case 2:
        printf("Cadastro da disciplina\n");
        cadastroDisciplina(listaDis);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Add disciplina a aluno\n6. Sair\n");
        //cadastro da disciplina
      break;

      case 3:
        printf("Consulta por aluno.\n");
        imprimeA(listaAl);
        printf("Digite o nome completo a ser consultado: ");
        char name[100];
        fgets(name,sizeof(name),stdin);
        name[strcspn(name, "\n")] = '\0'; // substitui \n por \0
        // consultaAluno(name);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Add disciplina a aluno\n6. Sair\n");
        //consulta por aluno
      break;
      case 4:
        printf("consulta por disciplina.\n");
        imprimeD(listaDis);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Add disciplina a aluno\n6. Sair\n");
        //consulta por disciplina
      break;
      case 5:
        printf("Add disciplinas a aluno.\n");
        printf("Digite o nome completo ou numero do aluno a ser consultado: ");
        char aluno[100];
        fgets(aluno,sizeof(aluno),stdin);
        aluno[strcspn(aluno, "\n")] = '\0'; // substitui \n por \0
        discEmAl(aluno);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Add disciplina a aluno\n6. Sair\n");
      break;  
      case 6:
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  char codigo[7];
  char nome[100];
  char cpf[15];
  struct aluno* prox;
} aluno;

typedef struct {
  char periodo[9];
  char codAl[7];
  char codDis[6];
  struct periodo* prox;
} periodo;

typedef struct {
  char codigo[6];
  char nome[50];
  char professor[100];
  int creditos;
  struct disciplina* prox;
} disciplina;


void insereAluno (char cod[7], char cpf[15], char nome[100], aluno *p){
  aluno *nova;
  nova = malloc (sizeof (aluno));
  strcpy(nova->codigo, cod);
  strcpy(nova->cpf, cpf);
  strcpy(nova->nome, nome);
  nova->prox = p->prox;
  p->prox = (struct aluno*)nova;
}

void insereDisciplina (char cod[6], char nome[50], char prof[100], int cred, disciplina *p){
  disciplina *nova;
  nova = malloc (sizeof (disciplina));
  strcpy(nova->codigo, cod);
  strcpy(nova->nome, nome);
  strcpy(nova->professor, prof);
  nova->creditos = cred;
  nova->prox = p->prox;
  p->prox = (struct disciplina*)nova;
}

void inserePeriodo (char codAl[7], char codDis[6], char per[9], periodo *p){
  periodo *nova;
  nova = malloc (sizeof (periodo));
  strcpy(nova->codAl, codAl);
  strcpy(nova->codDis, codDis);
  strcpy(nova->periodo, per);
  nova->prox = p->prox;
  p->prox = (struct periodo*)nova;
}

aluno* buscaAl (char str[100], aluno *le){
  if (le == NULL)  return NULL;
  if (strcmp(le->nome, str)==0 || strcmp(le->codigo, str)==0)  return le;
  return buscaAl (str, (aluno *)le->prox);
}

disciplina* buscaDis (char str[100], disciplina *le){
  if (le == NULL)  return NULL;
  if (strcmp(le->nome, str)==0 || strcmp(le->professor, str)==0 || strcmp(le->codigo, str)==0)  return le;
  return buscaDis (str, (disciplina *)le->prox);
}

periodo* buscaPer (char str[10], periodo* le){
  if (le == NULL)  return NULL;
  if (strcmp(le->periodo, str)==0 || strcmp(le->codAl, str)==0 || strcmp(le->codDis, str)==0)  return le;
  return buscaPer (str, (periodo *)le->prox);
}

void imprimeA (aluno *le) {
   aluno *p;
   for (p = (aluno *)le->prox; p != NULL; p = (aluno *)p->prox)
      printf ("Nome: %s\tCodigo: %s\n", p->nome, p->codigo);
}

void imprimeD (disciplina *le) {
   disciplina *p;
   for (p = (disciplina *)le->prox; p != NULL; p = (disciplina *)p->prox)
      printf ("Disciplina: %s\tCodigo: %s\tProfessor: %s\t Creditos: %d\n", p->nome, p->codigo, p->professor, p->creditos);
}

void imprimeP (periodo *le) {
   periodo *p;
   for (p = (periodo *)le->prox; p != NULL; p = (periodo *)p->prox)
      printf ("Periodo: %s\tCodigoDis: %s\tCodigoAl: %s\n", p->periodo, p->codDis, p->codAl);
}

void removeAluno(aluno** head_ref, char str[100]) {
  aluno* temp = *head_ref, *prev;
   if (temp != NULL && (strcmp(temp->codigo, str)==0 || strcmp(temp->nome, str)==0)) {
      *head_ref = (aluno *)temp->prox;
      free(temp);
      printf("Aluno excluido com sucesso.\n");
      return;
   }

   while (temp != NULL && (strcmp(temp->codigo, str)!=0 && strcmp(temp->nome, str)!=0)) {
      prev = temp;
      temp = (aluno *)temp->prox;
   }

   if (temp == NULL) {
      return;
   }
  prev->prox = temp->prox;
  free(temp);
  printf("Aluno excluido com sucesso.\n");
  return;
}

void removeDisc(disciplina** head_ref, char str[100]) {
  disciplina* temp = *head_ref, *prev;
   if (temp != NULL && (strcmp(temp->codigo, str)==0 || strcmp(temp->nome, str)==0 || strcmp(temp->professor, str)==0)) {
      *head_ref = (disciplina *)temp->prox;
      free(temp);
      return;
   }

   while (temp != NULL && (strcmp(temp->codigo, str)!=0 && strcmp(temp->nome, str)!=0 && strcmp(temp->professor, str)!=0)) {
      prev = temp;
      temp = (disciplina *)temp->prox;
   }

   if (temp == NULL) {
      return;
   }

  prev->prox = temp->prox;
  free(temp);
  printf("Disciplina excluida com sucesso.\n");
  return;
}

void removePer(periodo** head_ref, char str[10]){
  periodo* temp = *head_ref, *prev;
  if (temp != NULL && (strcmp(temp->codAl, str)==0 || strcmp(temp->codDis, str)==0 || strcmp(temp->periodo, str)==0)) {
      *head_ref = (periodo *)temp->prox;
      free(temp);
      return;
   }

   while (temp != NULL && (strcmp(temp->codAl, str)!=0 && strcmp(temp->codDis, str)!=0 && strcmp(temp->periodo, str)!=0)) {
      prev = temp;
      temp = (periodo *)temp->prox;
   }

   if (temp == NULL) {
      return;
   }

  prev->prox = temp->prox;
  free(temp);
  return;
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
  printf("Digite o nome do aluno: ");
  fgets(a->nome,sizeof(a->nome),stdin);
  a->nome[strcspn(a->nome, "\n")] = '\0'; // substitui \n por \0
  for(unsigned int i=0; i<strlen(a->nome); i++){
    a->nome[i] = tolower(a->nome[i]);
  }

  printf("Digite o codigo do aluno: ");
  fgets(a->codigo,sizeof(a->codigo),stdin);
  a->codigo[strcspn(a->codigo, "\n")] = '\0';

  printf("Digite o CPF do aluno: ");
  fgets(a->cpf,sizeof(a->cpf),stdin);
  a->cpf[strcspn(a->cpf, "\n")] = '\0'; // substitui \n por \0

  insereAluno(a->codigo, a->cpf, a->nome, a);
 
  printf("\nNovo aluno adicionado ao sistema.\n");

  return;
}

void cadastroDisciplina(disciplina* ld){
  printf("Digite o nome da disciplina: ");
  fgets(ld->nome,sizeof(ld->nome),stdin);
  ld->nome[strcspn(ld->nome, "\n")] = '\0'; // substitui \n por \0
  for(unsigned int i=0; i<strlen(ld->nome); i++){
    ld->nome[i] = tolower(ld->nome[i]);
  }

  printf("Digite o codigo da disciplina: ");
  fgets(ld->codigo,sizeof(ld->codigo),stdin);
  ld->codigo[strcspn(ld->codigo, "\n")] = '\0';

  printf("Digite o nome do professor: ");
  fgets(ld->professor,sizeof(ld->professor),stdin);
  ld->professor[strcspn(ld->professor, "\n")] = '\0'; // substitui \n por \0

  printf("Digite o numero de creditos da disciplina: ");
  scanf("%d", &ld->creditos);
  fflush(stdin);

  insereDisciplina(ld->codigo, ld->nome, ld->professor, ld->creditos, ld);

  printf("\nNova disciplina adicionada ao sistema.\n");

  return;
}

void matricula(disciplina* ld, aluno* la, periodo* lp){
  disciplina* dis;
  aluno* al;
  char str[100];

  while(1){ 
    printf("A qual disciplina deseja matricular o aluno?\n");
    imprimeD(ld); 
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")] = '\0';
    for(unsigned int i=0; i<strlen(str); i++){
      str[i] = tolower(str[i]);
    }
    dis = buscaDis(str, ld);
    if(dis == NULL){
      printf("Opção invalida. Tente novamente.\n");
    }else{
      break;
    }
  }
  while(1){
    printf("Qual aluno deseja matricular?\n");
    imprimeA(la);
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")] = '\0';
    for(unsigned int i=0; i<strlen(str); i++){
      str[i] = tolower(str[i]);
    }
    al = buscaAl(str, la);
    if(al == NULL){
      printf("Opção invalida. Tente novamente.\n");
    }else{
      break;
    }
  }
  printf("A qual periodo deseja matricular o aluno? (formato AAAA.S)\n");
  fgets(str,sizeof(str),stdin);
  str[strcspn(str, "\n")] = '\0';
  for(unsigned int i=0; i<strlen(str); i++){
    str[i] = tolower(str[i]);
  }
  inserePeriodo(al->codigo, dis->codigo, str, lp);
  printf("\nAluno %s matriculado na disciplina %s no periodo %s.\n", al->nome, dis->nome, str);
  return;
}

void pullStudents(){
  
}

int main(){
  int menu;
  char str[100];
  disciplina *listaDis;
  listaDis = (disciplina*)malloc(sizeof(disciplina));
  listaDis->prox = NULL;

  aluno *listaAl;
  listaAl = (aluno*)malloc(sizeof(aluno));
  listaAl->prox = NULL;

  periodo *listaPer;
  listaPer = (periodo*)malloc(sizeof(periodo));
  listaPer->prox = NULL;

  printf("MENU\n");
  printf("1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
  while(1){  
    scanf("%d", &menu);
    fflush(stdin);
    switch (menu){
      case 1:
        printf("Cadastro aluno.\n");
        cadastroAluno(listaAl);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");

      break;
      case 2:
        printf("Cadastro da disciplina\n");
        cadastroDisciplina(listaDis);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
        //cadastro da disciplina
      break;

      case 3:
        printf("Consulta por aluno.\n");
        imprimeA(listaAl);
        // printf("Digite o nome completo a ser consultado: ");
        // char name[100];
        // fgets(name,sizeof(name),stdin);
        // name[strcspn(name, "\n")] = '\0'; // substitui \n por \0
        // consultaAluno(name);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
        //consulta por aluno
      break;
      case 4:
        printf("consulta por disciplina.\n");
        imprimeD(listaDis);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
        //consulta por disciplina
      break;
      case 5:
        printf("Matricular aluno em disciplina.\n");
        matricula(listaDis, listaAl, listaPer);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
      break;  
      case 6:
        printf("Exibir lista de periodos.\n");
        imprimeP(listaPer);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
      break;
      case 7:
        printf("Excluir aluno.\n");
        printf("Qual aluno deseja deletar?\n");
        imprimeA(listaAl);
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")] = '\0';
        for(unsigned int i=0; i<strlen(str); i++){
          str[i] = tolower(str[i]);
        }
        aluno* codeAl = buscaAl(str, listaAl);
        removeAluno(&listaAl, str);
        //ver se funciona
        while(listaPer){
          removePer(&listaPer, codeAl->codigo);
          listaPer=(periodo *)buscaPer(codeAl->codigo, listaPer)->prox;
        }
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
      break;
      case 8:
        printf("Excluir disciplina.\n");
        printf("Qual disciplina deseja deletar?\n");
        imprimeD(listaDis);
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")] = '\0';
        for(unsigned int i=0; i<strlen(str); i++){
          str[i] = tolower(str[i]);
        }
        disciplina* codeDis = buscaDis(str, listaDis);
        removeDisc(&listaDis, str);
        //ver se funciona
        removePer(&listaPer, codeDis->codigo);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
      break;
      case 9:
        printf("Deletar um periodo do sistema.\n");
        printf("Qual periodo deseja deletar?\n");
        imprimeP(listaPer);
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")] = '\0';
        for(unsigned int i=0; i<strlen(str); i++){
          str[i] = tolower(str[i]);
        }
        //corrigir aqui tbm
        removePer(&listaPer, str);
        printf("Periodo removido.\n");
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir lista de periodos\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Deletar um periodo do sistema\n0. Sair\n");
      break;
      case 0:
        printf("Tchau\n");
        return 0;
      default:
        printf("Opção inválida! Tente novamente.\n");
      break;
    }
  }
}
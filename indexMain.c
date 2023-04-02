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
  char creditos[5];
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

void insereDisciplina (char cod[6], char nome[50], char prof[100], char cred[5], disciplina *p){
  disciplina *nova;
  nova = malloc (sizeof (disciplina));
  strcpy(nova->codigo, cod);
  strcpy(nova->nome, nome);
  strcpy(nova->professor, prof);
  strcpy(nova->creditos, cred);
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
      printf ("Disciplina: %s\tCodigo: %s\tProfessor: %s\t Creditos: %s\n", p->nome, p->codigo, p->professor, p->creditos);
}

void imprimeP (periodo *le) {
   periodo *p;
   for (p = (periodo *)le->prox; p != NULL; p = (periodo *)p->prox)
      printf ("Periodo: %s\tCodigoDis: %s\tCodigoAl: %s\n", p->periodo, p->codDis, p->codAl);
}

void removePer(periodo* head_ref, char str[10]){
  periodo* temp = head_ref, *prev = NULL;
  while(temp != NULL){
    if (strcmp(temp->codAl, str) == 0 || strcmp(temp->codDis, str) == 0 || strcmp(temp->periodo, str) == 0) {
      if (prev == NULL) {
        head_ref = (periodo *)temp->prox;
      } else {
        prev->prox = temp->prox;
      }
      printf("Periodo %s com codAl %s e codDis %s apagado\n", temp->periodo, temp->codAl, temp->codDis);
      free(temp);
      removePer(head_ref, str);
      temp = head_ref;
    } else {
      prev = temp;
      temp = (periodo *)temp->prox;
    }
  }
  return;
}

void removeAluno(aluno* head_ref, char str[100], periodo* lp) {
  aluno* temp = head_ref, *prev;
   if (temp != NULL && (strcmp(temp->codigo, str)==0 || strcmp(temp->nome, str)==0)) {
      head_ref = (aluno *)temp->prox;
      removePer(lp, temp->codigo);
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
  removePer(lp, temp->codigo);
  free(temp);
  printf("Aluno excluido com sucesso.\n");
  return;
}

void removeDisc(disciplina* head_ref, char str[100], periodo* lp) {
  disciplina* temp = head_ref, *prev;
   if (temp != NULL && (strcmp(temp->codigo, str)==0 || strcmp(temp->nome, str)==0 || strcmp(temp->professor, str)==0)) {
      head_ref = (disciplina *)temp->prox;
      removePer(lp, temp->codigo);
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
  removePer(lp, temp->codigo);
  free(temp);
  printf("Disciplina excluida com sucesso.\n");
  return;
}

void cadastroAluno(aluno* a){
  char nome[100], cpf[15], codigo[7];
  printf("Digite o nome do aluno: ");
  fgets(nome,sizeof(nome),stdin);
  nome[strcspn(nome, "\n")] = '\0'; // substitui \n por \0
  for(unsigned int i=0; i<strlen(nome); i++){
    nome[i] = tolower(nome[i]);
  }

  printf("Digite o codigo do aluno: ");
  fgets(codigo,sizeof(codigo),stdin);
  codigo[strcspn(codigo, "\n")] = '\0';

  printf("Digite o CPF do aluno: ");
  fgets(cpf,sizeof(cpf),stdin);
  cpf[strcspn(cpf, "\n")] = '\0'; // substitui \n por \0

  insereAluno(codigo, cpf, nome, a);
 
  printf("\nNovo aluno adicionado ao sistema.\n");

  return;
}

void cadastroDisciplina(disciplina* ld){
  char nome[50], professor[100], codigo[6], creditos[5];
  printf("Digite o nome da disciplina: ");
  fgets(nome,sizeof(nome),stdin);
  nome[strcspn(nome, "\n")] = '\0'; // substitui \n por \0
  for(unsigned int i=0; i<strlen(nome); i++){
    nome[i] = tolower(nome[i]);
  }

  printf("Digite o codigo da disciplina: ");
  fgets(codigo,sizeof(codigo),stdin);
  codigo[strcspn(codigo, "\n")] = '\0';

  printf("Digite o nome do professor: ");
  fgets(professor,sizeof(professor),stdin);
  professor[strcspn(professor, "\n")] = '\0'; // substitui \n por \0

  printf("Digite o numero de creditos da disciplina: ");
  fgets(creditos,sizeof(creditos),stdin);
  creditos[strcspn(creditos, "\n")] = '\0';

  insereDisciplina(codigo, nome, professor, creditos, ld);

  printf("\nNova disciplina adicionada ao sistema.\n");

  return;
}

void matricula(disciplina* ld, aluno* la, periodo* lp){
  disciplina* dis;
  aluno* al;
  char str[100];
  if(ld->prox == NULL){
    printf("Nao ha disciplinas cadastradas\n");
    return;
  }else if(la->prox == NULL){
    printf("Nao ha alunos cadastrados\n");
    return;
  }
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

void pullStudents(aluno* a){
  char nome[100], codigo[7], cpf[15];
  FILE* fp = fopen("../students.csv", "r");

  if (!fp){
    printf("Can't open file\n");
  }else{
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
          strcpy(nome, value);
        }

        // Column 2
        if (column == 1) {
          strcpy(codigo, value);
        }

        // Column 3
        if (column == 2) {
          value[strcspn(value, "\n")] = '\0'; // substitui \n por \0
          strcpy(cpf, value);
        }

        value = strtok(NULL, ",");
        column++;
      }
      insereAluno(codigo, cpf, nome, a);
    }
    fclose(fp); 
  }
  return;
}

void pullSubject(disciplina* d){
  char nome[50], codigo[6], professor[100], creditos[5];
  FILE* fp = fopen("../disciplinas.csv", "r");

  if (!fp){
    printf("Can't open file\n");
  }else{
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
          strcpy(nome, value);
        }

        // Column 2
        if (column == 1) {
          strcpy(codigo, value);
        }

        // Column 3
        if (column == 2) {
          strcpy(professor, value);
        }

        if (column == 3) {
          value[strcspn(value, "\n")] = '\0'; // substitui \n por \0
          strcpy(creditos, value);
        }

        value = strtok(NULL, ",");
        column++;
      }
      insereDisciplina(codigo, nome, professor, creditos, d);

    }
    fclose(fp); 
  }
  return;
}

void pullTerm(periodo* p){
  char per[9], codAl[7], codDis[6];  
  FILE* fp = fopen("../periodos.csv", "r");

  if (!fp){
    printf("Can't open file\n");
  }else{
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
          strcpy(per, value);
        }

        // Column 2
        if (column == 1) {
          strcpy(codAl, value);
        }

        // Column 3
        if (column == 2) {
          value[strcspn(value, "\n")] = '\0'; // substitui \n por \0
          strcpy(codDis, value);
        }

        value = strtok(NULL, ",");
        column++;
      }
      inserePeriodo(codAl, codDis, per, p);
    }
    fclose(fp); 
  }
  return;
}

void consultaAl(aluno* la, periodo* lp, disciplina* ld) {
  //recebe info do aluno e diz quais as marérias em quais períodos ele cursa/cursou
  aluno* al;
  disciplina* d;
  periodo* per = lp;
  int cont = 0;
  if(la->prox == NULL){
    printf("Nenhum aluno cadastrado\n");
    return;
  }
  printf("Qual aluno sera consultado?\n");
  imprimeA(la);
  char str[100];
  fgets(str,sizeof(str),stdin);
  str[strcspn(str, "\n")] = '\0'; 
  al = buscaAl(str, la);
  if(al ==  NULL){
    printf("Aluno não cadastrado.\n");
    return;
  }
  char term[9];
  printf("Qual periodo?\n");
  fgets(term,sizeof(term),stdin);
  term[strcspn(term, "\n")] = '\0'; 

  while(per != NULL){
    per = buscaPer(al->codigo, per);
    if (per != NULL){
      d = buscaDis(per->codDis, ld);
      if(d != NULL){
        if(strcmp(per->periodo,term)==0){
          cont++;
          printf("%s\n", d->nome);
        }
        else{
          cont++;
          printf("Nao ha disciplinas cadastradas para o aluno no periodo especificado.\n");
        }
      }
      per = (periodo *)per->prox;
    }
    if(cont==0){
    printf("Nenhum aluno matriculado nessa disciplina\n");
  }
  }

  return;
}

void consultaDis(aluno* la, periodo* lp, disciplina* ld){
  //recebe info da disc e diz quais os alunos em quais períodos foram matriculados
  aluno* al;
  disciplina* d;
  periodo* per = lp;
  int cont = 0;
  if(ld->prox == NULL){
    printf("Nenhuma disciplina cadastrada\n");
    return;
  }
  printf("Qual disciplina será consultada?\n");
  imprimeD(ld);
  char str[100];
  fgets(str,sizeof(str),stdin);
  str[strcspn(str, "\n")] = '\0'; 
  d = buscaDis(str, ld); 
  if(d ==  NULL){
    printf("Disciplina não cadastrada.\n");
    return;
  }
  char term[9];
  printf("Qual periodo?\n");
  fgets(term,sizeof(term),stdin);
  term[strcspn(term, "\n")] = '\0'; 
  while(per != NULL){
    per = buscaPer(d->codigo, per);
    if (per != NULL){
      al = buscaAl(per->codAl, la);
      if(al != NULL){
        if(strcmp(per->periodo,term)==0){
          cont++;
          printf("%s\n", al->nome);
        }
        else{
          cont++;
          printf("Nao ha disciplinas cadastradas para o aluno no periodo especificado.\n");
        }
      }
      per = (periodo *)per->prox;
    }
  }
  if(cont==0){
    printf("Nenhum aluno matriculado nessa disciplina\n");
  }
  return;
}

void pushStudents(aluno* la){
  FILE* fp = fopen("../students.csv", "w+");
  if (!fp) {
    printf("Can't open file\n");
    return;
  }
  aluno *p;
  for (p = (aluno *)la->prox; p != NULL; p = (aluno *)p->prox){
    fprintf(fp, "%s,%s,%s\n", p->nome, p->codigo, p->cpf);
  }
}

void pushSubject(disciplina* ld){
  FILE* fp = fopen("../disciplinas.csv", "w+");
  if (!fp) {
    printf("Can't open file\n");
    return;
  }
  disciplina *p;
  for (p = (disciplina *)ld->prox; p != NULL; p = (disciplina *)p->prox){
    fprintf(fp, "%s,%s,%s,%s\n", p->nome, p->codigo, p->professor, p->creditos);
  }
}

void pushTerm(periodo* lp){
  FILE* fp = fopen("../periodos.csv", "w+");
  if (!fp) {
    printf("Can't open file\n");
    return;
  }
  periodo *p;
  for (p = (periodo *)lp->prox; p != NULL; p = (periodo *)p->prox){
    fprintf(fp, "%s,%s,%s\n", p->periodo, p->codAl, p->codDis);
  }
}

void freeAl(aluno* la){
  aluno* atual, *proxNode;
  if(la->prox != NULL){
    atual = (aluno*)la->prox;
    while(atual != NULL){
      proxNode = (aluno*)atual->prox;
      free(atual);
      atual = proxNode;
    }
  }
}
void freeDis(disciplina* ld){
  disciplina* atual, *proxNode;
  if(ld->prox != NULL){
    atual = (disciplina*)ld->prox;
    while(atual != NULL){
      proxNode = (disciplina*)atual->prox;
      free(atual);
      atual = proxNode;
    }
  }
}
void freePer(periodo* lp){
  periodo* atual, *proxNode;
  if(lp->prox != NULL){
    atual = (periodo*)lp->prox;
    while(atual != NULL){
      proxNode = (periodo*)atual->prox;
      free(atual);
      atual = proxNode;
    }
  }
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

  pullStudents(listaAl);
  pullSubject(listaDis);
  pullTerm(listaPer);

  printf("MENU\n");
  printf("1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
  while(1){  
    scanf("%d", &menu);
    fflush(stdin);
    switch (menu){
      case 1:
        printf("Cadastro aluno.\n");
        cadastroAluno(listaAl);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
        
      break;
      case 2:
        printf("Cadastro da disciplina\n");
        cadastroDisciplina(listaDis);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
        //cadastro da disciplina
      break;
      case 3:
        printf("Matricular aluno em disciplina.\n");
        matricula(listaDis, listaAl, listaPer);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
      break;
      case 4:
        printf("Consulta por aluno.\n");
        consultaAl(listaAl, listaPer, listaDis);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
        //consulta por aluno
      break;
      case 5:
        printf("consulta por disciplina.\n");
        consultaDis(listaAl, listaPer, listaDis);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
        //consulta por disciplina
      break; 
      case 6:
        printf("Exibir listas.\n");
        int op;
        printf("1. Alunos\n2. Disciplinas\n3. Periodos\n");
        scanf("%d",&op);

        switch (op)
        {
        case 1:
          if(listaAl->prox != NULL){
            imprimeA(listaAl);
            printf("\n");
          }
          else{
            printf("Lista vazia!\n");
          }
        break;
        case 2:
          if(listaDis->prox != NULL){
            imprimeD(listaDis);
            printf("\n");
          }
          else{
            printf("Lista vazia!\n");
          }
        break;
        case 3:
          if(listaPer->prox != NULL){
            imprimeP(listaPer);
            printf("\n");
          }
          else{
            printf("Lista vazia!\n");
          }
        break;
        
        default:
          printf("Opcao invalida, tente novamente!");
        break;
        }
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
      break;
      case 7:
        printf("Excluir aluno.\n");
        if(listaAl->prox == NULL){
          printf("Nenhum aluno cadastrado\n");
        } else {
          printf("Qual aluno deseja excluir?\n");
          imprimeA(listaAl);
          fgets(str,sizeof(str),stdin);
          str[strcspn(str, "\n")] = '\0';
          for(unsigned int i=0; i<strlen(str); i++){
            str[i] = tolower(str[i]);
          }
          aluno* codeAl = buscaAl(str, listaAl);
          if(codeAl != NULL) {
            removeAluno(listaAl, str, listaPer);
          }else{
            printf("Aluno sem cadastro!");
          }
        }
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
      break;
      case 8:
        printf("Excluir disciplina.\n");
        if(listaDis->prox == NULL){
          printf("Nenhuma disciplina cadastrada\n");
        } else {
          printf("Qual disciplina deseja excluir?\n");
          imprimeD(listaDis);
          fgets(str,sizeof(str),stdin);
          str[strcspn(str, "\n")] = '\0';
          for(unsigned int i=0; i<strlen(str); i++){
            str[i] = tolower(str[i]);
          }
          disciplina* codeDis = buscaDis(str, listaDis);
          if(codeDis != NULL) {
            removeDisc(listaDis, str, listaPer);
          }else{
            printf("Disciplina sem cadastro!");
          }
        }
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5. Matricular aluno em disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
      break;
      case 9:
        printf("Excluir um periodo do sistema.\n");
        printf("Qual periodo deseja excluir?\n");
        imprimeP(listaPer);
        fgets(str,sizeof(str),stdin);
        str[strcspn(str, "\n")] = '\0';
        for(unsigned int i=0; i<strlen(str); i++){
          str[i] = tolower(str[i]);
        }
        removePer(listaPer, str);
        if(buscaPer(str,listaPer)!=NULL){
          printf("Periodo removido.\n");
        }
        else{
          printf("Nao ha alunos nem disciplinas cadastrados nesse periodo!");
        }
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Matricular aluno em disciplina\n4. Consulta por Aluno\n5. Consulta por Disciplina\n6. Exibir listas\n7. Excluir aluno do sistema\n8. Excluir disciplina do sistema\n9. Excluir um periodo do sistema\n0. Salvar e encerrar.\n");
      break;
      case 0:
        pushStudents(listaAl);
        pushSubject(listaDis);
        pushTerm(listaPer);
        freeAl(listaAl);
        freeDis(listaDis);
        freePer(listaPer);
        printf("Secao encerrada\n");
        return 0;
      default:
        printf("Opcao invalida! Tente novamente.\n");
      break;
    }
  }
}
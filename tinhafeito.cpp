case 5:
        printf("Digite o nome completo do aluno: ");
        char aluno[50];
        fgets(aluno,sizeof(aluno),stdin);
        aluno[strcspn(aluno, "\n")] = '\0'; // substitui \n por \0
        disciplinaAluno(aluno);
        printf("\n1. Cadastro do Aluno \n2. Cadastro da Disciplina\n3. Consulta por Aluno\n4. Consulta por Disciplina\n5.Disciplinas por período\n6.Sair\n");

void disciplinaAluno(char nome[50]){
  FILE* fp = fopen("../students.csv", "a+");
  if (!fp) {
    printf("Can't open file\n");
    return;
  }

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
          printf("passou aq");
          fprintf(fp, ", %s{", per);
          int oc=0;
          //materias do periodo
          do{
            printf("Qual a disciplina cursada?(digite 0 para sair)\n");
            fgets(str,sizeof(str),stdin);
            str[strcspn(str, "\n")] = '\0';
        
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
  
      fprintf(fp, "\n");
 
    } 
    
  }
  fclose(fp);
  
}


while(fgets(buffer,1024,fp)){
    fprintf("%s,%d,%s,%d" )
}